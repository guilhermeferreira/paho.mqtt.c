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

#include "StackTrace.h"

#include "unity.h"

void test_StackTrace_entry(void)
{
	TEST_ASSERT_EQUAL(1, 1);
}

void test_StackTrace_exit(void)
{
	TEST_ASSERT_EQUAL(1, 1);
}

void test_StackTrace_printStack(void)
{
	TEST_ASSERT_EQUAL(1, 1);
}

void test_StackTrace_get(void)
{
	TEST_ASSERT_EQUAL(1, 1);
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_StackTrace_entry);
	RUN_TEST(test_StackTrace_exit);
	RUN_TEST(test_StackTrace_printStack);
	RUN_TEST(test_StackTrace_get);

	return UNITY_END();
}
