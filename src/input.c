//
//  input.c
//  CETD-internal
//
//  Created by Duke on 12/09/13.
//  Copyright (c) 2013 Duke. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>//define CHAR_BIT
#include "../include/input.h"
#include "../include/write_txt.h"
#include "../include/write_csv.h"

#define PERIODIC 10

#define LC_BOUND 8192

/*
 *counter with same per of 0 and 1
blk1:128 , ..., blkn:128
blk1-1(0|1|2|3|4|5|6|7),...,blk1-n(0|1|2|3|4|5|6|7)
...
blkm-1(8*m-1|8*m-1 + 1|...),...
 * */
void linear_counter(uchar **input, int test_n, bool file_type, FILE *data_i, int number, int arr_length)
{
	uint a = test_n%LC_BOUND;	
	uint b=8*a;

	uchar tmp_arr[arr_length];
	for(int i=0;i<sizeof(tmp_arr);i++)
	{
		tmp_arr[i]=0;
	}

	int size =0;
	while(size+1< arr_length)
	{
		tmp_arr[size]= b & 0xFF;
		tmp_arr[size+1]= (b >> CHAR_BIT) & 0xFF;
		size +=2;
		b++;
	}
	
	for(int i=0;i<number;i++)
	{
		for(int j=0;j<arr_length;j++)
		{
			*(*(input+i)+j)=tmp_arr[j];
		}
	}

	if(file_type==TXT_file){
		write_txt_2array(data_i,number,arr_length,input);
	}
	else
	{
		write_csv_2array(data_i,number,arr_length,input);
	}

	
}


void all_0(uchar **input, FILE *data_i, bool file_type, int number, int arr_length)
{
	for(int i=0;i<number;i++)
	{
		for(int j=0;j<arr_length;j++)	
		{
			*(*(input+i)+j) = 0;
		}
	}

	if(file_type==TXT_file){
		write_txt_2array(data_i,number,arr_length,input);
	}
	else
	{
		write_csv_2array(data_i,number,arr_length,input);
	}

}

void all_1(uchar **input, FILE *data_i, bool file_type, int number, int arr_length)
{
	for(int i=0;i<number;i++)
	{
		for(int j=0;j<arr_length;j++)	
		{
			*(*(input+i)+j) = 0xFF;
		}
	}

	if(file_type==TXT_file){
		write_txt_2array(data_i,number,arr_length,input);
	}
	else
	{
		write_csv_2array(data_i,number,arr_length,input);
	}

}



void random_repeat_long(uchar **input, const uchar *rnd,FILE *data_i,  bool file_type, int number, int arr_length)
{
	for(int i=0;i<number;i++)
	{
		for(int j=0;j<arr_length;j++)
		{
			*(*(input+i)+j) = rnd[j];
		}
	}

	if(file_type==TXT_file){
		write_txt_2array(data_i,number,arr_length,input);
	}
	else
	{
		write_csv_2array(data_i,number,arr_length,input);
	}

}

void random_input(uchar **input, const uchar **rnd,FILE *data_i, bool file_type, int number, int arr_length)
{
    for(int i=0;i<number;i++)
    {
        for(int j=0;j<arr_length;j++)
        {
            *(*(input+i)+j)=rnd[i][j];
        }
    }

    if(file_type==TXT_file){
		write_txt_2array(data_i,number,arr_length,input);
	}
	else
	{
		write_csv_2array(data_i,number,arr_length,input);
	}


}
//
void random_repeat_short(uchar **input, FILE *data_i, int rand_num, bool file_type)
{
	uchar *out_p=input;
	
	for(int i=0;i<BLK_NUMBER;i++)
	{
		int tmp = rand_num;
		int j=0;
        while (tmp!=0) {
            *(out_p+j)=(uchar) (tmp  & 0xFF );
            j++;
            tmp = tmp >> CHAR_BIT;    
     	}
		out_p+=BLK_LENGTH;
	}	

	if(file_type==TXT_file){
		write_txt_2array(data_i,BLK_NUMBER,BLK_LENGTH,input);
	}
	else
	{
		write_csv_2array(data_i,BLK_NUMBER,BLK_LENGTH,input);
	}

}
void balance_counter(uchar **input, FILE *data_i, int test_n,bool file_type,int total_blk)
{
		
        int a=test_n%total_blk;
		int size=0;
		int b=8*a;

		while(size < BLK_NUMBER)
		{
			uchar *out_p=(uchar*)input+size*BLK_LENGTH;
			int length=0;
	 		while (length < BLK_LENGTH) {
				int tmp=b;
                int j=0;
        		while (tmp!=0) {
            		*(out_p+j)=(uchar) (tmp  & 0xFF );
            		j++;
            		tmp = tmp >> CHAR_BIT;    
     		   }
        		length += BLK_LENGTH/2;
        		out_p += BLK_LENGTH/2;
				b++;
    		}
			size++;	
		}
	 
	if(file_type==TXT_file){
		write_txt_2array(data_i,BLK_NUMBER,BLK_LENGTH,input);
	}
	else
	{
		write_csv_2array(data_i,BLK_NUMBER,BLK_LENGTH,input);
	}


}
/*
 p[i] = rand(i)+test_n,
 */
void count(uchar **input, int test_n, FILE *data_i, bool file_type)
{
    int start[BLK_NUMBER];
    for(int i=0;i<BLK_NUMBER;i++)
    {
        start[i]=rand();
    }
    uchar *tmp;
    tmp=(uchar *)malloc(sizeof(uchar)*BLK_LENGTH*BLK_NUMBER);
    
    memset(tmp, 0, BLK_LENGTH*BLK_NUMBER);
    
    // P[i] = rand+counter, 1<=i<=blk_number

        //int a=start[i]+test_n;
        //printf("a is %x\n",a);
        int a=test_n;
        int j=0;
        while (a!=0) {
            tmp[j] = (uchar) (a  & 0xFF );
            j++;
            a = a >> CHAR_BIT;
        }
   
    uchar *p1;
    p1=tmp;
    int length = 0;
    //printf("input of gmac\n");
    while (length<BLK_LENGTH*BLK_NUMBER) {
        for(int i=0;i<BLK_LENGTH;i++)
        {
            *((uchar*)input + length +i)=p1[i];
            //printf("%x ",p1[i]);
        }
        length += BLK_LENGTH;
        p1+=BLK_LENGTH;
        //printf("\n");
        
    }


   	if(file_type==TXT_file){
		write_txt_2array(data_i,BLK_NUMBER,BLK_LENGTH,input);
	}
	else
	{
		write_csv_2array(data_i,BLK_NUMBER,BLK_LENGTH,input);
	}

}
/*
 *counter with a random number as base
 * */
void complex_count(uchar **input, int test_n, FILE *data_i,bool file_type,uint *random)
{
    uchar *tmp;
    tmp=(uchar *)malloc(sizeof(uchar)*BLK_LENGTH*BLK_NUMBER);
    
    memset(tmp, 0, BLK_LENGTH*BLK_NUMBER);
    
        
    int length=0;
    uchar *out_p ;
    out_p=tmp;
    int index=0;
    
    //printf("store value into tmp");
    while (length < BLK_LENGTH*BLK_NUMBER) {
        //printf("length is %d\n",length);
        int a=test_n+random[index];
        //printf("%x,%x,%d\n",a,random[index],index);
        int j=0;
        while (a!=0) {
            *(out_p+j)=(uchar) (a  & 0xFF );
            //printf("%x",*(out_p+j));
            j++;
            a = a >> CHAR_BIT;
            
        }
        //printf(",\n");
        length += BLK_LENGTH;
        out_p += BLK_LENGTH;
        index++;
    }
    //printf("\n");
    
    uchar *p1;
    p1=tmp;
    length = 0;
    //printf("input of gmac\n");
    while (length<BLK_LENGTH*BLK_NUMBER) {
        for(int i=0;i<BLK_LENGTH;i++)
        {
            *((uchar*)input + length +i)=p1[i];
            //printf("%x",p1[i]);
        }
        length += BLK_LENGTH;
        p1+=BLK_LENGTH;
        //printf(" ");
        
    }
    //printf("\n");

   	/*
	 *store data to txt files
	 * */
	if(file_type==TXT_file){
		write_txt_2array(data_i,BLK_NUMBER,BLK_LENGTH,input);
	}
	else
	{
		write_csv_2array(data_i,BLK_NUMBER,BLK_LENGTH,input);
	}
	
	
}
void equal_input(uchar **input, FILE *data_i, bool file_type)
{
    
    
    uchar *tmp;
    tmp=(uchar *)malloc(sizeof(uchar)*BLK_LENGTH);
    
    memset(tmp, 0, BLK_LENGTH);
    
    for(int j=0;j<BLK_LENGTH;j++)
    {
        tmp[j]=(uchar) rand()%256;
    }

    
    for(int i=0;i<BLK_NUMBER;i++)
    {
        for(int j=0;j<BLK_LENGTH;j++)
        {
            (*((uchar*)input + i * BLK_LENGTH +j))=tmp[j];
        }
    } 

    if(file_type==TXT_file){
		write_txt_2array(data_i,BLK_NUMBER,BLK_LENGTH,input);
	}
	else
	{
		write_csv_2array(data_i,BLK_NUMBER,BLK_LENGTH,input);
	}


       //for(int i=0;i<BLK_NUMBER;i++)
    //{
    //     show((uchar*)original_data + i * BLK_LENGTH,BLK_LENGTH);
    //  }
    free(tmp);

}

void perodic_input(uchar **input, FILE *data_i,int index,bool file_type)
{
    uchar *tmp;
    tmp=(uchar *)malloc(sizeof(uchar)*BLK_LENGTH);
    
    memset(tmp, 0, BLK_LENGTH);
    
    for(int j=0;j<BLK_LENGTH;j++)
    {
        tmp[j]=(uchar) rand()%256;
    }

    if(index%PERIODIC==0)//the remainder of index/Per ==0
    {
        for(int i=0;i<BLK_NUMBER;i++)
        {
            for(int j=0;j<BLK_LENGTH;j++)
            {
                (*((uchar*)input + i * BLK_LENGTH +j))=tmp[j];
            }
        }
    }
    else
    {
        for(int i=0;i<BLK_NUMBER;i++)
        {
            for(int j=0;j<BLK_LENGTH;j++)
            {
                (*((uchar*)input + i * BLK_LENGTH +j))=(uchar) rand()%256;
            }
        }

    }

	if(file_type==TXT_file){
		write_txt_2array(data_i,BLK_NUMBER,BLK_LENGTH,input);
	}
	else
	{
		write_csv_2array(data_i,BLK_NUMBER,BLK_LENGTH,input);
	}


        //for(int i=0;i<BLK_NUMBER;i++)
    //{
    //     show((uchar*)original_data + i * BLK_LENGTH,BLK_LENGTH);
    //  }
    free(tmp);
}
