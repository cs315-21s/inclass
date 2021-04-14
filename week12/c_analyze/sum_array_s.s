.global sum_array_s

@ r0 = the array, r1 = array len
sum_array_s:
    mov r2, #0      @ r2 is the sum
    mov ip, #0      @ ip/r12 is the loop index
loop:
    cmp ip, r1      @ done?
    beq done
    ldr r3, [r0]    @ load r3 with the integer r0 points to
    add r2, r2, r3  @ accumulate sum
    add r0, r0, #4  @ walk r0 to the next 4-byte integer in the array
    add ip, ip, #1  @ increment loop index
    b loop
done:
    mov r0, r2      @ set up sum in r0
    bx lr
