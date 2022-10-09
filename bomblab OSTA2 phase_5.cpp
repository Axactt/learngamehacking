#include <iostream>


int main()
{
	
	int rbp_24 {0};
	int rbp_64 {};
	int rbp_84 {};
	std::cout<<"input first value\n";
	std::cin>>rbp_64;
	std::cout<<"input Second value\n";
	std::cin>>rbp_84;
	int arr[16] {10,2,14,7,8,12,15,11,0,4,1,13,3,9,6,5};
	int rbp_4 {0};
	while ( rbp_4<16)
	{
		if (rbp_64==15)
		{
			if (rbp_4==15)
			{
				if (rbp_84==rbp_24)
				{
					std::cout<<" answer found\n"; // and 5 and 115
					break;
				}
				else
				{
					std::cout<<" Explode bomb\n";
					break;
				}
			}
			else
			{
				std::cout<<" Explode bomb\n";
				break;
			}

		}
		else
		{
			++rbp_4;
			rbp_64 = arr[rbp_64];
			rbp_24 += rbp_64;
			std::cout<<" rbp_64: "<<rbp_64<<'\n';
			std::cout<<" rbp_24: "<<rbp_24<<'\n';
		}

	}

	return 0;
}



