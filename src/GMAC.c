#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#include "../include/GMAC.h"
#include "../include/gcm.h"
#include "../include/write_txt.h"
#include "../include/write_csv.h"

void GMAC_generator(const uchar **input, uchar *iv, gcm_context *ctx, FILE *gmac_y[GMAC_BLK_NUMBER], FILE *gmac_b, FILE *gmac_tag,bool file_type)
{
	uchar *tmp_input;	
	tmp_input=(uchar *)malloc(sizeof(uchar)*GMAC_BLK_NUMBER*INPUT_LENGTH);
	memset(tmp_input, 0, GMAC_BLK_NUMBER*INPUT_LENGTH);

	for(int i=0;i<GMAC_BLK_NUMBER*INPUT_LENGTH;i++)
	{
		*(tmp_input+i)= input[i/INPUT_LENGTH][i%INPUT_LENGTH];
	}

	//Y blocks 
  	uchar *Y=(uchar *)malloc(sizeof(uchar)*GMAC_BLK_NUMBER*INPUT_LENGTH);    
   	memset(Y,0,sizeof(Y));

 	uchar *B=(uchar *)malloc(sizeof(uchar)*INPUT_LENGTH); 
	memset(B,0,sizeof(B));

	uchar *tag=(uchar *)malloc(sizeof(uchar)*TAG_LENGTH);
	memset(tag,0,sizeof(tag));

 	gcm_crypt_and_tag(ctx,GCM_ENCRYPT,
			GMAC_BLK_NUMBER*INPUT_LENGTH,
			iv,sizeof(iv),
			tmp_input,	
			Y,
			TAG_LENGTH,tag
			);
  
	for(int i=0;i<INPUT_LENGTH;i++)
	{
		B[i]=ctx->buf[i];
	}
	//Y blocks are stored at long array Y
	//B stores B block
	//Tag stores the tag
  /*
   split Y array to Y blocks and store in Y files
   */	
	uchar *i_p=Y;
	int j=0;
	while(j<GMAC_BLK_NUMBER)
	{
		if(file_type==TXT_file)
		{
			write_txt_1array(gmac_y[j],INPUT_LENGTH,i_p);
		}
		else
		{
			write_csv_1array(gmac_y[j],INPUT_LENGTH,i_p);
		}
		j++;
		i_p += INPUT_LENGTH;
	}

	if(file_type == TXT_file)
	{
		write_txt_1array(gmac_b,INPUT_LENGTH,B);
	}
	else 
	{
		write_csv_1array(gmac_b,INPUT_LENGTH,B);
	}

	if(file_type == TXT_file)
	{
		write_txt_1array(gmac_tag,TAG_LENGTH,tag);
	}
	else 
	{
		write_csv_1array(gmac_tag,TAG_LENGTH,tag);
	}

	free(Y);
	free(B);
	free(tag);
	free(tmp_input);
		
	
}
