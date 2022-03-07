// This is a program in ARM assembly that will print a triangle of 
// given size to print to the screen

.data

i: .word 1
j: .word 0
space: .word 0
rows: .word 8

stars:  .asciz  "*"
spaces: .asciz  " "
newline: .asciz "\n"


.text
main:
    str lr, [sp, #-4]!
 
loop0:
    ldr r1, addressOfI
    ldr r2, addressOfRows
    ldr r3, [r1]
    ldr r4, [r2]

    cmp r3, r4
    bgt done

    ldr r1, addressOfI
    ldr r2, addressOfJ
    ldr r3, [r1]
    ldr r4, [r2]
    mov r4, r3
    str r4, [r2]                // j = i

// prints the trailing spaces
loop1:
    ldr r1, addressOfJ
    ldr r2, addressOfRows
    ldr r3, [r1]
    ldr r4, [r2]
    
    
    cmp r3, r4
    bge loop2_start

    ldr r0, addressOfSpaces
    bl printf

loop1_end:
    ldr r1, addressOfJ
    ldr r2, [r1]
    add r2, r2, #1
    str r2, [r1]
    b loop1
// end of first inner loop

// start of second inner loop
loop2_start:
    ldr r1, addressOfI
    ldr r2, addressOfJ
    ldr r3, addressOfRows
    ldr r4, [r1]
    ldr r5, [r2]
    ldr r6, [r3]
    mov r5, #1
    str r5, [r2]            // j = 1
loop2:
    ldr r1, addressOfI
    ldr r2, addressOfJ
    ldr r5, [r2]
    ldr r7, [r1]
    mov r7, r7, lsl#1       // i * 2 - 1
    sub r7, r7, #1
    
    cmp r5, r7
    bgt loop0_end

    ldr r1, addressOfI
    ldr r2, addressOfJ
    ldr r3, addressOfRows
    ldr r4, [r1]
    ldr r5, [r2]
    ldr r6, [r3]
    
    // print star for last row (i == rows)
    cmp r4, r6
    beq print_star
    
    // print star for first column ( j == 1 )
    cmp r5, #1
    beq print_star
    // print star for last column (j == 2*i-1)
    cmp r5, r7
    beq print_star

    bne print_space

print_space:
    ldr r0, addressOfSpaces
    bl printf 
    b loop2_end

print_star:
    ldr r0, addressOfStars
    bl printf
    b loop2_end

loop2_end:
    ldr r1, addressOfJ
    ldr r2, [r1]
    add r2, r2, #1              // j++
    str r2, [r1]
    b loop2
     

loop0_end:
    ldr r0, addressOfNewline
    bl printf
    ldr r1, addressOfI
    ldr r2, [r1]
    add r2, r2, #1
    str r2, [r1]
    b loop0    

done:
    ldr lr, [sp], #+4           // pop the lr from the stack
    bx lr


.global main
.global printf

addressOfI: .word i
addressOfJ: .word j
addressOfSpace: .word space
addressOfRows: .word rows
addressOfStars: .word stars
addressOfSpaces: .word spaces
addressOfNewline: .word newline

