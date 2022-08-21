#include<algorithm> // std::shuffle
#include<array>
#include<iostream>
#include<ctime>
#include<numeric> // std::reduce
#include<random>

int main()
{
    std::array arr{ 1,2,3,4 };

    std::cout << std::reduce(arr.begin(), arr.end()) << '\n'; // 10 // to add up all list elements

    std::cout << std::accumulate(arr.begin(), arr.end(), 0) << '\n'; // 10

    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

    std::shuffle(arr.begin(), arr.end(), mt); // randomly reordering element using merseene twister

    for (int i : arr)
        std::cout << i << ' ';

    std::cout << '\n';
}