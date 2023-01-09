#include<iostream>
#include<string>
class Fruit
{
private:
	const std::string& m_name {}; // works only if const and & are removed
	const std::string& m_color {}; // works only if const and & are removed
public:
	Fruit( const std::string& name ,  const std::string& color )
		:m_name { name }, m_color { color }
	{
		
	}
	 const std::string& getName() const
	{
		return m_name;
	}
	const   std::string& getColor()const
	{
		return m_color;
	}
};

class Apple : public Fruit
{
private:
	double m_fiber {};
public:
	Apple(const std::string& name, const std::string& color , double fiber = 0.0)
		: Fruit { name,color },m_fiber { fiber }
	{
		
	}
	friend std::ostream& operator<<(std::ostream& out, const Apple& apl);
	/* {
		out << "Apple (" << apl.getname() << ',' << apl.getColor() << ',' << apl.m_fiber << ')' << '\n';
		return out;
	}*/
};

class Banana : public Fruit
{
public:
	Banana(const std::string& name , const std::string& color )
		:Fruit { name,color }{ }
	friend std::ostream& operator<<(std::ostream& out, const Banana& ban);

};
std::ostream& operator<<(std::ostream& out, const Apple& apl)
{
	out << "Apple (" << apl.getName() << ", " << apl.getColor() << ", " << apl.m_fiber << ')' << '\n';
	return out;
}
std::ostream& operator<<(std::ostream& out, const Banana& ban)
{
	out << "Banana (" << ban.getName() << ", " << ban.getColor() << ")\n";
	return out;
}

int main()
{
	const Apple a { "Red delicious","red",4.2 };
  std::cout << a << '\n';

  const Banana b { "Cavendish","yellow" };
std::cout << b << '\n';
	return 0;
}

