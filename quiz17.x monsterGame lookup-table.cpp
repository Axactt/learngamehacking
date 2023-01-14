
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include"PRNGClass.h" // To use PRNGClass{}.operator(min,max) as functor which can be further written as PRNGClass{}(min,max)
class Creature
{
protected:
	std::string m_name;
	char m_symbol {};
	int m_health {};
	int m_damage {};
	int m_gold {};
public:
	Creature(const std::string& name="", char symbol='\n',int health = 0, int damage = 0, int gold = 0)
		:m_name{name},m_symbol{symbol},m_health{health},m_damage{damage},m_gold{gold}{ }
	const std::string& getName() const
	{
		return m_name;
	}
	char getSymbol() const
	{
		return m_symbol;
	}
	int getHealth()const
	{
		return m_health;
	}
	int getDamage()
	{
		return m_damage;
	}
	int getGold()
	{
		return m_gold;
	}

	void reduceHealth(int damage)
	{
		m_health -= damage;
	}
	bool isDead()
	{
		return(m_health <= 0);
	}
	void addGold(int gold)
	{
		m_gold += gold;
	}
};

class Player: public Creature
{
private:
	int m_level { 1};
public:
	Player(const std::string& name)  
		:Creature{name,'@',10,1,0}{ } // constructor of base class in initialzization list of derived class can contain variable as well as literals
	void levelUp()
	{
		++m_level;
		++m_gold;
	}
	int getLevel()
	{
		return m_level;
	}
	bool hasWon()
	{
		return(m_level >= 20);
	}

};
class Monster: public Creature
{
	

public:
// enum has to be defined first to make Monster constructor use it in parameter
	enum Type
	{
		dragon,
		orc,
		slime,
		max_types,
	};
	

private:
	// As a private member of Monster a static function using a lookup table
	// a look-up table is a set/group-of fixed properties arranged in an array
	// Each particular element or row of a table is a well-defined class or struct
	//Each index to array/table used to access a particular instance of class/struct
	//This index cam be assigned as Enum-type for giving meaning full name
	// array made static const & accessed by a static const getter member function
	static const Creature& getDefaultCreatureType( Type type )
	{
		//array of struct(classes) need double braces
		static const std::array<Creature, static_cast<std::size_t>(Type::max_types)> monsterData {
			{ {"dragon",'D',20,4,100},
			 {"orc",'o',4,2,25},
			 {"slime",'s',1,1,10}  } // note double outseid parenthesis

		};
		return monsterData.at( static_cast<std::size_t>(type) );
	}
	
public:
	// getDefaultCratureType function returns element of monsterData array
	//As each element of monsterData array is an object of type Creature
	//and the monsterData array is a fixed array
	//Creature base class constructor can be assigned with return value from 
	//getDefaultCreatureType() function. 
	Monster( Type type )
		:Creature( { getDefaultCreatureType( type ) }){ }

	static const Monster getRandomMonster()
	{
		int typeNumber { PRNGClass {}(static_cast<int>(Type::dragon), (static_cast<int>(Type::max_types) - 1)) };// use PRNGClass to generate 
		// Temporary object of type Monster returned by list initialization using Monster (Type type) constructor
		return { static_cast<Type>(typeNumber) };
	}
};

int main()
{
	
	Monster m { Monster::Type::orc };
	std::cout << " A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
	for (int i { 0 }; i < 10; ++i)
	{
		Monster m { Monster::getRandomMonster() };
		std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
	}
	return 0;
}