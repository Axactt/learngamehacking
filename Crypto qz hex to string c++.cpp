#define __STDC_WANT_LIB_EXT1__ 1
#include<cstring>
#include<iostream>
#include<iterator>




int main()
{
	 char hexString[]{"63727970746f7b596f755f77696c6c5f62655f776f726b696e675f776974685f6865785f737472696e67735f615f6c6f747d"};

	int length{ static_cast<int>(std::strlen(hexString))};

	char dest2[2]{};
	for (int i{ 0 }; i < length; i += 2)
	{
     
		char* charBytes{ strncpy(dest2,hexString[i],2) };

	}

	return 0;
}