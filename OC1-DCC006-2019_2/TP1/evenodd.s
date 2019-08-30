.data
  input:.word 3 # Coloca na memória o valor 3

.text
  lw x5, input # Lê da memória

jal x1, parity # Chama a função e coloca em x7 o resutado

addi a1, x7, 0 # Coloca o resultado (x7) no registrador de output (a1)
addi a0, x0, 1 # Fala pro ecall ser o de output no console (no registrador a0)
ecall # Printa a resposta

addi a0, x0, 10 # Fala pro ecall ser o de fim de programa (no registrador a0)
ecall # Termina o programa

parity:
  addi x6, x0, 2 # Cria um registrador (x6) com o valor 2
  rem x7, x5, x6 # Calcula x5 (input) mod x6 (valor 2) e guarda em x6
  jalr x0, 0(x1) # Retorna
