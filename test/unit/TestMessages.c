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

#include "Messages.h"

#include "unity.h"
#include "Log.h"

void test_Messages_get_BeforeFirstIndex(void)
{
	TEST_ASSERT_EQUAL(NULL, Messages_get(-1, TRACE_PROTOCOL));

	TEST_ASSERT_EQUAL(NULL, Messages_get(-1, TRACE_MAXIMUM));
	TEST_ASSERT_EQUAL(NULL, Messages_get(-1, TRACE_MEDIUM));
	TEST_ASSERT_EQUAL(NULL, Messages_get(-1, TRACE_MINIMUM));
	TEST_ASSERT_EQUAL(NULL, Messages_get(-1, LOG_ERROR));
	TEST_ASSERT_EQUAL(NULL, Messages_get(-1, LOG_SEVERE));
	TEST_ASSERT_EQUAL(NULL, Messages_get(-1, LOG_FATAL));
}

void test_Messages_get_FirstIndex(void)
{
	const char *protocol_msg = "%d %s -> CONNECT cleansession: %d (%d)";

	TEST_ASSERT_EQUAL_STRING(protocol_msg, Messages_get(0, TRACE_PROTOCOL));

	const char *trace_msg = "Failed to remove client from bstate->clients";

	TEST_ASSERT_EQUAL_STRING(trace_msg, Messages_get(0, TRACE_MAXIMUM));
	TEST_ASSERT_EQUAL_STRING(trace_msg, Messages_get(0, TRACE_MEDIUM));
	TEST_ASSERT_EQUAL_STRING(trace_msg, Messages_get(0, TRACE_MINIMUM));
	TEST_ASSERT_EQUAL_STRING(trace_msg, Messages_get(0, LOG_ERROR));
	TEST_ASSERT_EQUAL_STRING(trace_msg, Messages_get(0, LOG_SEVERE));
	TEST_ASSERT_EQUAL_STRING(trace_msg, Messages_get(0, LOG_FATAL));
}

void test_Messages_get_LastIndex(void)
{
	const char *protocol_msg = "Socket error for client identifier %s, socket %d, peer address %s; ending connection";

	TEST_ASSERT_EQUAL_STRING(protocol_msg, Messages_get(29, TRACE_PROTOCOL));

	const char *trace_msg = "Storing unsent QoS 0 message";

	TEST_ASSERT_EQUAL_STRING(trace_msg, Messages_get(12, TRACE_MAXIMUM));
	TEST_ASSERT_EQUAL_STRING(trace_msg, Messages_get(12, TRACE_MEDIUM));
	TEST_ASSERT_EQUAL_STRING(trace_msg, Messages_get(12, TRACE_MINIMUM));
	TEST_ASSERT_EQUAL_STRING(trace_msg, Messages_get(12, LOG_ERROR));
	TEST_ASSERT_EQUAL_STRING(trace_msg, Messages_get(12, LOG_SEVERE));
	TEST_ASSERT_EQUAL_STRING(trace_msg, Messages_get(12, LOG_FATAL));
}

void test_Messages_get_AfterLastIndex(void)
{
	TEST_ASSERT_EQUAL(NULL, Messages_get(30, TRACE_PROTOCOL));

	TEST_ASSERT_EQUAL(NULL, Messages_get(13, TRACE_MAXIMUM));
	TEST_ASSERT_EQUAL(NULL, Messages_get(13, TRACE_MEDIUM));
	TEST_ASSERT_EQUAL(NULL, Messages_get(13, TRACE_MINIMUM));
	TEST_ASSERT_EQUAL(NULL, Messages_get(13, LOG_ERROR));
	TEST_ASSERT_EQUAL(NULL, Messages_get(13, LOG_SEVERE));
	TEST_ASSERT_EQUAL(NULL, Messages_get(13, LOG_FATAL));
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_Messages_get_BeforeFirstIndex);
	RUN_TEST(test_Messages_get_FirstIndex);
	RUN_TEST(test_Messages_get_LastIndex);
	RUN_TEST(test_Messages_get_AfterLastIndex);

	return UNITY_END();
}
