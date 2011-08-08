.EQU SYSTEM_MODE,0x13
.EQU IRQ_MODE, 0x12
.EQU IRQ_MASK, 0x40
.EQU SIZE_OF_USER_MODE_STORED_REGISTERS_SIZE,(14*4)

.text
.global arm_common_trap,arm_clear_interrupt,arm_set_interrupt

arm_clear_interrupt:
    MRS     r1, CPSR
    BIC     r1, r1, #IRQ_MASK
    MSR     CPSR, r1
    mov pc,lr



arm_set_interrupt:
    MRS     r1, CPSR
    ORR     r1, r1, #IRQ_MASK
    MSR     CPSR_c, r1
    mov pc,lr



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
    /// Leave space for the PC register stored in IRQ mode
    ///
    push {r0}

    ///
    /// Save registers on user stack
    ///
    push {r0-r12,lr}

    ///
    /// Set the sp addr on r0 to parameterize system call common trap
    ///
    mov r0,sp

    ///
    /// Go back to irq mode
    ///
    msr cpsr,#IRQ_MODE

    ///
    /// Store the user PC on its stack (LR in IRQ MODE = PC before IRQ)
    ///
    str lr,[r0,#SIZE_OF_USER_MODE_STORED_REGISTERS_SIZE]

    ///
    /// Store flags
    ///
    mrs r2,SPSR
    stmfd  r0!, {r2}

    ///
    /// Store r0 (aka stack pointer) in the IRQ stack
    ///
    push {r0}

    ///
    /// Move to r0 the address stored previously, r0 = Context **
    ///
    mov r0,sp

    ///
    /// Call system trap with Context pointer as first parameter
    ///
    bl system_common_trap

    ///
    /// Retrieve User Stack Pointer (if context switch happened this value is different from the pushed value)
    ///
    pop {r0}
    //ldr r1, =0xFFFFF030
    //mov r2, #0
    //str r2,[r1]

    ///
    /// Restore flags
    ///
    ldr r1,[r0],#4
    msr cpsr,r1

    ///
    /// Set the stack pointer
    ///
    mov sp,r0

    ///
    /// Restore all registers
    ///
    pop {r0-r12,lr,pc}


    .end










