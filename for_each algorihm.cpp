#include <iostream>
#include<algorithm>
#include<array>

void doubleNumber(int& i)
{
    i *= 2;
}

int main()
{
    std::array<int, 5> list {1, 2, 3, 4, 5};

    std::ranges::for_each(list, doubleNumber); // std::ranges used in place of std::for_each(list.begin(),list.end(),doubleNumber)

    for (auto e : list)
        std::cout << e << ' ';

    std::cout << '\n';
    return 0;
}