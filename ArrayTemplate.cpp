#include"ArrayTemplate.h"
//template class definition to explicitly instantiate template for compiler and Linker
template class Array<int>; 
// member functions defined outside the class need their own template declaration
template <typename T>
int Array<T>::getLength() const // note class name is Array<T>, not Array
{
	return m_length;
}