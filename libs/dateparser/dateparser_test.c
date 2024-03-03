/**
 * @file dateParser_Test.c
 * @author QingTian
 * @brief unit tests for dateParser.c
 */

#include <stdio.h>
#include <string.h>

#include "dateparser.h"

#define TEST_FAIL "FAIL"
#define TEST_OKAY "OKAY"

#define TEST_FAIL_STATUS 0
#define TEST_OKAY_STATUS 1

int compareParserSettings(
    struct parserSettings firstParser,
    struct parserSettings secondParser
) {
    int paddingSettingsMatch = (
        (getDayFormat(firstParser) == getDayFormat(secondParser))
        &&
        (getMonthFormat(firstParser) == getMonthFormat(firstParser))
    );

    int specifierOrderingMatch = 1;
    int i;
    for (i = 0; i < UNIQUE_SUPPORTED_SPECIFIERS; i++) {
        if (firstParser.specifierOrder[i] != secondParser.specifierOrder[i]) {
            specifierOrderingMatch = 0;
            break;
        }
    }

    int result = paddingSettingsMatch && specifierOrderingMatch;
    return result;
}

int singleTest_parseFormatString(
    const char* testName,
    int testNumber,
    char* testFormatStr,
    const char testSeparator,
    struct parserSettings testParser,
    const struct parserSettings expectedOutput
) {
    int testStrLen;
    if (testFormatStr == NULL) { testStrLen = 0; }
    else { testStrLen = strlen(testFormatStr); }

    int testOutput = parseFormatString(
        testFormatStr,
        testStrLen,
        testSeparator,
        &testParser
    );

    int result = compareParserSettings(testParser, expectedOutput);
    printf(
        "Test %d: %*s -> %s -> %d (%2d %2d) | expected: %2d %2d | ",
        testNumber, MAX_DATE_STRING, testFormatStr, testName, testOutput,
        getDayFormat(testParser), getMonthFormat(testParser),
        getDayFormat(expectedOutput), getMonthFormat(expectedOutput)
    );
    if (result) {
        printf("%s\n", TEST_OKAY);
        return TEST_OKAY_STATUS;
    }
    printf("%s\n", TEST_FAIL);
    return TEST_FAIL_STATUS;
}

void test_parseFormatString() {
    const char testName[] = "parseFormatString()";
    printf("-------------------------\n");
    printf("TEST: %s\n\n", testName);

    int failCount = 0, successCount = 0;
    int testNumber = 1;
    int result;
    struct parserSettings testParser = {NULL, 0, 0};

    result = singleTest_parseFormatString(
        testName,
        testNumber++,
        "yyyy/MM/dd",
        '/',
        testParser,
        (struct parserSettings){{'y', 'M', 'd'}, 1, 1}
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_parseFormatString(
        testName,
        testNumber++,
        "dd-M-yyyy",
        '-',
        testParser,
        (struct parserSettings){{'d', 'M', 'y'}, 1, 0}
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_parseFormatString(
        testName,
        testNumber++,
        "MM_d_yyyy",
        '_',
        testParser,
        (struct parserSettings){{'M', 'd', 'y'}, 0, 1}
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_parseFormatString(
        testName,
        testNumber++,
        "d M yyyy",
        ' ',
        testParser,
        (struct parserSettings){{'d', 'M', 'y'}, 0, 0}
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_parseFormatString(
        testName,
        testNumber++,
        "y/D/m",
        '/',
        testParser,
        (struct parserSettings){NULL, -1, -1}
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_parseFormatString(
        testName,
        testNumber++,
        "yyyy/dd",
        '/',
        testParser,
        (struct parserSettings){NULL, -1, -1}
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_parseFormatString(
        testName,
        testNumber++,
        "ddMMyyyy",
        0,
        testParser,
        (struct parserSettings){{'d', 'M', 'y'}, 1, 1}
    );
    if (result) { successCount++; }
    else { failCount++; }

    result = singleTest_parseFormatString(
        testName,
        testNumber++,
        NULL,
        0,
        testParser,
        (struct parserSettings){NULL, -1, -1}
    );
    if (result) { successCount++; }
    else { failCount++; }

    printf("\n");
    printf("SUCCESS: %d | FAILURE: %d\n\n", successCount, failCount);
}

int main() {
    test_parseFormatString();
    return 0;
}
