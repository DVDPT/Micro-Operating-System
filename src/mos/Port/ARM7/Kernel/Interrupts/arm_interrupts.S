.EQU SYSTEM_MODE,0x13
.EQU IRQ_MODE, 0x12
.EQU FIQ_MODE, 0x11

.EQU NO_INTERRUPTS, 0xc0

.EQU CPSR_MODE_MASK, 0x1f
.EQU FIQ_MASK, 0x40
.EQU IRQ_MASK, 0x80
.EQU SIZE_OF_USER_MODE_STORED_REGISTERS_SIZE,(14*4)
.EQU FIQ_STATUS, 0xfffff004


.text
.global arm_common_trap,arm_enable_interrupt,arm_disable_interrupt,arm_is_intr_enable

arm_enable_interrupt:
    mrs     r1, CPSR
    bic     r1, r1, #IRQ_MASK | FIQ_MASK
    msr     CPSR_c, r1
    bx lr

arm_disable_interrupt:
    mrs     r1, CPSR
    orr     r1, r1, #IRQ_MASK | FIQ_MASK
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

	push {lr}

	mrs lr,cpsr
	and lr,lr,#CPSR_MODE_MASK
	cmp lr,#FIQ_MODE	//0 -> irq, 1->fiq
	beq fiq_trap
	pop {lr}
    ///
    /// Change back to system mode to store all registers.
    ///
    msr cpsr,#SYSTEM_MODE | NO_INTERRUPTS


    ///
    /// Leave space for the PC register stored in IRQ mode.
    ///
    sub sp,sp,#4

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
    msr cpsr,#IRQ_MODE | NO_INTERRUPTS

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

	msr cpsr,#SYSTEM_MODE | NO_INTERRUPTS

    ///
    /// Set the stack pointer.
    ///
    mov sp,r0

    ///
    /// Restore flags.
    ///
    pop {r1}
    msr cpsr,r1



    ///
    /// Restore all registers.
    ///
    pop {r0-r12,lr,pc}
 	/*pop {r12}
 	ldr r11,=0x20000056
	cmp r12,r11
	beq xpto
	mov pc,r12
*/

fiq_trap:

	pop {lr}
	sub lr,lr,#4


	///
	///	In fiq mode, store only needed registers.
	///
	stmfd sp!, {r0-r7,lr}

	///
	/// Call the fiq handler.
	///
	bl fiq_handler

	///
	///	Restore stored registers.
	///
	ldmfd sp!, {r0-r7,pc}^


	///
	///	Restore program counter and flags.
	///
	//subs pc,lr,#4

.end










