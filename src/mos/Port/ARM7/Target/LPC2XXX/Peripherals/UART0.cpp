/*
 * UART0.cpp
 *
 *  Created on: 21 de Jun de 2011
 *      Author: Sorcha
 */

#include "UART0.h"
#include "LPC2xxx.h"
#include "System.h"

#define BAUD 115200
#define UART0_Receiver_Pin 1
#define UART0_Transmiter_Pin 0
#define UART0_Pin 0x1
#define UART_RDA_INTERRUPT_MASK (0x1<<RDA)
#define RDR 0
#define THRE 5
#define DLAB 7
#define WORD 0
#define RDA 0
#define STOPBIT 2
#define LSR_RDR_MASK (0x1<<RDR);
#define LSR_THRE_MASK (0x1<<THRE)
#define LCR_WORD_MASK ((0x3)<<WORD)
#define LCR_STOPBIT_MASK (0<<STOPBIT)
#define DLL 179
#define DLM 0
#define MUL 11
#define DIV 1





UART0::UART0(PinConnectBlock& p)
	:
	_uart0((LPC22xx_UART0)UART0_BASE_ADDRESS),
	_uartIrq(INTERRUPT_ENTRY_UART0,NULL,this)
{

	_uartIrq.SetEpilogueForIsr((IsrComplete)UART0::OnUartIsrComplete);
	p.pinSelect(UART0_Receiver_Pin,UART0_Pin );
	p.pinSelect(UART0_Transmiter_Pin, UART0_Pin);

	_uart0->U0LCR = (1<<DLAB);
	_uart0->U0FDR = (DIV) |(MUL << 4);
	_uart0->U0Base.U0DLL = DLL;
	_uart0->U0Base2.U0DLM = DLM;
	_uart0->U0LCR = (0<<DLAB) | LCR_WORD_MASK | LCR_STOPBIT_MASK;

	///
	///	enable receive interrupts.
	///
	_uart0->U0Base2.U0IER = UART_RDA_INTERRUPT_MASK;

}


U32 UART0::CanWrite()
{

	return _uart0->U0LSR & LSR_THRE_MASK;
}
U32 UART0::CanRead()
{
	return _uart0->U0LSR & LSR_RDR_MASK;
}

U8* UART0::ReadString(U8 * string, U32 length)
{
	U32 idx=0;
	for(;idx < length; idx++)
	{
		ReadChar();
	}
	return 0;
}

U32 UART0::ReadInt()
{
	return 0;
}

U8 UART0::ReadChar()
{
	while(!CanRead());
	return _uart0->U0Base.U0RBR & 0xFF;
}

void UART0::WriteString(const U8 * string, U32 length)
{

}
void UART0::WriteInt(U32 number)
{

}
void UART0::WriteChar(U8 character)
{

	while(!CanWrite());
	_uart0->U0Base.U0THR = character & 0xFF;

}

void UART0::Write(U8 data)
{
	WriteChar(data);
}

void UART0::OnUartIsrComplete(InterruptArgs* irq,UART0* uart)
{
	uart->_uart0->U0Base3.U0IIR;
	DebugAssertEquals(0,status&1);
	uart->ReadChar();
}
