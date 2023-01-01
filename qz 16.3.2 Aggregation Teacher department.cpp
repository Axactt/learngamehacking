#include<iostream>
#include<functional>
#include <string_view>

class Teacher
{
private:
	std::string m_name {};
public:
	Teacher(std::string_view name)
		:m_name{name}{ }
	std::string_view getName() const
	{
		return m_name;
	}
};

class Department
{
private:
	std::vector<std::reference_wrapper<const Teacher>> m_teachers{};

public:
	Department() = default;
	void add(const Teacher& teacher)
	{
		m_teachers.push_back(teacher);
	}
	friend std::ostream& operator<<(std::ostream& out, const Department& department)
	{
		out << "Department: ";
		for ( const auto& elem : department.m_teachers)
		{
			out <<elem.get().getName()<<' ';
		}
		out << '\n';
		return out;

	}
};


int main()
{
	// Create a teacher oustside the scope of the Department
	Teacher t1 { "Bob" };
	Teacher t2 { "Frank" };
	Teacher t3 { "Beth" };
	{
		// Create a department and add some teachers to it
		Department department {};

		department.add(t1);
		department.add(t2);
		department.add(t3);

		std::cout << department;

	}// department goes out of scope here and is destroyed

	std::cout << t1.getName() << " still exists!\n";
	std::cout << t2.getName() << " still exists!\n";
	std::cout << t3.getName() << " still exists!\n";

	return 0;
}

