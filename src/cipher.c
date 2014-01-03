//
//  cipher.c
//  CETD-internal
//
//  Created by Duke on 13/09/13.
//  Copyright (c) 2013 Duke. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/cipher.h"
#include "../include/write_txt.h"
#include "../include/write_csv.h"

#define PERIODIC 20
/*
 *if the BLK_LENGTH=16, use this function as AES cipher
 * */
void cipher(aes_context ctx,uchar **dst, uchar ** src, FILE *cipher_o, bool file_type)
{
    /**
     Encrypt the plaintext and generate ciphertext
     **/
    for(int i=0;i<BLK_NUMBER;i++)
    {
        aes_crypt_ecb(&ctx, AES_ENCRYPT,(uchar*)src + i * BLK_LENGTH, (uchar*)dst + i * BLK_LENGTH);
    }
    
    /**
     Store Ciphertext
     **/
	if(file_type==TXT_file){
		write_txt_2array(cipher_o,BLK_NUMBER,BLK_LENGTH,dst);
	}
	else
	{
		write_csv_2array(cipher_o,BLK_NUMBER,BLK_LENGTH,dst);
	}

}

/*
 *if BLK_NUMBER*BLK_LENGTH=16, use this function as AES cipher
 * */
void cipher_short(aes_context ctx,uchar **dst, uchar ** src, FILE *cipher_o,bool file_type)
{
    int length=0;
    uchar *input;
    input=(uchar *)malloc(sizeof(uchar)*BLK_NUMBER*BLK_LENGTH);
    memset(input, 0, BLK_LENGTH*BLK_NUMBER);
    uchar *input_p=input;
    while (length<BLK_LENGTH*BLK_NUMBER) {
        for(int i=0;i<BLK_LENGTH;i++)
        {
            input_p[i]=*((uchar*)src + length +i);
        }
        length+=BLK_LENGTH;
        input_p+=length;
        
    }
    
    aes_crypt_ecb(&ctx, AES_ENCRYPT,input, input);
    
    length=0;
    input_p=input;
    while (length<BLK_LENGTH*BLK_NUMBER) {
        for(int i=0;i<BLK_LENGTH;i++)
        {
            *((uchar*)dst + length +i)=input_p[i];
            //printf("%x ",*((uchar*)dst + length +i));
        }
        length+=BLK_LENGTH;
        input_p+=BLK_LENGTH;
        //printf("\n");
    }

	if(file_type==TXT_file){
		write_txt_2array2(cipher_o,BLK_NUMBER,BLK_LENGTH,input);
	}
	else
	{
		write_csv_2array2(cipher_o,BLK_NUMBER,BLK_LENGTH,input);
	}


}

/*
 *
 * */
void perodic_cipher(aes_context ctx,uchar **dst, uchar ** src, FILE *cipher_o,int index,bool file_type)
{
    int length=0;
    uchar *input;
    input=(uchar *)malloc(sizeof(uchar)*BLK_NUMBER*BLK_LENGTH);
    memset(input, 0, BLK_LENGTH*BLK_NUMBER);
    uchar *input_p=input;
    while (length<BLK_LENGTH*BLK_NUMBER) {
        for(int i=0;i<BLK_LENGTH;i++)
        {
            input_p[i]=*((uchar*)src + length +i);
        }
        length+=BLK_LENGTH;
        input_p+=BLK_LENGTH;
        
    }
    if(index%PERIODIC != (PERIODIC/2)-1)//index/per==10*k
    {
        aes_crypt_ecb(&ctx, AES_ENCRYPT,input, input);
    }
    else
    {
        
    }
    
    length=0;
    input_p=input;
    while (length<BLK_LENGTH*BLK_NUMBER) {
        for(int i=0;i<BLK_LENGTH;i++)
        {
            *((uchar*)dst + length +i)=input_p[i];
            //printf("%x ",*((uchar*)dst + length +i));
        }
        length+=BLK_LENGTH;
        input_p+=BLK_LENGTH;
        //printf("\n");
    }
	if(file_type==TXT_file){
		write_txt_2array2(cipher_o,BLK_NUMBER,BLK_LENGTH,input);
	}
	else
	{
		write_csv_2array2(cipher_o,BLK_NUMBER,BLK_LENGTH,input);
	}

}

/*
 *do not encrypt the input plaintext
 * */
void only_plaintext(uchar **dst, const uchar **src, int number, int arr_length, FILE *cipher_o,bool file_type)
{
   for(int i=0;i<number;i++)
   {
	   for(int j=0;j<arr_length;j++)
	   {
		   *(*(dst+i)+j) = src[i][j];
	   }
   }
 	if(file_type==TXT_file){
		write_txt_2array(cipher_o,number,arr_length,dst);
	}
	else
	{
		write_csv_2array(cipher_o,number,arr_length,dst);
	}
       
}
