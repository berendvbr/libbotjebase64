#include "test_botje_base64__encode.h"

// example from: https://en.wikipedia.org/wiki/Base64#Examples
void test_botje_base64__encode_binary_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t ret_val;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);

    str_src_len = 1;
    memset(str_dst, 0, buf_size);
    unsigned char str_src_0[] = { 248 };
    ret_val = botje_base64__encode(str_dst, str_src_0, str_src_len);
    assert_int_equal(ret_val, 4);
    assert_memory_equal(str_dst, "+A==", 4);

    str_src_len = 1;
    memset(str_dst, 0, buf_size);
    unsigned char str_src_1[] = { 252 };
    ret_val = botje_base64__encode(str_dst, str_src_1, str_src_len);
    assert_int_equal(ret_val, 4);
    assert_memory_equal(str_dst, "/A==", 4);

    str_src_len = 2;
    memset(str_dst, 0, buf_size);
    unsigned char str_src_2[] = { 251, 240 };
    ret_val = botje_base64__encode(str_dst, str_src_2, str_src_len);
    assert_int_equal(ret_val, 4);
    assert_memory_equal(str_dst, "+/A=", 4);

    str_src_len = 3;
    memset(str_dst, 0, buf_size);
    unsigned char str_src_3[] = { 251, 255, 191 };
    ret_val = botje_base64__encode(str_dst, str_src_3, str_src_len);
    assert_int_equal(ret_val, 4);
    assert_memory_equal(str_dst, "+/+/", 4);

    // // example from rfc4648
    str_src_len = 4;
    memset(str_dst, 0, buf_size);
    unsigned char str_src_4[] = { 0x14, 0xfb, 0x9c, 0x03 };
    ret_val = botje_base64__encode(str_dst, str_src_4, str_src_len);
    assert_int_equal(ret_val, 8);
    assert_memory_equal(str_dst, "FPucAw==", 8);

    // // example from rfc4648
    str_src_len = 5;
    memset(str_dst, 0, buf_size);
    unsigned char str_src_5[] = { 0x14, 0xfb, 0x9c, 0x03, 0xd9 };
    ret_val = botje_base64__encode(str_dst, str_src_5, str_src_len);
    assert_int_equal(ret_val, 8);
    assert_memory_equal(str_dst, "FPucA9k=", 8);

    // // example from rfc4648
    str_src_len = 6;
    memset(str_dst, 0, buf_size);
    unsigned char str_src_6[] = { 0x14, 0xfb, 0x9c, 0x03, 0xd9, 0x7e };
    ret_val = botje_base64__encode(str_dst, str_src_6, str_src_len);
    assert_int_equal(ret_val, 8);
    assert_memory_equal(str_dst, "FPucA9l+", 8);

    // clean up
    free(str_dst);
}

void test_botje_base64__encode_text_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t ret_val;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);
    unsigned char *str_src = malloc(buf_size);

    str_src_len = 1;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "M", str_src_len);
    ret_val = botje_base64__encode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 4);
    assert_memory_equal(str_dst, "TQ==", 4);

    str_src_len = 2;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "Ma", str_src_len);
    ret_val = botje_base64__encode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 4);
    assert_memory_equal(str_dst, "TWE=", 4);

    str_src_len = 3;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "Man", str_src_len);
    ret_val = botje_base64__encode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 4);
    assert_memory_equal(str_dst, "TWFu", 4);

    str_src_len = 4;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "ManM", str_src_len);
    ret_val = botje_base64__encode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 8);
    assert_memory_equal(str_dst, "TWFuTQ==", 8);

    // example from rfc4648
    str_src_len = 4;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "foob", str_src_len);
    ret_val = botje_base64__encode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 8);
    assert_memory_equal(str_dst, "Zm9vYg==", 8);

    str_src_len = 5;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "ManMa", str_src_len);
    ret_val = botje_base64__encode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 8);
    assert_memory_equal(str_dst, "TWFuTWE=", 8);

    str_src_len = 5;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "ManXY", str_src_len);
    ret_val = botje_base64__encode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 8);
    assert_memory_equal(str_dst, "TWFuWFk=", 8);

    // example from rfc4648
    str_src_len = 5;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "fooba", str_src_len);
    ret_val = botje_base64__encode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 8);
    assert_memory_equal(str_dst, "Zm9vYmE=", 8);

    str_src_len = 6;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "ManMan", str_src_len);
    ret_val = botje_base64__encode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 8);
    assert_memory_equal(str_dst, "TWFuTWFu", 8);

    // example from rfc4648
    str_src_len = 6;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "foobar", str_src_len);
    ret_val = botje_base64__encode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 8);
    assert_memory_equal(str_dst, "Zm9vYmFy", 8);

    str_src_len = 27;
    memset(str_dst, 0, buf_size);
    memset(str_src, 0, buf_size);
    memcpy(str_src, "Many hands make light work.", str_src_len);
    ret_val = botje_base64__encode(str_dst, str_src, str_src_len);
    assert_int_equal(ret_val, 36);
    assert_memory_equal(str_dst, "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu", 36);

    // clean up
    free(str_dst);
    free(str_src);
}
