@ in find_max I gave you code looking like this:

ldr r0, [r1, r2, lsr #2]    @ r0 = *(r1 + (r2 * 4))

@ but that's an extra-credit problem. For regular credit you could
@ option 1: shift left, load, undo shift

lsl r1, r2, #2
ldr r0, [r1]
lsr r1, r2, #2

@ option 2: use callee-preserved register and prologue/epilogue

sub sp, sp, #8
str r4, [sp]

lsl r4, r2, #2
ldr r0, [r4]

ldr r4, [sp]
add sp, sp, #8

@ in merge_sort, you might have written code which looks like this:
@ but reading three registers in a single cycle is an extra-credit problem

str r0, [r1, r2]

@ option 1: add, load, undo add

add r1, r1, r2
str r0, [r1]
sub r1, r1, r2
