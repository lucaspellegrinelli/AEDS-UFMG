#include "player/human.h"

Human::Human(int id, std::string name, Deck allCardsList, Deck hand){
	this->id = id;
	this->name = name;
	this->hand = hand;

	for(Card c: allCardsList.getLittleDeck()){
    if(c.getObject()->getType() == WEAPON){
      this->allWeapons.push_back(dynamic_cast<Weapon*>(c.getObject()));
    }else if(c.getObject()->getType() == SUSPECT){
      this->allSuspects.push_back(dynamic_cast<Suspect*>(c.getObject()));
    }else{
      this->allPlaces.push_back(dynamic_cast<Place*>(c.getObject()));
    }
  }
}

DecisionGameAction Human::decision(){
	int option = 0;

	while(option != 2 && option != 3){
		std::cout << "Escolha uma opção:" << std::endl;
		std::cout << "[1] Ver mão" << std::endl;
		std::cout << "[2] Dar palpite" << std::endl;
		std::cout << "[3] Fazer acusação" << std::endl;

		std::cin >> option;

		if(option == 1){
			std::cout << std::endl;
			std::cout << "------------------------------------------------" << std::endl;
			std::cout << "---------------- Mão do jogador ----------------" << std::endl;
			std::cout << "----" << std::endl;

			for(Card c : this->hand.getLittleDeck()){
				std::cout << "---- " << c.getObject()->getName() << std::endl;
				std::cout << "Aperte esc para fechar" << std::endl;
				c.openImage();
			}

			std::cout << "----" << std::endl;

			std::cout << "------------------------------------------------" << std::endl;
			std::cout << std::endl;
		}else	if(option == 2){
			DecisionGameAction decision(ACTION_DECISAO_PALPITE);
			return decision;
		}else if(option == 3){
			DecisionGameAction decision(ACTION_DECISAO_ACUSACAO);
			return decision;
		}else throw InvalidOption("Opção não existente");
	}

	return DecisionGameAction(ACTION_DECISAO_PALPITE);
}

DestinationGameAction Human::choose_destination(std::vector<Place> places){
	std::cout << "Locais disponíveis:" << std::endl;

	for(int i = 0; i < (int)places.size(); i++){
		std::cout << "[" << i << "] " << places[i].getName() << std::endl;
	}

	std::cout << "Escolha um local a partir do seu número correspondente:" << std::endl;

	int choice;
	std::cin >> choice;
	checkExceptions(choice, (int)places.size());

	DestinationGameAction direction(ACTION_ANDAR_DESTINO, places.at(choice));
	return direction;
}

GuessGameAction Human::guess(Place place){
	int choice_s, choice_w;

	std::cout << "Agora que você esta em " << place.getName()	<< " diga qual o suspeito de acordo com seu número:" << std::endl;
	for(int i = 0; i < (int)this->allSuspects.size(); i++){
		std::cout << "[" << i << "] " << this->allSuspects[i]->getName() << std::endl;
	}

	std::cin >> choice_s;
	checkExceptions(choice_s, (int)allSuspects.size());

	std::cout << "Diga agora qual a arma que foi usada por este suspeito de acordo com seu número:" << std::endl;
	for(int i = 0; i < (int)this->allWeapons.size(); i++){
		std::cout << "[" << i << "] " << this->allWeapons[i]->getName() << std::endl;
	}

	std::cin >> choice_w;
	checkExceptions(choice_w, (int)allWeapons.size());

	GuessGameAction act(ACTION_PALPITE_ESCOLHAS, place, *this->allWeapons[choice_w], *this->allSuspects[choice_s], this->getId());
	return act;
}

GuessGameAction Human::make_accusation(Place place){
	int choice_s, choice_w;

	std::cout << "Agora que você esta em " << place.getName()	<< ", diga quem foi o assasino:" << std::endl;
	for(int i = 0; i < (int)this->allSuspects.size(); i++){
		std::cout << "[" << i << "] " << this->allSuspects[i]->getName() << std::endl;
	}

	std::cin >> choice_s;
	checkExceptions(choice_s, (int)allSuspects.size());

	std::cout << "Diga qual foi a arma usada no crime:" << std::endl;
	for(int i = 0; i < (int)this->allWeapons.size(); i++){
		std::cout << "[" << i << "] " << this->allWeapons[i]->getName() << std::endl;
	}

	std::cin >> choice_w;
	checkExceptions(choice_w, (int)allWeapons.size());

	GuessGameAction act(ACTION_ACUSACAO_ESCOLHAS, place, *this->allWeapons[choice_w], *this->allSuspects[choice_s], this->getId());
	return act;
}

ShowCardAction Human::show_card(GuessGameEvent guess){
	int id_card = -1;
	std::vector<Card> matchingCards;

  for(Card c : this->hand.getLittleDeck()){
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
		std::cout << "Você não tem nenhuma carta do palpite feito pelo jogador." << std::endl;
		ShowCardAction show(ACTION_MOSTRAR_CARTA, false);
    return show;
	}else{
		std::cout << std::endl << "Você tem ao menos uma carta do palpite, qual carta você deseja escolher?" << std::endl;
		for(int i = 0; i < (int)matchingCards.size(); i++){
			std::cout << "[" << i << "] " << matchingCards[i].getObject()->getName() << std::endl;
		}

		std::cin >> id_card;
		checkExceptions(id_card, (int)matchingCards.size());

		ShowCardAction show(ACTION_MOSTRAR_CARTA, matchingCards[id_card]);
		return show;
	}
}

void Human::view_card(std::vector<Card> cards, Player *whoShowed){
	std::cout << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "-------------- Carta(s) mostradas! --------------" << std::endl;
	std::cout << "---" << std::endl;
	std::cout << "--- " << whoShowed->getName() << " te mostrou a(s) carta(s):" << std::endl;
	for(Card c : cards){
		std::cout << "--- " << c.getObject()->getName() << std::endl;
		std::cout << "Aperte esc para fechar" << std::endl;
		c.openImage();
	}
	std::cout << "---" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl << std::endl;
}

void Human::checkExceptions(int choice, int vecSize) {
	if(choice >= vecSize)
		throw InvalidOption(choice);
	else if(choice < 0)
		throw InvalidOption("Números negativos são inválidos");
}