#ifndef GAME_ACTION_TYPES_H
#define GAME_ACTION_TYPES_H

enum GameActionTypes {
  ACTION_DECISAO_ANDAR,     // "Vou andar"                                              Classe Responsável: DecisionGameAction
  ACTION_DECISAO_PALPITE,   // "Vou dar palpite"                                        Classe Responsável: DecisionGameAction
  ACTION_DECISAO_ACUSACAO,  // "Vou acusar"                                             Classe Responsável: DecisionGameAction
  ACTION_ANDAR_DESTINO,     // "Já disse que eu andaria antes, aqui está o destino"     Classe Responsável: DestinationGameAction
  ACTION_PALPITE_ESCOLHAS,  // "Já disse que eu daria um palpite, aqui está ele"        Classe Responsável: GuessGameAction
  ACTION_ACUSACAO_ESCOLHAS, // "Já disse que eu acusaria, aqui está ela"                Classe Responsável: GuessGameAction
  ACTION_MOSTRAR_CARTA,     // "Pessoa deu um palpite, preciso mostrar carta"           Classe Responsável: ShowCardAction
  ACTION_PASSAR_VEZ         // Pessoa acabou de andar e não quer fazer nada
};

#endif
