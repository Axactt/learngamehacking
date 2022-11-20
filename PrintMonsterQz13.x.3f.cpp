#include<string>
#include<string_view>
#include<iostream>


class Monster
{
	// nested type should be declared on topmost part under public specifier. this will ensure two things:
	//a) nested-type are acccessible outside class, althogh with scope-resolution oprator(enclosing class as namespace)
	//b) nested-type not forward declared,other members should see full definition.
public:
	enum class Type
	{
		Dragon,
		Goblin,
		Ogre,
		Orc,
		Skeleton,
		Troll,
		Vampire,
		Zombie,
		max_monster_types,
	};
private:
	Type m_type {};
	std::string m_name {};
	std::string m_roar {};
	int m_hitPoints {};
public:

	Monster( Type type, const std::string& name, const std::string& roar, int hits )
		:m_type { type }, m_name { name }, m_roar { roar }, m_hitPoints { hits }
	{

	}

	constexpr std::string_view getTypeString( ) const
	{
		switch (m_type) 
		{
			case (Monster::Type::Dragon):
				return "Dragon";
			case (Monster::Type::Goblin):
			return "Goblin";
			case (Monster::Type::Ogre):
			return "Ogre";
			case (Monster::Type::Orc):
			return "Orc";
			case (Monster::Type::Skeleton):
			return "Skeleton";
			case (Monster::Type::Troll):
			return "Troll";
			case (Monster::Type::Vampire):
			return "Vampire";
			case (Monster::Type::Zombie):
			return "Zombie";
			default:
			return "???";
		}

	}

	void print() const
	{
		std::cout << m_name << " the " << getTypeString() << " has " << m_hitPoints << " hit-points and says " << m_roar << '\n';
	}
};

int main()
{
	Monster skeleton { Monster::Type::Skeleton,"Bones","rattles",4 };
	skeleton.print();

	return 0;


}