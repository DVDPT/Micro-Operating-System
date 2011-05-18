#pragma once

#define INLINE _inline
#define NOINLINE __declspec(noinline)
#define FASTCALL __fastcall
#define NAKED __declspec(naked)

typedef void Void;
typedef void* Void_P;

typedef unsigned int U32;
typedef unsigned int* U32_P;

typedef  int  S32;
typedef  int* S32_P;

typedef unsigned char U8;
typedef unsigned char* U8_P;

typedef char  S8;
typedef char* S8_P;

#define NULL (0)

enum BOOL {TRUE=1,FALSE=0};