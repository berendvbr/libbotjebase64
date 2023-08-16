#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cmocka.h>

#include "test_botje_base64__decode.h"
#include "test_botje_base64__encode.h"

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_botje_base64__decode_binary_test),
        cmocka_unit_test(test_botje_base64__decode_text_test),
        cmocka_unit_test(test_botje_base64__decode_wrong_input_test),
        cmocka_unit_test(test_botje_base64__encode_binary_test),
        cmocka_unit_test(test_botje_base64__encode_text_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
