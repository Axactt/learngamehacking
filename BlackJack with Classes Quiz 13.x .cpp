#include <algorithm> // std::shuffle
#include <array>
#include <cassert>
#include <ctime> // std::time
#include <iostream>
#include <random> // std::mt19937
/*
enum class CardSuit
{
	club,
	diamond,
	heart,
	spade,

	max_suits
};

enum class CardRank
{
	rank_2,
	rank_3,
	rank_4,
	rank_5,
	rank_6,
	rank_7,
	rank_8,
	rank_9,
	rank_10,
	rank_jack,
	rank_queen,
	rank_king,
	rank_ace,

	max_ranks
};

struct Card
{
	CardRank rank {};
	CardSuit suit {};
};

struct Player
{
	int score {};
};

using Deck = std::array<Card, 52>;
using Index = Deck::size_type;

// Maximum score before losing.
constexpr int g_maximumScore { 21 };

// Minimum score that the dealer has to have.
constexpr int g_minimumDealerScore { 17 };

void printCard( const Card& card )
{
	switch (card.rank)
	{
		case CardRank::rank_2:      std::cout << '2';   break;
		case CardRank::rank_3:      std::cout << '3';   break;
		case CardRank::rank_4:      std::cout << '4';   break;
		case CardRank::rank_5:      std::cout << '5';   break;
		case CardRank::rank_6:      std::cout << '6';   break;
		case CardRank::rank_7:      std::cout << '7';   break;
		case CardRank::rank_8:      std::cout << '8';   break;
		case CardRank::rank_9:      std::cout << '9';   break;
		case CardRank::rank_10:     std::cout << 'T';   break;
		case CardRank::rank_jack:   std::cout << 'J';   break;
		case CardRank::rank_queen:  std::cout << 'Q';   break;
		case CardRank::rank_king:   std::cout << 'K';   break;
		case CardRank::rank_ace:    std::cout << 'A';   break;
		default:
		std::cout << '?';
		break;
	}

	switch (card.suit)
	{
		case CardSuit::club:       std::cout << 'C';   break;
		case CardSuit::diamond:    std::cout << 'D';   break;
		case CardSuit::heart:      std::cout << 'H';   break;
		case CardSuit::spade:      std::cout << 'S';   break;
		default:
		std::cout << '?';
		break;
	}
}

int getCardValue( const Card& card )
{
	switch (card.rank)
	{
		case CardRank::rank_2:        return 2;
		case CardRank::rank_3:        return 3;
		case CardRank::rank_4:        return 4;
		case CardRank::rank_5:        return 5;
		case CardRank::rank_6:        return 6;
		case CardRank::rank_7:        return 7;
		case CardRank::rank_8:        return 8;
		case CardRank::rank_9:        return 9;
		case CardRank::rank_10:       return 10;
		case CardRank::rank_jack:     return 10;
		case CardRank::rank_queen:    return 10;
		case CardRank::rank_king:     return 10;
		case CardRank::rank_ace:      return 11;
		default:
		assert( false && "should never happen" );
		return 0;
	}
}

void printDeck( const Deck& deck )
{
	for (const auto& card : deck)
	{
		printCard( card );
		std::cout << ' ';
	}

	std::cout << '\n';
}

Deck createDeck()
{
	Deck deck {};

	// We could initialize each card individually, but that would be a pain.  Let's use a loop.

	Index index { 0 };

	for (int suit { 0 }; suit < static_cast<int>(CardSuit::max_suits); ++suit)
	{
		for (int rank { 0 }; rank < static_cast<int>(CardRank::max_ranks); ++rank)
		{
			deck[index].suit = static_cast<CardSuit>(suit);
			deck[index].rank = static_cast<CardRank>(rank);
			++index;
		}
	}

	return deck;
}

void shuffleDeck( Deck& deck )
{
	static std::mt19937 mt { static_cast<std::mt19937::result_type>(std::time( nullptr )) };

	std::shuffle( deck.begin(), deck.end(), mt );
}

bool playerWantsHit()
{
	while (true)
	{
		std::cout << "(h) to hit, or (s) to stand: ";

		char ch {};
		std::cin >> ch;

		switch (ch)
		{
			case 'h':
			return true;
			case 's':
			return false;
		}
	}
}

// Returns true if the player went bust. False otherwise.
bool playerTurn( const Deck& deck, Index& nextCardIndex, Player& player )
{
	while (true)
	{
		if (player.score > g_maximumScore)
		{
			// This can happen even before the player had a choice if they drew 2
			// aces.
			std::cout << "You busted!\n";
			return true;
		}
		else
		{
			if (playerWantsHit())
			{
				int cardValue { getCardValue( deck.at( nextCardIndex++ ) ) };
				player.score += cardValue;
				std::cout << "You were dealt a " << cardValue << " and now have " << player.score << '\n';
			}
			else
			{
				// The player didn't go bust.
				return false;
			}
		}
	}
}

// Returns true if the dealer went bust. False otherwise.
bool dealerTurn( const Deck& deck, Index& nextCardIndex, Player& dealer )
{
	// Draw cards until we reach the minimum value.
	while (dealer.score < g_minimumDealerScore)
	{
		int cardValue { getCardValue( deck.at( nextCardIndex++ ) ) };
		dealer.score += cardValue;
		std::cout << "The dealer turned up a " << cardValue << " and now has " << dealer.score << '\n';

	}

	// If the dealer's score is too high, they went bust.
	if (dealer.score > g_maximumScore)
	{
		std::cout << "The dealer busted!\n";
		return true;
	}

	return false;
}

bool playBlackjack( const Deck& deck )
{
	// Index of the card that will be drawn next. This cannot overrun
	// the array, because a player will lose before all cards are used up.
	Index nextCardIndex { 0 };

	// Create the dealer and give them 1 card.
	Player dealer { getCardValue( deck.at( nextCardIndex++ ) ) };

	// The dealer's card is face up, the player can see it.
	std::cout << "The dealer is showing: " << dealer.score << '\n';

	// Create the player and give them 2 cards.
	Player player { getCardValue( deck.at( nextCardIndex ) ) + getCardValue( deck.at( nextCardIndex + 1 ) ) };
	nextCardIndex += 2;

	std::cout << "You have: " << player.score << '\n';

	if (playerTurn( deck, nextCardIndex, player ))
	{
		// The player went bust.
		return false;
	}

	if (dealerTurn( deck, nextCardIndex, dealer ))
	{
		// The dealer went bust, the player wins.
		return true;
	}

	return (player.score > dealer.score);
}

int main()
{
	auto deck { createDeck() };

	shuffleDeck( deck );

	if (playBlackjack( deck ))
	{
		std::cout << "You win!\n";
	}
	else
	{
		std::cout << "You lose!\n";
	}

	return 0;
}    */


// Maximum score before losing.
constexpr int g_maximumScore { 21 };

// Minimum score that the dealer has to have.
constexpr int g_minimumDealerScore { 17 };

class Card 
{
public:

	
	enum CardRank
	{
		rank_2,
		rank_3,
		rank_4,
		rank_5,
		rank_6,
		rank_7,
		rank_8,
		rank_9,
		rank_10,
		rank_jack,
		rank_queen,
		rank_king,
		rank_ace,

		max_ranks
	};
	enum  CardSuit
	{
		club,
		diamond,
		heart,
		spade,

		max_suits
	};

private:
	CardRank m_rank{};
	CardSuit m_suit{};
public:
	 Card() = default; // default constructor
	
	 //Initialization of card object with member attribute of rank and suit
	Card(CardRank rank , CardSuit suit ) :
		m_rank { rank }, m_suit { suit } 
	{

	}
	void print()const 
	{
		switch (m_rank)
		{
			case CardRank::rank_2:      std::cout << '2';   break;
			case CardRank::rank_3:      std::cout << '3';   break;
			case CardRank::rank_4:      std::cout << '4';   break;
			case CardRank::rank_5:      std::cout << '5';   break;
			case CardRank::rank_6:      std::cout << '6';   break;
			case CardRank::rank_7:      std::cout << '7';   break;
			case CardRank::rank_8:      std::cout << '8';   break;
			case CardRank::rank_9:      std::cout << '9';   break;
			case CardRank::rank_10:     std::cout << 'T';   break;
			case CardRank::rank_jack:   std::cout << 'J';   break;
			case CardRank::rank_queen:  std::cout << 'Q';   break;
			case CardRank::rank_king:   std::cout << 'K';   break;
			case CardRank::rank_ace:    std::cout << 'A';   break;
			default:
			std::cout << '?';
			break;
		}

		switch (m_suit)
		{
			case CardSuit::club:       std::cout << 'C';   break;
			case CardSuit::diamond:    std::cout << 'D';   break;
			case CardSuit::heart:      std::cout << 'H';   break;
			case CardSuit::spade:      std::cout << 'S';   break;
			default:
			std::cout << '?';
			break;
		}
	}

	int value(  ) const
	{
		switch (m_rank)
		{
			case CardRank::rank_2:        return 2;
			case CardRank::rank_3:        return 3;
			case CardRank::rank_4:        return 4;
			case CardRank::rank_5:        return 5;
			case CardRank::rank_6:        return 6;
			case CardRank::rank_7:        return 7;
			case CardRank::rank_8:        return 8;
			case CardRank::rank_9:        return 9;
			case CardRank::rank_10:       return 10;
			case CardRank::rank_jack:     return 10;
			case CardRank::rank_queen:    return 10;
			case CardRank::rank_king:     return 10;
			case CardRank::rank_ace:      return 11;
			default:
			assert( false && "should never happen" );
			return 0;
		}
	}
};
using Index = std::array<Card, 52>::size_type; // create a size_type type-alias for std::array<type,size>::size_type
class Deck
{
private:
	std::array<Card, 52> m_deck {};
	Index   m_cardIndex {};

public:
	Deck() 
	{
		// We could initialize each card individually, but that would be a pain.  Let's use a loop.

		Index index { 0 };

		 for (int suit { 0 }; suit < static_cast<int>(Card::max_suits); ++suit) // 
		 {
			 for (int rank { 0 }; rank < static_cast<int>(Card::max_ranks); ++rank)
			 {
				 // m_deck is std::array<Card,52> with elements of type Card
				 //m_deck[index] is value of a particular Card, of type class Card object being placed in std::array<Card,52> m_deck{}
				 //m_deck[index] is initialised with temporary object matching class Card constructor with type  of Card(arg1,arg2)
				 // List initialization takes care of initializing temporary object to particaular card value
				 // for-Loop variable rank and suit are static-cast'ed to enum Card::CardRank and enum Card::CardSuit 
				 //This will initialise the individual  Card elements of std::array<Card,52>m_deck array
				 m_deck[index] = {static_cast<Card::CardRank>(rank),static_cast<Card::CardSuit>(suit) };
				 ++index;
			 }
		 }
	}
	void print() const
	{
		for (const auto& card : m_deck)
		{
			// as each member of array m_deck is basically type Card class object
			// the public member function of Class Card can be used directly with member resolution opeartor for elements of array m_deck
			card.print();
			std::cout << ' ';
		}
		std::cout << '\n';
	}
	void shuffle() 
	{
		static std::mt19937 mt { static_cast<std::mt19937::result_type>(std::time( nullptr )) };

		std::shuffle( m_deck.begin(), m_deck.end(), mt );
		m_cardIndex = 0;
	}
	// takes a Card element from deck-class member card-array, 
	// returns the Present card and increases card Index 
	// card Index now represents the index of next top card on deck

	const Card& dealCard() 
	{
		assert( m_cardIndex < m_deck.size());
		return m_deck[m_cardIndex++];

	}

	Index getCardIndex() const // getter function for deck card index
	{
		return m_cardIndex;

	}

	const std::array<Card, 52>& getCardDeck() const // getter function to get whole deck of card as an array
	{
		return m_deck;
	}
};

class Player 
{
private:
	int m_playerScore {};

	
public:
	Player() = default;
	
	int drawCard( Deck& deck )

	{ 
		// Player given a card from deck and value has been logged
		int cardValue = deck.dealCard().value();
        // playerScore should be tied with the drwaCard function
		// Each time drawCard function activated, playerScore will be increased by cardValue.
		m_playerScore += cardValue;
		return cardValue;
	}
	int score() const
	{
		return m_playerScore;
    }

	bool isBurst() const
	{
		return (m_playerScore > g_maximumScore);
			
	}
	
};
bool playerWantsHit()
{
	while (true)
	{
		std::cout << "(h) to hit, or (s) to stand: ";

		char ch {};
		std::cin >> ch;

		switch (ch)
		{
			case 'h':
			return true;
			case 's':
			return false;
		}
	}
}
//Returns true if player lost and got Busted. False otherwise
bool PlayerTurn(  Player& player, Deck& deck ) 
{
	while (true) 
	{
		if (player.isBurst()) 
		{
			std::cout << " You bursted.\n";
				return true;
		}
		else 
		{
			if (playerWantsHit()) 
			{	
				//C++ does not have many guarantees in order in which expression evaluates
	//Either player.drawCard() or player.score() could evaluate first. normally this wouldn't matter , but player.drawCrad() has side effect
	//of modifying the score that player.score() returns. if player.score() evaluates first, it will return score before card is drawn, which 
	// is not what we want. 
	// In the former snippet,we put the card draw as a separate statement in order to guarantee that it executes first
	// s0 player.score() will return the score after the card draw.
				int playerCard { player.drawCard( deck ) };
				std::cout << "You were dealt with a card of " << playerCard << " and now have a score of " << player.score() << '\n';
			}
			else 
			{
				//player didn't go burst
				return false;
			}
		}
			

	}

}
// returns true if dealer got bursted, false otherwise.
bool DealerTurn( Player& dealer, Deck& deck )
{
	//Draws untill we reach a minimum value
	while (dealer.score() < g_minimumDealerScore)
	{
		//C++ does not have many guarantees in order in which expression evaluates
	//Either player.drawCard() or player.score() could evaluate first. normally this wouldn't matter , but player.drawCrad() has side effect
	//of modifying the score that player.score() returns. if player.score() evaluates first, it will return score before card is drawn, which 
	// is not what we want. 
	// In the former snippet,we put the card draw as a separate statement in order to guarantee that it executes first
	// s0 player.score() will return the score after the card draw.
		int dealerCard { dealer.drawCard( deck ) };
		std::cout << "The dealer turned up a " << dealerCard << " and now has " << dealer.score() << '\n';
	}
	// If the dealer's score is too high, they went bust.
	if (dealer.score() > g_maximumScore)
	{
		std::cout << "The dealer busted!\n";
		return true;
	}

	return false;

}

//playBlackJack outcome function returns true when player wins
bool playBlackJack( Player& player,Player& dealer, Deck& deck ) 
{
	//C++ does not have many guarantees in order in which expression evaluates
	//Either player.drawCard() or player.score() could evaluate first. normally this wouldn't matter , but player.drawCrad() has side effect
	//of modifying the score that player.score() returns. if player.score() evaluates first, it will return score before card is drawn, which 
	// is not what we want. 
	// In the former snippet,we put the card draw as a separate statement in order to guarantee that it executes first
	// s0 player.score() will return the score after the card draw.
	int dealerCard { dealer.drawCard( deck ) };
	std::cout << "The dealer drew a card with value " << dealerCard << " and now has score " << dealer.score() << '\n';
	// Player gets his turn first
	std::cout << " Player gets his first card with value: " << player.drawCard( deck )<<'\n';
	std::cout << " Player gets his 2nd card with value: " << player.drawCard( deck )<<'\n';
	std::cout << " Player's score is now: " << player.score()<<'\n';
	// Player turn to play
	if (PlayerTurn( player, deck ))
		//player went burst
		return false;
	// Dealer Turn to play
	if (DealerTurn( dealer, deck ))
		// The dealer went burst, you win
		return true;
	if (player.score() > dealer.score())
		// Player wins
		return true;

}


int main()
{
	/*
	const Card cardQueenHearts { Card::rank_queen, Card::heart };
	//Card cardQueenHearts {}; // usi
	cardQueenHearts.print();
	std::cout << " has the value " << cardQueenHearts.value() << '\n'; */

	Deck deck {};
	
    deck.shuffle();
	deck.print();
	
	Player player {};
	Player dealer {};
	
	if (playBlackJack( player, dealer, deck ))
		std::cout << " You win. \n";
	else
		std::cout << " You Lost. \n";
	return 0;

}