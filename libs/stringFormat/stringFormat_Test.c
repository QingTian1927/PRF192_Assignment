/**
 * @file stringFormat_Test.c
 * @author QingTian
 * @brief unit tests for stringFormat.c
 */

#include <stdio.h>
#include "stringFormat.h"

#define TEST_FAIL "FAIL"
#define TEST_OKAY "OKAY"

void test_upper(void) {
    const char testName[] = "upper()";
    printf("-------------\n");
    printf("TEST: %s\n\n", testName);

    char testInput, testOutput, expectedOutput;
    int failCount = 0, successCount = 0;

    // TEST 1
    // ------
    testInput = 'a'; expectedOutput = 'A';
    testOutput = upper(testInput);
    printf(
        "Test 1: %c -> %s -> %c | expected: %c | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 2
    // ------
    testInput = 'r'; expectedOutput = 'R';
    testOutput = upper(testInput);
    printf(
        "Test 1: %c -> %s -> %c | expected: %c | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 3
    // ------
    testInput = '6'; expectedOutput = '6';
    testOutput = upper(testInput);
    printf(
        "Test 1: %c -> %s -> %c | expected: %c | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 4
    // ------
    testInput = 'R'; expectedOutput = 'R';
    testOutput = upper(testInput);
    printf(
        "Test 1: %c -> %s -> %c | expected: %c | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 5
    // ------
    testInput = '%'; expectedOutput = '%';
    testOutput = upper(testInput);
    printf(
        "Test 1: %c -> %s -> %c | expected: %c | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    printf("\n");
    printf("SUCCESS: %d | FAILURE: %d\n\n", successCount, failCount);
}

void test_lower(void) {
    const char testName[] = "lower()";
    printf("-------------\n");
    printf("TEST: %s\n\n", testName);

    char testInput, testOutput, expectedOutput;
    int failCount = 0, successCount = 0;

    // TEST 1
    // ------
    testInput = 'A'; expectedOutput = 'a';
    testOutput = lower(testInput);
    printf(
        "Test 1: %c -> %s -> %c | expected: %c | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 2
    // ------
    testInput = 'Z'; expectedOutput = 'z';
    testOutput = lower(testInput);
    printf(
        "Test 2: %c -> %s -> %c | expected: %c | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 3
    // ------
    testInput = '6'; expectedOutput = '6';
    testOutput = lower(testInput);
    printf(
        "Test 3: %c -> %s -> %c | expected: %c | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 4
    // ------
    testInput = 'f'; expectedOutput = 'f';
    testOutput = lower(testInput);
    printf(
        "Test 4: %c -> %s -> %c | expected: %c | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 5
    // ------
    testInput = '%'; expectedOutput = '%';
    testOutput = lower(testInput);
    printf(
        "Test 5: %c -> %s -> %c | expected: %c | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    printf("\n");
    printf("SUCCESS: %d | FAILURE: %d\n\n", successCount, failCount);
}

void test_isWhiteSpace(void) {
    const char testName[] = "isWhiteSpace()";
    printf("--------------------\n");
    printf("TEST: %s\n\n", testName);

    char testInput;
    int testOutput, expectedOutput;
    int failCount = 0, successCount = 0;

    const int resultIsWhiteSpace = 1;
    const int resultIsNotWhiteSpace = 0;

    // TEST 1
    // ------
    testInput = 'A'; expectedOutput = resultIsNotWhiteSpace;
    testOutput = isWhiteSpace(testInput);
    printf(
        "Test 1: %3d -> %s -> %d | expected: %d | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 2
    // ------
    testInput = ' '; expectedOutput = resultIsWhiteSpace;
    testOutput = isWhiteSpace(testInput);
    printf(
        "Test 2: %3d -> %s -> %d | expected: %d | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 3
    // ------
    testInput = '\t'; expectedOutput = resultIsWhiteSpace;
    testOutput = isWhiteSpace(testInput);
    printf(
        "Test 3: %3d -> %s -> %d | expected: %d | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 4
    // ------
    testInput = '\v'; expectedOutput = resultIsWhiteSpace;
    testOutput = isWhiteSpace(testInput);
    printf(
        "Test 4: %3d -> %s -> %d | expected: %d | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 5
    // ------
    testInput = '\f'; expectedOutput = resultIsWhiteSpace;
    testOutput = isWhiteSpace(testInput);
    printf(
        "Test 5: %3d -> %s -> %d | expected: %d | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 6
    // ------
    testInput = '\n'; expectedOutput = resultIsWhiteSpace;
    testOutput = isWhiteSpace(testInput);
    printf(
        "Test 6: %3d -> %s -> %d | expected: %d | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 7
    // ------
    testInput = '\r'; expectedOutput = resultIsWhiteSpace;
    testOutput = isWhiteSpace(testInput);
    printf(
        "Test 7: %3d -> %s -> %d | expected: %d | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    // TEST 8
    // ------
    testInput = '%'; expectedOutput = resultIsNotWhiteSpace;
    testOutput = isWhiteSpace(testInput);
    printf(
        "Test 8: %3d -> %s -> %d | expected: %d | ",
        testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        successCount++;
    }
    else {
        printf("%s\n", TEST_FAIL);
        failCount++;
    }

    printf("\n");
    printf("SUCCESS: %d | FAILURE: %d\n\n", successCount, failCount);
}

int main() {
    test_upper();
    test_lower();
    test_isWhiteSpace();

    return 0;
}