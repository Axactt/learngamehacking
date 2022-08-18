#include<array>
#include<iostream>

struct Houses
{
    int number{};
    int stories{};
    int roomPerStories{};
};

int main()
{
    // array type is struct, so each element of array "houses" is a struct of types Houses
    std::array<Houses, 3>houses{};

    houses[0] = { 13, 4, 30 };
    houses[1] = { 14, 3, 10 };
    houses[2] = { 15, 3, 40 };



    /* doesn't work with list initialization
    std::array<Houses, 3> houses{
    { 13, 4, 30 },
    { 14, 3, 10 },
    { 15, 3, 40 }
    };   */

    // To access individual characteristics  value use member selection operator to each houses array element 

    // ranged for loop with loop element " house" initialized as struct data type " Houses";
    // can be written  as type const auto&
    
    for (const auto& house : houses) 
        std::cout << " House number " << house.number << " has " << house.stories * house.roomPerStories << " rooms\n";
   
    return 0;
}