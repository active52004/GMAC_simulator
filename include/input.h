//
//  input.h
//  CETD-internal
//
//  Created by Duke on 12/09/13.
//  Copyright (c) 2013 Duke. All rights reserved.
//

#ifndef CETD_internal_input_h
#define CETD_internal_input_h
#include "config.h"
void linear_counter(uchar **input, int test_n, bool file_type, FILE *data_i, int number, int arr_length);
void all_1(uchar **input, FILE *data_i, bool file_type, int number, int arr_length);
void all_0(uchar **input, FILE *data_i, bool file_type,int number, int arr_length);
void random_repeat_long(uchar **input, const uchar *rnd,FILE *data_i,  bool file_type, int number, int arr_length);
void random_input(uchar **input, const uchar **rnd,FILE *data_i, bool file_type, int number, int arr_length);

void random_repeat_short(uchar **input, FILE *data_i, int rand_num, bool file_type);
void balance_counter(uchar **input, FILE *data_i, int test_n,bool file_type,int total_blk);

void equal_input(uchar **input, FILE *data_i, bool file_type);
void complex_count(uchar **input, int test_n, FILE *data_i,bool file_type,uint *random);
void count(uchar **input, int test_n, FILE *data_i, bool file_type);
void perodic_input(uchar **input, FILE *data_i,int index,bool file_type);


#endif
