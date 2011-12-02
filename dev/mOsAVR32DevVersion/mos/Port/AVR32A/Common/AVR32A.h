#pragma once

typedef unsigned int U32;

///
///	OS related definitions
///
#define MOS_INTERRUPT_LEVEL_USED_MASK (0)

///
///	AVR32A architecture related definitions
///
#define AVR32_MODE_NMI (7)
#define AVR32_MODE_EXCEPTION (6)
#define AVR32_MODE_INTERRUPT_LEVEL_3 (5)
#define AVR32_MODE_INTERRUPT_LEVEL_2_MODE (4)
#define AVR32_MODE_INTERRUPT_LEVEL_1 (3)
#define AVR32_MODE_INTERRUPT_LEVEL_0 (2)
#define AVR32_MODE_SUPERVISOR (1)
#define AVR32_MODE_APPLICATION_MODE (0)


#define AVR32_STATUS_REGISTER_MODE_POSITION (22)

#define AVR32_SYSTEM_REGISTERS_ADDRESS_STATUS_REGISTER (0)

#define AVR32_STATUS_REGISTER_INTERRUPT_MASK_POSITION (17)
#define AVR32_STATUS_REGISTER_GLOBAL_INTERRUPT_MASK_POSITION (16)

#define AVR32_STATUS_REGISTER_DISABLE_GLOBAL_INTERRUPTS (1)
#define AVR32_STATUS_REGISTER_ENABLE_INTERRUPTS (0)

#define AVR32_MAX_INTERRUPT_MODE (3)

#define avr32_get_system_register(regAddr) __builtin_mfsr(regAddr)
#define avr32_set_system_register(regAddr, value) __builtin_mtsr(regAddr, value)


