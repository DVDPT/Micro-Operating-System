#include "ADC.h"

#define PIN_ADC1 28
#define PIN_CONNECT_ADC_MASK 1
#define CHANNEL_ADC 1
#define CHANNEL_MASK (0x1 << CHANNEL_ADC)
#define CLKDIV_MASK 8
#define BURST 0
#define BURST_MASK (BURST << 16)
#define CLKS 0
#define CLKS_MASK (CLKS << 17)
#define PDN 1
#define PDN_MASK (PDN << 21)
#define START 0
#define START_CONVERTION 1
#define START_POSITION 24
#define START_MASK (START << START_POSITION)
#define NUMBER_OF_BITS_START 0x7
#define EDGE 1
#define EDGE_MASK (EDGE << 27)
#define DONE_MASK  (1 << 31)
#define LENGTH_SAMPLE 0x3FF
#define RESULT 6
#define ENTRY_ADC_INTERRUPT 18
#define ADC_CHANNEL1_INTERRUPT_MASK (1<<CHANNEL_ADC)
#define ADC_OVERUN

ADC::ADC(PinConnectBlock& p ): _adc((LPC2xxxADC *) 0xE0034000)
{
	p.pinSelect(PIN_ADC1,PIN_CONNECT_ADC_MASK);
	_adc->ADCR = CHANNEL_MASK | BURST_MASK | CLKS_MASK | PDN_MASK | START_MASK | EDGE_MASK;

}


ADC::ADC(PinConnectBlock& p, U8 clock):_adc((LPC2xxxADC *) 0xE0034000)
{

	p.pinSelect(PIN_ADC1,PIN_CONNECT_ADC_MASK);
	_adc->ADCR = START_MASK;
	_adc->ADCR = CHANNEL_MASK | (clock << CLKDIV_MASK) | BURST_MASK | CLKS_MASK | PDN_MASK | START_MASK;

}



U16 ADC::GetSample()
{
	U32 aux=0;
	_adc->ADCR = Bits<U32>::ModifyBits(START_POSITION,START_CONVERTION,_adc->ADCR,NUMBER_OF_BITS_START);
	do{
		aux =_adc->ADDR[CHANNEL_ADC];
		if((aux & DONE_MASK))
			return  ((aux>> RESULT) & LENGTH_SAMPLE) - 512;
	}while(true);

}


