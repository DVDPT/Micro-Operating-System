/*
 * Peripherals.cpp
 *
 *  Created on: Aug 5, 2011
 *      Author: DVD
 */

#include "Peripherals.h"

PeripheralContainer instance;

PeripheralContainer& PeripheralContainer::GetInstance(){return instance;}
