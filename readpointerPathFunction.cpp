#include<iostream>
#include<vector>



int readPointerPath(std::vector<uintptr_t>& chain)
{
    int retValue = *(reinterpret_cast <int*> (chain[0]));
 
   for (int i{ 1 }; i < static_cast<int>(chain.size()); ++i)
   {
          retValue = *(reinterpret_cast<int*> (retValue + chain[i]));    
   }
  
   return retValue;
}

int main()
{
    std::cout << " Enter the list and offset to pointer path "<<'\n';
    std::vector<uintptr_t> chain{ 0xDEADBEEF,0xAB,0x10,0xCC };
    std::cout<<std::hex<<readPointerPath(chain);
    return 0;
}
