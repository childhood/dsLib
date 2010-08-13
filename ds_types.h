/* ds_types.h - sine memory management headers */

#ifndef __DS_TYPES_H
#define __DS_TYPES_H

#define TRUE 1
#define FALSE 0

typedef unsigned short MODULE_ID_T;
typedef void(*FUNCPTR_T)(void);
typedef float(*FUNCPTR1_T)(float, float);
typedef int (*FUNCPTR2_T)(int arg1, int arg2, int arg3);

typedef enum {DS_NO=1, DS_YES=2} TRUTH_E;
typedef enum {DS_FALSE=0, DS_TRUE=1} BOOL_E;

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
typedef enum {
   DS_ERR_ERROR_HIGH = -512, /* fencepost */
   DS_ERR_MALLOC_FAIL,
   DS_ERR_ERR = -1, /* generic operational error */
   DS_ERR_OK = 0 /* routine returned without any errors */
} DS_ERR_E;

#if __STDC_VERSION__ < 199901L
#define false 0
#define true 1
#endif /* __STDC_VERSION__ */

#endif
