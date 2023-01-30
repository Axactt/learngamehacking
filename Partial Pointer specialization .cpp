#include<iostream>
template <typename T>
class Storage
{
private:
	T m_value;
public:
	Storage( T value )
		:m_value { value }
	{
	}
	~Storage()
	{
		// Explicit destructor has to be defined
	}
	void print() const
	{
		std::cout << m_value << '\n';
	}

};

//full specialized constructor version for char* storage class
//As constructor is function only full or explicit specialization can be done
template<>
 Storage<char*>::Storage(char* const value)	 
 {
	 //Figure out how long the string in value is
	 int length { 0 };
	 while (value[length] != '\0')
		 ++length;
	 ++length; // +1 to account for null terminator
	 //Allocate memory to hold the value string
	 m_value = new char[length];
	 //Copy the actual value string into the m_value memory we just allocated
	 for (int count { 0 }; count < length; ++count)
		 m_value[count] = value[count];
 }
 template<>
 Storage<char*>::~Storage()
 {
	 delete m_value;
 }

 // Partial specialization of Storage class for pointers
 template<typename T>
 class Storage<T*>
 {
 private:
	 T* m_value;
 public:
	 Storage( T* value )
		 :m_value { new T{*value} } //this copies a single value not an array
	 {

	 }
	 ~Storage()
	 {
		 delete m_value;
	 }
	 void print()const
	 {
		 std::cout << *m_value << '\n';
	 }

 };
 int main()
 {
	 // declare a non-pointer storage to show it works
	 Storage<int> myint { 5 };
	 myint.print();

	 //declare a pointer storage to show it works
	 int x { 7 };
	 Storage<int*> myintptr { &x};

	 //Lets show that myintptr is separate from x.
	 // if we change x, myintptr should not change
	 x = 9;
	 myintptr.print();

	 //Dynamically allocate a temporary string
	 char* name { new char[40]{"Alex"} };

	 //Store the name
	 Storage<char*> myname { name };
	 //delete the temporary string
	 delete[]name;

	 //Print out the name to prove we made a copy
	 myname.print();
	 return 0;
 }