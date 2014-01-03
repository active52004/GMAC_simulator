//
//  config.h
//  GCM
//
//  Created by Duke on 25/10/12.
//  Copyright (c) 2012 Duke. All rights reserved.
//

#ifndef GCM_config_h
#define GCM_config_h
#include <stdio.h>
#include <stdbool.h>
#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int

#define BLK_NUMBER 1
#define BLK_LENGTH 16
#define CSV_file false
#define TXT_file true

#define TAG_LENGTH 4
/**
 * \def POLARSSL_AES_C
 *
 * Enable the AES block cipher.
 *
 * Module:  library/aes.c
 * Caller:  library/ssl_tls.c
 *          library/pem.c
 *          library/ctr_drbg.c
 *
 * This module enables the following ciphersuites (if other requisites are
 * enabled as well):
 *      TLS_RSA_WITH_AES_128_CBC_SHA
 *      TLS_RSA_WITH_AES_256_CBC_SHA
 *      TLS_DHE_RSA_WITH_AES_128_CBC_SHA
 *      TLS_DHE_RSA_WITH_AES_256_CBC_SHA
 *      TLS_RSA_WITH_AES_128_CBC_SHA256
 *      TLS_RSA_WITH_AES_256_CBC_SHA256
 *      TLS_DHE_RSA_WITH_AES_128_CBC_SHA256
 *      TLS_DHE_RSA_WITH_AES_256_CBC_SHA256
 *      TLS_RSA_WITH_AES_128_GCM_SHA256
 *      TLS_RSA_WITH_AES_256_GCM_SHA384
 *
 * PEM uses AES for decrypting encrypted keys.
 */
#define POLARSSL_AES_C
/**
 * \def POLARSSL_PADLOCK_C
 *
 * Enable VIA Padlock support on x86.
 *
 * Module:  library/padlock.c
 * Caller:  library/aes.c
 *
 * This modules adds support for the VIA PadLock on x86.
 */
#define POLARSSL_PADLOCK_C
/**
 * \def POLARSSL_GCM_C
 *
 * Enable the Galois/Counter Mode (GCM) for AES
 *
 * Module:  library/gcm.c
 *
 * Requires: POLARSSL_AES_C
 *
 * This module enables the following ciphersuites (if other requisites are
 * enabled as well):
 *      TLS_RSA_WITH_AES_128_GCM_SHA256
 *      TLS_RSA_WITH_AES_256_GCM_SHA384
 */
#define POLARSSL_GCM_C
/**
 * \def POLARSSL_SELF_TEST
 *
 * Enable the checkup functions (*_self_test).
 */
#define POLARSSL_SELF_TEST


#endif
