#include "Player.h"
#include <cassert>
#include <algorithm>
#include <iostream>

class Simple : public Player {
public:

    Simple(const std::string &name_in) :
	   name(name_in), hand() {}

    const std::string & get_name() const override {
	   return this->name;
    }

    void add_card(const Card &c) override {
	   assert(this->hand.size() + 1 <= MAX_HAND_SIZE);
	   this->hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
	   int round, std::string &order_up_suit) const override {
	   assert(round == 1 || round == 2);

	   if (round == 1) {
		  int trump_face_cards = 0;
		  for (int i = 0; i < MAX_HAND_SIZE; ++i) {
			 if (this->hand[i].is_face() &&
				this->hand[i].is_trump(upcard.get_suit()))
				++trump_face_cards;
		  }

		  if (trump_face_cards >= 2) {
			 order_up_suit = upcard.get_suit();
			 /*std::cout << this->get_name() << " orders up "
				<< order_up_suit << std::endl << std::endl;*/
			 return true;
		  }
		  else
		  {
			 //std::cout << this->get_name() << " passes"<< std::endl;
			 return false;
		  }
	   }
	   else {
		  int next_face_cards = 0;
		  for (int i = 0; i < MAX_HAND_SIZE; ++i) {
			 if (this->hand[i].is_face() && (
				this->hand[i].get_suit() == Suit_next(upcard.get_suit())))
				++next_face_cards;
		  }

		  if (next_face_cards >= 1 || is_dealer) {
			 order_up_suit = Suit_next(upcard.get_suit());
			 /*std::cout << this->get_name() << " orders up "
				<< order_up_suit << std::endl << std::endl;*/
			 return true;
		  }
		  else 
			 return false;		  
	   }
    }

    void add_and_discard(const Card &upcard) override {
	   assert(this->hand.size() >= 1);
	   std::sort(this->hand.begin(), this->hand.end()); // {low to HIGH}
	   Card remove = upcard;
	   for (size_t i = 0; i < this->hand.size(); ++i) {
		  // Find card(s) lower than upcard
		  if (Card_less(this->hand.at(i), remove, upcard.get_suit())) {   
			 remove = this->hand.at(i);
		  }
	   }
	   if (remove != upcard) {  // if card found ^^
		  // Move selected to the right
		  this->remove(remove);
		  this->add_card(upcard);	// Add upcard to deck
	   }
	   // if no card found ^^, upcard is lowest so no change to hand
    }

    Card lead_card(const std::string &trump) override {
	   assert(this->hand.size() >= 1);
	   Card card;

	   size_t trump_cards = 0;
	   for (size_t i = 0; i < this->hand.size(); ++i) {
		  if (this->hand.at(i).is_trump(trump)) {
			 ++trump_cards;
		  }
	   }

	   if (trump_cards == this->hand.size()) {			// if all trump cards...
		  std::sort(this->hand.begin(), this->hand.end()); // sort {low to HIGH}
		  card = Card(Card::RANK_TWO, trump);
		  for (size_t i = 0; i < this->hand.size(); ++i) {
			 if (Card_less(card, hand.at(i), trump)) {
				card = this->hand.at(i);	  // select HIGH trump card
			 }
		  }	  
	   }
	   else {										// if has non-trumps...
		  std::sort(this->hand.rbegin(), this->hand.rend()); // sort {HIGH to low}
		  for (size_t j = 0; j < this->hand.size(); ++j) { 
			 if (!this->hand.at(j).is_trump(trump)) {
				card = this->hand.at(j);		 // select highest non_trump
				j = this->hand.size();
			 }
		  }
	   }
	   this->remove(card);	 // remove from hand
	   return card;
    }

    Card play_card(const Card &led_card, const std::string &trump) override {
	   assert(this->hand.size() >= 1);
	   Card card;
	   bool follow_suit = false;

	   for (size_t i = 0; i < this->hand.size(); ++i) {
		  // follow suit
		  if (led_card.get_suit(trump) == this->hand.at(i).get_suit(trump)) {
			 follow_suit = true;
		  }
	   }

	   if (follow_suit) { // can follow suit
		  std::sort(this->hand.begin(), this->hand.end()); // sort {low to HIGH}
		  card = Card(Card::RANK_TWO, led_card.get_suit(trump));
		  for (size_t i = 0; i < this->hand.size(); ++i) {
			 // find highest
			 if ((led_card.get_suit(trump) == this->hand.at(i).get_suit(trump)) 
				&& (Card_less(card, hand.at(i), led_card, trump))) {
				card = this->hand.at(i);
			 }
		  }
	   }
	   else { // cannot follow suit
		  std::sort(this->hand.begin(), this->hand.end());// sort {low to HIGH}
		  card = this->hand.at(this->hand.size() - 1);
		  for (size_t j = 0; j < this->hand.size(); ++j) {
			 // find lowest
			 if (Card_less(hand.at(j), card, trump)) {
				card = this->hand.at(j);
			 } 
		  }
	   }
	   this->remove(card);
	   return card;
    }
    
    void remove(Card const &card) {
	   for (size_t k = 0; k < this->hand.size() - 1; ++k) {
		  if (this->hand.at(k) == card) {
			 this->hand.at(k) = this->hand.at(this->hand.size() - 1);
			 break;
		  }
	   }
	   this->hand.pop_back();
    }

    static const int MAX_HAND_SIZE = 5;

    ~Simple() {}

private:
    std::string name;
    std::vector<Card> hand;
};


class Human : public Player {
public:

    Human(const std::string &name_in) :
	   name(name_in), hand() {}

    const std::string & get_name() const override {
	   return this->name;
    }

    void add_card(const Card &c) override {
	   assert(this->hand.size() + 1 <= MAX_HAND_SIZE);
	   this->hand.push_back(c);
	   std::sort(this->hand.begin(), this->hand.end());
    }

    void print_hand() const {
	   for (size_t i = 0; i < this->hand.size(); ++i) {
		  std::cout << "Human player " << this->name
			 << "'s hand: [" << i << "] " << this->hand.at(i)
			 << std::endl;
	   }
    }

    void remove(Card const &card) {
	   for (size_t k = 0; k < this->hand.size() - 1; ++k) {
		  if (this->hand.at(k) == card) {
			 this->hand.at(k) = this->hand.at(this->hand.size() - 1);
			 break;
		  }
	   }
	   this->hand.pop_back();
    }

    bool make_trump(const Card &upcard, bool is_dealer,
	   int round, std::string &order_up_suit) const override {
	   assert(round == 1 || round == 2);

	   
	   this->print_hand();

	   std::string action;

	   //if (round == 1)
	   std::cout << "Human player " << this->name
		  << ", please enter a suit, or \"pass\":" << std::endl;
	   /*else if (round == 2 && is_dealer)
		  std::cout << "Human player " << this->name
		  << ", you are the dealer and must order up a suit during round 2 of making!\n"
		  << "Please enter a valid suit\n"
		  << std::endl;*/
	   
	   std::cin >> action;

	   if (round == 1) {
		  if (action == "pass") {
			 //std::cout << this->get_name() << " passes\n";
			 return false;
		  }
		  else 
		  if (action == "Spades" || action == "Hearts" ||	
			 action == "Clubs" || action == "Diamonds") {
			 order_up_suit = action;
			 /*std::cout << this->get_name() << " orders up "
				<< order_up_suit << '\n';*/
			 return true;
		  }
		  return false;
	   }
	   else { // round == 2
		  if (!is_dealer) {
			 if (action == "pass") {
				std::cout << this->get_name() << " passes\n";
				return false;
			 }
			 else
				if ((action == "Spades" || action == "Hearts" ||
				    action == "Clubs" || action == "Diamonds") &&
				    (action != upcard.get_suit())) {
				    order_up_suit = action;
				    /*std::cout << this->get_name() << " orders up "
					   << order_up_suit << '\n';*/
				    return true;
				}
			 return false;
		  }
		  else { // is_dealer
			 if ((action == "Spades" || action == "Hearts" ||
				action == "Clubs" || action == "Diamonds") &&
				(action != upcard.get_suit())) {
				order_up_suit = action;
				/*std::cout << this->get_name() << " orders up "
				    << order_up_suit << '\n';*/
				return true;
			 }
			 else
				return true;
		  }
		  return false;
	   }
	   return false;
    }

    void add_and_discard(const Card &upcard) override {
	   assert(this->hand.size() >= 1);
	   
	   int remove_ind;
	   int const upcard_ind = -1;
	   Card remove;

	   std::sort(this->hand.begin(), this->hand.end());
	   this->print_hand();
	   std::cout << "Discard upcard: [-1]\n";
	   std::cout << "Human player " << this->name
		  << ", please select a card to discard:" << std::endl;
	   std::cin >> remove_ind;
	   if (upcard_ind != remove_ind) {
		  remove = this->hand.at(remove_ind);
		  this->remove(remove);
		  this->add_card(upcard);
		  return;
	   }
	   else if (remove_ind == upcard_ind) {
		  return;
	   }
    }

    Card lead_card(const std::string &trump) override {
	   assert(this->hand.size() >= 1);
	   int card_ind;

	   std::sort(this->hand.begin(), this->hand.end());
	   this->print_hand();
	   std::cout << "Human player " << this->name
		  << ", please select a card:" << std::endl;
	   std::cin >> card_ind;
	   	   
	   //std::cout << this->hand.at(card_ind) << " led by " << this->get_name() << '\n';
	   Card card = this->hand.at(card_ind);
	   this->remove(card);
	   return card;
    }
    

    Card play_card(const Card &led_card, const std::string &trump) override {
	   assert(this->hand.size() >= 1);

	   std::sort(this->hand.begin(), this->hand.end());
	   this->print_hand();

	   int card_ind;

	   int num_led = 0;
	   for (size_t i = 0; i < this->hand.size(); ++i) {
		  if (led_card.get_suit(trump) == this->hand.at(i).get_suit(trump)) {
			 ++num_led;
		  }
	   }

	   Card card;

	   std::cout << "Human player " << this->name
		  << ", please select a card:" << std::endl;
	   std::cin >> card_ind;
	  
	   card = this->hand.at(card_ind);
	   this->remove(card);
	   return card;
	  
    }

    static const int MAX_HAND_SIZE = 5;

    ~Human() {}

private:
    std::string name;
    std::vector<Card> hand;
};

Player * Player_factory(const std::string & name, const std::string & strategy)
{
    // We need to check the value of strategy and return 
    // the corresponding player type.
    if (strategy == "Simple") {
	   return new Simple(name);
    }
    if (strategy == "Human") {
	   return new Human(name);
    }
    else
	   assert(false);
    return nullptr;
}

std::ostream & operator<<(std::ostream & os, const Player & p)
{
    os << p.get_name();
    return os;
}