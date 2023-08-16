#include "botje_base64.h"

// example from: https://en.wikipedia.org/wiki/Base64#Examples

// decoding function
// input ASCII "TWFu"
//      T      W      F      u
//     84     87     70    117  (4x ASCII decimal values)
//     19     22      5     46  (4x Base64 decimal values)
// 010011 010110 000101 101110  (4x 6 bits binary values)
//  01001101 01100001 01101110  (3x 8 bits binary values)
//        77       97      110  (3x ASCII decimal values)
//         M        a        n
// output ASCII "Man"

int64_t botje_base64__decode(unsigned char * str_dst, unsigned char *str_src, int64_t str_src_len) {

    if(str_src_len % 4 != 0) {
        return -1;
    }

    int64_t num_chars = 0;
    unsigned char *cur_dst = str_dst;
    unsigned char *cur_src = str_src;
    int64_t remainder = str_src_len;
    while(remainder > 0) {

        if(cur_src[2] == '=' && cur_src[3] == '=') {
            int64_t retval0 = botje_base64__decode_ascii_to_base64(cur_src[0]);
            int64_t retval1 = botje_base64__decode_ascii_to_base64(cur_src[1]);
            if(retval0 == -1 || retval1 == -1)  return -2;

            int64_t combined = (retval0 << 18) + (retval1 << 12);
            *(cur_dst++) = (combined >> 16) & 0b11111111;

            num_chars += 1;
        } else if(cur_src[3] == '=') {
            int64_t retval0 = botje_base64__decode_ascii_to_base64(cur_src[0]);
            int64_t retval1 = botje_base64__decode_ascii_to_base64(cur_src[1]);
            int64_t retval2 = botje_base64__decode_ascii_to_base64(cur_src[2]);
            if(retval0 == -1 || retval1 == -1 || retval2 == -1)  return -2;

            int64_t combined = (retval0 << 18) + (retval1 << 12) + (retval2 << 6);

            *(cur_dst++) = (combined >> 16) & 0b11111111;
            *(cur_dst++) = (combined >> 8) & 0b11111111;

            num_chars += 2;
        } else {
            int64_t retval0 = botje_base64__decode_ascii_to_base64(cur_src[0]);
            int64_t retval1 = botje_base64__decode_ascii_to_base64(cur_src[1]);
            int64_t retval2 = botje_base64__decode_ascii_to_base64(cur_src[2]);
            int64_t retval3 = botje_base64__decode_ascii_to_base64(cur_src[3]);
            if(retval0 == -1 || retval1 == -1 || retval2 == -1 || retval3 == -1)  return -2;

            int64_t combined = (retval0 << 18) + (retval1 << 12) + (retval2 << 6) + retval3;

            *(cur_dst++) = (combined >> 16) & 0b11111111;
            *(cur_dst++) = (combined >> 8) & 0b11111111;
            *(cur_dst++) = combined & 0b11111111;

            num_chars += 3;
        }

        cur_src += 4;
        remainder -= 4;
    }

    return num_chars;
}

// A-Z ASCII -> A-Z Base64 == 65-90  -> 0-25   (-65)
// a-z ASCII -> a-z Base64 == 97-122 -> 26-51  (-71)
// 0-9 ASCII -> 0-9 Base64 == 48-57  -> 52-61  (+4)
//   + ASCII ->   + Base64 == 43     -> 62
//   / ASCII ->   / Base64 == 47     -> 63
int64_t botje_base64__decode_ascii_to_base64(int64_t chr) {
  
    if(chr >= 65 && chr <= 90) { return chr - 65; }
    else if(chr >= 97 && chr <= 122) { return chr - 71; }
    else if(chr >= 48 && chr <= 57) { return chr + 4; }
    else if(chr == 43) { return 62; }
    else if(chr == 47) { return 63; }

    return -1;
}

// encoding function
// input ASCII "Man"
//       77       97      110   (decimal values of ASCII "Man")
// 01001101 01100001 01101110   (3x 8 bits ASCII input)
// 010011 010110 000101 101110  (4x 6 bits)
//     19     22      5     46  (4x decimal values of the 6 bits)
//     84     87     70    117  (4x decimal Base64 values converted to decimal ASCII values)
//      T      W      F      u  (4x ASCII characters)
// output ASCII "TWFu"

// input ASCII "Ma"
//       77       97     (decimal values of ASCII "Ma")
// 01001101 01100001     (2x 8 bits ASCII input)
// 010011 010110 000100  (3x 6 bits, last 2 zeros added, because we go from 16 to 18 bits)
//     19     22      4  (3x decimal values of the 6 bits)
//     84     87     69  (3x decimal Base64 values converted to decimal ASCII values)
//      T      W      E  (3x ASCII characters)
// output "TWE="         (1x decimal 61, char '=', added for padding)

// input  "M"
//       77       (decimal values of ASCII "M")
// 01001101       (1x 8 bits ASCII input)
// 010011 010000  (2x 6 bits, last 4 zeros added, because we go from 8 to 12 bits)
//     19     16  (2x decimal values of the 6 bits)
//     84     81  (2x decimal Base64 values converted to decimal ASCII values)
//      T      Q  (2x ASCII characters)
// output "TQ=="  (2x decimal 61, char '=', added for padding)

int64_t botje_base64__encode(unsigned char *str_dst, unsigned char *str_src, int64_t str_src_len) {

    int64_t num_chars = 0;
    unsigned char *cur_dst = str_dst;
    unsigned char *cur_src = str_src;
    int64_t remainder = str_src_len;
    while(remainder > 0) {

        if(remainder >= 3) {
            int64_t combined = (cur_src[0] << 16) + (cur_src[1] << 8) + cur_src[2];

            *(cur_dst++) = botje_base64__encode_base64_to_ascii((combined & (0b111111 << 18)) >> 18);
            *(cur_dst++) = botje_base64__encode_base64_to_ascii((combined & (0b111111 << 12)) >> 12);
            *(cur_dst++) = botje_base64__encode_base64_to_ascii((combined & (0b111111 << 6)) >> 6);
            *(cur_dst++) = botje_base64__encode_base64_to_ascii(combined & 0b111111);
        } else if(remainder == 2) {
            int64_t combined = ((cur_src[0] << 8) + cur_src[1]) << 2;

            *(cur_dst++) = botje_base64__encode_base64_to_ascii((combined & (0b111111 << 12)) >> 12);
            *(cur_dst++) = botje_base64__encode_base64_to_ascii((combined & (0b111111 << 6)) >> 6);
            *(cur_dst++) = botje_base64__encode_base64_to_ascii(combined & 0b111100);
            *(cur_dst++) = 61;
        } else if(remainder == 1) {
            int64_t combined = cur_src[0] << 4;

            *(cur_dst++) = botje_base64__encode_base64_to_ascii((combined & (0b111111 << 6)) >> 6);
            *(cur_dst++) = botje_base64__encode_base64_to_ascii(combined & 0b110000);
            *(cur_dst++) = 61;
            *(cur_dst++) = 61;
        }

        cur_src += 3;
        remainder -= 3;
        num_chars += 4;
    }

    return num_chars;
}

// A-Z Base64 -> A-Z ASCII == 0-25  -> 65->90  (+65)
// a-z Base64 -> a-z ASCII == 26-51 -> 97->122 (+71)
// 0-9 Base64 -> 0-9 ASCII == 52-61 -> 48-57   (-4)
//   + Base64 ->   + ASCII == 62    -> 43
//   / Base64 ->   / ASCII == 63    -> 47
int64_t botje_base64__encode_base64_to_ascii(int64_t chr) {
  
    if(chr >= 0 && chr <= 25) { return chr + 65; }
    else if(chr >= 26 && chr <= 51) { return chr + 71; }
    else if(chr >= 52 && chr <= 61) { return chr - 4; }
    else if(chr == 62) { return 43; }
    else if(chr == 63) { return 47; }

    printf("botje_base64__encode_base64_to_ascii error\n");
    abort();

    return -1;
}
