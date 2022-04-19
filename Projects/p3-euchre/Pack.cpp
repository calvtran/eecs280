#include "Pack.h"
#include <cassert>
#include <iostream>
using namespace std;
Pack::Pack() {
    for (int i = 0; i < PACK_SIZE; i += 6) {
	   
	   for (int k = 0; k < 6; ++k) {
		  string rank = RANK_NAMES_BY_WEIGHT[k + 7]; // 9 to A (7 to 12)
		  string suit = SUIT_NAMES_BY_WEIGHT[i / 6]; // S to D (0 to 3)
		  Card c(rank, suit);
		  this->cards[i + k] = c;
	   }
	   
    }
    this->next = 0;
}

Pack::Pack(std::istream & pack_input) {
    string suit, of, rank;
    for (int i = 0; i < PACK_SIZE; ++i) {
	   pack_input >> rank >> of >> suit;
	   Card c(rank, suit);
	   this->cards[i] = c;
    }
    this->next = 0;
}

Card Pack::deal_one() {
    assert(!this->empty());
    ++this->next;
    return this->cards[this->next - 1];
}

void Pack::reset() {
    this->next = 0;
}

void Pack::shuffle() {
    this->next = 0;
    array<Card, PACK_SIZE> newCards;

    for (int t = 0; t < 7; ++t) {
	   for (int i = 0; i < 12; ++i) {
		  newCards[2 * i + 1] = this->cards[i];  // (0 to 11) onto (odd nums)
	   }
	   for (int j = 12; j < PACK_SIZE; ++j) {
		  newCards[2 * (j - 12)] = this->cards[j];  // (12 to 23) onto (even nums)
	   }

	   for (int k = 0; k < PACK_SIZE; ++k) {
		  this->cards[k] = newCards[k];	   // Copy newPack to Pack
	   }
    }
}

bool Pack::empty() const {
    if (this->next >= PACK_SIZE)
	   return true;
    else
	   return false;
}

