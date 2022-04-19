#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include "Pack.h"
#include "Card.h"
#include "Player.h"
using namespace std;

class Game {
private:
    Pack game_pack;
    string shuffle;
    int points_to_win, team1_score, team2_score;
    vector<Player *> players;
    int dealer_ind, player_ordered_up, team1_tricks, team2_tricks;
    Player * player0;
    Player * player1;
    Player * player2;
    Player * player3;

public:
    Game() : game_pack(), shuffle(), points_to_win(0), team1_score(0), 
	   team2_score(0) {}

    Game(istream &pack_in, string shuffle_in, int points_in)
	   : game_pack(pack_in), shuffle(shuffle_in), 
	   points_to_win(points_in), team1_score(0),
	   team2_score(0), players(), dealer_ind(0) {
	   
    }

    void init_player0(string name_in, string type_in, int player_ind) {
	   player0 = Player_factory(name_in, type_in);
	   players.push_back(player0);
    }

    void init_player1(string name_in, string type_in, int player_ind) {
	   player1 = Player_factory(name_in, type_in);
	   players.push_back(player1);
    }

    void init_player2(string name_in, string type_in, int player_ind) {
	   player2 = Player_factory(name_in, type_in);
	   players.push_back(player2);
    }

    void init_player3(string name_in, string type_in, int player_ind) {
	   player3 = Player_factory(name_in, type_in);
	   players.push_back(player3);
    }
    
    string init_hand() {
	   cout << *this->players.at(this->dealer_ind) << " deals\n";
	   //deal cards
	   if (shuffle == "shuffle")
		  this->game_pack.shuffle();
	   else
		  this->game_pack.reset();

	   this->deal_cards();
	   this->team1_tricks = 0;
	   this->team2_tricks = 0;
	   string order_up_suit;
	   Card upcard = this->game_pack.deal_one();
	   cout << upcard << " turned up\n";
	   
	   this->Game_make_trump(upcard, order_up_suit);
	   return order_up_suit;
    }

    void Game_make_trump(Card & upcard, string & ordered_suit_in) {
	   int round = 1;
	   bool ordered_up = false;
	   int cur_player = operator++(this->dealer_ind);
	   
	   // Round 1 of making
	   for (int i = 0; (i < 4) && !ordered_up; ++i, cur_player = operator++(cur_player)) {
		  ordered_up = this->players.at(cur_player)
			 ->make_trump(upcard, this->is_dealer(cur_player),
				round, ordered_suit_in);
		  if (!ordered_up) {
			 cout << *this->players.at(cur_player) << " passes\n";
		  }
		  else {
			 cout << *this->players.at(cur_player) << " orders up "
				<< ordered_suit_in << endl;
			 this->player_ordered_up = cur_player;
		  }
	   }
	   
	   // Round 2 of making (if necessary)
	   if (!ordered_up) {
		  ++round;
		  cur_player = operator++(this->dealer_ind);

		  for (int i = 0; (i < 4) && !ordered_up; 
			 ++i, cur_player = this->operator++(cur_player)) {
			 ordered_up = this->players.at(cur_player)
				->make_trump(upcard, this->is_dealer(cur_player),
				    round, ordered_suit_in);
			 if (!ordered_up) {
				cout << *this->players.at(cur_player) << " passes\n";
			 }
			 else {
				cout << *this->players.at(cur_player) << " orders up "
				    << ordered_suit_in << endl;
				this->player_ordered_up = cur_player;
			 }
		  }
	   }
	   else {
		  this->players.at(dealer_ind)->add_and_discard(upcard);
		  return;
	   }


    }

    int get_dealer_ind() {
	   return this->dealer_ind;
    }

    bool is_dealer(int player_ind) const {
	   if (player_ind == this->dealer_ind)
		  return true;
	   else
		  return false;
    }

    int operator++(int player_ind) {
	   //int int_result = player_ind;
	   if (player_ind < 3) {
		  return ++player_ind;
	   }
	   else {
		  return 0;
	   }
	   //return int_result;
    }
    
    void deal_cards() {
	   int cur_player = operator++(dealer_ind);
	   for (int i = 0; i < 8; ++i, cur_player = operator++(cur_player)) {
		  if (i < 4) {
			 if (i % 2 == 0) {
				this->players.at(cur_player)->add_card(this->game_pack.deal_one());
				this->players.at(cur_player)->add_card(this->game_pack.deal_one());
				this->players.at(cur_player)->add_card(this->game_pack.deal_one());
			 }
			 else {
				this->players.at(cur_player)->add_card(this->game_pack.deal_one());
				this->players.at(cur_player)->add_card(this->game_pack.deal_one());
			 }
		  }
		  else {	// i >= 4
			 if (i % 2 == 0) {
				this->players.at(cur_player)->add_card(this->game_pack.deal_one());
				this->players.at(cur_player)->add_card(this->game_pack.deal_one());
			 }
			 else {
				this->players.at(cur_player)->add_card(this->game_pack.deal_one());
				this->players.at(cur_player)->add_card(this->game_pack.deal_one());
				this->players.at(cur_player)->add_card(this->game_pack.deal_one());
			 }
		  }
	   }
    }

    void Game_play(string & trump, int & player_ind) {
	   for (int i = 0; i < 5; ++i) {
		  Card led_card = this->players.at(player_ind)->lead_card(trump);
		  Card card2, card3, card4, hi_card;
		  int lead = player_ind;
		  hi_card = led_card;
		  cout << led_card << " led by "
			 << *this->players.at(player_ind) << endl;

		  player_ind = operator++(player_ind);
		  card2 = this->players.at(player_ind)->play_card(led_card, trump);
		  cout << card2 << " played by "
			 << *this->players.at(player_ind) << endl;

		  if (!Card_less(card2, hi_card, led_card, trump)) {
			 hi_card = card2;
			 lead = player_ind;
		  }

		  player_ind = operator++(player_ind);
		  card3 = this->players.at(player_ind)->play_card(led_card, trump);
		  cout << card3 << " played by "
			 << *this->players.at(player_ind) << endl;

		  if (!Card_less(card3, hi_card, led_card, trump)) {
			 hi_card = card3;
			 lead = player_ind;
		  }

		  player_ind = operator++(player_ind);
		  card4 = this->players.at(player_ind)->play_card(led_card, trump);
		  cout << card4 << " played by "
			 << *this->players.at(player_ind) << endl;

		  if (!Card_less(card4, hi_card, led_card, trump)) {
			 hi_card = card4;
			 lead = player_ind;
		  }

		  cout << *this->players.at(lead) << " takes the trick\n\n";
		  add_tricks(lead);
		  player_ind = lead;
	   }
	   hand_summary();
    }

    void add_tricks(int winner_index_in) {
	   if (winner_index_in == 0 || winner_index_in == 2) {
		  this->team1_tricks += 1;
	   }
	   else {
		  this->team2_tricks += 1;
	   }
    }

    void hand_summary() {
	   if (this->team1_tricks > this->team2_tricks) {
		  cout << *this->players.at(0) << " and "
			 << *this->players.at(2) << " win the hand\n";
		  // if ordered up
		  if (this->player_ordered_up == 0 || this->player_ordered_up == 2) {
			 // 3 or 4 tricks
			 if (this->team1_tricks == 3 || this->team1_tricks == 4) {
				this->team1_score += 1;
			 }
			 // 5 tricks
			 if (this->team1_tricks == 5) {
				this->team1_score += 2;
				cout << "march!\n";
			 }
		  }
		  else { // not ordered up
			 if (this->team1_tricks > 2) {
				this->team1_score += 2;
				cout << "euchred!\n";
			 }
		  }
	   }
	   else {
		  cout << *this->players.at(1) << " and "
			 << *this->players.at(3) << " win the hand\n";
		  // if ordered up
		  if (this->player_ordered_up == 1 || this->player_ordered_up == 3) {
			 // 3 or 4 tricks
			 if (this->team2_tricks == 3 || this->team2_tricks == 4) {
				this->team2_score += 1;
			 }
			 // 5 tricks
			 if (this->team2_tricks == 5) {
				this->team2_score += 2;
				cout << "march!\n";
			 }
		  }
		  else { // not ordered up
			 if (this->team2_tricks > 2) {
				this->team2_score += 2;
				cout << "euchred!\n";
			 }
		  }
	   }

	   cout << *this->players.at(0) << " and "
		  << *this->players.at(2) << " have "
		  << this->team1_score << " points\n";
	   cout << *this->players.at(1) << " and "
		  << *this->players.at(3) << " have "
		  << this->team2_score << " points\n";
	   this->dealer_ind = operator++(this->dealer_ind);
    }

    bool determine_win() {
	   if (team1_score >= points_to_win || team2_score >= points_to_win) {
		  if (team1_score > team2_score) {
			 cout << endl << *this->players.at(0) << " and "
				<< *this->players.at(2) << " win!\n";
		  }
		  else {
			 cout << endl << *this->players.at(1) << " and "
				<< *this->players.at(3) << " win!\n";
		  }
		  return true;
	   }
	   else
		  return false;
    }

    bool check_invariants() {
	   if (points_to_win < 1 || 100 < points_to_win ||
		  !(shuffle != "shuffle" || shuffle != "noshuffle")) {
		  cout << "testUsage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
			 << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
			 << "NAME4 TYPE4" << endl;
		  return false;
	   }
	   else
		  return true;
    }

    bool check_players(string type1_in, string type2_in, 
	   string type3_in, string type4_in) {
	   check_invariants();
	   char str[7] = "Simple";
	   char str2[6] = "Human";
	   if (!(type1_in != str || type1_in != str2)
		  || !(type2_in != str || type2_in != str2)
		  || !(type3_in != str || type3_in != str2)
		  || !(type4_in != str || type4_in != str2)) {
		  cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
			 << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
			 << "NAME4 TYPE4" << endl;
		  return false;
	   }
	   else
		  return true;
    }

    ~Game() {
	   delete player0;
	   delete player1;
	   delete player2;
	   delete player3;
    }
};


// ./euchre.exe pack.in shuffle 10 Edsger Simple Fran Simple Gabriel Simple Herb Simple
int main(int argc, char *argv[]) {
    ifstream pack_in;
    string in_file = argv[1];
    pack_in.open(in_file);
    if (!pack_in.is_open()) {
	   cout << "Error opening " << in_file << endl;
	   return 1;
    }
    string name1 = argv[4]; string type1 = argv[5];
    string name2 = argv[6]; string type2 = argv[7];
    string name3 = argv[8]; string type3 = argv[9];
    string name4 = argv[10]; string type4 = argv[11];
    for (int j = 0; j < argc; ++j) {
	   cout << argv[j] << " ";
    }
    Game * game = new Game(pack_in, argv[2], atoi(argv[3]));
    game->init_player0(name1, type1, 0);
    game->init_player1(name2, type2, 1);
    game->init_player2(name3, type3, 2);
    game->init_player3(name4, type4, 3);
    if (!game->check_players(type1, type2, type3, type4)) {
	   return 1;
    }
    bool win = false;
    string trump;
    int next;
    for (int hand = 0; !win; ++hand) {
	   cout << "\nHand " << hand << endl;
	   trump = game->init_hand();
	   cout << endl;
	   next = game->operator++(game->get_dealer_ind());
	   game->Game_play(trump, next);
	   win = game->determine_win();
    }
    pack_in.close();
    delete game;
    return 0;
}