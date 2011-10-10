/*
 * atomic.S
 *
 *  Created on: Jun 21, 2011
 *      Author: DVD
 */

.text
.global atomic_compare_exchange32,atomic_compare_exchange16,atomic_compare_exchange8

atomic_compare_exchange32:
/// r10 - U8 * addr
/// r11 - U8 value
/// r12 - U8 comparand


atomic_compare_exchange16:
/// r10 - U8 * addr
/// r11 - U8 value
/// r12 - U8 comparand

 


atomic_compare_exchange8:
/// r10 - U8 * addr
/// r11 - U8 value
/// r12 - U8 comparand

