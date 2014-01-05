#include "config.h"
#include "gcm.h"

/*
\param uchar **input    ciphertext blocks
\param uchar *iv        iv block
\param FILE *y
\param FILE *B
\param FILE *tag
\param bool file_type
*/
#define GMAC_BLK_NUMBER 1
#define IV_LENGTH 12
#define INPUT_LENGTH 16

//#define iv_dir "../NIST_suite/long/iv%d.csv"
#define B_dir "../NIST_suite/long/B%d.csv"
#define y_dir_split_csv "../NIST_suite/long/y%d-%d.csv"
#define tag_GMAC_dir "../NIST_suite/short/tag%d.csv"

#define B_dir_txt "../NIST_suite/long/B%d.txt"
//#define iv_dir_txt "../NIST_suite/long/iv%d.txt"
#define y_dir_split_txt "../NIST_suite/long/y%d-%d.txt"
#define tag_GMAC_dir_txt "../NIST_suite/short/tag%d.txt"


void GMAC_generator(const uchar **input, uchar *iv, gcm_context *ctx, FILE *gmac_y[GMAC_BLK_NUMBER], FILE *gmac_b, FILE *gmac_tag,bool file_type);
