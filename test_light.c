#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Provide minimal AVR register/macro stubs for host testing
unsigned int DDRH;
unsigned int TCCR4A;
unsigned int TCCR4B;
unsigned int OCR4A;
unsigned int OCR4B;

#define PH3 3
#define PH4 4
#define COM4A1 7
#define COM4B1 6
#define WGM40 0
#define WGM42 1
#define CS41 1

// Bring in the implementation under test
#include "light.c"

static int tests_run = 0;

static void assert_true(int cond, const char *msg) {
    tests_run++;
    if (!cond) {
        fprintf(stderr, "FAIL: %s\n", msg);
        exit(1);
    }
}

static void test_initLight(void) {
    DDRH = TCCR4A = TCCR4B = OCR4A = OCR4B = 0xFFFFu; // set to nonzero
    initLight();
    // DDRH should have PH3 and PH4 set
    assert_true((DDRH & ((1<<PH3)|(1<<PH4))) == ((1<<PH3)|(1<<PH4)), "DDRH bits not set by initLight");
    // OCRs should be zero (lightOff called)
    assert_true(OCR4A == 0, "OCR4A not zero after initLight");
    assert_true(OCR4B == 0, "OCR4B not zero after initLight");
}

static void test_lightStart(void) {
    // clear regs
    TCCR4A = TCCR4B = OCR4A = OCR4B = 0;
    lightStart();
    assert_true(OCR4A == 110, "OCR4A != LIGHT_FULL_FRONT in lightStart");
    assert_true(OCR4B == 40, "OCR4B != LIGHT_HALF in lightStart");
    assert_true((TCCR4A & (1<<COM4A1)) != 0, "COM4A1 not set in TCCR4A by lightStart");
}

static void test_lightForward(void) {
    TCCR4A = TCCR4B = OCR4A = OCR4B = 0;
    lightForward();
    assert_true(OCR4A == 110, "OCR4A != LIGHT_FULL_FRONT in lightForward");
    assert_true(OCR4B == 40, "OCR4B != LIGHT_HALF in lightForward");
    assert_true((TCCR4A & (1<<COM4A1)) != 0, "COM4A1 not set in TCCR4A by lightForward");
    assert_true((TCCR4B & (1<<COM4B1)) != 0, "COM4B1 not set in TCCR4B by lightForward");
}

static void test_lightReverse(void) {
    TCCR4A = TCCR4B = OCR4A = OCR4B = 0;
    lightReverse();
    assert_true(OCR4A == 110, "OCR4A != LIGHT_FULL_FRONT in lightReverse");
    assert_true(OCR4B == 110, "OCR4B != LIGHT_FULL_BACK in lightReverse");
    assert_true((TCCR4A & (1<<COM4A1)) != 0, "COM4A1 not set in TCCR4A by lightReverse");
    assert_true((TCCR4B & (1<<COM4B1)) != 0, "COM4B1 not set in TCCR4B by lightReverse");
}

static void test_lightOff(void) {
    // set bits then call
    TCCR4A = (1<<COM4A1);
    TCCR4B = (1<<COM4B1);
    OCR4A = OCR4B = 0xFFFFu;
    lightOff();
    assert_true(OCR4A == 0, "OCR4A not cleared by lightOff");
    assert_true(OCR4B == 0, "OCR4B not cleared by lightOff");
    assert_true((TCCR4A & (1<<COM4A1)) == 0, "COM4A1 not cleared in TCCR4A by lightOff");
    assert_true((TCCR4B & (1<<COM4B1)) == 0, "COM4B1 not cleared in TCCR4B by lightOff");
}

int main(void) {
    test_initLight();
    test_lightStart();
    test_lightForward();
    test_lightReverse();
    test_lightOff();
    printf("All %d tests passed.\n", tests_run);
    return 0;
}
