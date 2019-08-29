addi x5, x0, 5 # Número que o fatorial vai ser calculado
jal x1, fact # Chama a função e coloca em x7 o resutado

addi a1, x7, 0 # Coloca o resultado (x7) no registrador de output (a1)
addi a0, x0, 1 # Fala pro ecall ser o de output no console (no registrador a0)
ecall # Printa a resposta

addi a0, x0, 10 # Fala pro ecall ser o de fim de programa (no registrador a0)
ecall # Termina o programa

fact:
  addi x6, x5, -1 # Cria o contador que vai decrescer ao longo do fatorial (começa com input - 1)
  add x7, x0, x5 # Cria a variavel de resposta que já começa igual ao input
  jal x0, factloop # Chama a função que vai loopar as multiplicaçoes

  factloop:
    mul x7, x7, x6 # Multiplica o valor atual por n-1
    addi x6, x6, -1 # Decrementa o n
    bne x6, x0, factloop # Se n != 0, tem que continuar o loop
    jalr x0, 0(x1) # Se n == 0, retorna o valor
