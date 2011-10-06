#pragma once




#define PORT_SPECIFIC

///
///	All the critical, most used functions are marked with this annotation
///	so that the user can reallocate the code to fastest sections.
///
#define CRITICAL_OPERATION SECTION(".internalmem")



typedef void* Void_P;

typedef unsigned long long U64;
typedef unsigned long long* U64_P;

typedef long long S64;
typedef long long* S64_P;

typedef unsigned int U32;
typedef unsigned int* U32_P;

typedef  int  S32;
typedef  int* S32_P;

typedef unsigned short U16;
typedef unsigned short* U16_P;


typedef short S16;
typedef short* S16_P;

typedef unsigned char U8;
typedef unsigned char* U8_P;

typedef char  S8;
typedef char* S8_P;

#define NULL (0)



#include "PortConfig.h"
