// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());

    Card c1;
    ASSERT_EQUAL(Card::RANK_TWO, c1.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c1.get_suit());
}

TEST(test_get_rank_and_suit) {
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_ACE);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_SPADES);
}

TEST(test_is_face) {
    Card Jack(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card Queen(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card King(Card::RANK_KING, Card::SUIT_CLUBS);
    Card NotFace(Card::RANK_NINE, Card::SUIT_CLUBS);

    ASSERT_TRUE(Jack.is_face());
    ASSERT_TRUE(Queen.is_face());
    ASSERT_TRUE(King.is_face());
    ASSERT_FALSE(NotFace.is_face());
}

TEST(test_is_right_bower) {
    Card r_bow(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card Not_r_bow(Card::RANK_FOUR, Card::SUIT_HEARTS);
    string const trump = Card::SUIT_HEARTS;

    ASSERT_TRUE(r_bow.is_right_bower(trump));
    ASSERT_FALSE(r_bow.is_right_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(r_bow.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Not_r_bow.is_right_bower(trump));
}

TEST(test_is_left_bower) {
    Card l_bow(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card Not_l_bow(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    string const trump = Card::SUIT_HEARTS;

    ASSERT_TRUE(l_bow.is_left_bower(trump));
    ASSERT_FALSE(l_bow.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(l_bow.is_left_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(Not_l_bow.is_left_bower(trump));
}

TEST (test_is_trump) {
    string const trump = Card::SUIT_HEARTS;
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);		 // trump
    Card l_bow(Card::RANK_JACK, Card::SUIT_DIAMONDS);	 // trump (left bow.)
    Card c_fail(Card::RANK_NINE, Card::SUIT_SPADES);	 // not trump

    ASSERT_TRUE(c.is_trump(trump));
    ASSERT_TRUE(l_bow.is_trump(trump));
    ASSERT_FALSE(c_fail.is_trump(trump));

}

TEST(test_logic_operators) {
    Card Large(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card Medium(Card::RANK_ACE, Card::SUIT_SPADES);
    Card Small(Card::RANK_NINE, Card::SUIT_SPADES);

    ASSERT_TRUE(Large > Small);
    ASSERT_TRUE(Large > Medium);
    ASSERT_TRUE(Medium > Small);
    ASSERT_FALSE(Medium > Large);
    ASSERT_FALSE(Large < Small);
    ASSERT_FALSE(Large < Medium);
    ASSERT_TRUE(Large != Small && Large != Medium);
    ASSERT_FALSE(Large == Small && Large == Medium);
    
}

TEST(test_os_operator) {
    Card c(Card::RANK_TWO, Card::SUIT_SPADES);
    ostringstream s;
    s << c;

    // Correct output
    ostringstream correct;
    correct << "Two of Spades";
    ASSERT_EQUAL(s.str(), correct.str());
}

TEST(test_suit_next) {
    string const suit = Card::SUIT_DIAMONDS;
    string const suit2 = Card::SUIT_SPADES;

    ASSERT_EQUAL(Suit_next(suit), Card::SUIT_HEARTS);
    ASSERT_NOT_EQUAL(Suit_next(suit), Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Suit_next(suit2), Card::SUIT_CLUBS);
    ASSERT_NOT_EQUAL(Suit_next(suit2), Card::SUIT_SPADES);
}

TEST(test_card_less_trump) {
    string const trump = Card::SUIT_HEARTS;

    Card r_bow(Card::RANK_JACK, trump);					// Highest
    Card l_bow(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card high_trump(Card::RANK_ACE, trump);
    Card low_trump(Card::RANK_NINE, trump);			  
    Card hi_non(Card::RANK_ACE, Card::SUIT_SPADES);	 
    Card low_non(Card::RANK_NINE, Card::SUIT_SPADES);		 // Lowest

    ASSERT_FALSE(Card_less(r_bow, l_bow, trump));		 // r_bow > ...
    ASSERT_FALSE(Card_less(r_bow, high_trump, trump));
    ASSERT_FALSE(Card_less(r_bow, low_trump, trump));
    ASSERT_FALSE(Card_less(r_bow, hi_non, trump));
    ASSERT_FALSE(Card_less(r_bow, low_non, trump));

    ASSERT_TRUE(Card_less(l_bow, r_bow, trump));		 // l_bow < r_bow
    ASSERT_FALSE(Card_less(l_bow, high_trump, trump));	 // l_bow > ...
    ASSERT_FALSE(Card_less(l_bow, low_trump, trump));
    ASSERT_FALSE(Card_less(l_bow, hi_non, trump));
    ASSERT_FALSE(Card_less(l_bow, low_non, trump));

    ASSERT_TRUE(Card_less(high_trump, r_bow, trump));	 // high_trump < r_bow
    ASSERT_TRUE(Card_less(high_trump, l_bow, trump));	 // high_trump < l_bow
    ASSERT_FALSE(Card_less(high_trump, low_trump, trump)); // high_trump > ...
    ASSERT_FALSE(Card_less(high_trump, hi_non, trump));
    ASSERT_FALSE(Card_less(high_trump, low_non, trump));

    ASSERT_TRUE(Card_less(low_trump, r_bow, trump));		// low_trump < r_bow
    ASSERT_TRUE(Card_less(low_trump, l_bow, trump));		// low_trump < l_bow
    ASSERT_TRUE(Card_less(low_trump, high_trump, trump));	// low_trump < high_trump
    ASSERT_FALSE(Card_less(low_trump, hi_non, trump));	     // low_trump > ...
    ASSERT_FALSE(Card_less(low_trump, low_non, trump));

    ASSERT_TRUE(Card_less(hi_non, r_bow, trump));		// hi_non < r_bow
    ASSERT_TRUE(Card_less(hi_non, l_bow, trump));		// hi_non < l_bow
    ASSERT_TRUE(Card_less(hi_non, high_trump, trump));	// hi_non < high_trump
    ASSERT_TRUE(Card_less(hi_non, low_trump, trump));  // hi_non < low_trump
    ASSERT_FALSE(Card_less(hi_non, low_non, trump));   // hi_non > ...

    ASSERT_TRUE(Card_less(low_non, r_bow, trump));	 // low_non < ...
    ASSERT_TRUE(Card_less(low_non, l_bow, trump));		
    ASSERT_TRUE(Card_less(low_non, high_trump, trump));
    ASSERT_TRUE(Card_less(low_non, low_trump, trump));
    ASSERT_TRUE(Card_less(low_non, hi_non, trump));
}

TEST(test_card_less_trump_led_card) {
    string const trump = Card::SUIT_HEARTS;
    string const led_suit = Card::SUIT_SPADES;
    Card const led_card(Card::RANK_KING, led_suit);

    Card r_bow(Card::RANK_JACK, trump);					// Highest
    Card l_bow(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card high_trump(Card::RANK_ACE, trump);
    Card low_trump(Card::RANK_NINE, trump);
    Card hi_led(Card::RANK_ACE, led_suit);
    Card low_led(Card::RANK_NINE, led_suit);
    Card hi_non(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card low_non(Card::RANK_NINE, Card::SUIT_CLUBS);		 // Lowest

    ASSERT_FALSE(Card_less(r_bow, l_bow, led_card, trump));		 // r_bow > ...
    ASSERT_FALSE(Card_less(r_bow, high_trump, led_card, trump));
    ASSERT_FALSE(Card_less(r_bow, low_trump, led_card, trump));
    ASSERT_FALSE(Card_less(r_bow, hi_led, led_card, trump));
    ASSERT_FALSE(Card_less(r_bow, low_led, led_card, trump));
    ASSERT_FALSE(Card_less(r_bow, hi_non, led_card, trump));
    ASSERT_FALSE(Card_less(r_bow, low_non, led_card, trump));

    ASSERT_TRUE(Card_less(l_bow, r_bow, led_card, trump));		 // l_bow < r_bow
    ASSERT_FALSE(Card_less(l_bow, high_trump, led_card, trump));	 // l_bow > ...
    ASSERT_FALSE(Card_less(l_bow, low_trump, led_card, trump));
    ASSERT_FALSE(Card_less(l_bow, hi_led, led_card, trump));
    ASSERT_FALSE(Card_less(l_bow, low_led, led_card, trump));
    ASSERT_FALSE(Card_less(l_bow, hi_non, led_card, trump));
    ASSERT_FALSE(Card_less(l_bow, low_non, led_card, trump));

    ASSERT_TRUE(Card_less(high_trump, r_bow, led_card, trump));	 // high_trump < r_bow
    ASSERT_TRUE(Card_less(high_trump, l_bow, led_card, trump));	 // high_trump < l_bow
    ASSERT_FALSE(Card_less(high_trump, low_trump, led_card, trump)); // high_trump > ...
    ASSERT_FALSE(Card_less(high_trump, hi_led, led_card, trump));
    ASSERT_FALSE(Card_less(high_trump, low_led, led_card, trump));
    ASSERT_FALSE(Card_less(high_trump, hi_non, led_card, trump));
    ASSERT_FALSE(Card_less(high_trump, low_non, led_card, trump));

    ASSERT_TRUE(Card_less(low_trump, r_bow, led_card, trump));		// low_trump < r_bow
    ASSERT_TRUE(Card_less(low_trump, l_bow, led_card, trump));		// low_trump < l_bow
    ASSERT_TRUE(Card_less(low_trump, high_trump, led_card, trump));	// low_trump < high_trump
    ASSERT_FALSE(Card_less(low_trump, hi_led, led_card, trump));	     // low_trump > ...
    ASSERT_FALSE(Card_less(low_trump, low_led, led_card, trump));
    ASSERT_FALSE(Card_less(low_trump, hi_non, led_card, trump));	    
    ASSERT_FALSE(Card_less(low_trump, low_non, led_card, trump));

    ASSERT_TRUE(Card_less(hi_led, r_bow, led_card, trump));		// hi_led < r_bow
    ASSERT_TRUE(Card_less(hi_led, l_bow, led_card, trump));		// hi_led < l_bow
    ASSERT_TRUE(Card_less(hi_led, high_trump, led_card, trump));	// hi_led < high_trump
    ASSERT_TRUE(Card_less(hi_led, low_trump, led_card, trump));  // hi_led < low_trump
    ASSERT_FALSE(Card_less(hi_led, low_led, led_card, trump));   // hi_led > ...
    ASSERT_FALSE(Card_less(hi_led, hi_non, led_card, trump));  
    ASSERT_FALSE(Card_less(hi_led, low_non, led_card, trump));   

    ASSERT_TRUE(Card_less(low_led, r_bow, led_card, trump));		// low_led < r_bow
    ASSERT_TRUE(Card_less(low_led, l_bow, led_card, trump));		// low_led < l_bow
    ASSERT_TRUE(Card_less(low_led, high_trump, led_card, trump));	// low_led < high_trump
    ASSERT_TRUE(Card_less(low_led, low_trump, led_card, trump));		// low_led < low_trump
    ASSERT_TRUE(Card_less(low_led, hi_led, led_card, trump));		// low_led < hi_led
    ASSERT_FALSE(Card_less(low_led, hi_non, led_card, trump));	     // low_led > ...
    ASSERT_FALSE(Card_less(low_led, low_non, led_card, trump));

    ASSERT_TRUE(Card_less(hi_non, r_bow, led_card, trump));		   // hi_non < r_bow
    ASSERT_TRUE(Card_less(hi_non, l_bow, led_card, trump));		   // hi_non < l_bow
    ASSERT_TRUE(Card_less(hi_non, high_trump, led_card, trump));	   // hi_non < high_trump
    ASSERT_TRUE(Card_less(hi_non, low_trump, led_card, trump));	   // hi_non < low_trump
    ASSERT_TRUE(Card_less(hi_non, hi_led, led_card, trump));	   // hi_non < hi_led
    ASSERT_TRUE(Card_less(hi_non, low_led, led_card, trump));	   // hi_non < low_led
    ASSERT_FALSE(Card_less(hi_non, low_non, led_card, trump));	   // hi_non > ...

    ASSERT_TRUE(Card_less(low_non, r_bow, led_card, trump));   // low_non < ...
    ASSERT_TRUE(Card_less(low_non, l_bow, led_card, trump));		 
    ASSERT_TRUE(Card_less(low_non, high_trump, led_card, trump));	   
    ASSERT_TRUE(Card_less(low_non, low_trump, led_card, trump));	  
    ASSERT_TRUE(Card_less(low_non, hi_led, led_card, trump));	  
    ASSERT_TRUE(Card_less(low_non, low_led, led_card, trump));	  
    ASSERT_TRUE(Card_less(low_non, hi_non, led_card, trump));
}
// Add more test cases here

TEST_MAIN()
