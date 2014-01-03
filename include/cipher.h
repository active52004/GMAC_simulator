//
//  cipher.h
//  CETD-internal
//
//  Created by Duke on 13/09/13.
//  Copyright (c) 2013 Duke. All rights reserved.
//

#ifndef CETD_internal_cipher_h
#define CETD_internal_cipher_h
#include "config.h"
#include "aes.h"

void perodic_cipher(aes_context ctx,uchar **dst, uchar ** src, FILE *cipher_o,int index,bool file_type);
void cipher_short(aes_context ctx,uchar **dst, uchar ** src, FILE *cipher_o,bool file_type);
void cipher(aes_context ctx,uchar **dst, uchar ** src, FILE *cipher_o, bool file_type);

void only_plaintext(uchar **dst, const uchar **src, int number, int arr_length, FILE *cipher_o,bool file_type);
#endif
