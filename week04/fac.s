# COMP1521 Lab 04 ... Simple MIPS assembler


### Global data

   .data
msg1:
   .asciiz "n: "
msg2:
   .asciiz "n! = "
eol:
   .asciiz "\n"

### main() function

   .data
   .align 2
main_ret_save:
   .word 4

   .text
   .globl main

main:
   sw   $ra, main_ret_save

#  ... your code for main() goes here

   lw   $ra, main_ret_save

   #print out "n:"
   li   $v0, 4
   la   $a0, msg1 
   syscall

   #read input number
   li   $v0, 5
   syscall
   move $t0, $v0

   #print out "n !=" 
   li   $v0, 4
   la   $a0, msg2
   syscall

   #run function
   move $a0, $t0
   jal  fac
   move $a0, $v0
   li   $v0, 1
   syscall

   li   $v0, 4
   la   $a0, eol
   syscall

   li   $v0, 10
   syscall

   jr   $ra           # return

### fac() function

   .data
   .align 2
fac_ret_save:
   .space  4

   .text

fac:

#  ... your code for fac() goes here
   sw   $ra, fac_ret_save

   li   $t1, 1 # i = 1
   li   $t2, 1 # f = 1
for:
   bgt  $t1, $a0 end_for
   mul  $t2, $t2, $t1 # f = f * i
   addi $t1, $t1, 1 # i++
   j for
end_for:
   move $v0, $t2
   lw   $ra, fac_ret_save
   jr   $ra            # return ($v0)



#recursive fac() goes here
   
#    sw   $fp, -4($sp)
#    sw   $ra, -8($sp)
#    sw   $s0, -12($sp)
#    sw	$s1, -16($sp)
#    sw	$s2, -20($sp)
#    la   $fp, -4($sp)
#    add  $sp, $sp, -20
#    move $s0, $t0
#    bne  $s0, 1, Else
#    jr   $ra
# Else:
#    jal  fra
#    mul  $s1, $s0, $s1
#    jr   $ra
