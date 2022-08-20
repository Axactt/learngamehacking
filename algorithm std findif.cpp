#include<algorithm>
#include<array>
#include<string_view>
#include<iostream>

//Our function will return true if the element matches
bool containsNuts(std::string_view str)
{
    // std::string_view::find returns std::string_view::npos if it doesn't find
    // the substring. otherwise it returns the index where substring occurs

    return ((str.find("nut")) != std::string_view::npos);
}

// std::find_if to find a value in container that matches some condition
// instaed of passing value we pass in acallable object such as function pointer
// that checks the matching condition


int main()
{
    std::array<std::string_view,4> arr{ "apple","banana","walnut","lemon" };
    // scan our array to see if any elemnt contains substring "nut"
    auto found{ std::find_if(arr.begin(),arr.end(),containsNuts) };

    if (found == arr.end())

        std::cout << " No nuts\n";
    else
        std::cout << "Found " << *found << '\n';

    

    return 0;
}