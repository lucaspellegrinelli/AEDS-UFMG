# --------------- SUMÁRIO DE COMO OS REGISTRADORES FORAM USADOS ---------------
#
# x5 - Constante - O tamanho das sequências em quantidade de itens
# x6 - Constante - Bytes por registrador/espaço na memória
# x7 - Constante - O tamanho das sequências na memória
#
# x9 [s] - Usando como um "return address" secundário
#
# x10 [s] - Valor de retorno geral (0 = Não são permutação, 1 = São permutação)
#
# x18 [s] - Inicio do vetor que estamos calculando a soma a o produto atualmente
# x19 [s] - Final do vetor que estamos calculando a soma a o produto atualmente
#
# x20 [s] - Depois de calcular a soma do primeiro vetor, ela é armazenada aqui
# x21 [s] - Depois de calcular o produto do primeiro vetor, ele é armazenado aqui
#
# x28 - Salva em qual posição de memória os vetores começam
#
# x29 - Ao buscar os valores dos vetores na memória para realizar as operações,
#		eles são armazenados aqui / variável temporária na criação dos vetores
#
# x30 - Armazena a soma parcial (enquanto o loop no vetor acontece)
# x31 - Armazena o produto parcial (enquanto o loop no vetor acontece)
#
# -----------------------------------------------------------------------------

# ------------------------ SUMÁRIO DE FUNÇÕES CRIADAS -------------------------
#
# linha 111 - create_sequence_1
# linha 129 - create_sequence_2
# linha 146 - test_sequence
# linha 165 - sequences_sum_ok
# linha 171 - test_success
# linha 177 - test_fail
# linha 183 - make_operations
# linha 190 - loop_operations
# linha 200 - loop_operations_end
#
# -----------------------------------------------------------------------------


# --------------- CRIAÇÃO DAS CONSTANTES DO PROGRAMA ---------------

addi x5, x0, 4 # O tamanho dos vetores em quantidade de itens
addi x6, x0, 4 # Bytes por registrador/espaço na memória
mul x7, x5, x6 # O tamanho dos vetores na memória

addi x28, sp, 0 # Salva a posição inicial do stack


# --------------- SALVANDO OS VALORES DOS SAVED REGISTERS NA MEMÓRIA ---------------

sw x9, 0(x28) # Salva o valor de x10 pois é um "saved register"
sub x28, x28, x6 # Incrementa uma posição de memória no contador

sw x10, 0(x28) # Salva o valor de x10 pois é um "saved register"
sub x28, x28, x6 # Incrementa uma posição de memória no contador

sw x18, 0(x28) # Salva o valor de x10 pois é um "saved register"
sub x28, x28, x6 # Incrementa uma posição de memória no contador

sw x19, 0(x28) # Salva o valor de x10 pois é um "saved register"
sub x28, x28, x6 # Incrementa uma posição de memória no contador

sw x20, 0(x28) # Salva o valor de x10 pois é um "saved register"
sub x28, x28, x6 # Incrementa uma posição de memória no contador

sw x21, 0(x28) # Salva o valor de x10 pois é um "saved register"
sub x28, x28, x6 # Incrementa uma posição de memória no contador


# --------------- CRIANDO OS VETORES E OS GUARDANDO NA MEMÓRIA ---------------

jal x1, create_sequence_1 # Cria o primeiro vetor e salva na memória
jal x1, create_sequence_2 # Cria o segundo vetor e salva na memória


# --------------- TESTE SE OS VETORES SÃO PERMUTAÇÃO UM DO OUTRO ---------------

jal x1, test_sequence # Testa se os vetores tem os mesmos elementos e salva a resposta em x10


# --------------- OUTPUT DO PROGRAMA NO CONSOLE ---------------

addi a1, x10, 0 # Coloca o resultado (x10) no registrador de output (a1)
addi a0, x0, 1 # Fala pro ecall ser o de output no console (no registrador a0 = 1)
ecall # Printa a resposta


# ------------ RECUPERAÇÃO DOS VALORES ANTIGOS DOS SAVED REGISTERS -------------

add x28, x28, x6 # Decrementa uma posição de memória no contador
lw x21, 0(x28) # Pega da memória o valor antigo de x21  pois é um "saved register"

add x28, x28, x6 # Decrementa uma posição de memória no contador
lw x20, 0(x28) # Pega da memória o valor antigo de x21  pois é um "saved register"

add x28, x28, x6 # Decrementa uma posição de memória no contador
lw x19, 0(x28) # Pega da memória o valor antigo de x21  pois é um "saved register"

add x28, x28, x6 # Decrementa uma posição de memória no contador
lw x18, 0(x28) # Pega da memória o valor antigo de x21  pois é um "saved register"

add x28, x28, x6 # Decrementa uma posição de memória no contador
lw x10, 0(x28) # Pega da memória o valor antigo de x21  pois é um "saved register"

add x28, x28, x6 # Decrementa uma posição de memória no contador
lw x9, 0(x28) # Pega da memória o valor antigo de x21  pois é um "saved register"


# ------------------------- FINALIZAÇÃO DOS PROGRAMAS --------------------------

addi a0, x0, 10 # Fala pro ecall ser o de fim de programa (no registrador a0 = 10)
ecall # Termina o programa


# ----------------------- FUNÇÃO QUE CRIA A SEQUÊNCIA 1 ------------------------
create_sequence_1:
  addi x29, x0, 1
  sw x29, 0(x28)

  addi x29, x0, 2
  sw x29, -4(x28)

  addi x29, x0, 3
  sw x29, -8(x28)

  addi x29, x0, 4
  sw x29, -12(x28)

  jalr x0, 0(x1)


# ----------------------- FUNÇÃO QUE CRIA A SEQUÊNCIA 2 ------------------------
create_sequence_2:
  addi x29, x0, 1
  sw x29, -16(x28)

  addi x29, x0, 2
  sw x29, -20(x28)

  addi x29, x0, 3
  sw x29, -24(x28)

  addi x29, x0, 4
  sw x29, -28(x28)

  jalr x0, 0(x1)


# ----------------------- FUNÇÃO CONTROLADORA PRINCIPAL ------------------------
test_sequence:
  sub x18, x28, x0 # Indica o inicio do vetor que iremos calcular as variáveis
  sub x19, x28, x7 # Indica o final do vetor que iremos calcular as variáveis

  jal x9, make_operations # Calcula a soma (em x30) e a multiplicação (em x31)

  addi x20, x30, 0 # Salva a soma
  addi x21, x31, 0 # Salva a multiplicação

  sub x18, x28, x7 # Coloca o x18 como a posição inicial do próximo vetor
  sub x19, x19, x7 # Coloca o x19 como a posição final do próximo vetor

  jal x9, make_operations # Calcula a soma (em x30) e a multiplicação (em x31)

  beq x20, x30, sequences_sum_ok # Se as somas estiverem ok, vai testar a multiplcação
  beq x0, x0, test_fail # Caso as somas não forem iguais, retorna 0


# ------------------- FUNÇÃO DE COMPARAÇÃO DA MULTIPLICAÇÃO --------------------
sequences_sum_ok:
  beq x21, x31, test_success # Se as multiplicações estiverem ok também, retorna 1
  beq x0, x0, test_fail # Caso as multiplicações não forem iguais, retorna 0


# -------------------- FUNÇÃO DE OUPUT POSITIVO DO PROGRAMA --------------------
test_success:
  addi x10, x0, 1 # Coloca o valor de retorno (em x8) como 1
  jalr x0, 0(x1) # Volta para o programa inicial


# -------------------- FUNÇÃO DE OUPUT NEGATIVO DO PROGRAMA --------------------
test_fail:
  addi x10, x0, 0 # Coloca o valor de retorno (em x10) como 0
  jalr x0, 0(x1) # Volta para o programa inicial


# --------------- FUNÇÃO DE INICIO DO PROCESSAMENTO DE UM VETOR ----------------
make_operations:
  addi x30, x0, 0 # Variável que vai tomar conta da soma
  addi x31, x0, 1 # Variável que vai tomar conta da multiplicação
  beq x0, x0, loop_operations # Execute as contas no vetor


# -------------- FUNÇÃO DE SOMA/PRODUTO DOS ELEMENTOS DE UM VETOR --------------
loop_operations:
  lw x29, 0(x18) # Pega da memória o elemento atual (na posição x18)
  add x30, x30, x29 # Soma com a variável de soma
  mul x31, x31, x29 # Multiplica com a variável de multiplicação
  sub x18, x18, x6 # Avança 1 posição na memória
  beq x18, x19, loop_operations_end # Se tiver passado da última posição do vetor, sai do loop
  beq x0, x0, loop_operations # Se ainda estiver dentro do vetor, continue o loop


# ------------------- FUNÇÃO DE FIM DA SOMA/PRODUTO DO VETOR -------------------
loop_operations_end:
  jalr x0, 0(x9) # Volta para 'test_seq' na posição certa
