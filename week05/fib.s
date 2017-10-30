# MIPS assembler to compute Fibonacci numbers

   .data
msg1:
   .asciiz "n = "
msg2:
   .asciiz "fib(n) = "
msg3:
   .asciiz "n must be > 0\n"

   .text

# int main(void)
# {
#    int n;
#    printf("n = ");
#    scanf("%d", &n);
#    if (n >= 1)
#       printf("fib(n) = %d\n", fib(n));
#    else {
#       printf("n must be > 0\n");
#       exit(1);
#    }
#    return 0;
# }

   .globl main
main:
   # prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   move $fp, $sp
   addi $sp, $sp, -4
   sw   $ra, ($sp)

   # function body
   la   $a0, msg1       # printf("n = ");
   li   $v0, 4
   syscall

   li   $v0, 5          # scanf("%d", &n);
   syscall
   move $a0, $v0

   # ... add code to check (n >= 1)
   # ... print an error message, if needed
   # ... and return a suitable value from main()

if_start1:
   move $a1, $v0
   blt  $a1, 1, error
   bge  $a1, 1, else_part1
   j end_if

error:
   li   $v0, 4
   la   $a0, msg3
   syscall
   j end_if

else_part1:
   jal  fib             # $s0 = fib(n);
   nop
   move $s0, $v0

   la   $a0, msg2       # printf((fib(n) = ");
   li   $v0, 4
   syscall

   move $a0, $s0        # printf("%d", $s0);
   li   $v0, 1
   syscall

   li   $a0, '\n'       # printf("\n");
   li   $v0, 11
   syscall
   j end_if

end_if:
   # epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   jr   $ra



# int fib(int n)
# {
#    if (n < 1)
#       return 0;
#    else if (n == 1)
#       return 1;
#    else
#       return fib(n-1) + fib(n-2);
# }

fib:
   # prologue
   # ... add a suitable prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   move $fp, $sp
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   # function body
if_start2:
   li   $v0, 1
   beq  $a1, $v0, equal_part
   bgt	$a1, $v0, else_part2
   move $v0, $0
   j    exitfib
equal_part:
   li   $v0, 1	
   j    exitfib
else_part2:
   add  $s0, $a1, $0

   addi $a1, $s0, -1
   jal  fib
   add  $s1, $0, $v0 

   addi $a1, $s0, -2
   jal  fib
   add  $v0, $v0, $s1 
exitfib:
   # epilogue
   # ... add a suitable epilogue
   lw   $s1, -12($fp)
   lw   $s0, -8($fp)
   lw   $ra, -4($fp)
   la   $sp,  4($fp)
   lw   $fp,  ($fp)
   jr   $ra


