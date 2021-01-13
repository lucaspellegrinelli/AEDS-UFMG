.data
  array_size:.word 4 # Tamanho dos vetores
  word_size:.word 4 # Tamanho da palavra em bytes

  array1:.word 4, 3, 2, 1
  array2:.word 2, 1, 4, 3

.text
  lw x5, array_size # Tamanho dos vetores
  lw x6, word_size # Tamanho da palavra em bytes

  mul x7, x5, x6 # Tamanho do vetor no stack

  la x18, array1 # Inicio do primeiro vetor
  add x19, x18, x7 # Fim do segundo vetor
  sub x19, x19, x6 # Fim do segundo vetor

  la x20, array2 # Inicio do segundo vetor
  add x21, x20, x7 # Fim do segundo vetor
  sub x21, x21, x6 # Fim do segundo vetor

add x23, x0, x18 # Inicio do vetor a ser ordenado (primeiro)
add x24, x0, x19 # Fim do vetor a ser ordenado (primeiro)

jal x1, bubblesort-caller

add x23, x0, x20 # Inicio do vetor a ser ordenado (segundo)
add x24, x0, x21 # Fim do vetor a ser ordenado (segundo)

jal x1, bubblesort-caller

jal x1, compare-arrays

addi a1, x10, 0 # Coloca o resultado (x10) no registrador de output (a1)
addi a0, x0, 1 # Fala pro ecall ser o de output no console (no registrador a0)
ecall # Printa a resposta

addi a0, x0, 10 # Fala pro ecall ser o de fim de programa (no registrador a0)
ecall # Termina o programa

bubblesort-caller:
  add x28, x0, x0 # Marca se o bubblesort fez alguma troca
  add x29, x23, x0 # Endereço primeiro elemento para o primeiro teste da ordenação
  add x30, x23, x6 # Endereço segundo elemento para o primeiro teste da ordenação
  lw x25, 0(x29) # Valor primeiro elemento para o primeiro teste da ordenação
  lw x26, 0(x30) # Valor segundo elemento para o primeiro teste da ordenação

  bubblesort-loop:
    beq x24, x29, bubblesort-end-loop # Se chegou no final, sai do loop
    blt x26, x25 bubblesort-swap # Se os elementos estiverem trocados, troque-os

    beq x0, x0, bubblesort-step # Dê um passo na iteração

    bubblesort-swap:
      add x31, x26, x0 # Variável temporária para a troca com o valor da segunda pos
      sw x25, 0(x30) # Coloca o valor da primeira posição na segunda posição
      sw x31, 0(x29) # Coloca o valor da segunda posição (na temp) na primeira posição

      addi x28, x0, 1 # Marca que alguma troca foi feita no loop

      beq x0, x0, bubblesort-step # Dê um passo na iteração

    bubblesort-step:
      add x29, x29, x6 # Avança uma posição no vetor
      add x30, x30, x6 # Avança uma posição no vetor
      lw x25, 0(x29) # Lê os novos valores
      lw x26, 0(x30) # Lê os novos valores

      beq x0, x0, bubblesort-loop # Vá para a próxima iteração

    bubblesort-end-loop:
      bne x28, x0, bubblesort-caller # Se alguma troca foi feita, roda denovo
      jalr x0, 0(x1) # Caso contrário, retorne

  compare-arrays:
    add x30, x18, x0 # Endereço da posição atual do primeiro vetor
    add x31, x20, x0 # Endereço da posição atual do segundo vetor

    compare-arrays-loop:
      lw x25, 0(x30) # Lê o valor do primeiro vetor na posição atual
      lw x26, 0(x31) # Lê o valor do segundo vetor na posição atual

      bne x25, x26, compare-arrays-fail # Se os elementos forem diferentes, dê erro
      beq x30, x19, compare-arrays-loop-end # Caso chegue no final do vetor, saia

      add x30, x30, x6 # Vai para a proxima posição do primeiro vetor
      add x31, x31, x6 # Vai para a proxima posição do segundo vetor

      beq x0, x0, compare-arrays-loop # Continue o loop

    compare-arrays-fail:
      addi x10, x0, 0 # Coloca no x10 o valor de retorno "falso = 0"
      jalr x0, 0(x1)

    compare-arrays-loop-end:
      addi x10, x0, 1 # Coloca no x10 o valor de retorno "verdadeiro = 1"
      jalr x0, 0(x1)
