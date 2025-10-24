
#ifndef BYTEARRAY_COMMON_H
#define BYTEARRAY_COMMON_H

#ifndef _BOOL_DEFINED
    typedef  unsigned char      bool;
    #define _BOOL_DEFINED
#endif

struct bytearray_s
{
    bool     static_buffer;
    unsigned size;
    unsigned reserved;
    void    *bytes;
};

typedef struct bytearray_s bytearray_t;


#endif // BYTEARRAY_COMMON_H

