// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

// { A spades, A spades, A spades, A spades, A spades }
static void add_cards(Player *player) {
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    for (int i = 0; i < 5; ++i) {
	   player->add_card(ace_spades);
    }
}

// { 2 spades, 2 spades, 2 spades, 2 spades, 2 spades }
static void add_cards2(Player *player) {
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    for (int i = 0; i < 5; ++i) {
	   player->add_card(two_spades);
    }
}

// { 9 club, 10 club, 9 spade, 10 spade, 9 heart }
static void add_cards3(Player *player) {
    Card card1 = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    player->add_card(card1);
    Card card2 = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    player->add_card(card2);
    Card card3 = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    player->add_card(card3);
    Card card4 = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    player->add_card(card4);
    Card card5 = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    player->add_card(card5);
}

// { J spades, J clubs, 2 spades, 2 spades, 2 spades }
static void add_cards4(Player *player) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    player->add_card(jack_spades);
    player->add_card(jack_clubs);
    player->add_card(two_spades);
    player->add_card(two_spades);
    player->add_card(two_spades);
}

TEST(test_player_get_name) {
    Player * alice = Player_factory("Simple Alice", "Simple");
    ASSERT_EQUAL("Simple Alice", alice->get_name());
    delete alice;

    Player * bob = Player_factory("Human Bob", "Human");
    ASSERT_EQUAL("Human Bob", bob->get_name());

    delete bob;
}

TEST(test_simple_player_make_trump_round_1) {
    Player * bob = Player_factory("Bob", "Simple");
    add_cards(bob);
    // { A spades, A spades, A spades, A spades, A spades }

    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);

    // TEST 1a: Round 1, dealer, 5 trump face cards
    string trump1 = "NULL";
    bool orderup1 = bob->make_trump(
	   nine_spades,    //upcard
	   true,           //Bob is the dealer
	   1,              //first round
	   trump1          //ordered up spades
    );
    ASSERT_TRUE(orderup1);
    ASSERT_EQUAL(trump1, Card::SUIT_SPADES);

    // TEST 1b: Round 1, not dealer, 5 trump face cards
    trump1 = "NULL";
    orderup1 = bob->make_trump(
	   nine_spades,    //upcard
	   false,          //Bob is NOT the dealer
	   1,              //first round
	   trump1          //ordered up spades
    );
    ASSERT_TRUE(orderup1);
    ASSERT_EQUAL(trump1, Card::SUIT_SPADES);

    // TEST 2a: Round 1, dealer, 5 non-trump face cards
    trump1 = "NULL";
    orderup1 = bob->make_trump(
	   nine_clubs,     //upcard
	   true,           //Bob is the dealer
	   1,              //first round
	   trump1          //ordered up nothing
    );
    ASSERT_FALSE(orderup1);
    ASSERT_EQUAL(trump1, "NULL");

    // TEST 2b: Round 1, not dealer, 5 non-trump face cards
    trump1 = "NULL";
    orderup1 = bob->make_trump(
	   nine_clubs,     //upcard
	   false,          //Bob is NOT the dealer
	   1,              //first round
	   trump1          //ordered up nothing
    );
    ASSERT_FALSE(orderup1);
    ASSERT_EQUAL(trump1, "NULL");

    delete bob;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    Player * joe = Player_factory("Joe", "Simple");
    add_cards2(joe);
    // { 2 spades, 2 spades, 2 spades, 2 spades, 2 spades }
    
    // TEST 3a: Round 1, dealer, 5 trump non-face cards
    string trump2 = "NULL";
    bool orderup2 = joe->make_trump(
	   nine_spades,    //upcard
	   true,           //Joe is the dealer
	   1,              //first round
	   trump2          //ordered up nothing
    );
    ASSERT_FALSE(orderup2);
    ASSERT_EQUAL(trump2, "NULL");

    // TEST 3b: Round 1, not dealer, 5 trump non-face cards
    trump2 = "NULL";
    orderup2 = joe->make_trump(
	   nine_spades,    //upcard
	   false,          //Joe is NOT the dealer
	   1,              //first round
	   trump2          //ordered up nothing
    );
    ASSERT_FALSE(orderup2);
    ASSERT_EQUAL(trump2, "NULL");

    // TEST 4a: Round 1, dealer, 5 non-trump non-face cards
    trump2 = "NULL";
    orderup2 = joe->make_trump(
	   nine_clubs,     //upcard
	   true,           //Joe is the dealer
	   1,              //first round
	   trump2          //ordered up nothing
    );
    ASSERT_FALSE(orderup2);
    ASSERT_EQUAL(trump2, "NULL");

    // TEST 4b: Round 1, not dealer, 5 non-trump non-face cards
    trump2 = "NULL";
    orderup2 = joe->make_trump(
	   nine_clubs,     //upcard
	   false,          //Joe is NOT the dealer
	   1,              //first round
	   trump2          //ordered up nothing
    );
    ASSERT_FALSE(orderup2);
    ASSERT_EQUAL(trump2, "NULL");

    delete joe;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Player * cam = Player_factory("Cam", "Simple");
    add_cards4(cam);
    // { J spades, J clubs, 2 spades, 2 spades, 2 spades }

    // TEST 5a: Round 1, dealer, 2 trump face cards/3 trump non-face
    string trump3 = "NULL";
    bool orderup3 = cam->make_trump(
	   nine_spades,    //upcard
	   true,           //Joe is the dealer
	   1,              //first round
	   trump3          //ordered up spades
    );
    ASSERT_TRUE(orderup3);
    ASSERT_EQUAL(trump3, Card::SUIT_SPADES);

    // TEST 5b: Round 1, not dealer, 2 trump face/3 trump non-face
    trump3 = "NULL";
    orderup3 = cam->make_trump(
	   nine_spades,    //upcard
	   false,          //Joe is NOT the dealer
	   1,              //first round
	   trump3          //ordered up spades
    );
    ASSERT_TRUE(orderup3);
    ASSERT_EQUAL(trump3, Card::SUIT_SPADES);

    // TEST 6a: Round 1, dealer, 2 non-trump face/3 non-trump non-face
    trump3 = "NULL";
    orderup3 = cam->make_trump(
	   nine_hearts,    //upcard
	   true,           //Joe is the dealer
	   1,              //first round
	   trump3          //ordered up nothing
    );
    ASSERT_FALSE(orderup3);
    ASSERT_EQUAL(trump3, "NULL");

    // TEST 6b: Round 1, not dealer, 2 non-trump face/3 non-trump non-face
    trump3 = "NULL";
    orderup3 = cam->make_trump(
	   nine_hearts,    //upcard
	   false,          //Joe is NOT the dealer
	   1,              //first round
	   trump3          //ordered up nothing
    );
    ASSERT_FALSE(orderup3);
    ASSERT_EQUAL(trump3, "NULL");

    delete cam;
}

TEST(test_simple_player_make_trump_round_2) {
    Player * bob = Player_factory("Bob", "Simple");

    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card three_diamonds = Card(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    bob->add_card(king_hearts);
    bob->add_card(three_diamonds);
    bob->add_card(three_diamonds);
    bob->add_card(three_diamonds);
    bob->add_card(three_diamonds);
    // { K hearts, 3 diamonds, 3 diamonds, 3 diamonds, 3 diamonds }
    
    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);

    // TEST 1a: Round 2, not dealer, 1 same-color face card/ 4 same-suit non-face
    string trump1 = "NULL";
    bool orderup1 = bob->make_trump(
	   nine_diamonds,  //upcard
	   false,          //Bob is NOT the dealer
	   2,              //second round
	   trump1          //ordered up hearts
    );
    ASSERT_TRUE(orderup1);
    ASSERT_EQUAL(trump1, Card::SUIT_HEARTS);

    // TEST 1b: Round 2, dealer, 1 same-color face card/ 4 same-suit non-face
    trump1 = "NULL";
    orderup1 = bob->make_trump(
	   nine_diamonds,  //upcard
	   true,           //Bob is NOT the dealer
	   2,              //second round
	   trump1          //ordered up hearts
    );
    ASSERT_TRUE(orderup1);
    ASSERT_EQUAL(trump1, Card::SUIT_HEARTS);

    // TEST 2a: Round 2, not dealer, 1 same-suit face card/ 4 same-color non-face
    trump1 = "NULL";
    orderup1 = bob->make_trump(
	   nine_hearts,    //upcard
	   false,          //Bob is NOT the dealer
	   2,              //second round
	   trump1          //ordered up nothing
    );
    ASSERT_FALSE(orderup1);
    ASSERT_EQUAL(trump1, "NULL");

    // TEST 2b: Round 2, dealer, 1 same-suit face card/ 4 same-color non-face
    trump1 = "NULL";
    orderup1 = bob->make_trump(
	   nine_hearts,    //upcard
	   true,           //Bob is NOT the dealer
	   2,              //second round
	   trump1          //ordered up diamonds
    );
    ASSERT_TRUE(orderup1);
    ASSERT_EQUAL(trump1, Card::SUIT_DIAMONDS);

    // TEST 3a: Round 2, not dealer, 1 diff-color face card/ 4 diff-color non-face
    trump1 = "NULL";
    orderup1 = bob->make_trump(
	   nine_spades,    //upcard
	   false,          //Bob is NOT the dealer
	   2,              //second round
	   trump1          //ordered up nothing
    );
    ASSERT_FALSE(orderup1);
    ASSERT_EQUAL(trump1, "NULL");

    // TEST 3b: Round 2, dealer, 1 diff-color face card/ 4 diff-color non-face
    trump1 = "NULL";
    orderup1 = bob->make_trump(
	   nine_spades,    //upcard
	   true,           //Bob is NOT the dealer
	   2,              //second round
	   trump1          //ordered up clubs
    );
    ASSERT_TRUE(orderup1);
    ASSERT_EQUAL(trump1, Card::SUIT_CLUBS);

    delete bob;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Player * joe = Player_factory("Joe", "Simple");

    add_cards2(joe);
    // { 2 spades, 2 spades, 2 spades, 2 spades, 2 spades }

    // TEST 4a: Round 2, not dealer, 5 diff-color non-face cards
    string trump2 = "NULL";
    bool orderup2 = joe->make_trump(
	   nine_hearts,    //upcard
	   false,          //Joe is NOT the dealer
	   2,              //second round
	   trump2          //ordered up nothing
    );
    ASSERT_FALSE(orderup2);
    ASSERT_EQUAL(trump2, "NULL");

    // TEST 4b: Round 2, dealer, 5 diff-color non-face cards
    trump2 = "NULL";
    orderup2 = joe->make_trump(
	   nine_spades,    //upcard
	   true,           //Joe is the dealer
	   2,              //second round
	   trump2          //ordered up clubs
    );
    ASSERT_TRUE(orderup2);
    ASSERT_EQUAL(trump2, Card::SUIT_CLUBS);

    // TEST 5a: Round 2, not dealer, 5 same-color non-face cards
    trump2 = "NULL";
    orderup2 = joe->make_trump(
	   nine_clubs,     //upcard
	   false,          //Joe is NOT the dealer
	   2,              //second round
	   trump2          //ordered up nothing
    );
    ASSERT_FALSE(orderup2);
    ASSERT_EQUAL(trump2, "NULL");

    // TEST 5b: Round 2, dealer, 5 same-color non-face cards
    trump2 = "NULL";
    orderup2 = joe->make_trump(
	   nine_clubs,     //upcard
	   true,           //Joe is the dealer
	   2,              //second round
	   trump2          //ordered up spades
    );
    ASSERT_TRUE(orderup2);
    ASSERT_EQUAL(trump2, Card::SUIT_SPADES);
    delete joe;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Player * cam = Player_factory("Cam", "Simple");
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    cam->add_card(jack_clubs);
    cam->add_card(three_diamonds);
    cam->add_card(three_diamonds);
    cam->add_card(three_diamonds);
    cam->add_card(three_diamonds);
    // { J clubs, 3 diamonds, 3 diamonds, 3 diamonds, 3 diamonds }

    // TEST 6a: Round 2, not dealer, 1 left-to-right bower/4 diff-color non-face
    string trump3 = "NULL";
    bool orderup3 = cam->make_trump(
	   nine_spades,    //upcard
	   false,          //Joe is NOT the dealer
	   2,              //second round
	   trump3          //ordered up clubs
    );
    ASSERT_TRUE(orderup3);
    ASSERT_EQUAL(trump3, Card::SUIT_CLUBS);

    // TEST 6b: Round 2, dealer, 1 right-to-left bower/4 diff-color non-face
    trump3 = "NULL";
    orderup3 = cam->make_trump(
	   nine_clubs,     //upcard
	   true,           //Joe is the dealer
	   2,              //second round
	   trump3          //ordered up spades
    );
    ASSERT_TRUE(orderup3);
    ASSERT_EQUAL(trump3, Card::SUIT_SPADES);
    delete cam;
}

TEST(test_simple_player_lead_card) {
// TEST 1: Not adding the upcard
    Player * bob = Player_factory("Bob", "Simple");
    add_cards(bob);
    // { A spades, A spades, A spades, A spades, A spades }

    Card upcard(Card::RANK_NINE, Card::SUIT_SPADES); 	 // Spades is trump
    bob->add_and_discard(upcard);
    // { A spades, A spades, A spades, A spades, A spades }
    // Do not add upcard

    // check all 5 cards; play all five A spades
    Card card_led = bob->lead_card(Card::SUIT_SPADES);
    Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, ace_spades);			      // check led card 1

    card_led = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, ace_spades);			      // check led card 2
    
    card_led = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, ace_spades);			      // check led card 3

    card_led = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, ace_spades);			      // check led card 4

    card_led = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, ace_spades);			      // check led card 5

    delete bob;

// TEST 2: Adding the upcard
    Player * joe = Player_factory("Joe", "Simple");
    joe->add_card(Card());
    joe->add_card(Card(Card::RANK_THREE, Card::SUIT_SPADES));
    joe->add_card(Card(Card::RANK_FOUR, Card::SUIT_SPADES));
    joe->add_card(Card(Card::RANK_FIVE, Card::SUIT_SPADES));
    joe->add_card(Card(Card::RANK_SIX, Card::SUIT_SPADES));
    // { 2 spades, 3 spades, 4 spades, 5 spades, 6 spades }

    Card upcard2 = ace_spades;	 // Spades is trump
    joe->add_and_discard(upcard2);
    // { A spades, 3 spades, 4 spades, 5 spades, 6 spades }
    // Add upcard

    // check all 5 cards; play A spades, then remaining cards
    Card card_led2 = joe->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led2, ace_spades);			 
    // check led card 1

    card_led2 = joe->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led2, Card(Card::RANK_SIX, Card::SUIT_SPADES));			 
    // check led card 2

    card_led2 = joe->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led2, Card(Card::RANK_FIVE, Card::SUIT_SPADES));		
    // check led card 3

    card_led2 = joe->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led2, Card(Card::RANK_FOUR, Card::SUIT_SPADES));		
    // check led card 4

    card_led2 = joe->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led2, Card(Card::RANK_THREE, Card::SUIT_SPADES));	
    // check led card 5

    delete joe;

// TEST 3: Adding trump over highest suit
    Player * cam = Player_factory("Cam", "Simple");
    cam->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    cam->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    cam->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    cam->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    cam->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    // { A diamonds, K diamonds, Q diamonds, J diamonds, 10 diamonds }

    Card upcard3 = ace_spades;		// Spades is trump
    cam->add_and_discard(upcard3);
    // { A diamonds, K diamonds, Q diamonds, J diamonds, A spades }
    // Add upcard
    
    // check all cards; play non-trump cards, then A spades
    Card card_led3 = cam->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led3, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    
    card_led3 = cam->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led3, Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
    
    card_led3 = cam->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led3, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
    
    card_led3 = cam->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led3, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    
    card_led3 = cam->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led3, ace_spades);

    delete cam;
}

TEST(test_simple_player_play_card) {
// TEST 1: Cannot follow suit
    Player * bob = Player_factory("Bob", "Simple");
    add_cards3(bob);
    // { 9 club, 10 club, 9 spade, 10 spade, 9 heart }

    Card led(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    string trump = Card::SUIT_CLUBS;

    Card card_played = bob->play_card(led, trump); // Diamonds(non-trump) is led
    // Play lowest diff-suit card (9 spades)
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_played, nine_spades);
    delete bob;

// TEST 2: Can follow suit
    Player * joe = Player_factory("Bob", "Simple");
    add_cards3(joe);
    // { 9 club, 10 club, 9 spade, 10 spade, 9 heart }

    Card led2(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump2 = Card::SUIT_CLUBS;

    Card card_played2 = joe->play_card(led2, trump2); // Spades(non-trump) is led
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    // Play highest same-suit (non-trump) card (10 spades)
    ASSERT_EQUAL(card_played2, ten_spades);
    delete joe;

// TEST 3: Cannot follow suit (w/ trump)
    Player * cam = Player_factory("Cam", "Simple");
    cam->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    cam->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    cam->add_card(Card(Card::RANK_TWO, Card::SUIT_DIAMONDS));
    cam->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    cam->add_card(Card(Card::RANK_TWO, Card::SUIT_HEARTS));
    // { J hearts, J diamonds, 2 diamonds, K hearts, 2 hearts }

    Card led3(Card::RANK_JACK, Card::SUIT_CLUBS);
    string trump3 = Card::SUIT_HEARTS;

    Card card_played3 = cam->play_card(led3, trump3); // Clubs(non-trump) is led
    // Play lowest non-trump (2 diamonds)
    ASSERT_EQUAL(card_played3, Card(Card::RANK_TWO, Card::SUIT_DIAMONDS));
    delete cam;

// TEST 4: Can follow suit (w/ left bower)
    Player * dot = Player_factory("Dot", "Simple");
    dot->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    dot->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    dot->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    dot->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    dot->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    // { J hearts, A diamonds, 10 spades, 9 spades, 9 clubs }

    Card led4(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    string trump4 = Card::SUIT_DIAMONDS;

    Card card_played4 = dot->play_card(led4, trump4); // Diamonds(trump) is led
    // Play highest same-suit card (J hearts) left bower
    ASSERT_EQUAL(card_played4, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    delete dot;
}

// Add more tests here

TEST_MAIN()
