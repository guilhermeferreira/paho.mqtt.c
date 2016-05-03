#*******************************************************************************
#  Copyright (c) 2016
# 
#  All rights reserved. This program and the accompanying materials
#  are made available under the terms of the Eclipse Public License v1.0
#  and Eclipse Distribution License v1.0 which accompany this distribution. 
# 
#  The Eclipse Public License is available at 
#     http://www.eclipse.org/legal/epl-v10.html
#  and the Eclipse Distribution License is available at 
#    http://www.eclipse.org/org/documents/edl-v10.php.
# 
#  Contributors:
#     Guilherme Maciel Ferreira - add test subdir
#*******************************************************************************/

# Note: on OS X you should install XCode and the associated command-line tools

## compilation/linkage settings
INCLUDE_DIRECTORIES(
    .
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}
    )

# test files c
ADD_EXECUTABLE(test1 test1.c)
ADD_EXECUTABLE(test2 test2.c)
ADD_EXECUTABLE(sync_client_test sync_client_test.c)
ADD_EXECUTABLE(test_mqtt4sync test_mqtt4sync.c)

TARGET_LINK_LIBRARIES(test1 paho-mqtt3c)
TARGET_LINK_LIBRARIES(test2 paho-mqtt3c)
TARGET_LINK_LIBRARIES(sync_client_test paho-mqtt3c)
TARGET_LINK_LIBRARIES(test_mqtt4sync paho-mqtt3c)

ADD_EXECUTABLE(test4 test4.c)
ADD_EXECUTABLE(test6 test6.c)
ADD_EXECUTABLE(test8 test8.c)
ADD_EXECUTABLE(test_mqtt4async test_mqtt4async.c)

TARGET_LINK_LIBRARIES(test4 paho-mqtt3a)
TARGET_LINK_LIBRARIES(test6 paho-mqtt3a)
TARGET_LINK_LIBRARIES(test8 paho-mqtt3a)
TARGET_LINK_LIBRARIES(test_mqtt4async paho-mqtt3a)

INSTALL(TARGETS test1
                test2
                test4
                test6
                test8
                sync_client_test
                test_mqtt4async
                test_mqtt4sync
    RUNTIME DESTINATION bin)

IF (PAHO_WITH_SSL)
    ADD_EXECUTABLE(test3 test3.c)
    ADD_EXECUTABLE(test5 test5.c)

    TARGET_LINK_LIBRARIES(test3 paho-mqtt3cs)
    TARGET_LINK_LIBRARIES(test5 paho-mqtt3as)

    INSTALL(TARGETS test3
                    test5
    RUNTIME DESTINATION bin)
ENDIF()
