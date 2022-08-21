#include<iostream>

void printCharacter( char* str,int len)
    {
    for (char* p{ str }; p != str + len; ++p) // pointer iterator with ptr arithmentic as data stored sequentially in memory
    {
        std::cout<<'\n' << *p ;
        
    }

    }
int main()
{
    char cString[]{ "Hello,world!" };

    int stringLength{ static_cast<int>(std::size(cString)) };
    
    printCharacter(cString,stringLength-1); // stringLength-1 to avoid printing last null terminator character'\0'
   
    return 0;
}