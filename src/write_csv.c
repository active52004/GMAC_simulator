#include "../include/write_csv.h"

void write_csv_2array(FILE *dst, int number, int length, uchar **array)
{
	for(int i=0;i<number;i++)
    {
        
        for(int j=0;j<length;j++)
        {
            fprintf(dst,"%d,",((*((uchar*)array + i * length +j))>>7)&0x01);
            // printf("%d",((*((uchar*)data + i * length +j))>>7)&0x01);
            fprintf(dst,"%d,",((*((uchar*)array + i * length +j))>>6)&0x01);
            //printf("%d",((*((uchar*)data + i * length +j))>>6)&0x01);
            fprintf(dst,"%d,",((*((uchar*)array + i * length +j))>>5)&0x01);
            //printf("%d",((*((uchar*)data + i * length +j))>>5)&0x01);
            fprintf(dst,"%d,",((*((uchar*)array + i * length +j))>>4)&0x01);
            //printf("%d",((*((uchar*)data + i * length +j))>>4)&0x01);
            fprintf(dst,"%d,",((*((uchar*)array + i * length +j))>>3)&0x01);
            //printf("%d",((*((uchar*)data + i * length +j))>>3)&0x01);
            fprintf(dst,"%d,",((*((uchar*)array + i * length +j))>>2)&0x01);
            // printf("%d",((*((uchar*)data + i * length +j))>>2)&0x01);
            fprintf(dst,"%d,",((*((uchar*)array + i * length +j))>>1)&0x01);
            // printf("%d",((*((uchar*)data + i * length +j))>>1)&0x01);
            
            if((i == number-1)&&(j==length-1))
            {
                fprintf(dst,"%d",(*((uchar*)array + i * length +j))&0x01);
                //printf("%d",(*((uchar*)data + i * length +j))&0x01);
            }
            else
            {
                fprintf(dst,"%d,",(*((uchar*)array + i * length +j))&0x01);
                //printf("%d",(*((uchar*)data + i * length +j))&0x01);
            }
            //printf(" ");
            
        }
        
    }
    fprintf(dst, "\n");
}
   
void write_csv_2array2(FILE *dst, int num, int len, uchar *array)
{
	int length=0;
    uchar *out_p = array;
    while (length < len*num) {
        //printf("length is %d\n",length);
        for(int i=0;i<len;i++)
        {
            fprintf(dst,"%d,",(out_p[i]>>7)&0x01);
            fprintf(dst,"%d,",(out_p[i]>>6)&0x01);
            fprintf(dst,"%d,",(out_p[i]>>5)&0x01);
            fprintf(dst,"%d,",(out_p[i]>>4)&0x01);
            fprintf(dst,"%d,",(out_p[i]>>3)&0x01);
            fprintf(dst,"%d,",(out_p[i]>>2)&0x01);
            fprintf(dst,"%d,",(out_p[i]>>1)&0x01);
            if(length==(num-1)*len && i==len-1)
            {
                fprintf(dst,"%d",out_p[i]&0x01);
            }
            else
            {
                fprintf(dst,"%d,",out_p[i]&0x01);
            }
            
        }
        
        length += len;
        out_p += len;
    }
    fprintf(dst, "\n");
}
void write_csv_1array(FILE *dst, int length, uchar *array)
{
	for(int i=0;i<length;i++)
    {
        fprintf(dst,"%d,",(array[i]>>7)&0x01);
        fprintf(dst,"%d,",(array[i]>>6)&0x01);
        fprintf(dst,"%d,",(array[i]>>5)&0x01);
        fprintf(dst,"%d,",(array[i]>>4)&0x01);
        fprintf(dst,"%d,",(array[i]>>3)&0x01);
        fprintf(dst,"%d,",(array[i]>>2)&0x01);
        fprintf(dst,"%d,",(array[i]>>1)&0x01);
        if(i==length-1)
        {
            fprintf(dst,"%d",array[i]&0x01);
        }
        else
        {
            fprintf(dst,"%d,",array[i]&0x01);
        }
        
    }
    fprintf(dst, "\n");

}
