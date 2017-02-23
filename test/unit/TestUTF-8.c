/*******************************************************************************
 * Copyright (c) 2017 Guilherme M. Ferreira <guilherm.maciel.ferreira@gmail.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Guilherme M. Ferreira - initial implementation
 *******************************************************************************/

#include "utf-8.h"

#include "unity.h"

typedef struct
{
	int len;
	char data[20];
} string;

void test_UTF8_validate_ValidString(void)
{
	string utf8_valid_strings[] =
	{
		{0, ""},
		{3, "hjk" },
		{7, {0x41, 0xE2, 0x89, 0xA2, 0xCE, 0x91, 0x2E} },
		{3, {'f', 0xC9, 0xB1 } },
		{9, {0xED, 0x95, 0x9C, 0xEA, 0xB5, 0xAD, 0xEC, 0x96, 0xB4} },
		{9, {0xE6, 0x97, 0xA5, 0xE6, 0x9C, 0xAC, 0xE8, 0xAA, 0x9E} },
		{4, {0x2F, 0x2E, 0x2E, 0x2F} },
		{7, {0xEF, 0xBB, 0xBF, 0xF0, 0xA3, 0x8E, 0xB4} },
	};

	TEST_ASSERT_TRUE(UTF8_validate(utf8_valid_strings[0].len, utf8_valid_strings[0].data));
	TEST_ASSERT_TRUE(UTF8_validate(utf8_valid_strings[1].len, utf8_valid_strings[1].data));
	TEST_ASSERT_TRUE(UTF8_validate(utf8_valid_strings[2].len, utf8_valid_strings[2].data));
	TEST_ASSERT_TRUE(UTF8_validate(utf8_valid_strings[3].len, utf8_valid_strings[3].data));
	TEST_ASSERT_TRUE(UTF8_validate(utf8_valid_strings[4].len, utf8_valid_strings[4].data));
	TEST_ASSERT_TRUE(UTF8_validate(utf8_valid_strings[5].len, utf8_valid_strings[5].data));
}

void test_UTF8_validate_InvalidString(void)
{
	string utf8_invalid_strings[] =
	{
		{2, {0xC0, 0x80} },
		{5, {0x2F, 0xC0, 0xAE, 0x2E, 0x2F} },
		{6, {0xED, 0xA1, 0x8C, 0xED, 0xBE, 0xB4} },
		{1, {0xF4} },
	};

	TEST_ASSERT_FALSE(UTF8_validate(utf8_invalid_strings[0].len, utf8_invalid_strings[0].data));
	TEST_ASSERT_FALSE(UTF8_validate(utf8_invalid_strings[1].len, utf8_invalid_strings[1].data));
	TEST_ASSERT_FALSE(UTF8_validate(utf8_invalid_strings[2].len, utf8_invalid_strings[2].data));
	TEST_ASSERT_FALSE(UTF8_validate(utf8_invalid_strings[3].len, utf8_invalid_strings[3].data));
}

void test_UTF8_validateString_ValidString(void)
{
	// TODO WHY DECLARING const char* utf8_invalid_strings[] CAUSES A SEGFAULT IN strlen()?
	const char utf8_valid_strings[][10] = // TODO USAR DIFERENTES STRINGS, PARA NAO FICAR REPETITIVO
	{
		"hjk",
		{0x41, 0xE2, 0x89, 0xA2, 0xCE, 0x91, 0x2E, '\0'},
		{'f', 0xC9, 0xB1, '\0'},
		{0xED, 0x95, 0x9C, 0xEA, 0xB5, 0xAD, 0xEC, 0x96, 0xB4, '\0'},
		{0xE6, 0x97, 0xA5, 0xE6, 0x9C, 0xAC, 0xE8, 0xAA, 0x9E, '\0'},
		{0x2F, 0x2E, 0x2E, 0x2F, '\0'},
		{0xEF, 0xBB, 0xBF, 0xF0, 0xA3, 0x8E, 0xB4, '\0'},
	};

	TEST_ASSERT_TRUE(UTF8_validateString(utf8_valid_strings[0]));
	TEST_ASSERT_TRUE(UTF8_validateString(utf8_valid_strings[1]));
	TEST_ASSERT_TRUE(UTF8_validateString(utf8_valid_strings[2]));
	TEST_ASSERT_TRUE(UTF8_validateString(utf8_valid_strings[3]));
	TEST_ASSERT_TRUE(UTF8_validateString(utf8_valid_strings[4]));
	TEST_ASSERT_TRUE(UTF8_validateString(utf8_valid_strings[5]));
}

void test_UTF8_validateString_InvalidString(void)
{
	// TODO WHY DECLARING const char* utf8_invalid_strings[] CAUSES A SEGFAULT IN strlen()?
	const char utf8_invalid_strings[][7] = // TODO USAR DIFERENTES STRINGS INVALIDAS, PARA NAO FICAR REPETITIVO
	{
		{0xC0, 0x80, '\0'},
		{0x2F, 0xC0, 0xAE, 0x2E, 0x2F, '\0'},
		{0xED, 0xA1, 0x8C, 0xED, 0xBE, 0xB4, '\0'},
		{0xF4, '\0'},
	};

	TEST_ASSERT_FALSE(UTF8_validateString(utf8_invalid_strings[0]));
	TEST_ASSERT_FALSE(UTF8_validateString(utf8_invalid_strings[1]));
	TEST_ASSERT_FALSE(UTF8_validateString(utf8_invalid_strings[2]));
	TEST_ASSERT_FALSE(UTF8_validateString(utf8_invalid_strings[3]));
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_UTF8_validate_ValidString);
	RUN_TEST(test_UTF8_validate_InvalidString);
	RUN_TEST(test_UTF8_validateString_ValidString);
	RUN_TEST(test_UTF8_validateString_InvalidString);

	return UNITY_END();
}
