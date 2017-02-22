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

#include "LinkedList.h"

#include "unity.h"

void test_ListZero(void)
{
	List list;
	ListZero(&list);

	TEST_ASSERT_EQUAL(NULL, list.first);
	TEST_ASSERT_EQUAL(NULL, list.last);
	TEST_ASSERT_EQUAL(NULL, list.current);
	TEST_ASSERT_EQUAL(0, list.count);
	TEST_ASSERT_EQUAL(0, list.size);
}

void test_ListInitialize(void)
{
	List *list = NULL;
	list = ListInitialize();

	TEST_ASSERT_NOT_EQUAL(NULL, list);
	TEST_ASSERT_EQUAL(NULL, list->first);
	TEST_ASSERT_EQUAL(NULL, list->last);
	TEST_ASSERT_EQUAL(NULL, list->current);
	TEST_ASSERT_EQUAL(0, list->count);
	TEST_ASSERT_EQUAL(0, list->size);

	ListFree(list);
}

void test_ListAppend(void)
{
	List *list = NULL;
	list = ListInitialize();
	size_t list_size = 0;

	TEST_ASSERT_EQUAL(NULL, list->first);
	TEST_ASSERT_EQUAL(NULL, list->last);
	TEST_ASSERT_EQUAL(0, list->count);
	TEST_ASSERT_EQUAL(0, list->size);

	int d1 = 10;
	size_t d1_size = sizeof(d1);
	list_size += d1_size;

	ListAppend(list, &d1, d1_size);
	TEST_ASSERT_NOT_EQUAL(NULL, list->first);
	TEST_ASSERT_NOT_EQUAL(NULL, list->last);
	TEST_ASSERT_EQUAL(1, list->count);
	TEST_ASSERT_EQUAL(d1_size, list->size);
	TEST_ASSERT_EQUAL(&d1, list->first->content);
	TEST_ASSERT_EQUAL(d1, *(int*)list->first->content);
	TEST_ASSERT_EQUAL(&d1, list->last->content);
	TEST_ASSERT_EQUAL(d1, *(int*)list->last->content);

	int d2 = 20;
	size_t d2_size = sizeof(d2);
	list_size += d2_size;

	ListAppend(list, &d2, d2_size);
	TEST_ASSERT_NOT_EQUAL(NULL, list->first);
	TEST_ASSERT_NOT_EQUAL(NULL, list->last);
	TEST_ASSERT_EQUAL(2, list->count);
	TEST_ASSERT_EQUAL(list_size, list->size);
	TEST_ASSERT_NOT_EQUAL(&d2, list->first->content);
	TEST_ASSERT_NOT_EQUAL(d2, *(int*)list->first->content);
	TEST_ASSERT_EQUAL(&d2, list->last->content);
	TEST_ASSERT_EQUAL(d2, *(int*)list->last->content);

	int d3 = 30;
	size_t d3_size = sizeof(d3);
	list_size += d3_size;

	ListAppend(list, &d3, d3_size);
	TEST_ASSERT_NOT_EQUAL(NULL, list->first);
	TEST_ASSERT_NOT_EQUAL(NULL, list->last);
	TEST_ASSERT_EQUAL(3, list->count);
	TEST_ASSERT_EQUAL(list_size, list->size);
	TEST_ASSERT_NOT_EQUAL(&d3, list->first->content);
	TEST_ASSERT_NOT_EQUAL(d3, *(int*)list->first->content);
	TEST_ASSERT_EQUAL(&d3, list->last->content);
	TEST_ASSERT_EQUAL(d3, *(int*)list->last->content);

	ListElement *next = NULL;
	TEST_ASSERT_NOT_EQUAL(NULL, ListNextElement(list, &next));
	TEST_ASSERT_EQUAL(d1, *(int*) next->content);
	TEST_ASSERT_NOT_EQUAL(NULL, ListNextElement(list, &next));
	TEST_ASSERT_EQUAL(d2, *(int*) next->content);
	TEST_ASSERT_NOT_EQUAL(NULL, ListNextElement(list, &next));
	TEST_ASSERT_EQUAL(d3, *(int*) next->content);

	ListFree(list);
}

void test_ListAppendNoMalloc(void)
{
}

void test_ListInsert(void)
{
	List *list = NULL;
	list = ListInitialize();
	size_t list_size = 0;

	TEST_ASSERT_EQUAL(NULL, list->first);
	TEST_ASSERT_EQUAL(NULL, list->last);
	TEST_ASSERT_EQUAL(0, list->count);
	TEST_ASSERT_EQUAL(0, list->size);

	int d1 = 10;
	size_t d1_size = sizeof(d1);
	list_size += d1_size;

	ListInsert(list, &d1, d1_size, NULL);
	TEST_ASSERT_NOT_EQUAL(NULL, list->first);
	TEST_ASSERT_NOT_EQUAL(NULL, list->last);
	TEST_ASSERT_EQUAL(1, list->count);
	TEST_ASSERT_EQUAL(d1_size, list->size);
	TEST_ASSERT_EQUAL(&d1, list->first->content);
	TEST_ASSERT_EQUAL(d1, *(int*)list->first->content);

	int d2 = 20;
	size_t d2_size = sizeof(d2);
	list_size += d2_size;

	ListInsert(list, &d2, d2_size, list->first);
	TEST_ASSERT_NOT_EQUAL(NULL, list->first);
	TEST_ASSERT_NOT_EQUAL(NULL, list->last);
	TEST_ASSERT_EQUAL(2, list->count);
	TEST_ASSERT_EQUAL(d1_size + d2_size, list->size);
	TEST_ASSERT_EQUAL(&d2, list->first->content);
	TEST_ASSERT_EQUAL(d2, *(int*)list->first->content);

	int d3 = 30;
	size_t d3_size = sizeof(d3);
	list_size += d3_size;

	ListInsert(list, &d3, d3_size, list->first);
	TEST_ASSERT_NOT_EQUAL(NULL, list->first);
	TEST_ASSERT_NOT_EQUAL(NULL, list->last);
	TEST_ASSERT_EQUAL(3, list->count);
	TEST_ASSERT_EQUAL(d1_size + d2_size + d3_size, list->size);
	TEST_ASSERT_EQUAL(&d3, list->first->content);
	TEST_ASSERT_EQUAL(d3, *(int*)list->first->content);

	ListElement *next = NULL;
	TEST_ASSERT_NOT_EQUAL(NULL, ListNextElement(list, &next));
	TEST_ASSERT_EQUAL(d3, *(int*) next->content);
	TEST_ASSERT_NOT_EQUAL(NULL, ListNextElement(list, &next));
	TEST_ASSERT_EQUAL(d2, *(int*) next->content);
	TEST_ASSERT_NOT_EQUAL(NULL, ListNextElement(list, &next));
	TEST_ASSERT_EQUAL(d1, *(int*) next->content);

	ListFree(list);
}


void test_ListRemove(void)
{
	List *list = NULL;
	list = ListInitialize();
	size_t list_size = 0;

	int d1 = 10;
	size_t d1_size = sizeof(d1);
	list_size += d1_size;

	ListAppend(list, &d1, d1_size);
	TEST_ASSERT_NOT_EQUAL(NULL, list->first);
	TEST_ASSERT_NOT_EQUAL(NULL, list->last);
	TEST_ASSERT_EQUAL(1, list->count);
	TEST_ASSERT_EQUAL(d1_size, list->size);
	TEST_ASSERT_EQUAL(&d1, list->first->content);
	TEST_ASSERT_EQUAL(d1, *(int*)list->first->content);
	TEST_ASSERT_EQUAL(&d1, list->last->content);
	TEST_ASSERT_EQUAL(d1, *(int*)list->last->content);

	int d2 = 20;
	size_t d2_size = sizeof(d2);
	list_size += d2_size;

	ListAppend(list, &d2, d2_size);
	TEST_ASSERT_NOT_EQUAL(NULL, list->first);
	TEST_ASSERT_NOT_EQUAL(NULL, list->last);
	TEST_ASSERT_EQUAL(2, list->count);
	TEST_ASSERT_EQUAL(list_size, list->size);
	TEST_ASSERT_NOT_EQUAL(&d2, list->first->content);
	TEST_ASSERT_NOT_EQUAL(d2, *(int*)list->first->content);
	TEST_ASSERT_EQUAL(&d2, list->last->content);
	TEST_ASSERT_EQUAL(d2, *(int*)list->last->content);

	int d3 = 30;
	size_t d3_size = sizeof(d3);
	list_size += d3_size;

	ListAppend(list, &d3, d3_size);
	TEST_ASSERT_NOT_EQUAL(NULL, list->first);
	TEST_ASSERT_NOT_EQUAL(NULL, list->last);
	TEST_ASSERT_EQUAL(3, list->count);
	TEST_ASSERT_EQUAL(list_size, list->size);
	TEST_ASSERT_NOT_EQUAL(&d3, list->first->content);
	TEST_ASSERT_NOT_EQUAL(d3, *(int*)list->first->content);
	TEST_ASSERT_EQUAL(&d3, list->last->content);
	TEST_ASSERT_EQUAL(d3, *(int*)list->last->content);

	ListElement *next = NULL;
	TEST_ASSERT_NOT_EQUAL(NULL, ListNextElement(list, &next));
	TEST_ASSERT_EQUAL(d1, *(int*) next->content);
	TEST_ASSERT_NOT_EQUAL(NULL, ListNextElement(list, &next));
	TEST_ASSERT_EQUAL(d2, *(int*) next->content);
	TEST_ASSERT_NOT_EQUAL(NULL, ListNextElement(list, &next));
	TEST_ASSERT_EQUAL(d3, *(int*) next->content);

	ListFree(list);
}

void test_ListRemoveItem(void)
{
}

void test_ListDetachHead(void)
{
}

void test_ListRemoveHead(void)
{
}

void test_ListPopTail(void)
{
}


void test_ListDetach(void)
{
}

void test_ListDetachItem(void)
{
}

void test_ListFree(void)
{
}

void test_ListEmpty(void)
{
}

void test_ListFreeNoContent(void)
{
}


void test_ListNextElement(void)
{
}

void test_ListPrevElement(void)
{
}

void test_ListFind(void)
{
}
void test_ListFindItem(void)
{
}

void test_intcompare(void)
{
}
void test_stringcompare(void)
{
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_ListZero);
	RUN_TEST(test_ListInitialize);

	RUN_TEST(test_ListAppend);
	RUN_TEST(test_ListAppendNoMalloc);
	RUN_TEST(test_ListInsert);

	RUN_TEST(test_ListRemove);
	RUN_TEST(test_ListRemoveItem);
	RUN_TEST(test_ListDetachHead);
	RUN_TEST(test_ListRemoveHead);
	RUN_TEST(test_ListPopTail);

	RUN_TEST(test_ListDetach);
	RUN_TEST(test_ListDetachItem);
	RUN_TEST(test_ListFree);
	RUN_TEST(test_ListEmpty);
	RUN_TEST(test_ListFreeNoContent);

	RUN_TEST(test_ListNextElement);
	RUN_TEST(test_ListPrevElement);
	RUN_TEST(test_ListFind);
	RUN_TEST(test_ListFindItem);

	RUN_TEST(test_intcompare);
	RUN_TEST(test_stringcompare);

	return UNITY_END();
}
