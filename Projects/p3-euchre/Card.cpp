// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
Card::Card() : rank(Card::RANK_TWO), suit(Card::SUIT_SPADES){}

Card::Card(const string &rank_in, const string &suit_in) : 
rank(rank_in), suit(suit_in) {
    assert(suit_in == SUIT_SPADES || suit_in == SUIT_HEARTS
	   || suit_in == SUIT_CLUBS || suit_in == SUIT_DIAMONDS);
    assert(rank_in == RANK_TWO || rank_in == RANK_THREE || rank_in == RANK_FOUR
	   || rank_in == RANK_FIVE || rank_in == RANK_SIX || rank_in == RANK_SEVEN
	   || rank_in == RANK_EIGHT || rank_in == RANK_NINE || rank_in == RANK_TEN
	   || rank_in == RANK_JACK || rank_in == RANK_QUEEN
	   || rank_in == RANK_KING || rank_in == RANK_ACE);
}

string Card::get_rank() const {
    return this->rank;
}

string Card::get_suit() const {
    return this->suit;
}

string Card::get_suit(const string &trump) const {
    assert(trump == SUIT_SPADES || trump == SUIT_HEARTS 
	   || trump == SUIT_CLUBS || trump == SUIT_DIAMONDS);
    if (this->is_left_bower(trump)) {
	   return trump;
    }
    else {
	   return get_suit();
    }
}

bool Card::is_face() const {
    if (this->get_rank() == RANK_JACK || this->get_rank() == RANK_QUEEN
	   || this->get_rank() == RANK_KING || this->get_rank() == RANK_ACE) {
	   return true;
    }
    else
	   return false;
}

bool Card::is_right_bower(const string &trump) const {
    assert(trump == SUIT_SPADES || trump == SUIT_HEARTS
	   || trump == SUIT_CLUBS || trump == SUIT_DIAMONDS);
    if (this->get_rank() == RANK_JACK && this->get_suit() == trump) {
	   return true;
    }
    else {
	   return false;
    }
}

bool Card::is_left_bower(const string &trump) const {
    assert(trump == SUIT_SPADES || trump == SUIT_HEARTS
	   || trump == SUIT_CLUBS || trump == SUIT_DIAMONDS);
    if (this->get_rank() == RANK_JACK) {
	   if (   (trump == SUIT_CLUBS && this->get_suit() == SUIT_SPADES)
		  || (trump == SUIT_DIAMONDS && this->get_suit() == SUIT_HEARTS)
		  || (trump == SUIT_HEARTS && this->get_suit() == SUIT_DIAMONDS)
		  || (trump == SUIT_SPADES && this->get_suit() == SUIT_CLUBS)) {
		  return true;
	   }
	   else
		  return false;
    }
    else
	   return false;
}

bool Card::is_trump(const string &trump) const {
    assert(trump == SUIT_SPADES || trump == SUIT_HEARTS
	   || trump == SUIT_CLUBS || trump == SUIT_DIAMONDS);
    if (this->get_suit() == trump) {
	   return true;
    }
    else if (this->is_left_bower(trump)) {
	   return true;
    }
    else {
	   return false;
    }
}

bool operator<(const Card & lhs, const Card & rhs)
{
    int lhs_rank, rhs_rank;
    for (int j = 0; j < NUM_RANKS; ++j) {
	   if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j])
		  lhs_rank = j;
	   if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j])
		  rhs_rank = j;
    }

    if (lhs_rank < rhs_rank)		 // compare rank
	   return true;
    else if (lhs_rank > rhs_rank)
	   return false;
    else {					 //same rank
	   int lhs_suit, rhs_suit;
	   for (int i = 0; i < NUM_SUITS; ++i) {
		  if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i])
			 lhs_suit = i;
		  if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i])
			 rhs_suit = i;
	   }

	   if (lhs_suit < rhs_suit)	  //compare suit
		  return true;
	   else
		  return false;
    }

}

bool operator>(const Card & lhs, const Card & rhs)
{
    int lhs_rank, rhs_rank;
    for (int j = 0; j < NUM_RANKS; ++j) {
	   if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j])
		  lhs_rank = j;
	   if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j])
		  rhs_rank = j;
    }

    if (lhs_rank > rhs_rank)		 // compare rank
	   return true;
    else if (lhs_rank < rhs_rank)
	   return false;
    else {					 //same rank
	   int lhs_suit, rhs_suit;
	   for (int i = 0; i < NUM_SUITS; ++i) {
		  if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i])
			 lhs_suit = i;
		  if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i])
			 rhs_suit = i;
	   }

	   if (lhs_suit > rhs_suit)	  //compare suit
		  return true;
	   else
		  return false;
    }
}

bool operator==(const Card & lhs, const Card & rhs)
{
    if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
	   return true;
    }
    else
	   return false;
}

bool operator!=(const Card & lhs, const Card & rhs)
{
    if (!(lhs == rhs)) {
	   return true;
    }
    else
	   return false;
}

string Suit_next(const string & suit)
{
    int suit_index;
    for (int i = 0; i < NUM_SUITS; ++i) {
	   if (suit == SUIT_NAMES_BY_WEIGHT[i]) {
		  suit_index = i;
	   }
    }

    if (suit_index > 1) {
	   suit_index -= 2;
    }
    else {
	   suit_index += 2;
    }
    assert(0 <= suit_index && suit_index < NUM_SUITS);
    return SUIT_NAMES_BY_WEIGHT[suit_index];
}

ostream & operator<<(ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool Card_less(const Card &a, const Card &b, const string &trump) {
    // Determine trump
    if (a.is_trump(trump) && !b.is_trump(trump))	//a is trump
	   return false;
    else if (b.is_trump(trump) && !a.is_trump(trump))    //b is trump
	   return true;
    else if (a.is_trump(trump) && b.is_trump(trump)) { //both are trump
	   if (a.get_rank() == Card::RANK_JACK || b.get_rank() == Card::RANK_JACK) {
		  if (a.is_right_bower(trump))
			 return false;
		  else if (a.is_left_bower(trump) && b.is_right_bower(trump)) // both jack
			 return true;
		  else if (a.is_left_bower(trump) && !b.is_right_bower(trump))
			 return false;
		  else
			 return true;
	   }
	   else {
		  int a_rank, b_rank;
		  for (int j = 0; j < NUM_RANKS; ++j) {
			 if (a.get_rank() == RANK_NAMES_BY_WEIGHT[j])
				a_rank = j;
			 if (b.get_rank() == RANK_NAMES_BY_WEIGHT[j])
				b_rank = j;
		  }
		  return a_rank < b_rank;
	   }
    }
    else if (!a.is_trump(trump) && !b.is_trump(trump)) { // neither trump
	   return a < b;
    } 
    else
	   return false;
}

bool Card_less(const Card &a, const Card &b, const Card &led_card,
    const string &trump) {

    string a_suit = a.get_suit();
    string b_suit = b.get_suit();
    string led_suit = led_card.get_suit();

    // Determine by trump
    if (led_card.is_trump(trump)) {
	   return Card_less(a, b, trump);
    }
    else {
	   if (!a.is_trump(trump) && !b.is_trump(trump)) {  // neither trump

		  // Determine by led card
		  if (a_suit == led_suit
			 && b_suit != led_suit)//a is led suit
			 return false;
		  else if (b_suit == led_suit
			 && a_suit != led_suit)//b is led suit
			 return true;
		  else if ((a_suit == led_suit && b_suit == led_suit)  // both led
			 || (a_suit != led_suit && b_suit != led_suit)) {// neither led
			 return a < b;
		  }
		  else
			 return false;
	   } 
	   else if (a.is_trump(trump) && !b.is_trump(trump))	//a is trump
		  return false;
	   else if (b.is_trump(trump) && !a.is_trump(trump))	    //b is trump
		  return true;
	   else if (a.is_trump(trump) && b.is_trump(trump)) {    //both are trump
		  return Card_less(a, b, trump);
	   }
	   else
		  return false;
    }
}