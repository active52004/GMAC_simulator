//
//  show.c
//  X_generation
//
//  Created by Duke on 5/07/13.
//  Copyright (c) 2013 Duke. All rights reserved.
//

#include <stdio.h>
#include "../include/show.h"
void show(const void *object, size_t size)
{
    const unsigned char *byte;
    for ( byte = object; size--; ++byte )
    {
        unsigned char mask;
        for ( mask = 1 << (CHAR_BIT - 1); mask; mask >>= 1 )
        {
            putchar(mask & *byte ? '1' : '0');
        }
        putchar(' ');
    }
    putchar('\n');
}
