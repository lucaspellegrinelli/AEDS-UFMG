# Projeto Final - PDS II

## Jogo: Detetive – Assassinato no ICEX

### Grupo 13:
* André de Oliveira Godoy
* Isadora Cristina de Matos Rodrigues
* Lucas Resende Pellegrinelli Machado
* Luiz Guilherme Leroy e Vieira

## Descrição

O corpo de um estudante de Ciência da Computação foi encontrado na portaria principal do ICEX e você é o detetive contratado para solucionar esse mistério!

### Como compilar/iniciar

Para compilar o programa é necessário apenas executar o comando "make" no terminal do Linux na pasta do projeto. Para executa-lo é necessário executar o comando "./bin/game" no terminal. Para rodar os testes, basta executar o comando "make tests".

### Objetivo do Jogo

O objetivo do jogo é descobrir, no menor número de rodadas, o autor do crime, a arma utilizada e o local do asassinato.

### Regras

A cada rodada o dado indica o número de casas que o jogador se moverá pelo tabuleiro. Ao entrar em determinado local o jogador deve dar um palpite: o local onde ele se encontra, uma arma e um suspeito. Caso algum de seus adversários possua alguma das cartas mencionadas, a mesma é revelada e o jogo segue. Quando o jogador achar que resolveu todo o mistério ele pode dar um palpite final.

Se o palpite estiver certo, parabéns!! Tente agora resolver o mistério em menos rodadas. Se você errar o palpite final o assassino sairá impune para cometer novos crimes…

### Programa

O programa será elaborado em linguagem C++, com foco na orientação a objetos. Enquanto todos os objetos gerados serão estanciados em classes diversas, o jogo em si será executado por um único usuário na função main.

* **Modelagem**: A modelagem do problema foi pensada de modo a facilitar sua implementação, visualização, abstração e entendimento. A figura 1 ilustra como foi o planejamento inicial para a modelagem do problema. Ao longo da implementação do programa, percebendo-se a necessidade, alterações nessa modelagem devem ser feitas.

![Figura 1](https://i.imgur.com/KhnXB59.jpg)
###### Figura 1 - Diagrama esquemático do programa - Versão atual

[Diagrama versão inicial](https://i.imgur.com/PCkj3Ly.png)

### Execução

Para a execução do programa será utilizado o terminal e toda a interação do usuário é feita através de comandos.

### Desafios Futuros

Essa é a primeira versão do programa. Como desafios para as próximas etapas temos a implementação de uma interface gráfica agradável, inclusão de multiplayer e desenvolvimento de aplicativos mobile.
