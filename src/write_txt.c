#include "../include/write_txt.h"
void write_txt_2array(FILE *dst, int number, int length, const uchar **array)
{

	int b;
	for(int i=0;i<number;i++)
    {
        
        for(int j=0;j<length;j++)
        {
			b=array[i][j];
            fprintf(dst,"%d\n",(b>>7)&0x01);
//             printf("%d",(b>>7)&0x01);
            fprintf(dst,"%d\n",(b>>6)&0x01);
  //          printf("%d",(b>>6)&0x01);
            fprintf(dst,"%d\n",(b>>5)&0x01);
    //        printf("%d",(b>>5)&0x01);
            fprintf(dst,"%d\n",(b>>4)&0x01);
      //      printf("%d",(b>>4)&0x01);
            fprintf(dst,"%d\n",(b>>3)&0x01);
        //    printf("%d",(b>>3)&0x01);
            fprintf(dst,"%d\n",(b>>2)&0x01);
          //   printf("%d",(b>>2)&0x01);
            fprintf(dst,"%d\n",(b>>1)&0x01);
            // printf("%d",(b>>1)&0x01);
            
           if((i==number-1)&&(j==length-1))
		   {
		        fprintf(dst,"%d",b&0x01);
   	
		   }
		   else
		   {
	            fprintf(dst,"%d\n",b&0x01);
	   	
		   }

             //   printf("%d",b&0x01);
            //printf(" ");
            
        }
        
    }
    fprintf(dst, "\n");
	//printf("\n");
}

void write_txt_1array(FILE *dst,  int length, const uchar *array)
{
	for(int i=0;i<length;i++)
    {
		int b= array[i];
        fprintf(dst,"%d\n",(b>>7)&0x01);
        fprintf(dst,"%d\n",(b>>6)&0x01);
        fprintf(dst,"%d\n",(b>>5)&0x01);
        fprintf(dst,"%d\n",(b>>4)&0x01);
        fprintf(dst,"%d\n",(b>>3)&0x01);
        fprintf(dst,"%d\n",(b>>2)&0x01);
        fprintf(dst,"%d\n",(b>>1)&0x01);
 		if(i==length-1)
        {
            fprintf(dst,"%d",b&0x01);
        }
        else
        {
            fprintf(dst,"%d\n",b&0x01);
        }
       
        
    }
    fprintf(dst, "\n");

}
void write_txt_2array2(FILE *dst, int num, int len, const uchar *array)
{
	int length=0;
    uchar *out_p = array;
    while (length < len*num) {
        //printf("length is %d\n",length);
        for(int i=0;i<len;i++)
        {
            fprintf(dst,"%d\n",(out_p[i]>>7)&0x01);
            fprintf(dst,"%d\n",(out_p[i]>>6)&0x01);
            fprintf(dst,"%d\n",(out_p[i]>>5)&0x01);
            fprintf(dst,"%d\n",(out_p[i]>>4)&0x01);
            fprintf(dst,"%d\n",(out_p[i]>>3)&0x01);
            fprintf(dst,"%d\n",(out_p[i]>>2)&0x01);
            fprintf(dst,"%d\n",(out_p[i]>>1)&0x01);
            if(length==(num-1)*len && i==len-1)
            {
                fprintf(dst,"%d",out_p[i]&0x01);
            }
            else
            {
                fprintf(dst,"%d\n",out_p[i]&0x01);
            }
            
        }
        
        length += len;
        out_p += len;
    }
    fprintf(dst, "\n");
}

