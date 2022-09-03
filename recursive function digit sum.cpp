#include<iostream>

int digitSum( int x )
{
	if (x == 0) 
		return 0;
	else 
		return (x % 10) + digitSum( x / 10 );
}




int main()
{
	std::cout << " enter an integer " << '\n';
	int num {};
	std::cin >> num;

	std::cout << " sum of all digits is: " << digitSum( num );

	return 0;

}