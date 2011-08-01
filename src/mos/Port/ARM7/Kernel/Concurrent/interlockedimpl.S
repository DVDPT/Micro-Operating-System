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

    ldr r3,[r0]     // r3 = *addr
    cmp r3,r2       // *addr == *comparand
    movne r0,#0
    movne pc,lr     // if(*addr != *comparand) return false;

    swp r3,r1,[r0]  // trySet *addr = *value
    cmp r3,#0       // if ok
    moveq r0,#1     // return true
    mov pc,lr

atomic_compare_exchange16:
/// r0 - U32 * addr
/// r1 - U32 value
/// r2 - U32 comparand

    ldrh r3,[r0]     // r3 = *addr
    cmp r3,r2       // *addr == *comparand
    movne r0,#0
    movne pc,lr     // if(*addr != *comparand) return false;

    swp r3,r1,[r0]  // trySet *addr = *value
    cmp r3,#0       // if ok
    moveq r0,#1     // return true
    mov pc,lr


atomic_compare_exchange8:
/// r0 - U8 * addr
/// r1 - U8 value
/// r2 - U8 comparand

    ldrb r3,[r0]     // r3 = *addr
    cmp r3,r2       // *addr == *comparand
    movne r0,#0
    movne pc,lr     // if(*addr != *comparand) return false;

    swpb r3,r1,[r0]  // trySet *addr = *value
    cmp r3,#0       // if ok
    moveq r0,#1     // return true
    mov pc,lr
