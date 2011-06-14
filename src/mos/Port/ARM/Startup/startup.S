.section .startup, "ax"
.global _start


_start:
    ldr sp, =__stack_end__
    mov fp,sp
    bl target_config
    ldr r0, =__bss_end__
    ldr r1,= __bss_start__

iniciar_bss:
    mov r2,#0
    cmp r1,r0
    beq ctors
    str r2,[r1],#2
    b iniciar_bss

ctors:
    ldr r0,=__ctors_init__
    ldr r1,=end
    bl init_constructors

callMain:
    bl system_main
    b .


.section .stack
.space 1024


