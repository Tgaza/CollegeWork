.data

A:    .word 19, 3, 2, -5, 5, 7, 821, 43, 90, -987, 43, 21, 0, 6, 15
size: .word 15
      
.text
main:
      # set up $a0 to hold base address of array
      # set up $a1 to hold size of array
      la a0, A
      la a1, size
      lw a1, 0(a1)
      
#      p = &array[0];
#loop: *p=0;
#      p++; // adds sizeof(int)!
#      if (p<&array[size]) goto loop;

      add  t0, a0, zero  # p=&array[0]
loop: sw   zero, 0(t0)    # *p=0
      addi t0, t0, 4   # p++ (p=p+4)
      slli t1, a1, 2   # t1=size*4
      add  t2, a0, t1 # t2=&array[size]
      blt  t0, t2, loop # if (p<&array[size]) goto loop

      addi a7, zero, 10  #exit
      ecall
