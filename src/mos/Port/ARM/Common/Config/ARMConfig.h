/*
 * ARMConfig.h
 *
 *  Created on: 9 de Jun de 2011
 *      Author: DVD
 */

#pragma once

#include "GCCCompilerAtributes.h"

///
///	On ARM FASTCALL makes no sense since the first 4 parameters are passed by register
///
#ifdef FASTCALL
#undef FASTCALL
#define FASTCALL
#endif
