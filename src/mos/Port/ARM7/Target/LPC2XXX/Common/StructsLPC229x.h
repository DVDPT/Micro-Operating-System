/*
 * StructsLPC2294.h
 *
 *  Created on: 17 de Mai de 2011
 *      Author: Sorcha
 */

#pragma once


typedef struct _ExternalMemoryController
{
	int BCFG0;
	int BCFG1;
	int BCFG2;
	int BCFG3;

}LPC22xx_ExternalMemoryController,*LPC22xxP_ExternalMemoryController;

typedef struct _GPIO
{
	int IOPIN;
	int IOSET;
	int IODIR;
	int IOCLR;

}LPC22xx_GPIO,*LPC22xxP_GPIO;





