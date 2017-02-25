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

#include "Log.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "unity.h"

//-----------------------------------------------------------------------------
// TODO if other modules use these macros, move to a common file

static const char *received_msg = NULL;

static void UnityLogTraceCallback(
		enum LOG_LEVELS level,
		char *msg)
{
	Log_setTraceCallback(NULL);
	received_msg = msg;
}

// The actual parameter is part of the ellipsis
#define TEST_ASSERT_EQUAL_LOG_MSG_FORMAT(expected, ...) \
	do { \
		const char *expected_msg = (expected); \
		Log_setTraceCallback(UnityLogTraceCallback); \
		Log(LOG_FATAL, 0, __VA_ARGS__); \
		TEST_ASSERT_NOT_NULL(strstr(received_msg, expected_msg)); \
	} while (0)

#define TEST_ASSERT_EQUAL_LOG_MSG_ID(expected, actual) \
	do { \
		const char *expected_msg = (expected); \
		Log_setTraceCallback(UnityLogTraceCallback); \
		Log(LOG_FATAL, (actual), NULL); \
		TEST_ASSERT_NOT_NULL(strstr(received_msg, expected_msg)); \
	} while (0)

//-----------------------------------------------------------------------------

void UnityReadFileLine(
		const char* file_name,
		const int file_line,
		char *line,
		int line_size)
{
	FILE *file = fopen(file_name, "r");

	int line_num;
	for (line_num = 0; line_num <= file_line; line_num++) {
		/* TODO use fseek() to get to the line */
		if (fgets(line, line_size, file) == NULL) {
			/* fail if there aren't enough lines */
			break;
		}
	}
	/* remove trailing newline */
	line[strcspn(line, "\n")] = '\0';

	fclose(file);
}

static const char *log_file = "/tmp/log.txt";
#define MAX_LINE_LENGTH 512

#define TEST_ASSERT_EQUAL_FILE_LINE(expected, actual) \
	do { \
		char line[MAX_LINE_LENGTH] = { '\0' }; \
		UnityReadFileLine(log_file, (actual), line, sizeof(line)); \
		if ((expected) && (strlen(line) > 0)) { \
			TEST_ASSERT_EQUAL_STRING(expected, line); \
		} \
	} while (0)

//-----------------------------------------------------------------------------

void test_Log_initialize_TraceDestinationEmpty(void)
{
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE"));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_MAX_LINES"));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_LEVEL"));

	TEST_ASSERT_TRUE(Log_initialize(NULL));

	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", 0);
	// TODO TEST_ASSERT_EQUAL_STDOUT("                   Trace Output", 1);
	// TODO TEST_ASSERT_EQUAL_STDOUT("/proc/version: ", 2);
	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", 3);

	Log_terminate();
}

void test_Log_initialize_TraceDestinationOn(void)
{
	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE", "ON", 1));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_MAX_LINES"));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_LEVEL"));

	TEST_ASSERT_TRUE(Log_initialize(NULL));

	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", 0);
	// TODO TEST_ASSERT_EQUAL_STDOUT("                   Trace Output", 1);
	// TODO TEST_ASSERT_EQUAL_STDOUT("/proc/version: ", 2);
	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", 3);

	Log_terminate();
}

void test_Log_initialize_TraceDestinationFile(void)
{
	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE", log_file, 1));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_MAX_LINES"));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_LEVEL"));

	TEST_ASSERT_TRUE(Log_initialize(NULL));

	TEST_ASSERT_EQUAL(0, access(log_file, F_OK)); // File created?

	TEST_ASSERT_EQUAL_FILE_LINE("=========================================================", 0);
	TEST_ASSERT_EQUAL_FILE_LINE("                   Trace Output", 1);
	//TEST_ASSERT_EQUAL_FILE_LINE("/proc/version: ", 2);
	TEST_ASSERT_EQUAL_FILE_LINE("", 3);
	TEST_ASSERT_EQUAL_FILE_LINE("=========================================================", 4);

	Log_terminate();

	TEST_ASSERT_EQUAL(0, access(log_file, F_OK)); // File still exists?
}

void test_Log_initialize_TraceMaxLinesEmpty(void)
{
	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE", log_file, 1));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_LEVEL"));

	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE_MAX_LINES", "", 1));
	TEST_ASSERT_TRUE(Log_initialize(NULL));
	TEST_ASSERT_EQUAL_FILE_LINE("=========================================================", 0);
	TEST_ASSERT_EQUAL_FILE_LINE("                   Trace Output", 1);
	//TEST_ASSERT_EQUAL_FILE_LINE("/proc/version: ", 2);
	TEST_ASSERT_EQUAL_FILE_LINE("", 3);
	TEST_ASSERT_EQUAL_FILE_LINE("=========================================================", 4);
	Log_terminate();
}

void test_Log_initialize_TraceMaxLinesPositive(void)
{
	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE", log_file, 1));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_LEVEL"));

	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE_MAX_LINES", "100", 1));
	TEST_ASSERT_TRUE(Log_initialize(NULL));
	TEST_ASSERT_EQUAL_FILE_LINE("=========================================================", 0);
	TEST_ASSERT_EQUAL_FILE_LINE("                   Trace Output", 1);
	//TEST_ASSERT_EQUAL_FILE_LINE("/proc/version: ", 2);
	TEST_ASSERT_EQUAL_FILE_LINE("", 3);
	TEST_ASSERT_EQUAL_FILE_LINE("=========================================================", 4);
	Log_terminate();
}

void test_Log_initialize_TraceMaxLinesNegative(void)
{
	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE", log_file, 1));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_LEVEL"));

	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE_MAX_LINES", "-80", 1));
	TEST_ASSERT_TRUE(Log_initialize(NULL));
	TEST_ASSERT_EQUAL_FILE_LINE("=========================================================", 0);
	TEST_ASSERT_EQUAL_FILE_LINE("                   Trace Output", 1);
	//TEST_ASSERT_EQUAL_FILE_LINE("/proc/version: ", 2);
	TEST_ASSERT_EQUAL_FILE_LINE("", 3);
	TEST_ASSERT_EQUAL_FILE_LINE("=========================================================", 4);
	Log_terminate();
}

void test_Log_initialize_TraceLevel(void)
{
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE"));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_MAX_LINES"));

	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE_LEVEL", "ERROR", 1));
	TEST_ASSERT_TRUE(Log_initialize(NULL));
	// TODO Log something with higher levels and check if it appears
	// TODO Log something with lower levels and check if it DOESN'T appear
	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", );
	// TODO TEST_ASSERT_EQUAL_STDOUT("                   Trace Output", );
	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", );
	Log_terminate();

	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE_LEVEL", "MAXIMUM", 1));
	TEST_ASSERT_TRUE(Log_initialize(NULL));
	// TODO Log something with higher levels and check if it appears
	// TODO Log something with lower levels and check if it DOESN'T appear
	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", );
	// TODO TEST_ASSERT_EQUAL_STDOUT("                   Trace Output", );
	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", );
	Log_terminate();

	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE_LEVEL", "MEDIUM", 1));
	TEST_ASSERT_TRUE(Log_initialize(NULL));
	// TODO Log something with higher levels and check if it appears
	// TODO Log something with lower levels and check if it DOESN'T appear
	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", );
	// TODO TEST_ASSERT_EQUAL_STDOUT("                   Trace Output", );
	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", );
	Log_terminate();

	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE_LEVEL", "MINIMUM", 1));
	TEST_ASSERT_TRUE(Log_initialize(NULL));
	// TODO Log something with higher levels and check if it appears
	// TODO Log something with lower levels and check if it DOESN'T appear
	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", );
	// TODO TEST_ASSERT_EQUAL_STDOUT("                   Trace Output", );
	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", );
	Log_terminate();

	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE_LEVEL", "PROTOCOL", 1));
	TEST_ASSERT_TRUE(Log_initialize(NULL));
	// TODO Log something with higher levels and check if it appears
	// TODO Log something with lower levels and check if it DOESN'T appear
	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", );
	// TODO TEST_ASSERT_EQUAL_STDOUT("                   Trace Output", );
	// TODO TEST_ASSERT_EQUAL_STDOUT("=========================================================", );
	Log_terminate();
}

void test_Log_initialize_LogNameValue(void)
{
	TEST_ASSERT_EQUAL(0, setenv("MQTT_C_CLIENT_TRACE", log_file, 1));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_MAX_LINES"));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_LEVEL"));

	Log_nameValue libinfo[] = {
		{ "key1", "value1" },
		{ "key2", "value2" },
		{ NULL, NULL }
	};

	TEST_ASSERT_TRUE(Log_initialize(libinfo));

	TEST_ASSERT_EQUAL_FILE_LINE("=========================================================", 0);
	TEST_ASSERT_EQUAL_FILE_LINE("                   Trace Output", 1);
	TEST_ASSERT_EQUAL_FILE_LINE("key1: value1",2);
	TEST_ASSERT_EQUAL_FILE_LINE("key2: value2", 3);
	//TEST_ASSERT_EQUAL_FILE_LINE("/proc/version: ", 4);
	TEST_ASSERT_EQUAL_FILE_LINE("", 5);
	TEST_ASSERT_EQUAL_FILE_LINE("=========================================================", 6);

	Log_terminate();
}

void test_Log_terminate(void)
{
	Log_terminate();
}

void test_Log_NullFormat(void)
{
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE"));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_MAX_LINES"));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_LEVEL"));

	TEST_ASSERT_TRUE(Log_initialize(NULL));

	TEST_ASSERT_EQUAL_LOG_MSG_ID("Failed to remove client from bstate->clients", 0);
	TEST_ASSERT_EQUAL_LOG_MSG_ID("Storing unsent QoS 0 message", 12);

	Log_terminate();
}

void test_Log_WithFormat(void)
{
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE"));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_MAX_LINES"));
	TEST_ASSERT_EQUAL(0, unsetenv("MQTT_C_CLIENT_TRACE_LEVEL"));

	TEST_ASSERT_TRUE(Log_initialize(NULL));

	TEST_ASSERT_EQUAL_LOG_MSG_FORMAT("No extra arguments", "No extra arguments");
	TEST_ASSERT_EQUAL_LOG_MSG_FORMAT("Integer format: 1", "Integer format: %d", 1);
	TEST_ASSERT_EQUAL_LOG_MSG_FORMAT("Floating-point format: 1.99", "Floating-point format: %f", 1.99);
	TEST_ASSERT_EQUAL_LOG_MSG_FORMAT("Character array format: string", "Character array format: %s", "string");

	Log_terminate();
}

void test_Log_stackTrace_TraceQueueNULL(void)
{
	// If you don't call Log_initialize(), the trace_queue is NULL
	Log_stackTrace(TRACE_MAXIMUM, 10, 20, 1, "dddd", 10, NULL);

	// TODO how to evaluate the success?
}

void test_Log_stackTrace_LogLevelLessThanTraceLevel(void)
{
	TEST_ASSERT_TRUE(Log_initialize(NULL));

	Log_setTraceLevel(TRACE_MEDIUM);
	Log_stackTrace(LOG_FATAL, 10, 20, 1, "dddd", 10, NULL);

	// TODO how to evaluate the success?

	Log_terminate();
}

void test_Log_stackTrace(void)
{
	TEST_ASSERT_TRUE(Log_initialize(NULL));

	Log_setTraceLevel(TRACE_MEDIUM);

	int rc;
	Log_stackTrace(LOG_FATAL, 10, 20, 1, "dddd", 10, &rc);

	// TODO how to evaluate the success?

	Log_terminate();
}

void trace_callback(enum LOG_LEVELS level, char* message)
{
	printf("Trace : %d, %s\n", level, message);
}

void test_Log_setTraceCallback(void)
{
	Log_setTraceCallback(trace_callback);

	// TODO how to evaluate the success?
}

void test_Log_setTraceLevel(void)
{
	Log_setTraceLevel(TRACE_MAXIMUM);
	Log_setTraceLevel(TRACE_MEDIUM);
	Log_setTraceLevel(TRACE_MINIMUM);
	Log_setTraceLevel(TRACE_PROTOCOL);
	Log_setTraceLevel(LOG_ERROR);
	Log_setTraceLevel(LOG_SEVERE);
	Log_setTraceLevel(LOG_FATAL);

	// TODO Test after each Log_setTraceLevel() the variables
	//      trace_settings.trace_level and trace_output_level
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_Log_initialize_TraceDestinationEmpty);
	RUN_TEST(test_Log_initialize_TraceDestinationOn);
	RUN_TEST(test_Log_initialize_TraceDestinationFile);
	RUN_TEST(test_Log_initialize_TraceMaxLinesEmpty);
	RUN_TEST(test_Log_initialize_TraceMaxLinesPositive);
	RUN_TEST(test_Log_initialize_TraceMaxLinesNegative);
	RUN_TEST(test_Log_initialize_TraceLevel);
	RUN_TEST(test_Log_initialize_LogNameValue);
	RUN_TEST(test_Log_terminate);
	RUN_TEST(test_Log_NullFormat);
	RUN_TEST(test_Log_WithFormat);
	RUN_TEST(test_Log_stackTrace_TraceQueueNULL);
	RUN_TEST(test_Log_stackTrace_LogLevelLessThanTraceLevel);
	RUN_TEST(test_Log_stackTrace);
	RUN_TEST(test_Log_setTraceCallback);
	RUN_TEST(test_Log_setTraceLevel);

	return UNITY_END();
}
