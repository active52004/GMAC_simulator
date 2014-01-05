//
//  main.c
//  32 bits tag generation
//  CETD, GMAC
//  input data is stored in array
//  Created by Duke on 24/09/12.
//  Copyright (c) 2012 Duke. All rights reserved.
//  better to generate nonce bit by bit
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <math.h>
//public API
#include "../include/show.h"
#include "../include/input.h"
#include "../include/config.h"
#include "../include/aes.h"
#include "../include/cipher.h"
#include "../include/write_txt.h"
#include "../include/write_csv.h"
//GMAC API
#include "../include/gcm.h"
#include "../include/GMAC.h"


#define data_dir "../NIST_suite/long/p%d.csv"
#define ciphertext_dir "../NIST_suite/long/c%d.csv"

#define data_dir_txt "../NIST_suite/long/p%d.txt"
#define ciphertext_dir_txt "../NIST_suite/long/c%d.txt"

//#define iv_dir "/Users/duke/Documents/Research_work/tag_result/Rare_data/scheme_compare/gmac/iv%d.csv"

int main()
{
    
	/*
	 * txt files
	 * */
	FILE *fp_plaintext_txt;
	fp_plaintext_txt=NULL;
	char filename_plain_txt[256];

	FILE *fp_cipher_txt;
	fp_cipher_txt=NULL;
	char filename_cipher_txt[256];
	//

	//GMAC files
	/*
	FILE *fp_iv_GMAC_txt;
	fp_iv_GMAC_txt = NULL;
	char filename_iv_GMAC_txt[256];
*/
	FILE *fp_y_txt[GMAC_BLK_NUMBER];
	for(int i=0;i<GMAC_BLK_NUMBER;i++)
	{
		fp_y_txt[i]=NULL;
	}
	char y_name_txt[GMAC_BLK_NUMBER][256];

	FILE *fp_B_GMAC_txt;
	fp_B_GMAC_txt = NULL;
	char filename_B_GMAC_txt[256];

    FILE *fp_tag_GMAC_txt;//tag
    fp_tag_GMAC_txt=NULL;
    char filename_tag_GMAC_txt[256];

	//control paremeter
    int test_count;//number of test
    printf("input the test number\n");
    scanf("%d",&test_count);
    
    int n;//number of tags per test
    printf("input the number of tags\n");
    scanf("%d",&n);
    
    srand((int)time(0));
    
    /**
     Generate input sequences to NIST test, the No. of sequences is test_count
     **/
    for(int test_round=0;test_round<test_count;test_round++)
    {
        
      
        
        /**
         1 key per sequence,randomly generated
         **/
        uchar *AES_key;
        AES_key = (uchar *)malloc(sizeof(uchar)*16);
        memset(AES_key, 0, 16);
        //show(AES_key, 16);
        
        for(int i=0;i<16;i++)
        {
            *(AES_key+i)= (uchar) (rand()%256);
        }
		//
        //set aes key for all the block cipehr
		gcm_context gcm_ctx;
		gcm_init(&gcm_ctx,AES_key,128);

		/*
		 *set filenames for txt files
		 * */
		sprintf(filename_plain_txt,data_dir_txt,test_round+1);
		fp_plaintext_txt=fopen(filename_plain_txt,"w");
                
        sprintf(filename_cipher_txt, ciphertext_dir_txt,test_round+1);
        fp_cipher_txt=fopen(filename_cipher_txt, "w");
        
		//GMAC FILES
        sprintf(filename_B_GMAC_txt,B_dir_txt ,test_round+1);
        fp_B_GMAC_txt=fopen(filename_B_GMAC_txt, "w");
        
		for(int i=0;i<GMAC_BLK_NUMBER;i++)
		{
			sprintf((char*)y_name_txt + i * 256,y_dir_split_txt,test_round+1,i+1);
			fp_y_txt[i]=fopen((char*)y_name_txt + i * 256,"w");
		}

		        
        sprintf(filename_tag_GMAC_txt, tag_GMAC_dir_txt,test_round+1);
        fp_tag_GMAC_txt=fopen(filename_tag_GMAC_txt, "w");
        
        /**
         Each sequence require several blocks, the No. of blocks is n.
         **/

       		uchar *rnd2;
		   rnd2 = (uchar *)malloc(sizeof(uchar)*BLK_LENGTH);
		   memset(rnd2,0,BLK_NUMBER);

		   for(int i=0;i<BLK_LENGTH;i++)
		   {
				rnd2[i]=(uchar) (rand()%256);
		   }


        for(int test_n=0;test_n<n;test_n++)
        {
			/*
			 * Construct the plaintxt block sequence
			 * */

            //original_data=plaintext
            uchar **original_data;
            original_data=(uchar **)malloc(sizeof(uchar *)*BLK_NUMBER);
            for(int i=0;i<BLK_NUMBER;i++)
            {
                original_data[i]=(uchar *)malloc(sizeof(uchar)*BLK_LENGTH);
                
                memset(original_data[i], 0, BLK_LENGTH);
            }

// 	 all_1(original_data, fp_plaintext_txt, TXT_file, BLK_NUMBER, BLK_LENGTH);
//		all_0(original_data,fp_plaintext_txt,TXT_file, BLK_NUMBER, BLK_LENGTH);

//	linear_counter(original_data,  test_n, TXT_file, fp_plaintext_txt,BLK_NUMBER , BLK_LENGTH);
			random_repeat_long(original_data, rnd2,fp_plaintext_txt, TXT_file, BLK_NUMBER, BLK_LENGTH);

			uchar **rnd3;
			rnd3=(uchar **)malloc(sizeof(uchar *)*BLK_NUMBER);
            for(int i=0;i<BLK_NUMBER;i++)
            {
                rnd3[i]=(uchar *)malloc(sizeof(uchar)*BLK_LENGTH);
                memset(rnd3[i], 0, BLK_LENGTH);
            }
            
			for(int i=0;i<BLK_NUMBER;i++)
    		{
        		for(int j=0;j<BLK_LENGTH;j++)
        		{
            		*(*(rnd3+i)+j)=(uchar) (rand()%256);
        		}
    		}		

			/*
			random_input(original_data, rnd3,fp_plaintext_txt, TXT_file, BLK_NUMBER, BLK_LENGTH);
			*/
         	/*
			 *encrypting the plaintext
			 *construct the input block sequence for scheme
			 * */
   
            uchar **ciper_data;
            
            ciper_data=(uchar **)malloc(sizeof(uchar *)*BLK_NUMBER);
            for(int i=0;i<BLK_NUMBER;i++)
            {
                ciper_data[i]=(uchar *)malloc(sizeof(uchar)*BLK_LENGTH);
                
                memset(ciper_data[i], 0, BLK_LENGTH);
            }
            
            
		            //cipher_short(ctx,ciphertext, original_data,fp_cipher_txt,TXT_file);
            //perodic_cipher(ctx,ciphertext, original_data, fp_cipher_txt,test_n,TXT_file);

		 	only_plaintext(ciper_data, original_data, BLK_NUMBER,BLK_LENGTH, fp_cipher_txt,TXT_file);

            uchar *iv_gmac= (uchar *)malloc(sizeof(uchar)*IV_LENGTH);
			memset(iv_gmac, 0 , IV_LENGTH);
			for(int i=0;i<IV_LENGTH;i++)
			{
				*(iv_gmac+i) = (uchar) (rand()%256);
			}

 			GMAC_generator(ciper_data,
					iv_gmac, 
					&gcm_ctx, 
					fp_y_txt,
					fp_B_GMAC_txt , 
					fp_tag_GMAC_txt,
					TXT_file);

			free(iv_gmac);

			for(int i=0;i<BLK_NUMBER;i++)
			{
				free(rnd3[i]);
			}
			free(rnd3);
	

        }
        /**
         close the files to prepre for the next input sequence
         **/
        free(rnd2);
        free(AES_key);

		for(int i=0;i<BLK_NUMBER;i++)
		{
			fclose(fp_y_txt[i]);
		}
		fclose(fp_B_GMAC_txt);
		fclose(fp_tag_GMAC_txt);

		fclose(fp_plaintext_txt);
		fclose(fp_cipher_txt);
       
    }
     printf("finish \n");
    return 0;
    
}



