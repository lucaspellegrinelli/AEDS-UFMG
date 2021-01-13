#include "game/game.h"

Game::Game(){
  srand(time(NULL));
  this->n_of_humans = 1;
  this->humanLost = false;
  this->n_of_bots = 5;
  this->finished = false;
  this->finalDeck = Final_Deck();

  std::vector<Place> allPlaces;
  for(Card c : this->finalDeck.getAllCards().getLittleDeck()){
    if(c.getObject()->getType() == PLACE){
      allPlaces.push_back(*(dynamic_cast<Place*>(c.getObject())));
    }
  }

  this->board = Board(allPlaces);
}

std::vector<Player*> Game::getPlayers(){
  return this->players;
}

void Game::initializePlayers(){
  NameHelper n_helper = NameHelper();

  for(int i = 0; i < n_of_humans + n_of_bots; i++){
    if(i < n_of_humans){
      Human *human = new Human(i, n_helper.askForName(i), this->finalDeck.getAllCards(), this->finalDeck.getHand(i));
      this->players.push_back(human);
    }else{
      Bot *bot = new Bot(i, n_helper.generateName(true), this->finalDeck.getAllCards(), this->finalDeck.getHand(i));
      this->players.push_back(bot);
    }
  }

  std::random_shuffle(this->players.begin(), this->players.end());

  for(int i = 0; i < (int)this->players.size(); i++){
    this->board.addPlayer(this->players[i], this->board.getPlaces()[i]);
  }
}

void Game::run(){
  std::cout << "----------------------------------------------------------" << std::endl;
  std::cout << "------------ Informações de início de partida ------------" << std::endl;
  std::cout << "----------------------------------------------------------" << std::endl;
  this->board.printMap();

  std::cout << std::endl << "--------------------------------------------------------------------------------------------------------" << std::endl;
  std::cout << "---- A ordem dos jogadores é:" << std::endl;
  std::cout << "---- ";
  for(Player *p : this->players) std::cout << p->getName() << " -> ";
  std::cout << std::endl << "--------------------------------------------------------------------------------------------------------" << std::endl;

  std::cout << std::endl;

  std::cout << std::endl << "Digite qualquer coisa para começar o jogo" << std::endl;
  std::string tmp;
  std::cin >> tmp;

  int turnPlayer = 0;
  while(!this->finished){
    std::cout << std::endl << "----------------------------------------------------------" << std::endl;
    std::cout << "----------------- Jogador Atual: " << this->getPlayers()[turnPlayer]->getName() << " -" << std::endl;
    std::cout              << "----------------------------------------------------------" << std::endl << std::endl;
    int dice = rand() % 6 + 1;
    Place currPlace = this->board.getPosition(this->getPlayers()[turnPlayer]);
    std::cout << this->getPlayers()[turnPlayer]->getName() << " tirou " << dice << " no dado de movimento!" << std::endl;
    DestinationGameAction dest = this->getPlayers()[turnPlayer]->choose_destination(this->board.getMaxPlace(dice + 1, currPlace));
    this->walkDecision(turnPlayer, dest.getPlace());

    if(this->finished) break;

    if(dynamic_cast<Human*>(this->getPlayers()[turnPlayer]) == nullptr){
      std::cout << std::endl << "Digite qualquer coisa para avançar o turno" << std::endl;
      std::cin >> tmp;
    }

    turnPlayer = (turnPlayer + 1) % this->getPlayers().size();
  }

  if(this->finished){
    this->finalDeck.solveMystery();
    if(this->humanLost){
      return;
    } 
  }
}

void Game::interpretDecision(DecisionGameAction decision, int turnPlayer){
  GameActionTypes decisionType = decision.getActionType();

  if(decisionType == ACTION_DECISAO_PALPITE){
    std::cout << std::endl << this->getPlayers()[turnPlayer]->getName() << " escolheu dar palpite" << std::endl;
    guessDecision(turnPlayer);
  }else if(decisionType == ACTION_DECISAO_ACUSACAO){
    std::cout << std::endl << this->getPlayers()[turnPlayer]->getName() << " escolheu acusar" << std::endl;
    accusationDecision(turnPlayer);
  }else if(decisionType == ACTION_PASSAR_VEZ){
    // Nada
  }
}

void Game::walkDecision(int turnPlayer, Place place){
  std::cout << this->getPlayers()[turnPlayer]->getName() << " andou de " << this->board.getPosition(this->getPlayers()[turnPlayer]).getName() << " para " << place.getName() << std::endl;
  this->board.move(this->getPlayers()[turnPlayer], place);
  DecisionGameAction decision = this->getPlayers()[turnPlayer]->decision();

  interpretDecision(decision, turnPlayer);
}

void Game::guessDecision(int turnPlayer){
  GuessGameAction guess = this->getPlayers()[turnPlayer]->guess(this->board.getPosition(this->getPlayers()[turnPlayer]));
  Place place = guess.getPlace();
  Weapon weapon = guess.getWeapon();
  Suspect suspect = guess.getSuspect();

  int whoShowedCard = -1;

  int showCardPlayer = (turnPlayer + 1) % this->getPlayers().size();
  while(showCardPlayer != turnPlayer){
    for(Card c : this->getPlayers()[showCardPlayer]->getHand().getLittleDeck()){
      if(c.getObject()->getId() == place.getIdPlace() ||
         c.getObject()->getId() == weapon.getIdWeapon() ||
         c.getObject()->getId() == suspect.getIdSuspect()){
        whoShowedCard = showCardPlayer;
      }
    }

    if(whoShowedCard != -1){
      ShowCardAction cardToShow = this->getPlayers()[whoShowedCard]->show_card(GuessGameEvent(EVENT_PALPITE_MOSTRAR_CARTA, place, weapon, suspect));

      if(cardToShow.isValid()){
        std::vector<Card> cardsToShow;
        cardsToShow.push_back(cardToShow.getCard());
        this->getPlayers()[turnPlayer]->view_card(cardsToShow, this->getPlayers()[whoShowedCard]);

        std::cout << std::endl << this->getPlayers()[whoShowedCard]->getName() << " teve de mostrar alguma carta por causa do último palpite!" << std::endl;
      }

      break;
    }

    showCardPlayer = (showCardPlayer + 1) % this->getPlayers().size();
  }

  if(whoShowedCard == -1){
    std::cout << std::endl << "Ninguém mostrou nenhuma carta após o último palpite!" << std::endl;
  }
}

void Game::accusationDecision(int turnPlayer){
  GuessGameAction guess = this->getPlayers()[turnPlayer]->make_accusation(this->board.getPosition(this->getPlayers()[turnPlayer]));
  Place place = guess.getPlace();
  Weapon weapon = guess.getWeapon();
  Suspect suspect = guess.getSuspect();

  bool gotItRight = true;
  for(Card c : this->finalDeck.getTopSecret().getLittleDeck()){
    if(c.getObject()->getType() == WEAPON){
      Weapon *other = dynamic_cast<Weapon*>(c.getObject());
      if(other->getIdWeapon() != weapon.getIdWeapon()){
        gotItRight = false;
        break;
      }
    }else if(c.getObject()->getType() == PLACE){
      Place *other = dynamic_cast<Place*>(c.getObject());
      if(other->getIdPlace() != place.getIdPlace()){
        gotItRight = false;
        break;
      }
    }else if(c.getObject()->getType() == SUSPECT){
      Suspect *other = dynamic_cast<Suspect*>(c.getObject());
      if(other->getIdSuspect() != suspect.getIdSuspect()){
        gotItRight = false;
        break;
      }
    }
  }

  if(gotItRight){
    if((dynamic_cast<Human*>(this->getPlayers()[turnPlayer])) != nullptr){
      this->humanLost = true;
    }
    this->finished = true;
  }else{
    showCardsToEveryone(turnPlayer, this->getPlayers()[turnPlayer]->getHand().getLittleDeck());
  }
}

void Game::showCardsToEveryone(int turnPlayer, std::vector<Card> cards){
  for(int i = 0; i < (int)this->getPlayers().size(); i++){
    if(i == turnPlayer) continue;
    this->getPlayers()[i]->view_card(cards, this->getPlayers()[turnPlayer]);
  }
}

Game::~Game(){
  for (unsigned int i = 0; i < this->players.size(); i++){
    delete this->players[i];
  }
}
