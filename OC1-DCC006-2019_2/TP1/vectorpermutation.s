.data
  vet00:.word 4
  vet01:.word 3
  vet02:.word 5
  vet03:.word 1

  vet10:.word 2
  vet11:.word 1
  vet12:.word 4
  vet13:.word 3

.text
  lw x29, vet00
  sw x29, 0(sp)
  lw x29, vet01
  sw x29, -4(sp)
  lw x29, vet02
  sw x29, -8(sp)
  lw x29, vet03
  sw x29, -12(sp)
  lw x29, vet10
  sw x29, -16(sp)
  lw x29, vet11
  sw x29, -20(sp)
  lw x29, vet12
  sw x29, -24(sp)
  lw x29, vet13
  sw x29, -28(sp)

addi x5, x0, 4 # Tamanho dos vetores
addi x6, x0, 4 # Tamanho da palavra (em bytes)
mul x7, x5, x6 # Tamanho do vetor no stack

sub x18, sp, x0 # Inicio do primeiro vetor
sub x19, x18, x7 # Fim do segundo vetor
add x19, x19, x6 # Fim do segundo vetor

sub x20, sp, x7 # Inicio do segundo vetor
sub x21, x20, x7 # Fim do segundo vetor
add x21, x21, x6 # Fim do segundo vetor

add x23, x0, x18 # Inicio do vetor a ser ordenado (primeiro)
add x24, x0, x19 # Fim do vetor a ser ordenado (primeiro)

jal x1, bubblesort-caller

add x23, x0, x20 # Inicio do vetor a ser ordenado (primeiro)
add x24, x0, x21 # Fim do vetor a ser ordenado (primeiro)

jal x1, bubblesort-caller

jal x1, compare-order

addi a1, x10, 0 # Coloca o resultado (x10) no registrador de output (a1)
addi a0, x0, 1 # Fala pro ecall ser o de output no console (no registrador a0)
ecall # Printa a resposta

addi a0, x0, 10 # Fala pro ecall ser o de fim de programa (no registrador a0)
ecall # Termina o programa

bubblesort-caller:
  add x28, x0, x0 # Marca se o bubblesort fez alguma troca
  sub x29, x23, x0 # Endereço primeiro elemento para o primeiro teste da ordenação
  sub x30, x23, x6 # Endereço segundo elemento para o primeiro teste da ordenação
  lw x25, 0(x29) # Valor primeiro elemento para o primeiro teste da ordenação
  lw x26, 0(x30) # Valor segundo elemento para o primeiro teste da ordenação

  bubblesort-loop:
    beq x24, x29, bubblesort-end-loop # Se chegou no final, sai do loop
    blt x26, x25 bubblesort-invert

    sub x29, x29, x6 # Avança uma posição no vetor
    sub x30, x30, x6 # Avança uma posição no vetor
    lw x25, 0(x29) # Lê os novos valores
    lw x26, 0(x30) # Lê os novos valores

    beq x0, x0, bubblesort-loop

    bubblesort-invert:
      add x31, x26, x0 # Variável temporária para a troca com o valor da segunda pos
      sw x25, 0(x30) # Coloca o valor da primeira posição na segunda posição
      sw x31, 0(x29) # Coloca o valor da segunda posição (na temp) na primeira posição

      sub x29, x29, x6 # Avança uma posição no vetor
      sub x30, x30, x6 # Avança uma posição no vetor
      lw x25, 0(x29) # Lê os novos valores
      lw x26, 0(x30) # Lê os novos valores

      addi x28, x0, 1 # Marca que alguma troca foi feita no loop

      beq x0, x0, bubblesort-loop

    bubblesort-end-loop:
      bne x28, x0, bubblesort-caller # Se alguma troca foi feita, roda denovo
      jalr x0, 0(x1) # Caso contrário, retorne

  compare-order:
    add x30, x18, x0 # Endereço da posição atual do primeiro vetor
    add x31, x20, x0 # Endereço da posição atual do segundo vetor

    compare-order-loop:
      lw x25, 0(x30) # Lê o valor do primeiro vetor na posição atual
      lw x26, 0(x31) # Lê o valor do segundo vetor na posição atual

      bne x25, x26, compare-order-fail
      beq x30, x19, compare-order-loop-end

      sub x30, x30, x6 # Vai para a proxima posição do primeiro vetor
      sub x31, x31, x6 # Vai para a proxima posição do segundo vetor

      beq x0, x0, compare-order-loop

    compare-order-fail:
      addi x10, x0, 0 # Coloca no x10 o valor de retorno "falso = 0"
      jalr x0, 0(x1)

    compare-order-loop-end:
      addi x10, x0, 1 # Coloca no x10 o valor de retorno "verdadeiro = 1"
      jalr x0, 0(x1)
