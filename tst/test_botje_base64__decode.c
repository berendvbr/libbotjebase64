#include "test_botje_base64__decode.h"

// example from: https://en.wikipedia.org/wiki/Base64#Examples
void test_botje_base64__decode_binary_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t ret_val;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);
    unsigned char *str_src = malloc(buf_size);

    // the following tests are the opposites of the encode tests
    str_src_len = 4;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "+A==", 4);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 1);
    assert_int_equal(str_dst[0], 248);

    str_src_len = 4;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "/A==", 4);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 1);
    assert_int_equal(str_dst[0], 252);

    str_src_len = 4;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "+/A=", 4);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 2);
    assert_int_equal(str_dst[0], 251);
    assert_int_equal(str_dst[1], 240);

    str_src_len = 4;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "+/+/", 4);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 3);
    assert_int_equal(str_dst[0], 251);
    assert_int_equal(str_dst[1], 255);
    assert_int_equal(str_dst[2], 191);

    // clean up
    free(str_dst);
    free(str_src);
}

void test_botje_base64__decode_text_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t ret_val;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);
    unsigned char *str_src = malloc(buf_size);

    str_src_len = 4;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "TQ==", str_src_len);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 1);
    assert_memory_equal(str_dst, "M", 1);

    str_src_len = 4;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "TWE=", str_src_len);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 2);
    assert_memory_equal(str_dst, "Ma", 2);

    str_src_len = 4;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "TWFu", str_src_len);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 3);
    assert_memory_equal(str_dst, "Man", 3);

    str_src_len = 8;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "TWFuTQ==", str_src_len);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 4);
    assert_memory_equal(str_dst, "ManM", 4);

    str_src_len = 8;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "TWFuTWE=", str_src_len);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 5);
    assert_memory_equal(str_dst, "ManMa", 5);

    str_src_len = 8;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "TWFuWFk=", str_src_len);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 5);
    assert_memory_equal(str_dst, "ManXY", 5);

    str_src_len = 8;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "TWFuTWFu", str_src_len);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 6);
    assert_memory_equal(str_dst, "ManMan", 6);

    str_src_len = 36;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu", str_src_len);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 27);
    assert_memory_equal(str_dst, "Many hands make light work.", 27);

    // clean up
    free(str_dst);
    free(str_src);
}

void test_botje_base64__decode_wrong_input_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t ret_val;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);
    unsigned char *str_src = malloc(buf_size);

    str_src_len = 0;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 0);

    str_src_len = 1;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "T", str_src_len);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, -1);

    str_src_len = 2;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "TQ", str_src_len);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, -1);
    
    str_src_len = 3;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "TWE", str_src_len);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, -1);

    str_src_len = 4;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    unsigned char str_src_4[4] = { 0, 1, 2, 3 };
    ret_val = botje_base64__decode(str_dst, str_src_4, str_src_len);
    assert_int_equal(ret_val, -2);

    str_src_len = 5;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "TWFuT", str_src_len);
    ret_val = botje_base64__decode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, -1);

    // clean up
    free(str_dst);
    free(str_src);
}
