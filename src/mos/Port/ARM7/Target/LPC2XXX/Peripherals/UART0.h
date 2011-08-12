/*
 * UART0.h
 *
 *  Created on: 21 de Jun de 2011
 *      Author: Sorcha
 */

#pragma once

#define INTERRUPT_ENTRY_UART0 6

#include "LPC2xxxTypes.h"
#include "PinConnectBlock.h"
#include "VectorInterruptController.h"
#include "TextOutputStream.h"

class UART0 : public TextOutputStream{
private:

	typedef struct _UART
	{
		union _U0Base
		{
			LPC2xxx_REG U0RBR;
			LPC2xxx_REG U0THR;
			LPC2xxx_REG U0DLL;
		}U0Base;
		union _U0Base2
		{
			LPC2xxx_REG U0DLM;
			LPC2xxx_REG U0IER;
		}U0Base2;
		union _U0Base3
		{
			LPC2xxx_REG U0IIR;
			LPC2xxx_REG U0FCR;
		}U0Base3;
		LPC2xxx_REG U0LCR;
		LPC2xxx_REG DUMMY;
		LPC2xxx_REG U0LSR;
		LPC2xxx_REG DUMMY1;
		LPC2xxx_REG U0SCR;
		LPC2xxx_REG U0ACR;
		LPC2xxx_REG DUMMY2;
		LPC2xxx_REG U0FDR;
		LPC2xxx_REG DUMMY3;
		LPC2xxx_REG U0TER;
	}*LPC22xx_UART0;

	LPC22xx_UART0 _uart0;

	U32 CanWrite();
	U32 CanRead();

public:
	UART0(PinConnectBlock& p);
	void ConfigureInterrupts(VectorInterruptController& vic);

	U8* ReadString(U8 * string, U32 length);
	U32 ReadInt();
	U8 ReadChar();

	void WriteString(const U8 * string, U32 length);
	void Write(U32 number);
	void WriteChar(U8 character);

	void Write(U8 data);

};


