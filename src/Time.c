/*******************************************************************************
 * Copyright (c) 2016
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
 *    Guilherme Ferreir - initial implementation
 ******************************************************************************/

#include "Time.h"

#include "StackTrace.h"

#if !defined(WIN32) || !defined(WIN64)
#include <unistd.h>
#endif


#if defined(WIN32) || defined(WIN64)
START_TIME_TYPE Time_start_clock(void)
{
	return GetTickCount();
}
#elif defined(AIX)
START_TIME_TYPE Time_start_clock(void)
{
	START_TIME_TYPE start_time;
	clock_gettime(CLOCK_REALTIME, &start_time);
	return start_time;
}
#else
START_TIME_TYPE Time_start_clock(void)
{
	START_TIME_TYPE start_time;
	gettimeofday(&start_time, NULL);
	return start_time;
}
#endif


#if defined(WIN32) || defined(WIN64)
long Time_elapsed(START_TIME_TYPE start_time_ms)
{
	return GetTickCount() - start_time_ms;
}
#elif defined(AIX)
#define assert(a)
long Time_elapsed(START_TIME_TYPE start_time)
{
	START_TIME_TYPE now;
	START_TIME_TYPE res;

	clock_gettime(CLOCK_REALTIME, &now);
	ntimersub(now, start_time, res);
	return (res.tv_sec) * 1000L + (res.tv_nsec) / 1000000L;
}
#else
long Time_elapsed(START_TIME_TYPE start_time)
{
	START_TIME_TYPE now;
	START_TIME_TYPE res;

	gettimeofday(&now, NULL);
	timersub(&now, &start_time, &res);
	return (res.tv_sec) * 1000 + (res.tv_usec) / 1000;
}
#endif


void Time_sleep(long milliseconds)
{
	FUNC_ENTRY;
#if defined(WIN32) || defined(WIN64)
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif
	FUNC_EXIT;
}
