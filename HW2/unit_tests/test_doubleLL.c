/*
* FileName        : 	test_doubleLL.c
* Description     :	Code to perform unit test on Double LL
* File Author Name:	Divya Sampath Kumar
* Tools used	  :	gcc
*/

#include <math.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "doubleLL.h"

struct Node* head_test=NULL;

void test_remove_empty_dll(void **state)
{
    uint32_t position = 5;
    enum Errorcode Errorcode = remove_node(&head_test,position);
    assert_int_equal(Errorcode, LL_EMPTY); 
}

void test_add_outofindex_dll(void **state)
{
    uint32_t nodeVal = 5;
    uint32_t position = 2;
    enum Errorcode Errorcode = add_node(&head_test,nodeVal,position);
    assert_int_equal(Errorcode, INDEX_OUT_OF_BOUND);
}

void test_add_head_dll(void **state)
{
    uint32_t nodeVal = 1;
    uint32_t position = 0;
    enum Errorcode Errorcode = add_node(&head_test,nodeVal,position);
    assert_int_equal(Errorcode, ADD_SUCCESS);
}

void test_add_mid_dll(void **state)
{
    uint32_t nodeVal = 2;
    uint32_t position = 0;
    enum Errorcode Errorcode;
    Errorcode = add_node(&head_test,nodeVal,position);
    assert_int_equal(Errorcode, ADD_SUCCESS);
    nodeVal = 3;
    position = 1;
    Errorcode = add_node(&head_test,nodeVal,position);
    assert_int_equal(Errorcode, ADD_SUCCESS);
    nodeVal = 4;
    position = 2;
    Errorcode = add_node(&head_test,nodeVal,position);
    assert_int_equal(Errorcode, ADD_SUCCESS);
    nodeVal = 4;
    position = 1;
    Errorcode = add_node(&head_test,nodeVal,position);
    assert_int_equal(Errorcode, ADD_SUCCESS);
}

void test_add_tail_dll(void **state)
{
    uint32_t nodeVal = 5;
    uint32_t position = size()-1;
    enum Errorcode Errorcode = add_node(&head_test,nodeVal,position);
    assert_int_equal(Errorcode, ADD_SUCCESS);
}

void test_remove_outofindex_dll(void **state)
{
    uint32_t position = 10;
    enum Errorcode Errorcode = remove_node(&head_test,position); 
    assert_int_equal(Errorcode, INDEX_OUT_OF_BOUND);
}

void test_destroy_success_dll(void **state)
{
    enum Errorcode Errorcode = destroy(&head_test); 
    assert_int_equal(Errorcode, DESTROY_SUCCESS);	
}

void test_remove_head_dll(void **state)
{
    uint32_t nodeVal = 2;
    uint32_t position = 0;
    enum Errorcode Errorcode;
    Errorcode = add_node(&head_test,nodeVal,position); 
    nodeVal = 3;
    position = 0;
    Errorcode = add_node(&head_test,nodeVal,position); 
    nodeVal = 4;
    position = 1;
    Errorcode = add_node(&head_test,nodeVal,position); 
    nodeVal = 5;
    position = 2;
    Errorcode = add_node(&head_test,nodeVal,position); 
    nodeVal = 6;
    position = 3;
    Errorcode = add_node(&head_test,nodeVal,position); 
    position = 0;
    Errorcode = remove_node(&head_test,position); 
    assert_int_equal(Errorcode, DELETE_SUCCESS);
    
}

void test_remove_middle_dll(void **state)
{
    uint32_t position = 1;
    enum Errorcode Errorcode = remove_node(&head_test,position); 
    assert_int_equal(Errorcode, DELETE_SUCCESS);    
}

void test_remove_tail_dll(void **state)
{
    uint32_t position = size();
    enum Errorcode Errorcode = remove_node(&head_test,position); 
    assert_int_equal(Errorcode, DELETE_SUCCESS);
    Errorcode = destroy(&head_test); 
    assert_int_equal(Errorcode, DESTROY_SUCCESS);
        
}


void test_search_success_dll(void **state)
{
    uint32_t nodeVal = 2;
    uint32_t position = 0;
    uint32_t searchVal = 5;
    uint32_t searchIndex =0;
    enum Errorcode Errorcode;
    Errorcode = add_node(&head_test,nodeVal,position); 
    nodeVal = 3;
    position = 0;
    Errorcode = add_node(&head_test,nodeVal,position); 
    nodeVal = 4;
    position = 1;
    Errorcode = add_node(&head_test,nodeVal,position); 
    nodeVal = 5;
    position = 2;
    Errorcode = add_node(&head_test,nodeVal,position); 
    nodeVal = 6;
    position = 3;
    Errorcode = add_node(&head_test,nodeVal,position); 
    search(&head_test,searchVal,&searchIndex); 
    assert_int_equal(searchIndex, 4); 
    assert_int_equal(Errorcode, ADD_SUCCESS);   
}

void test_search_notfound_dll(void **state)
{
    uint32_t searchVal = 10;
    uint32_t searchIndex =0;
    enum Errorcode Errorcode;
    search(&head_test,searchVal,&searchIndex); 
    assert_int_equal(searchIndex, 0); 
    Errorcode = destroy(&head_test); 
    assert_int_equal(Errorcode, DESTROY_SUCCESS);
       
}



void test_destroy_fail_dll(void **state)
{ 
    enum Errorcode Errorcode = destroy(&head_test); 
    assert_int_equal(Errorcode, ERROR_DESTROY);
}


int main(int argc, char **argv)
{
    const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_remove_empty_dll),
    cmocka_unit_test(test_add_outofindex_dll),
    cmocka_unit_test(test_add_head_dll),
    cmocka_unit_test(test_add_mid_dll),
    cmocka_unit_test(test_add_tail_dll),
    cmocka_unit_test(test_remove_outofindex_dll),
    cmocka_unit_test(test_destroy_success_dll),
    cmocka_unit_test(test_remove_head_dll),
    cmocka_unit_test(test_remove_middle_dll),
    cmocka_unit_test(test_remove_tail_dll),
    cmocka_unit_test(test_search_success_dll),
    cmocka_unit_test(test_search_notfound_dll),
    cmocka_unit_test(test_destroy_fail_dll),
    };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
