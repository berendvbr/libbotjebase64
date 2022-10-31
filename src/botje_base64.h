#ifndef BOTJE_BASE64_H
#define BOTJE_BASE64_H

#include <stdio.h>
#include <stdlib.h>

int64_t botje_base64__decode(unsigned char *, unsigned char *, int64_t);
int64_t botje_base64__decode_ascii_to_base64(int64_t);
int64_t botje_base64__encode(unsigned char *, unsigned char *, int64_t);
int64_t botje_base64__encode_base64_to_ascii(int64_t);

#endif
