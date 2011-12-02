#pragma once

#include "UC3InterruptController.h"
#include "UC3Timer.h"
#define INTC_ADDRESS (0xFFFF0800)
#define TC0_ADDRESS (0xffff3800)

#define INTC ((UC3InterruptController*)(INTC_ADDRESS))
#define TC0 ((UC3Timer*)TC0_ADDRESS)