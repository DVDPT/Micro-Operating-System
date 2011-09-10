.EQU SYSTEM_MODE,0xD3
.EQU IRQ_MODE, 0xD2
.EQU IRQ_MASK, 0x80
.EQU SIZE_OF_USER_MODE_STORED_REGISTERS_SIZE,(14*4)

.text
.global arm_common_trap,arm_enable_interrupt,arm_disable_interrupt,arm_is_intr_enable

arm_enable_interrupt:
    mrs     r1, CPSR
    bic     r1, r1, #IRQ_MASK
    msr     CPSR_c, r1
    bx lr



arm_disable_interrupt:
    mrs     r1, CPSR
    orr     r1, r1, #IRQ_MASK
    msr     CPSR_c, r1
    bx lr

arm_is_intr_enable:
    mrs r0,cpsr
    and r0,r0,#IRQ_MASK
    eor r0,r0,#IRQ_MASK
    bx lr


arm_common_trap:

    ///
    /// +============+
    /// |     r0     | -
    /// +------------+  |
    /// |     r1     |  |
    /// +------------+  |
    /// |     r2     |  |
    /// +------------+  |> User Mode Saved Registers
    /// |      :     |  |
    ///        :        |
    /// |      :     |  |
    /// +------------+  |
    /// |     lr     | / > User Mode stack pointer
    /// +============+
    /// |     pc     | -
    /// +------------+  |
    /// |    FLAGS   |  | > IRQ Mode Saved Registers, r0
    /// +------------+  |
    /// |            | /
    /// +------------+
    //


    ///
    /// Change back to system mode to store all registers.
    ///
    msr cpsr,#SYSTEM_MODE

    ///
    /// Leave space for the PC register stored in IRQ mode.
    ///
    push {r0}

    ///
    /// Save registers on user stack.
    ///
    push {r0-r12,lr}

    ///
    /// Set the sp addr on r0 to parameterize system call common trap.
    ///
    mov r0,sp

    ///
    /// Go back to irq mode
    ///
    msr cpsr,#IRQ_MODE

    ///
    /// PC (lr in IRQ MODE) is 1 instruction ahead, so put it in the correct position.
    ///
    sub lr,lr,#4

    ///
    /// Store the user PC on its stack (LR in IRQ MODE = PC before IRQ).
    ///
    str lr,[r0,#SIZE_OF_USER_MODE_STORED_REGISTERS_SIZE]

    ///
    /// Store flags.
    ///
    mrs r1,SPSR
    stmfd  r0!, {r1}

    ///
    /// Store r0 (aka stack pointer) in the IRQ stack.
    ///
    push {r0}

    ///
    /// Move to r0 the address stored previously, r0 = Context **.
    ///
    mov r0,sp

    ///
    /// Call system trap with Context pointer as first parameter.
    ///
    bl system_common_trap

    ///
    /// Retrieve User Stack Pointer (if context switch happened this value is different from the pushed value).
    ///
    pop {r0}


    ///
    /// Restore flags.
    ///
    ldmfd  r0!, {r1}
    msr cpsr,r1

    ///
    /// Set the stack pointer.
    ///
    mov sp,r0

    ///
    /// Restore all registers.
    ///
    pop {r0-r12,lr,pc}



    .end










