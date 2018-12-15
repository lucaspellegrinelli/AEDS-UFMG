#include "player/bot.h"

Bot::Bot(int id, std::string name, Deck allCardsList, Deck hand){
  this->id = id;
  this->name = name;
  this->hand = hand;
  this->allCardsList = allCardsList;

  for(Card c: allCardsList.getLittleDeck()){
  	viewedCards.insert(std::pair<std::string, bool>(c.getIdCard(), false));

    if(c.getObject()->getType() == WEAPON){
      this->allWeapons.push_back(dynamic_cast<Weapon*>(c.getObject()));
    }else if(c.getObject()->getType() == SUSPECT){
      this->allSuspects.push_back(dynamic_cast<Suspect*>(c.getObject()));
    }else{
      this->allPlaces.push_back(dynamic_cast<Place*>(c.getObject()));
    }
  }

  for(Card c: hand.getLittleDeck()){
  	this->viewedCards[c.getIdCard()] = true;
  }
}

DecisionGameAction Bot::decision(){
	int numChecks = 0;
	for(auto it = this->viewedCards.begin(); it != this->viewedCards.end(); it++){
		bool check = it->second;
		if(!check){
			numChecks++;
		}
	}

	if(numChecks <= 3){
		DecisionGameAction decision(ACTION_DECISAO_ACUSACAO);
		return decision;
	}else{
		DecisionGameAction decision(ACTION_DECISAO_PALPITE);
		return decision;
	}
}

DestinationGameAction Bot::choose_destination(std::vector<Place> places){
  std::random_shuffle(places.begin(), places.end());
	DestinationGameAction direction(ACTION_ANDAR_DESTINO, places.at(0));
	return direction;
}

GuessGameAction Bot::guess(Place place){
  std::random_shuffle(allSuspects.begin(), allSuspects.end());
  std::random_shuffle(allWeapons.begin(), allWeapons.end());

	std::cout << "O palpite é " << allSuspects[0]->getName() << " com a arma " << allWeapons[0]->getName() << " no/na " << place.getName() << std::endl;

	GuessGameAction act(ACTION_PALPITE_ESCOLHAS, place, *this->allWeapons[0], *this->allSuspects[0], this->getId());
	return act;
}

GuessGameAction Bot::make_accusation(Place place){
	//std::cout<<"O jogador " << this->getName() << " está em "<< place.getName() <<"."<<std::endl;
	std::vector<std::string> idsUnviewedCards;
	for(auto it = this->viewedCards.begin(); it != this->viewedCards.end(); it++){
    	if(it->second == false){
        	idsUnviewedCards.push_back(it->first);
    	}
	}

	std::vector<Card> unviewedCards;
	for(std::string s : idsUnviewedCards){
    for(Card c : this->allCardsList.getLittleDeck()){
      if(c.getIdCard() == s){
        unviewedCards.push_back(c);
      }
    }
	}

  Weapon *unviewedWeapon;
  Suspect *unviewedSuspect;

  for(Card c : unviewedCards){
    if(c.getObject()->getType() == WEAPON){
      unviewedWeapon = dynamic_cast<Weapon*>(c.getObject());
    }else if(c.getObject()->getType() == SUSPECT){
      unviewedSuspect = dynamic_cast<Suspect*>(c.getObject());
    }
  }

	GuessGameAction act(ACTION_ACUSACAO_ESCOLHAS, place, *unviewedWeapon, *unviewedSuspect, this->getId());
	return act;
}

ShowCardAction Bot::show_card(GuessGameEvent guess){
	int id_card = -1;
	std::vector<Card> matchingCards;

  for(Card c : this->allCardsList.getLittleDeck()){
    if(c.getObject()->getType() == PLACE){
      Place *thisPlace = dynamic_cast<Place*>(c.getObject());
      if(thisPlace->getIdPlace() == guess.getPlace().getIdPlace()){
        matchingCards.push_back(c);
      }
    }else if(c.getObject()->getType() == WEAPON){
      Weapon *thisWeapon = dynamic_cast<Weapon*>(c.getObject());
      if(thisWeapon->getIdWeapon() == guess.getWeapon().getIdWeapon()){
        matchingCards.push_back(c);
      }
    }else if(c.getObject()->getType() == SUSPECT){
      Suspect *thisSuspect = dynamic_cast<Suspect*>(c.getObject());
      if(thisSuspect->getIdSuspect() == guess.getSuspect().getIdSuspect()){
        matchingCards.push_back(c);
      }
    }
  }

	if (matchingCards.size() == 0){
		std::cout << "O jogador " << this->getName() << " não tem nenhuma carta do palpite feito." << std::endl;
    ShowCardAction show(ACTION_MOSTRAR_CARTA, false);
    return show;
	}else{
		id_card = rand() % matchingCards.size();
    ShowCardAction show(ACTION_MOSTRAR_CARTA, matchingCards[id_card]);
  	return show;
	}
}

void Bot::view_card(std::vector<Card> cards, Player *whoShowed){
  for(Card c : cards){
	 viewedCards[c.getIdCard()] = true;
  }
}
