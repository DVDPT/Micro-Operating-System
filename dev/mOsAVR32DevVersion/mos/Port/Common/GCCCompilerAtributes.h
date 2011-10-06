/*
 * GCCCompilerAtributes.h
 *
 *  Created on: 9 de Jun de 2011
 *      Author: DVD
 */

#pragma once

#define INLINE inline
#define NOINLINE __attribute__((noinline))
#define FASTCALL __attribute__((fastcall))
#define NAKED __attribute__((naked))
#define SECTION(sec) __attribute__ ((section (sec)))
#define ASM_VOLATILE __asm__ volatile
