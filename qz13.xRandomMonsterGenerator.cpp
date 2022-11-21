#include<iostream>
#include<string_view>
#include<random> // for std::mt19337,std::random_device & std::uniform_int_distribution
#include<array>
class Monster 
{
public: // MONOSTate class with all members being created static
	// use of static inline to declare as well ass define  member 
	 enum class Type
	{
		dragon,
		goblin,
		ogre,
		orc,
		skeleton,
		troll,
		vampire,
		zombie,
		max_monster_types
	};

private:

	Type m_type {};
    std::string_view m_name {};
    std::string_view m_roar {};
    int m_hitPoints {};

public:

	Monster( Type type, std::string_view name, std::string_view roar, int hitPoints )
		: m_type { type }, m_name { name }, m_roar { roar }, m_hitPoints { hitPoints }
	{

	}

	std::string_view getTypeString() const
	{
		switch (m_type)
		{
			case Type::dragon: return "dragon";
			case Type::goblin: return "goblin";
			case Type::ogre: return "ogre";
			case Type::orc: return "orc";
			case Type::skeleton: return "skeleton";
			case Type::troll: return "troll";
			case Type::vampire: return "vampire";
			case Type::zombie: return "zombie";
			default: return "???";
		}
	}

	void print() const
	{
		std::cout << m_name << " the " << getTypeString() << " has " << m_hitPoints << " hit points and says " << m_roar << '\n';
	}

};

class MonsterGenerator 
{
	
private:
	//static  Monster s_m ; No need to define Monster class instance inside the MonsterGenerator
	// Two static constexpr array of names and voices defined as member variable of MonsterGenerator class
	static inline std::array<std::string_view, 7> s_names { "Kanchan","Gauri","Nemo","Axat","Amber","Papa","Mummy" };
	static inline std::array<std::string_view, 7> s_roars { "*bleets*","*meows*","*cries*","*screams*","*brays*","*shrieks*","*rattles*" };
public:
	// Declaration of static member function to deal with static member variables
	static int getRandomNumber( int min, int max );// static randomnumber generation function declared
	static Monster generateMonster(); // static random monster generator function declaration
	
};



int MonsterGenerator::getRandomNumber( int min, int max )
{
	std::mt19937 mt( std::random_device {}() );
	//int maxMonsterType { static_cast<int>(Monster::Type::max_monster_types) - 1 };
	//std::uniform_int_distribution<> monsterTypeDice { 0, maxMonsterType };
	std::uniform_int_distribution<>randomNumber { min,max };
	return randomNumber( mt );
}
// Definition of static function MonsterGenerator outside class with scope-resolution operator
// No need to specify static keyword here again
// Member variable of class accessed directly without scope resolution opeartor
Monster MonsterGenerator::generateMonster()
{
	// getRandomNumeber() static function is used to generate random values of the Monster class member cvariables
	int monsterMaxRange { static_cast<int>(Monster::Type::max_monster_types) - 1 };
	int typeNum { getRandomNumber( 0,monsterMaxRange ) };
	
	// Here the integer typeNum has to be converted to the enum_class enumerator type
	//int cannot be implicitly converted to enumclass types. this give type of monster
	Monster::Type type { static_cast<Monster::Type>(typeNum) };
	// Random hitpoint values for various monsters
	int hitPoints { getRandomNumber( 1,100 ) };
	std::string_view name { s_names.at( getRandomNumber( 0,6) ) }; // Random name generation from static name array
	std::string_view roar { s_roars.at( getRandomNumber( 0,6 ) ) }; // Random voice geenartion from staic voice array

	// return type of fubction is object of class Monster
	// Here temporary object with brace initialization is used to create the Monster object type
	return { type,name,roar,hitPoints };
}

int main()
{
	Monster m { MonsterGenerator::generateMonster() };
	m.print();

	return 0;
}