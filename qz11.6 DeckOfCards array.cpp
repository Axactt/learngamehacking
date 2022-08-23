#include <iostream>
#include<array>
#include<string>
#include<algorithm> // for std::shuffle
#include<random> // for std::mt19937
#include<iterator>
#include<cassert> // for assert

enum class Ranks
{
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    Jack,
    Queen,
    King,
    Ace,

    max_ranks,
};

enum class Suits
{
    clubs,
    diamonds,
    hearts,
    spades,

    max_suits,
};

struct CardType
{
    Ranks cardRank{};
    Suits cardSuit{};
};

 /*  void printCard(const CardType& card)
{
    switch (card.cardRank)
    {
        case(Ranks::two):
        std::cout << '2';
        break;
        case(Ranks::three):
        std::cout << '3';
        break;
        case(Ranks::four):
        std::cout << '4';
        break;
        case(Ranks::five):
        std::cout << '5';
        break;
        case(Ranks::six):
        std::cout << '6';
        break;
        case(Ranks::seven):
        std::cout << '7';
        break;
        case(Ranks::eight):
        std::cout << '8';
        break;
        case(Ranks::nine):
        std::cout << '9';
        break;
        case(Ranks::ten):
        std::cout << '10';
        break;
        case(Ranks::Jack):
        std::cout << 'J';
        break;
        case(Ranks::Queen):
        std::cout << 'Q';
        break;
        case(Ranks::King):
        std::cout << 'K';
        break;
		case(Ranks::Ace):
		std::cout << 'A';
		break;
        default:
        std::cout << '?';
        break;
    }

    switch (card.cardSuit)
    {
        case (Suits::clubs):
        std::cout << 'C';
        break;
        case (Suits::diamonds):
        std::cout << 'D';
        break;
        case (Suits::hearts):
        std::cout << 'H';
        break;
        case (Suits::spades):
        std::cout << 'S';
        break;
        default:
        std::cout << '?';
        break;
    }
}    */



auto getCardValue( const CardType& card1 )
{
	
	switch (card1.cardRank)
	{
		case(Ranks::two):
		 return 2;

		case(Ranks::three):
		 return 3;
	
		case(Ranks::four):
		return 4;

		case(Ranks::five):
		return 5;

		case(Ranks::six):
		 return 6;

		case(Ranks::seven):
		 return 7;

		case(Ranks::eight):
		 return 8;

		case(Ranks::nine):
		 return 9;

		case(Ranks::ten):
	    return 10;

		case(Ranks::Jack):
		 return 10;

		case(Ranks::Queen):
		return 10;

		case(Ranks::King):
		 return 10;

		case(Ranks::Ace):
	     return 11;

		default:
		 assert(false && "should never happen"); // assert being used to returrn an error message in case of default condition 
		 return 0;

	}

	
}  

using array_type = std::array<std::string, 52>;


array_type createDeck(std::array<std::string, 52>& deck)
{
	
	array_type finalDeck  = deck;
	for (int i { 0 }; i < 13; ++i)
	{

		for (int j { 0 }; j < 4; ++j)

		{
			
		   CardType  card1 {static_cast<Ranks>(i) ,static_cast<Suits>(j) };

		   {
			   std::string str1 {};
			   std::string str2 {};
			   std::string str {};
			   switch (card1.cardRank)
			   {
				   case(Ranks::two):
				   str1 = "2";
				   break;
				   case(Ranks::three):
				   str1 = "3";
				   break;
				   case(Ranks::four):
				   str1 = "4";
				   break;
				   case(Ranks::five):
				   str1 = "5";
				   break;
				   case(Ranks::six):
				   str1 = "6";
				   break;
				   case(Ranks::seven):
				   str1 = "7";
				   break;
				   case(Ranks::eight):
				   str1 = "8";
				   break;

				   case(Ranks::nine):
				   str1 = "9";
				   break;
				   case(Ranks::ten):
				   str1 = "10";
				   break;
				   case(Ranks::Jack):
				   str1 = "J";
				   break;
				   case(Ranks::Queen):
				   str1 = "Q";
				   break;
				   case(Ranks::King):
				   str1 = "K";
				   break;
				   case(Ranks::Ace):
				   str1 = "A";
				   break;
				   default:
				   str1 = "?";
				   break;
			   }

			   switch (card1.cardSuit)
			   {
				   case (Suits::clubs):
				   str2 = "C";
				   break;
				   case (Suits::diamonds):
				   str2 = "D";
				   break;
				   case (Suits::hearts):
				   str2 = "H";
				   break;
				   case (Suits::spades):
				   str2 = "S";
				   break;
				   default:
				   str2 = "?";
				   break;
			   }

			     str = str1 + str2;
				 int getSingleIndex { i * 4 + j }; // get single index of two dimensional arary = {(presentRowIndex * numberOfColumnsIn2dArray)+ presentColumnIndex};
				 finalDeck.at( static_cast<std::array<std::string, 52Ui64>::size_type>(getSingleIndex )) = str;
		   }

			
			
		}

	}
	return finalDeck;
}

void printCard( const array_type& deckOfCards )
{
	for (const auto& element : deckOfCards)
		std::cout << element << ',';
}

void shuffleDeck( array_type& deckOfCards ) // shuffleDeck function has return_type void as argument passsed by reference so original parameter changed by function
{
	std::mt19937 mt { static_cast<std::mt19937::result_type>(std::time( nullptr )) };
	std::shuffle( deckOfCards.begin(), deckOfCards.end(), mt );
	
}

int main()
{
    using enum Ranks;
    using enum Suits;
    //CardType card{ five,hearts };
    //printCard(card);
    std::array<std::string, 52> emptyDeckOfCards{};
    // Initializing deckOfCards std::array using createDeck() func callable from main
    createDeck( emptyDeckOfCards );
	std::array<std::string, 52> deckOfCards = { createDeck( emptyDeckOfCards ) };

	printCard( deckOfCards );

	std::cout << '\n' << '\n';
	
	shuffleDeck( deckOfCards );

	printCard( deckOfCards );

	std::cout << '\n'<<'\n';

	CardType card { five,hearts };
	std::cout << getCardValue( card )<<'\n';
	

    return 0;
}