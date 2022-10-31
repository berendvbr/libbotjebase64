#include "test_botje_base64__encode.h"

// example from: https://en.wikipedia.org/wiki/Base64#Examples
void test_botje_base64__encode_binary_test(void **state) {

  unsigned char *str_dst = calloc(1, 1024);
  unsigned char *str_src = calloc(1, 1024);
  int64_t len;
  int64_t ret_num;

  len = 1;
  str_src[0] = 248;
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 4);
  assert_memory_equal(str_dst, "+A==", 4);

  len = 1;
  str_src[0] = 252;
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 4);
  assert_memory_equal(str_dst, "/A==", 4);

  len = 2;
  str_src[0] = 251;
  str_src[1] = 240;
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 4);
  assert_memory_equal(str_dst, "+/A=", 4);

  len = 3;
  str_src[0] = 251;
  str_src[1] = 255;
  str_src[2] = 191;
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 4);
  assert_memory_equal(str_dst, "+/+/", 4);

  // example from rfc4648
  len = 4;
  str_src[0] = 0x14;
  str_src[1] = 0xfb;
  str_src[2] = 0x9c;
  str_src[3] = 0x03;
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 8);
  assert_memory_equal(str_dst, "FPucAw==", 8);

  // example from rfc4648
  len = 5;
  str_src[0] = 0x14;
  str_src[1] = 0xfb;
  str_src[2] = 0x9c;
  str_src[3] = 0x03;
  str_src[4] = 0xd9;
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 8);
  assert_memory_equal(str_dst, "FPucA9k=", 8);

  // example from rfc4648
  len = 6;
  str_src[0] = 0x14;
  str_src[1] = 0xfb;
  str_src[2] = 0x9c;
  str_src[3] = 0x03;
  str_src[4] = 0xd9;
  str_src[5] = 0x7e;
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 8);
  assert_memory_equal(str_dst, "FPucA9l+", 8);

  // clean up
  free(str_dst);
  free(str_src);
}

void test_botje_base64__encode_performance_test(void **state) {

  unsigned char *str_dst = calloc(1, 1024*1024*10);
  unsigned char *str_src = calloc(1, 1024*1024*10);
  int64_t len;
  int64_t ret_num;
  int64_t t1;
  int64_t t2;

  len = 1;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 1000 * 1000); l++) {
    ret_num = botje_base64__encode(str_dst, str_src, len);
    assert_int_equal(ret_num, 4);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 2;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 1000 * 1000); l++) {
    ret_num = botje_base64__encode(str_dst, str_src, len);
    assert_int_equal(ret_num, 4);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 3;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 1000 * 1000); l++) {
    ret_num = botje_base64__encode(str_dst, str_src, len);
    assert_int_equal(ret_num, 4);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 30;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 1000 * 100); l++) {
    ret_num = botje_base64__encode(str_dst, str_src, len);
    assert_int_equal(ret_num, 40);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 300;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 1000 * 10); l++) {
    ret_num = botje_base64__encode(str_dst, str_src, len);
    assert_int_equal(ret_num, 400);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 3000;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 1000); l++) {
    ret_num = botje_base64__encode(str_dst, str_src, len);
    assert_int_equal(ret_num, 4000);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 30000;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 100); l++) {
    ret_num = botje_base64__encode(str_dst, str_src, len);
    assert_int_equal(ret_num, 40000);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 300000;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 10); l++) {
    ret_num = botje_base64__encode(str_dst, str_src, len);
    assert_int_equal(ret_num, 400000);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  // len = 300001;
  // printf("start |%lld|\n", len);
  // for(int64_t l = 0; l < len; l++) {
  //   str_src[l] = 'A';
  // }
  // t1 = time(NULL);
  // for(int64_t l = 0; l < (1000 * 10); l++) {
  //   ret_num = base64__encode(str_dst, str_src, len);
  //   assert_int_equal(ret_num, 400004);
  // }
  // t2 = time(NULL);
  // printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  // len = 300002;
  // printf("start |%lld|\n", len);
  // for(int64_t l = 0; l < len; l++) {
  //   str_src[l] = 'A';
  // }
  // t1 = time(NULL);
  // for(int64_t l = 0; l < (1000 * 10); l++) {
  //   ret_num = base64__encode(str_dst, str_src, len);
  //   assert_int_equal(ret_num, 400004);
  // }
  // t2 = time(NULL);
  // printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 3000000;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000); l++) {
    ret_num = botje_base64__encode(str_dst, str_src, len);
    assert_int_equal(ret_num, 4000000);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  // clean up
  free(str_dst);
  free(str_src);
}

void test_botje_base64__encode_text_test(void **state) {
  unsigned char *str_dst = calloc(1, 1024);
  unsigned char *str_src = calloc(1, 1024);
  int64_t len;
  int64_t ret_num;

  len = 1;
  memcpy(str_src, "M", len);
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 4);
  assert_memory_equal(str_dst, "TQ==", 4);

  len = 2;
  memcpy(str_src, "Ma", len);
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 4);
  assert_memory_equal(str_dst, "TWE=", 4);

  len = 3;
  memcpy(str_src, "Man", len);
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 4);
  assert_memory_equal(str_dst, "TWFu", 4);

  len = 4;
  memcpy(str_src, "ManM", len);
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 8);
  assert_memory_equal(str_dst, "TWFuTQ==", 8);

  // example from rfc4648
  len = 4;
  memcpy(str_src, "foob", len);
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 8);
  assert_memory_equal(str_dst, "Zm9vYg==", 8);

  len = 5;
  memcpy(str_src, "ManMa", len);
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 8);
  assert_memory_equal(str_dst, "TWFuTWE=", 8);

  len = 5;
  memcpy(str_src, "ManXY", len);
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 8);
  assert_memory_equal(str_dst, "TWFuWFk=", 8);

  // example from rfc4648
  len = 5;
  memcpy(str_src, "fooba", len);
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 8);
  assert_memory_equal(str_dst, "Zm9vYmE=", 8);

  len = 6;
  memcpy(str_src, "ManMan", len);
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 8);
  assert_memory_equal(str_dst, "TWFuTWFu", 8);

  // example from rfc4648
  len = 6;
  memcpy(str_src, "foobar", len);
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 8);
  assert_memory_equal(str_dst, "Zm9vYmFy", 8);

  len = 27;
  memcpy(str_src, "Many hands make light work.", len);
  ret_num = botje_base64__encode(str_dst, str_src, len);
  assert_int_equal(ret_num, 36);
  assert_memory_equal(str_dst, "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu", 36);

  // clean up
  free(str_dst);
  free(str_src);
}
