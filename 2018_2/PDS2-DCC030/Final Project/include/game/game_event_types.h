#ifndef GAME_EVENT_TYPES_H
#define GAME_EVENT_TYPES_H

enum GameEventTypes {
  EVENT_INICIO_TURNO,             // "Jogador do Turno, decida o que você vai fazer no seu turno"
  EVENT_ANDAR,                    // "Jogador do Turno, você escolheu andar, me diga para onde"
  EVENT_FIM_ANDAR,                // "Jogador do Turno, você andou, decida o que vai fazer agora"
  EVENT_PALPITE,                  // "Jogador do Turno, você escolheu dar palpite, me diga qual"
  EVENT_PALPITE_MOSTRAR_CARTA,    // "Jogador, o Jogador do Turno deu um palpite, decida qual carta da sua mão vocẽ vai mostrar"
  EVENT_ACUSACAO,                 // "Jogador do Turno, você escolheu acusar, me diga a acusação"
  EVENT_MOSTRAR_MAO,              // "Jogador, o Jogador do Turno perdeu, olhe a mão dele"
  EVENT_QUEM_MOSTROU_PALPITE      // "Jogador, esse foi o jogador que mostrou a carta no palpite x"
};

#endif
