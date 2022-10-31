#include "test_botje_base64__decode.h"

// example from: https://en.wikipedia.org/wiki/Base64#Examples
void test_botje_base64__decode_binary_test(void **state) {

  unsigned char *str_dst = calloc(1, 1024);
  unsigned char *str_src = calloc(1, 1024);
  int64_t len;
  int64_t ret_num;

  // len = 1;
  // str_src[0] = 248;
  // ret_num = base64__encode(str_dst, str_src, len);
  // assert_int_equal(ret_num, 4);
  // assert_memory_equal(str_dst, "+A==", 4);

  len = 4;
  memcpy(str_src, "+A==", 4);
  ret_num = botje_base64__decode(str_dst, str_src, len);
  assert_int_equal(ret_num, 1);
  assert_int_equal(str_dst[0], 248);

  // len = 1;
  // str_src[0] = 252;
  // ret_num = base64__encode(str_dst, str_src, len);
  // assert_int_equal(ret_num, 4);
  // assert_memory_equal(str_dst, "/A==", 4);

  len = 4;
  memcpy(str_src, "/A==", 4);
  ret_num = botje_base64__decode(str_dst, str_src, len);
  assert_int_equal(ret_num, 1);
  assert_int_equal(str_dst[0], 252);

  // len = 2;
  // str_src[0] = 251;
  // str_src[1] = 240;
  // ret_num = base64__encode(str_dst, str_src, len);
  // assert_int_equal(ret_num, 4);
  // assert_memory_equal(str_dst, "+/A=", 4);

  len = 4;
  memcpy(str_src, "+/A=", 4);
  ret_num = botje_base64__decode(str_dst, str_src, len);
  assert_int_equal(ret_num, 2);
  assert_int_equal(str_dst[0], 251);
  assert_int_equal(str_dst[1], 240);

  // len = 3;
  // str_src[0] = 251;
  // str_src[1] = 255;
  // str_src[2] = 191;
  // ret_num = base64__encode(str_dst, str_src, len);
  // assert_int_equal(ret_num, 4);
  // assert_memory_equal(str_dst, "+/+/", 4);

  len = 4;
  memcpy(str_src, "+/+/", 4);
  ret_num = botje_base64__decode(str_dst, str_src, len);
  assert_int_equal(ret_num, 3);
  assert_int_equal(str_dst[0], 251);
  assert_int_equal(str_dst[1], 255);
  assert_int_equal(str_dst[2], 191);

  // clean up
  free(str_dst);
  free(str_src);
}

void test_botje_base64__decode_performance_test(void **state) {

  unsigned char *str_dst = calloc(1, 1024*1024*10);
  unsigned char *str_src = calloc(1, 1024*1024*10);
  int64_t len;
  int64_t ret_num;

  len = 4;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  int64_t t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 1000 * 1000); l++) {
    ret_num = botje_base64__decode(str_dst, str_src, len);
    assert_int_equal(ret_num, 3);
  }
  int64_t t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 40;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 1000 * 100); l++) {
    ret_num = botje_base64__decode(str_dst, str_src, len);
    assert_int_equal(ret_num, 30);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 400;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 1000 * 10); l++) {
    ret_num = botje_base64__decode(str_dst, str_src, len);
    assert_int_equal(ret_num, 300);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 4000;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 1000); l++) {
    ret_num = botje_base64__decode(str_dst, str_src, len);
    assert_int_equal(ret_num, 3000);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 40000;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 100); l++) {
    ret_num = botje_base64__decode(str_dst, str_src, len);
    assert_int_equal(ret_num, 30000);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 400000;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000 * 10); l++) {
    ret_num = botje_base64__decode(str_dst, str_src, len);
    assert_int_equal(ret_num, 300000);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  // len = 400004;
  // printf("start |%lld|\n", len);
  // for(int64_t l = 0; l < len; l++) {
  //   str_src[l] = 'A';
  // }
  // t1 = time(NULL);
  // for(int64_t l = 0; l < (1000 * 10); l++) {
  //   ret_num = base64__decode(str_dst, str_src, len);
  //   assert_int_equal(ret_num, 300003);
  // }
  // t2 = time(NULL);
  // printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  len = 4000000;
  printf("start |%lld|\n", len);
  for(int64_t l = 0; l < len; l++) {
    str_src[l] = 'A';
  }
  t1 = time(NULL);
  for(int64_t l = 0; l < (1000); l++) {
    ret_num = botje_base64__decode(str_dst, str_src, len);
    assert_int_equal(ret_num, 3000000);
  }
  t2 = time(NULL);
  printf("end   |%lld| -> timediff: |%lld|\n", len, t2 - t1);

  // clean up
  free(str_dst);
  free(str_src);
}

void test_botje_base64__decode_text_test(void **state) {
  unsigned char *str_dst = calloc(1, 1024);
  unsigned char *str_src = calloc(1, 1024);
  int64_t len;
  int64_t ret_num;

  len = 4;
  memcpy(str_src, "TQ==", len);
  ret_num = botje_base64__decode(str_dst, str_src, len);
  assert_int_equal(ret_num, 1);
  assert_memory_equal(str_dst, "M", 1);

  len = 4;
  memcpy(str_src, "TWE=", len);
  ret_num = botje_base64__decode(str_dst, str_src, len);
  assert_int_equal(ret_num, 2);
  assert_memory_equal(str_dst, "Ma", 2);

  len = 4;
  memcpy(str_src, "TWFu", len);
  ret_num = botje_base64__decode(str_dst, str_src, len);
  assert_int_equal(ret_num, 3);
  assert_memory_equal(str_dst, "Man", 3);

  len = 8;
  memcpy(str_src, "TWFuTQ==", 8);
  ret_num = botje_base64__decode(str_dst, str_src, len);
  assert_int_equal(ret_num, 4);
  assert_memory_equal(str_dst, "ManM", 4);

  len = 8;
  memcpy(str_src, "TWFuTWE=", 8);
  ret_num = botje_base64__decode(str_dst, str_src, len);
  assert_int_equal(ret_num, 5);
  assert_memory_equal(str_dst, "ManMa", 5);

  len = 8;
  memcpy(str_src, "TWFuWFk=", 8);
  ret_num = botje_base64__decode(str_dst, str_src, len);
  assert_int_equal(ret_num, 5);
  assert_memory_equal(str_dst, "ManXY", 5);

  len = 8;
  memcpy(str_src, "TWFuTWFu", 8);
  ret_num = botje_base64__decode(str_dst, str_src, len);
  assert_int_equal(ret_num, 6);
  assert_memory_equal(str_dst, "ManMan", 6);

  len = 36;
  memcpy(str_src, "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu", 36);
  ret_num = botje_base64__decode(str_dst, str_src, len);
  assert_int_equal(ret_num, 27);
  assert_memory_equal(str_dst, "Many hands make light work.", 27);

  // clean up
  free(str_dst);
  free(str_src);
}
