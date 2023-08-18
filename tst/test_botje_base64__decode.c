#include "test_botje_base64__decode.h"

// example from: https://en.wikipedia.org/wiki/Base64#Examples
void test_botje_base64__decode_binary_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t num_chars;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);

    // the following tests are the opposites of the encode tests
    {
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "+A==";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 1);
        unsigned char str_dst_cmp[] = { 248 };
        assert_memory_equal(str_dst, str_dst_cmp, num_chars);
    }

    {
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "/A==";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 1);
        unsigned char str_dst_cmp[] = { 252 };
        assert_memory_equal(str_dst, str_dst_cmp, num_chars);
    }

    {
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "+/A=";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 2);
        unsigned char str_dst_cmp[] = { 251, 240 };
        assert_memory_equal(str_dst, str_dst_cmp, num_chars);
    }

    {
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "+/+/";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 3);
        unsigned char str_dst_cmp[] = { 251, 255, 191 };
        assert_memory_equal(str_dst, str_dst_cmp, num_chars);
    }

    // clean up
    free(str_dst);
}

void test_botje_base64__decode_text_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t num_chars;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);

    {
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "TQ==";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 1);
        assert_memory_equal(str_dst, "M", num_chars);
    }

    {
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "TWE=";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 2);
        assert_memory_equal(str_dst, "Ma", num_chars);
    }

    {
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "TWFu";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 3);
        assert_memory_equal(str_dst, "Man", num_chars);
    }

    {
        str_src_len = 8;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "TWFuTQ==";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 4);
        assert_memory_equal(str_dst, "ManM", num_chars);
    }

    {
        str_src_len = 8;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "TWFuTWE=";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 5);
        assert_memory_equal(str_dst, "ManMa", num_chars);
    }

    {
        str_src_len = 8;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "TWFuWFk=";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 5);
        assert_memory_equal(str_dst, "ManXY", num_chars);
    }

    {
        str_src_len = 8;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "TWFuTWFu";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 6);
        assert_memory_equal(str_dst, "ManMan", num_chars);
    }

    {
        str_src_len = 36;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 27);
        assert_memory_equal(str_dst, "Many hands make light work.", num_chars);
    }

    // clean up
    free(str_dst);
}

void test_botje_base64__decode_wrong_input_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t num_chars;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);

    {
        str_src_len = 0;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 0);
    }

    {
        str_src_len = 1;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "T";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, -1);
    }

    {
        str_src_len = 2;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "TQ";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, -1);
    }
    
    {
        str_src_len = 3;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "TWE";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, -1);
    }

    {
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 0, 1, 2, 3 };
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, -2);
    }

    {
        str_src_len = 5;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "TWFuT";
        num_chars = botje_base64__decode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, -1);
    }

    // clean up
    free(str_dst);
}
