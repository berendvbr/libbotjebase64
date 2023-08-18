#include "test_botje_base64__encode.h"

// example from: https://en.wikipedia.org/wiki/Base64#Examples
void test_botje_base64__encode_binary_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t num_chars;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);

    {
        str_src_len = 1;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 248 };
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 4);
        assert_memory_equal(str_dst, "+A==", num_chars);
    }

    {
        str_src_len = 1;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 252 };
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 4);
        assert_memory_equal(str_dst, "/A==", num_chars);
    }

    {
        str_src_len = 2;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 251, 240 };
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 4);
        assert_memory_equal(str_dst, "+/A=", num_chars);
    }

    {
        str_src_len = 3;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 251, 255, 191 };
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 4);
        assert_memory_equal(str_dst, "+/+/", num_chars);
    }

    {
        // example from rfc4648
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 0x14, 0xfb, 0x9c, 0x03 };
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 8);
        assert_memory_equal(str_dst, "FPucAw==", num_chars);
    }

    {
        // example from rfc4648
        str_src_len = 5;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 0x14, 0xfb, 0x9c, 0x03, 0xd9 };
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 8);
        assert_memory_equal(str_dst, "FPucA9k=", num_chars);
    }

    {
        // example from rfc4648
        str_src_len = 6;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = { 0x14, 0xfb, 0x9c, 0x03, 0xd9, 0x7e };
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 8);
        assert_memory_equal(str_dst, "FPucA9l+", num_chars);
    }

    // clean up
    free(str_dst);
}

void test_botje_base64__encode_text_test(void **state) {

    // init and default values
    int64_t buf_size = 1024;
    int64_t num_chars;
    int64_t str_src_len;
    unsigned char *str_dst = malloc(buf_size);

    {
        str_src_len = 1;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "M";
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 4);
        assert_memory_equal(str_dst, "TQ==", num_chars);
    }

    {
        str_src_len = 2;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "Ma";
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 4);
        assert_memory_equal(str_dst, "TWE=", num_chars);
    }

    {
        str_src_len = 3;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "Man";
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 4);
        assert_memory_equal(str_dst, "TWFu", num_chars);
    }

    {
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "ManM";
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 8);
        assert_memory_equal(str_dst, "TWFuTQ==", num_chars);
    }

    {
        // example from rfc4648
        str_src_len = 4;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "foob";
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 8);
        assert_memory_equal(str_dst, "Zm9vYg==", num_chars);
    }

    {
        str_src_len = 5;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "ManMa";
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 8);
        assert_memory_equal(str_dst, "TWFuTWE=", num_chars);
    }

    {
        str_src_len = 5;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "ManXY";
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 8);
        assert_memory_equal(str_dst, "TWFuWFk=", num_chars);
    }

    {
        // example from rfc4648
        str_src_len = 5;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "fooba";
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 8);
        assert_memory_equal(str_dst, "Zm9vYmE=", num_chars);
    }

    {
        str_src_len = 6;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "ManMan";
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 8);
        assert_memory_equal(str_dst, "TWFuTWFu", num_chars);
    }

    {
        // example from rfc4648
        str_src_len = 6;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "foobar";
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 8);
        assert_memory_equal(str_dst, "Zm9vYmFy", num_chars);
    }

    {
        str_src_len = 27;
        memset(str_dst, 0, buf_size);
        unsigned char str_src[] = "Many hands make light work.";
        num_chars = botje_base64__encode(str_dst, str_src, str_src_len);
        assert_int_equal(num_chars, 36);
        assert_memory_equal(str_dst, "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu", num_chars);
    }

    // clean up
    free(str_dst);
}
