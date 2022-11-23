#include<iostream>
#include<algorithm>
#include<cassert>
#include<array>
#include<algorithm>
#include<random>
#include<string_view>

constexpr int g_maximumScore { 21 };
constexpr int g_dealerScore { 16 };
constexpr int g_aceMaxValue { 11 };
constexpr int g_aceMinValue { 1 };


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


// We'll need these many more times, create an aliases.
using Deck = std::array<Card, 52>;
using Index = Deck::size_type; // size_type is equivalent to size_t

Deck createDeck()
{
	Deck deck {};// Deck is basically std::array of struct Card

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
	// mt is static so it only gets seeded once.
	static std::mt19937 mt { static_cast<std::mt19937::result_type>(std::time( nullptr )) };

	std::shuffle( deck.begin(), deck.end(), mt ); // from algorithm header
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
#include <cassert>

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

bool playBlackJack( Deck& deck) 
{
	Index index { 0 }; // Card number on deck 
	std::cout << " Lets play blackjack. \n";
	
	std::cout << " Dealer takes a card to play with. \n";
	Card dealerCard1 = deck[index];
	int dealerCardValue = getCardValue( dealerCard1 );
	std::cout << "Dealer shows card: ";
	printCard( dealerCard1 );
	std::cout << '\n';

	std::cout << " Get two cards for player. \n";
	++index;
	Card playerCard1 = deck[index];
	std::cout << " Player card 1 is: ";
	printCard( playerCard1 );
	std::cout << '\n';
	++index; // card number on deck increased
	Card playerCard2 = deck[index];
	std::cout << " Player card 2 is: ";
	printCard( playerCard2 );
	std::cout << '\n';

	int playerCardValue { getCardValue( playerCard1 ) + getCardValue( playerCard2 ) };
	std::cout << " Your total cards value is: " << playerCardValue << '\n';
	if ( playerCardValue== g_maximumScore)
	{
		std::cout << " Player card value 21. He gets 1.5 times of initial bet.\n";
		return true; // true condition means player won
	}
	
	std::cout << " Dear Player: Type 1 to HIT(continue) or 0 to STAND(finish turn)\n";
	bool choice {};
	std::cin >> choice;	
	while (choice)
	{

		++index;
		std::cout << " Next player card is: ";
		printCard( deck[index] );
		std::cout << '\n';
		
		playerCardValue += getCardValue( deck[index] );
		std::cout << " Your total cards value is: " << playerCardValue << '\n';
		if (playerCardValue == g_maximumScore)
		{
			std::cout << " Player card value 21. He gets 1.5 times of initial bet.\n";
			return true; // true condition means player won
		}
		else if (deck[index].rank == (CardRank::rank_ace)&&(playerCardValue>g_maximumScore)) 
		{
			playerCardValue = (playerCardValue - g_aceMaxValue) + g_aceMinValue;

		}
		std::cout << " Your total cards value is: " << playerCardValue << '\n';
		if (playerCardValue > g_maximumScore) 
		{
			std::cout << " Go Back Home .\n";
			return false;
		}
		std::cout << "Dear Player: Type 1 to HIT(continue turn) or 0 to STAND(finish turn) \n";
		std::cin >> choice;
	}
	std::cout << " Your total card value is: " << playerCardValue << '\n';
	// Get one card for dealer: Dealer Turn
	
	while (dealerCardValue <= g_dealerScore)
	{
		std::cout << " Dealer card-value is " << dealerCardValue << " less than 17. Dealer Takes anothercard.\n";
			++index;
			std::cout << " Next dealer card is: ";
			printCard( deck[index] );
			std::cout << '\n';
			dealerCardValue += getCardValue( deck[index] );
			// If next card is Ace and total score goes above maximum 21 score
			// Consider ace to be value of 1(g_aceMinValue)
			if (deck[index].rank == (CardRank::rank_ace) && (dealerCardValue > g_maximumScore))
			{
				dealerCardValue = (dealerCardValue - g_aceMaxValue) + g_aceMinValue;

			}

	}
	std::cout << " Value of dealer cards is: " << dealerCardValue;
	
	if (dealerCardValue >= g_maximumScore)
	{
		std::cout << "  Dealer looses. Take double amount. ";
		return true;
	}
	else if (dealerCardValue > playerCardValue)
	{
		std::cout << "  Go back home.\n";
		return false;
	}
	

	else
	{
		std::cout << " Take double amount .\n";
		return true;
	}

}
int main()
{
	auto deck { createDeck() }; // a  deck of card is created here

	shuffleDeck( deck ); // Card deck is shuffled up now
	
	printDeck( deck );

	// Here we will call our playBlackJack() function 
	if (playBlackJack( deck ))
		std::cout << " YOU WON.\n";
	else
		std::cout << " YOU LOST.\n";
	return 0;
}