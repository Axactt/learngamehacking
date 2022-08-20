#include<functional>
#include<algorithm>
#include<array>
#include<iostream>

void sort(int* begin, int* end, std::function<bool(int, int)>compare)
{
    for (auto startElement{ begin }; startElement != end; ++startElement)
    {
        auto smallestElement{ startElement };
        for (auto currentElement{ std::next(startElement) }; currentElement != end; ++currentElement)
            if (compare(*currentElement, *smallestElement))
                smallestElement = currentElement;
        std::swap(*startElement, *smallestElement);
    }
}


int main()
{
    int   array[]{2,1,9,4,5};
    
    // use greater to sort in descending oreder
    // (we have to use the global namespace selector to prevent collision 
    // between our sort function and std::sort.

    ::sort(std::begin(array), std::end(array), std::greater{});

    for (auto i : array)
        std::cout << i << '\t';
    std::cout << '\n';

    return 0;
}
