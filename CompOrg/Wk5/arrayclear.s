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

#      i = 0;
#loop: array[i]=0;
#      i++;
#      if (i<size) goto loop;
      add  t0, zero, zero   # i=0
loop: slli  t1, t0, 2   # t1=i*4 (offset from $a0)
      add  t2, a0, t1 # t2=&array[i]
      sw   zero, 0(t2)    # array[i]=0
      addi t0, t0, 1   # i++
      blt  t0, a1, loop  # if (i<size) goto loop


      addi a7, zero, 10  #exit
      ecall
