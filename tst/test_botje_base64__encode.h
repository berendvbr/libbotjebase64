#ifndef TEST_BOTJE_BASE64__ENCODE_H
#define TEST_BOTJE_BASE64__ENCODE_H

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cmocka.h>

#include "../src/botje_base64.h"

void test_botje_base64__encode_binary_test(void **);
void test_botje_base64__encode_text_test(void **);

#endif
