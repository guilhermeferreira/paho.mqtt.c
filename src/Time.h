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

#if !defined(TIME_H)
#define TIME_H

#if !defined(WIN32) && !defined(WIN64)
	#include <sys/time.h>
#endif

#if defined(WIN32) || defined(WIN64)
#define START_TIME_TYPE DWORD
#elif defined(AIX)
#define START_TIME_TYPE struct timespec
#else
#define START_TIME_TYPE struct timeval
#endif

START_TIME_TYPE Time_start_clock(void);
long Time_elapsed(START_TIME_TYPE start);
void Time_sleep(long milliseconds);

#endif
