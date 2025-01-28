#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <string>

/** 
 * @brief Test suite. Runs all tests.
 * @return true if all tests pass, false otherwise
 */
bool run_all_tests();

/**
 * @brief A generic test function, that simply prints "PASSED" if LHS equals RHS 
 * and otherwise prints FAILED. Do not modify this function.
 * 
 * @param testNum Number of the test.  Value will be incremented upon completion
 * @param MESSAGE description of test
 * @param LHS computed result
 * @param RHS expected result
 * @return 1 if test passed, 0 otherwise
 */
int test_int_pointer(int& testNum, const std::string MESSAGE, const int* LHS, const int* RHS);

/**
 * @brief A generic test function, that simply prints "PASSED" if LHS does not equal RHS 
 * and otherwise prints FAILED. Do not modify this function.
 * 
 * @param testNum Number of the test.  Value will be incremented upon completion
 * @param MESSAGE description of test
 * @param LHS computed result
 * @param RHS expected result
 * @return 1 if test passed, 0 otherwise
 */
int test_int_pointer_not(int& testNum, const std::string MESSAGE, const int* LHS, const int* RHS);

/**
 * @brief A generic test function, that simply prints "PASSED" if LHS equals RHS 
 * and otherwise prints FAILED. Do not modify this function.
 * 
 * @param testNum Number of the test.  Value will be incremented upon completion
 * @param MESSAGE description of test
 * @param LHS computed result
 * @param RHS expected result
 * @return 1 if test passed, 0 otherwise
 */
int test_int(int& testNum, const std::string MESSAGE, const int LHS, const int RHS);

/**
 * @brief A generic test function, that simply prints "PASSED" if LHS equals RHS 
 * and otherwise prints FAILED. Do not modify this function.
 * 
 * @param testNum Number of the test.  Value will be incremented upon completion
 * @param MESSAGE description of test
 * @param LHS computed result
 * @param RHS expected result
 * @return 1 if test passed, 0 otherwise
 */
int test_unsigned_long(int& testNum, const std::string MESSAGE, const unsigned long LHS, const unsigned long RHS);

/**
 * @brief A generic test function, that simply prints "PASSED" if exception was thrown 
 * and otherwise prints FAILED. Do not modify this function.
 * 
 * @param testNum Number of the test.  Value will be incremented upon completion
 * @param MESSAGE description of test
 * @param EXCEPTION_THROWN flag denoting if exception was properly thrown
 * @return 1 if test passed, 0 otherwise
 */
int test_exception(int& testNum, const std::string MESSAGE, const bool EXCEPTION_THROWN);


/**
 * @brief A generic test function, that simply prints "FAILED" if exception was not thrown
 * and otherwise prints FAILED. Do not modify this function.
 * 
 * @param testNum Number of the test.  Value will be incremented upon completion
 * @param MESSAGE description of test
 * @param EXCEPTION_THROWN flag denoting if exception was properly not thrown
 * @return 1 if test passed, 0 otherwise
 */
int test_exception_not(int& testNum, const std::string MESSAGE, const bool EXCEPTION_NOT_THROWN);

#endif