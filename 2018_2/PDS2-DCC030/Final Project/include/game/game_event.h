#ifndef GAME_EVENT_H
#define GAME_EVENT_H

#include "game_event_types.h"
#include "cards/place.h"
#include "cards/weapon.h"
#include "cards/suspect.h"

/*
  Eventos no jogo que requerem resposta do jogador
*/

class GameEvent{
protected:
  GameEventTypes type;

public:
  GameEventTypes getEventType();
};

#endif
