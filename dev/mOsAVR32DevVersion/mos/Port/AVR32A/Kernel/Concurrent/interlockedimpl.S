/*
 * atomic.S
 *
 *  Created on: Jun 21, 2011
 *      Author: DVD
 */

.text
.global atomic_compare_exchange32,atomic_compare_exchange16,atomic_compare_exchange8

atomic_compare_exchange32:
/// r0 - U32 * addr
/// r1 - U32 value
/// r2 - U32 comparand

    swp r1,r1,[r0]  // trySet *addr = *value
    mov r0,r1
    bx lr

atomic_compare_exchange16:
/// r0 - U32 * addr
/// r1 - U32 value
/// r2 - U32 comparand

    b atomic_compare_exchange32


atomic_compare_exchange8:
/// r0 - U8 * addr
/// r1 - U8 value
/// r2 - U8 comparand
    swpb r1,r1,[r0]  // trySet *addr = *value
    mov r0,r1
    bx lr
