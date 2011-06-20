.section .startup, "ax"
.global _start

SYSTEM_MODE   EQU  0x10
_start:
    ///
    /// Set system mode
    ///
    mov r0,#SYSTEM_MODE
    msr cpsr,r0

    ///
    /// Initialize stack
    ///
    ldr sp, =__stack_end__
    mov fp,sp

    ///
    /// Run target configuration
    ///
    bl target_config

    ///
    /// Initialize BSS
    ///
    ldr r0, =__bss_end__
    ldr r1,= __bss_start__

iniciar_bss:
    mov r2,#0
    cmp r1,r0
    beq ctors
    str r2,[r1],#2
    b iniciar_bss

    ///
    /// Call global instances ctors
    ///
ctors:
    ldr r0,=__ctors_init__
    ldr r1,=__ctors_end__
    bl init_constructors

    ///
    /// Call system main
    ///
callMain:
    bl system_main
    b .


.section .stack
.space 1024


