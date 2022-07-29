#include <iostream>
#include<iterator>

void charPrint(int* array,int arrayLength)
{
    for (int i{ 0 }; i < arrayLength; ++i)
    {
        std::cout << char{ static_cast<char>(array[i]) };
    }
}




int main()
{
    int array[]{ 99, 114, 121, 112, 116, 111, 123, 65, 83, 67, 73, 73, 95, 112, 114, 49, 110, 116, 52, 98, 108, 51, 125 };
    int arrayLength{ static_cast<int>(std::size(array)) };

    charPrint(array, arrayLength);

    return 0;
    
}
