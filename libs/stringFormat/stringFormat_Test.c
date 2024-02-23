/**
 * @file stringFormat_Test.c
 * @author QingTian
 * @brief unit tests for stringFormat.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stringFormat.h"

#define TEST_FAIL "FAIL"
#define TEST_OKAY "OKAY"

#define TEST_FAIL_STATUS 0
#define TEST_OKAY_STATUS 1

int singleTest_upper(
    const char* testName,
    int testNumber,
    char testInput,
    char expectedOutput
) {
    char testOutput = upper(testInput);
    printf(
        "Test %d: %c -> %s -> %c | expected: %c | ",
        testNumber, testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        return TEST_OKAY_STATUS;
    }
    printf("%s\n", TEST_FAIL);
    return TEST_FAIL_STATUS;
}

void test_upper(void) {
    const char testName[] = "upper()";
    printf("-------------\n");
    printf("TEST: %s\n\n", testName);

    int failCount = 0, successCount = 0;
    int testNumber = 1;
    int result;

    result = singleTest_upper(testName, testNumber++, 'a', 'A');
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_upper(testName, testNumber++, 'r', 'R');
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_upper(testName, testNumber++, '6', '6');
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_upper(testName, testNumber++, 'H', 'H');
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_upper(testName, testNumber++, '%', '%');
    if (result) { successCount++; }
    else { failCount++; }

    printf("\n");
    printf("SUCCESS: %d | FAILURE: %d\n\n", successCount, failCount);
}

int singleTest_lower(
    const char* testName,
    int testNumber,
    char testInput,
    char expectedOutput
) {
    char testOutput = lower(testInput);
    printf(
        "Test %d: %c -> %s -> %c | expected: %c | ",
        testNumber, testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        return TEST_OKAY_STATUS;
    }
    printf("%s\n", TEST_FAIL);
    return TEST_FAIL_STATUS;
}

void test_lower(void) {
    const char testName[] = "lower()";
    printf("-------------\n");
    printf("TEST: %s\n\n", testName);

    int failCount = 0, successCount = 0;
    int testNumber = 1;
    int result;

    result = singleTest_lower(testName, testNumber++, 'B', 'b');
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_lower(testName, testNumber++, 'Z', 'z');
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_lower(testName, testNumber++, '0', '0');
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_lower(testName, testNumber++, 'f', 'f');
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_lower(testName, testNumber++, '#', '#');
    if (result) { successCount++; }
    else { failCount++; }

    printf("\n");
    printf("SUCCESS: %d | FAILURE: %d\n\n", successCount, failCount);
}

int singleTest_isWhiteSpace(
    const char* testName,
    int testNumber,
    char testInput,
    int expectedOutput
) {
    int testOutput = isWhiteSpace(testInput);
    printf(
        "Test %d: %3d -> %s -> %d | expected: %d | ",
        testNumber, testInput, testName, testOutput, expectedOutput
    );
    if (testOutput == expectedOutput) {
        printf("%s\n", TEST_OKAY);
        return TEST_OKAY_STATUS;
    }
    printf("%s\n", TEST_FAIL);
    return TEST_FAIL_STATUS;
}

void test_isWhiteSpace(void) {
    const char testName[] = "isWhiteSpace()";
    printf("--------------------\n");
    printf("TEST: %s\n\n", testName);

    int failCount = 0, successCount = 0;
    int testNumber = 1;
    int result;

    const int resultIsWhiteSpace = 1;
    const int resultIsNotWhiteSpace = 0;

    result = singleTest_isWhiteSpace(testName, testNumber++, 'A', resultIsNotWhiteSpace);
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_isWhiteSpace(testName, testNumber++, ' ', resultIsWhiteSpace);
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_isWhiteSpace(testName, testNumber++, '\t', resultIsWhiteSpace);
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_isWhiteSpace(testName, testNumber++, '\v', resultIsWhiteSpace);
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_isWhiteSpace(testName, testNumber++, '\f', resultIsWhiteSpace);
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_isWhiteSpace(testName, testNumber++, '\n', resultIsWhiteSpace);
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_isWhiteSpace(testName, testNumber++, '\r', resultIsWhiteSpace);
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_isWhiteSpace(testName, testNumber++, '>', resultIsNotWhiteSpace);
    if (result) { successCount++; }
    else { failCount++; }

    printf("\n");
    printf("SUCCESS: %d | FAILURE: %d\n\n", successCount, failCount);
}

char* newString(int strLen) {
    char* newStr = (char*) calloc(strLen, sizeof(char));
    if (newStr == NULL) {
        printf("newString(): calloc() returned NULL.\n");
        printf("Process terminated.\n");
        exit(1);
    }
    return newStr;
}

int singleTest_capitalizeString(
    const char* testName,
    int testNumber,
    const char* inputStr,
    const char* expectedOutputStr,
    int maxStrLen
) {
    char* testInput;
    char* expectedOutput;
    char* preservedTestInput;
    int result;

    testInput = newString(maxStrLen + 1);
    expectedOutput = newString(maxStrLen + 1);
    preservedTestInput = newString(maxStrLen + 1);

    testInput = strncpy(testInput, inputStr, maxStrLen);
    preservedTestInput = strncpy(preservedTestInput, testInput, maxStrLen);
    expectedOutput = strncpy(expectedOutput, expectedOutputStr, maxStrLen);

    capitalizeString(testInput, strlen(testInput));
    result = (strncmp(testInput, expectedOutput, maxStrLen) == 0);

    printf("Test %d:\n", testNumber);
    printf("  *) input:    \"%s\"\n", preservedTestInput);
    printf("  *) output:   \"%s\"\n", testInput);
    printf("  *) expected: \"%s\"\n", expectedOutput);
    printf("--> %s ", testName);

    if (result) {
        printf("%s\n", TEST_OKAY);
        result = TEST_OKAY_STATUS;
    } else {
        printf("%s\n", TEST_FAIL);
        result = TEST_FAIL_STATUS;
    }

    free(testInput);
    free(expectedOutput);
    free(preservedTestInput);

    return result;
}

void test_capitalizeString(void) {
    const char testName[] = "capitalizeString()";
    printf("------------------------\n");
    printf("TEST: %s\n\n", testName);

    const int maxStrLen = 50;
    int failCount = 0, successCount = 0;
    int testNumber = 1;
    int result;

    result = singleTest_capitalizeString(
        testName,
        testNumber++,
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
        "Lorem Ipsum Dolor Sit Amet, Consectetur Adipiscing Elit.",
        maxStrLen
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_capitalizeString(
        testName,
        testNumber++,
        "pUbLiC STatIc VOiD MaIN STRiNg arGs",
        "Public Static Void Main String Args",
        maxStrLen
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_capitalizeString(
        testName,
        testNumber++,
        "愿此刻永遠是我们的晴天",
        "愿此刻永遠是我们的晴天",
        maxStrLen
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_capitalizeString(
        testName,
        testNumber++,
        "Oăn mắt in ma giừn si sớt phớt háp pi",
        "Oăn Mắt In Ma Giừn Si Sớt Phớt Háp Pi",
        maxStrLen
    );
    if (result) { successCount++; }
    else { failCount++; }

    printf("\n");
    printf("SUCCESS: %d | FAILURE: %d\n\n", successCount, failCount);
}

int singleTest_trimFunction(
    const char* testName,
    int testNumber,
    const char* inputStr,
    const char* expectedOutputStr,
    int maxStrLen,
    int (*trimFunction)(char*, int)
) {
    char* testInput;
    char* expectedOutput;
    char* preservedTestInput;
    int result;

    testInput = newString(maxStrLen + 1);
    expectedOutput = newString(maxStrLen + 1);
    preservedTestInput = newString(maxStrLen + 1);

    testInput = strncpy(testInput, inputStr, maxStrLen);
    preservedTestInput = strncpy(preservedTestInput, testInput, maxStrLen);
    expectedOutput = strncpy(expectedOutput, expectedOutputStr, maxStrLen);

    trimFunction(testInput, strlen(testInput));
    result = (strncmp(testInput, expectedOutput, maxStrLen) == 0);

    printf("Test %d:\n", testNumber);
    printf("  *) input:    \"%s\"\n", preservedTestInput);
    printf("  *) output:   \"%s\"\n", testInput);
    printf("  *) expected: \"%s\"\n", expectedOutput);
    printf("--> %s ", testName);

    if (result) {
        printf("%s\n", TEST_OKAY);
        result = TEST_OKAY_STATUS;
    } else {
        printf("%s\n", TEST_FAIL);
        result = TEST_FAIL_STATUS;
    }

    free(testInput);
    free(expectedOutput);
    free(preservedTestInput);

    return result;
}

void test_trimLeft(void) {
    const char testName[] = "trimLeft()";
    printf("----------------\n");
    printf("TEST: %s\n\n", testName);

    const int maxStrLen = 50;
    int failCount = 0, successCount = 0;
    int testNumber = 1;
    int result;
    int (*trimFunction)(char*, int) = &trimLeft;

    result = singleTest_trimFunction(
        testName,
        testNumber++,
        "    abcdxyz",
        "abcdxyz",
        maxStrLen,
        trimFunction
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_trimFunction(
        testName,
        testNumber++,
        "  lorem ipsum dolor sit amet   ",
        "lorem ipsum dolor sit amet   ",
        maxStrLen,
        trimFunction
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_trimFunction(
        testName,
        testNumber++,
        "   東風と  桜の花が    空を飛ぶ    ",
        "東風と  桜の花が    空を飛ぶ    ",
        maxStrLen,
        trimFunction
    );
    if (result) { successCount++; }
    else { failCount++; }

    printf("\n");
    printf("SUCCESS: %d | FAILURE: %d\n\n", successCount, failCount);
}

void test_trimRight(void) {
    const char testName[] = "trimRight()";
    printf("-----------------\n");
    printf("TEST: %s\n\n", testName);

    const int maxStrLen = 50;
    int failCount = 0, successCount = 0;
    int testNumber = 1;
    int result;
    int (*trimFunction)(char*, int) = &trimRight;

    result = singleTest_trimFunction(
        testName,
        testNumber++,
        "    abcdxyz  ",
        "    abcdxyz",
        maxStrLen,
        trimFunction
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_trimFunction(
        testName,
        testNumber++,
        "  lorem ipsum dolor sit amet   ",
        "  lorem ipsum dolor sit amet",
        maxStrLen,
        trimFunction
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_trimFunction(
        testName,
        testNumber++,
        "   東風と  桜の花が    空を飛ぶ    ",
        "   東風と  桜の花が    空を飛ぶ",
        maxStrLen,
        trimFunction
    );
    if (result) { successCount++; }
    else { failCount++; }

    printf("\n");
    printf("SUCCESS: %d | FAILURE: %d\n\n", successCount, failCount);
}

void test_fullTrim(void) {
    const char testName[] = "fullTrim()";
    printf("----------------\n");
    printf("TEST: %s\n\n", testName);

    const int maxStrLen = 50;
    int failCount = 0, successCount = 0;
    int testNumber = 1;
    int result;
    int (*trimFunction)(char*, int) = &fullTrim;

    result = singleTest_trimFunction(
        testName,
        testNumber++,
        "    abcdxyz  ",
        "abcdxyz",
        maxStrLen,
        trimFunction
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_trimFunction(
        testName,
        testNumber++,
        "  lorem ipsum dolor sit amet   ",
        "lorem ipsum dolor sit amet",
        maxStrLen,
        trimFunction
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_trimFunction(
        testName,
        testNumber++,
        "   東風と  桜の花が    空を飛ぶ    ",
        "東風と 桜の花が 空を飛ぶ",
        maxStrLen,
        trimFunction
    );
    if (result) { successCount++; }
    else { failCount++; }

    printf("\n");
    printf("SUCCESS: %d | FAILURE: %d\n\n", successCount, failCount);
}

int main() {
    test_upper();
    test_lower();

    test_isWhiteSpace();
    test_capitalizeString();

    test_trimLeft();
    test_trimRight();
    test_fullTrim();

    return 0;
}