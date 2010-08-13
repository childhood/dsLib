/* sine_mem.h - sine memory management headers */

#ifndef __SINE_TYPES_H
#define __SINE_TYPES_H

#define TRUE 1
#define FALSE 0

#define ERROR   -1
#define OK      0

typedef unsigned short MODULE_ID_T;
typedef void(*FUNCPTR_T)(void);
typedef float(*FUNCPTR1_T)(float, float);
typedef int (*FUNCPTR2_T)(int arg1, int arg2, int arg3);

typedef union
    {
    long idata;
    unsigned long uidata;
    char cdata;
    unsigned char ucdata;
    void* vpdata;
    FUNCPTR2_T fpdata;
    } NODE_DATA_T;

typedef enum {
    IDATA=0,
    UIDATA,
    CDATA,
    UCDATA,
    VPDATA,
    FPDATA,
    LDATA,
    LLDATA,
    ULDATA,
    ULLDATA
} NODE_DATA_TYPE_E;

typedef enum {INT, CHAR, ULONG, LONG, ULONGLONG, LONGLONG, VOIDP } ELE_T;

#if __STDC_VERSION__ < 199901L
#define false 0
#define true 1
#endif /* __STDC_VERSION__ */

#endif
