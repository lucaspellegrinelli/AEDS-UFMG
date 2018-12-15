#ifndef SIMPLE_GAME_EVENT_H
#define SIMPLE_GAME_EVENT_H

#include "game/game_event.h"

/*
  Evento de jogo sem maiores especificades
*/

class SimpleGameEvent : public GameEvent{
public:
  SimpleGameEvent(GameEventTypes);
};

#endif
