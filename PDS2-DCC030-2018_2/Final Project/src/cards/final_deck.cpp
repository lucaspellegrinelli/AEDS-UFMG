#include "cards/final_deck.h"


//O construtor do final_deck serve para inicializar todas as cartas do jogo.
//Alem disso, ele implementa o TopSecret, que ira de forma aleatoria selecionar
//uma arma, um local e um suspeito para a solucao do misterio.
//Por fim, a classe junta todas as cartas restantes e monta um BigDeck que depois
//sera dividido entre os jogadores da partida.
Final_Deck::Final_Deck(){
  Deck weapons;
  Deck suspects;
  Deck places;

  Weapon *a1 = new Weapon("A1", "Prova", "A1.jpg", WEAPON);
  Weapon *a2 = new Weapon("A2", "Molho", "A2.jpg", WEAPON);
  Weapon *a3 = new Weapon("A3", "Robo", "A3.jpg", WEAPON);
  Weapon *a4 = new Weapon("A4", "Ar", "A4.jpg", WEAPON);
  Weapon *a5 = new Weapon("A5", "Coco", "A5.jpg", WEAPON);
  Weapon *a6 = new Weapon("A6", "Algebrismo", "A6.jpg", WEAPON);

  Card c1 = Card("c1", a1);
  Card c2 = Card("c2", a2);
  Card c3 = Card("c3", a3);
  Card c4 = Card("c4", a4);
  Card c5 = Card("c5", a5);
  Card c6 = Card("c6", a6);

  weapons.addCard(c1);
  weapons.addCard(c2);
  weapons.addCard(c3);
  weapons.addCard(c4);
  weapons.addCard(c5);
  weapons.addCard(c6);

  weapons.shuffle();

  Place *l1 = new Place("L1", "Bola", "L1.jpg", PLACE);
  Place *l2 = new Place("L2", "Sala", "L2.jpg", PLACE);
  Place *l3 = new Place("L3", "Banheiro", "L3.jpg", PLACE);
  Place *l4 = new Place("L4", "Cabine", "L4.jpg", PLACE);
  Place *l5 = new Place("L5", "CRC", "L5.jpg", PLACE);
  Place *l6 = new Place("L6", "Lounge", "L6.jpg", PLACE);
  Place *l7 = new Place("L7", "DA", "L7.jpg", PLACE);
  Place *l8 = new Place("L8", "Museu", "L8.jpg", PLACE);
  Place *l9 = new Place("L9", "Corredor", "L9.jpg", PLACE);

  Card c7("c7", l1);
  Card c8("c8", l2);
  Card c9("c9", l3);
  Card c10("c10", l4);
  Card c11("c11", l5);
  Card c12("c12", l6);
  Card c13("c13", l7);
  Card c14("c14", l8);
  Card c15("c15", l9);

  places.addCard(c7);
  places.addCard(c8);
  places.addCard(c9);
  places.addCard(c10);
  places.addCard(c11);
  places.addCard(c12);
  places.addCard(c13);
  places.addCard(c14);
  places.addCard(c15);

  places.shuffle();

  Suspect *s1 = new Suspect("S1", "Adelaide", "S1.jpg", SUSPECT);
  Suspect *s2 = new Suspect("S2", "Suelem", "S2.jpg", SUSPECT);
  Suspect *s3 = new Suspect("S3", "Rubinho", "S3.jpg", SUSPECT);
  Suspect *s4 = new Suspect("S4", "Tonico", "S4.jpg", SUSPECT);
  Suspect *s5 = new Suspect("S5", "Mirtes", "S5.jpg", SUSPECT);
  Suspect *s6 = new Suspect("S6", "Josimar", "S6.jpg", SUSPECT);

  Card c16("c16", s1);
  Card c17("c17", s2);
  Card c18("c18", s3);
  Card c19("c19", s4);
  Card c20("c20", s5);
  Card c21("c21", s6);

  suspects.addCard(c16);
  suspects.addCard(c17);
  suspects.addCard(c18);
  suspects.addCard(c19);
  suspects.addCard(c20);
  suspects.addCard(c21);

  suspects.shuffle();


  for(Card c : weapons.getLittleDeck()) this->allCards.addCard(c);
  for(Card c : suspects.getLittleDeck()) this->allCards.addCard(c);
  for(Card c : places.getLittleDeck()) this->allCards.addCard(c);


  TopSecret.addCard(weapons.getLittleDeck()[0]);
  TopSecret.addCard(places.getLittleDeck()[0]);
  TopSecret.addCard(suspects.getLittleDeck()[0]);

  Deck BigDeck;

  for(int i = 1; i < 6; i++){
    Card c = weapons.getLittleDeck()[i];
    BigDeck.addCard(c);
  }
  for(int i = 1; i < 9; i++){
    Card c = places.getLittleDeck()[i];
    BigDeck.addCard(c);
  }
  for(int i = 1; i < 6; i++){
    Card c = suspects.getLittleDeck()[i];
    BigDeck.addCard(c);
  }
  
  BigDeck.shuffle();

  int bigDeckCount = 0;
  for (int p = 0; p < 6; p++) {
    Deck deck;
    for (int i = 0; i != (18 / NUM_OF_PLAYERS); i++) {
      deck.addCard(BigDeck.getLittleDeck()[bigDeckCount++]);
    }

    this->allDecks.push_back(deck);
  }
}

Deck Final_Deck::getTopSecret(){
  return TopSecret;
}

Deck Final_Deck::getAllCards(){
  return allCards;
}

Deck Final_Deck::getHand(int num){
  return this->allDecks[num];
}

//Caso o jogador forneca o palpite correto, e chamada a funcao solveMystery
//Ela mostra as cartas que de fato pertencem ao TopSecret e encerra o caso.
void Final_Deck::solveMystery(){
  std::cout << "O mistério foi desvendado..." << std::endl;
  TopSecret.showCards();
  std::cout << "A arma utilizada foi: " << std::endl;
  TopSecret.getLittleDeck()[0].getObject()->getImage();
  std::cout << "O local do crime foi: " << std::endl;
  TopSecret.getLittleDeck()[1].getObject()->getImage();
  std::cout << "O assassino foi: " << std::endl;
  TopSecret.getLittleDeck()[2].getObject()->getImage();
  std::cout << "Parabens detetive! Por sua causa o Icex é um lugar um pouco mais seguro!";
  std::cout << std::endl;
}
