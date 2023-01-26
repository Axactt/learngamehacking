#include<iostream>
#include"ArrayTemplate.h"

int main()
{
	Array<int> intArray { 12 }; // class instantiation at this point here
	Array<double> doubleArray { 12 };

	for (int count { 0 }; count < intArray.getLength(); ++count)
	{
		intArray[count] = count;
		doubleArray[count] = count + 0.5;
	}
	for (int count { intArray.getLength() - 1 }; count >= 0; --count)
		std::cout << intArray[count] << '\t' << doubleArray[count] << '\n';
	return 0;
}