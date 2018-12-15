#ifndef BOT_H
#define BOT_H

#include "player.h"

class Bot : public Player{
private:
	std::map<std::string, bool> viewedCards;
public:
  Bot(int id, std::string name, Deck allCardsList, Deck hand);

	virtual DecisionGameAction decision() override;
  virtual DestinationGameAction choose_destination(std::vector<Place> places) override;
  virtual GuessGameAction guess(Place place) override;
  virtual GuessGameAction make_accusation(Place place) override;
  virtual ShowCardAction show_card(GuessGameEvent guess) override;
	virtual void view_card(std::vector<Card> cards, Player *whoShowed) override;

  ~Bot(){}
};

#endif
