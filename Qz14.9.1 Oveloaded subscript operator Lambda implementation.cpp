#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

struct StudentGrade
{
	std::string name {};
	char grade {};
};

class GradeMap
{
private:
	std::vector<StudentGrade> m_map {};
public:
	GradeMap() = default;
	char& operator[]( std::string studentName);
	
};

char& GradeMap::operator[]( std::string studentName )
{ // use of Lambda as a predicate to compare the given name
 // std::find_if algorithm automatically provides/ passes  vector elements of m_map (which are struct) as parameter to Lambda 
 // for comparison which Lambda then chooses how elements are compared against each other
	//std::find_if returns the iterator back as type "auto" which is iterator_type and name as found
	// Dereferncing this iterator will give underlying struct-member which is element of vector of class-type
	auto found { std::find_if( m_map.begin(),m_map.end(),
							  [&](const auto& a)
							  {
							  return(a.name == studentName);
                              
                              }
	                          )};  

	if (found == m_map.end())
	{
		// Using dereferenced iterator to allocate stuct-member which are element of vector_member_Variable of Class
		// std::vector::push_back() used to add Struct Data member to the class_memnber_variable m_map of vector type
		m_map.push_back( {std::string { studentName }} );
		// StudentGrade lastGrade { m_map.back() }; // if create a variable like this the program won't work?????????

		// Dirctly chain std::vector::back() to retrieve last member of vectorm_map and chain it with member selection operator to get struct element
		// By doing direct-chaining of std::vector::back() we retrieve the original present member of vector m_map,  
		// This when returned by non-const l-value reference is modifiable and can be changed/assigned by caller to give it some value
		return m_map.back().grade;
	}

		return found->grade;

}

int main()
{
	GradeMap grades { };
	// Here overloaded operator[]( ...grades.operator[](arg1)......) is returned by non-const l-value reference , so it can be assigned a different value.
	(grades["Joe"]) = 'A';
	
	grades.operator[]( "Axat" )= 'A';
	grades["Frank"] = 'B';
	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
	std::cout << "Axat has a grade of " << grades.operator[]( "Axat" ) << '\n';
	return 0;

}