# Unit test for Double Linked List
# Referenced from :https://github.com/afosdick/ecen5013/tree/develop/tutorials/unit_tests
# Author : Divya Sampath Kumar
# Unit test for HW2 - ECEN5013-001

* [cmocka](https://cmocka.org/)

* cmocka [API](https://api.cmocka.org/index.html)

cmocka is included in this repository as a git subtree. See
3rd-party/README.md for details.

## Requirements

* cmake - available through most package managers.

## Build

* building cmocka:

    ```SHELL
    make cmocka
    ```

    This will go into the 3rd-party libraries directory and call cmake
    correctly to build cmocka.

* building and running tests:

    ```SHELL
    make lltest
    ```

    
* cleaing up local build artifacts:

    ```SHELL
    make clean
    ```
    
* removing all generated files, including 3rd-party builds

    ```SHELL
    make clobber
    ```
    
## Source

Included source files are:

* doubleLL.{h|c} - Library implementation of Double Linked List

* test_doubleLL.c - unit tests for Double Linked List Library

* main.c - simple demo driver using the library
