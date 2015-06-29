/* test_utf8.c */
#include <stdio.h>

#define VALID 0
#define INVALID 1

#define STATE_START_BYTE 0
#define STATE_CONTINUATION 1

#define IS_CONTINUATION(c) ((c) & (1 << 7))

int bytes_in_codepoint(unsigned char start_byte) {
    int count = 0;
    int mask = 1 << 6;
    for (count = 0; start_byte & mask; count++) {
        mask = mask >> 1;
    }
    return count;
}

int test_utf8(const unsigned char *str)
{
    const unsigned char *c;
    int state = STATE_START_BYTE;
    int codepoint_length = 0;
    
    for (c = str; *c != 0; c++) {
        switch (state) {
        case STATE_START_BYTE:
            if (IS_CONTINUATION(*c)) {
                codepoint_length = bytes_in_codepoint(*c);
                // only possible invalid case in this state
                // is an invalid continuation byte... 10000000
                if (!codepoint_length) {
                    return INVALID;
                }
                state = STATE_CONTINUATION;
            }
            break;
        case STATE_CONTINUATION:
            // only possible invalid case in this state is if we
            // were expecting a continuation byte but didn't get one
            if (!IS_CONTINUATION(*c)) {
                return INVALID;
            }
            codepoint_length--;
            if (!codepoint_length) {
                state = STATE_START_BYTE;
            }
            break;
        }
    }
    
    // if we were expecting more bytes...
    return codepoint_length ? INVALID : VALID;
}

/* "K", should be valid */
const unsigned char test1[] = { 0x4B, 0x00 };

/* "hey" with accented e, should be valid */
const unsigned char test2[] = { 0x68, 0xC3, 0xA8, 0x79, 0x00 };

/* junk, should fail */
const unsigned char test3[] = { 0x5A, 0xC3, 0xC3, 0xE9, 0x5A, 0x00 };

/* a random-ish sequence I think is valid */
const unsigned char test4[] = { 0xF4, 0xAF, 0xA7, 0xB2, 0xE6, 0xA1, 0xB3, 0x00 };

/* junk, should fail */
const unsigned char test5[] = { 0x5A, 0x79, 0xF4, 0xAF, 0xA7, 0x00 };

const unsigned char *tests[] = {test1, test2, test3, test4, test5};

int main() {
    int i;
    for (i = 0; i < 5; i++) {
        printf("test%d: %s\n", i+1, test_utf8(tests[i]) == VALID ? "VALID" : "INVALID");
    }
    return 0;
}