
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include"PRNGClass.h" // To use PRNGClass{}.operator(min,max) as functor which can be further written as PRNGClass{}(min,max)
class Player;
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
	int getDamage() const
	{
		return m_damage;
	}
	int getGold() const
	{
		return m_gold;
	}	
	bool isDead() const
	{
		return(m_health <= 0);
	}
	void addGold(int gold)
	{
		m_gold += gold;
	}
	void increaseHealth( int effect ) // for potion increase health
	{
		m_health += effect;
	}
	void increaseDamage( int effect ) // for potion increase damage
	{
		m_damage += effect;
	}
	void reduceHealth( int damage ) // for potion reduce health and for monster damage
	{
		m_health -= damage;
	}
	
};

class Monster : public Creature
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
	// As a private member of Monster a static function using a lookup table is used
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
	// getDefaultCreatureType function returns element of monsterData array
	//As each element of monsterData array is an object of type Creature
	//and the monsterData array is a fixed array
	//Creature base class constructor can be assigned with return value from 
	//getDefaultCreatureType() function. 
	Monster( Type type )
		:Creature( { getDefaultCreatureType( type ) } )
	{
	}

	static   Monster getRandomMonster()
	{
		int typeNumber { PRNGClass {}(static_cast<int>(Type::dragon), (static_cast<int>(Type::max_types) - 1)) };// use PRNGClass to generate 
		return Monster { static_cast<Type>(typeNumber) };
	
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
		++m_damage;
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

class Potion
{
public:

	enum PotionType
	{
		health1,
		health2,
		strength,
		poison,
		max_types,
	};
private:
	PotionType m_potionType {};
	std::string m_name;
	int m_sizeEffect {};
	static const Potion& getPotionData( PotionType type )
	{
		static const std::array<Potion, static_cast<std::size_t>(max_types)> potionPrakar
		{

			{
				{type,"Health",2},
				{type,"Health",5},
				{type,"Strength",1},
				{type,"Poison",-1},
			}
		};
		return potionPrakar.at( static_cast<std::size_t>(type) );
	}

public:

	Potion(PotionType type,std::string name,int sizeEffect)
		:m_potionType{type},m_name{name},m_sizeEffect{sizeEffect}{ }

	~Potion() = default;

	
	static Potion getRandomPotion()
	{
		int potionType { PRNGClass {}(static_cast<int>(PotionType::health1), (static_cast<int>(PotionType::max_types) - 1)) };
		
		return { getPotionData( static_cast<PotionType>(potionType) ) };
	}
	std::string_view getName()
	{
		return m_name;
	}
	
	PotionType getPotionType() const
	{
		return m_potionType;
	}

};


void getPotionEffect( Potion::PotionType type, Player& player )
{
	switch (type)
	{
		case Potion::PotionType::health1:
		player.increaseHealth( 2 );
		break;

		case Potion::PotionType::health2:
		player.increaseHealth( 5 );
		break;

		case Potion::PotionType::strength:
		player.increaseDamage(1 );
		break;

		case Potion::PotionType::poison:
		player.reduceHealth( 1 );
		break;

	}

}


// This function handles the player attacking the monster
void attackMonster( Player& player, Monster& monster )
{
	// If the player is dead, we can't attack the monster
	if (player.isDead())
		return;

	std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage.\n";

	// Reduce the monster's health by the player's damage
	monster.reduceHealth( player.getDamage() );

	// If the monster is now dead, level the player up
	if (monster.isDead())
	{
		std::cout << "You killed the " << monster.getName() << ".\n";
		player.levelUp();
		std::cout << "You are now level " << player.getLevel() << ".\n";
		std::cout << "You found " << monster.getGold() << " gold.\n";
		player.addGold( monster.getGold() );

		 int chanceOfPotion { PRNGClass{}(1,100) };
		 if(chanceOfPotion<=30) // 30% chance of finding potion
		 {

			 // Create a new potion after death of monster
			 Potion* pPotion { new Potion{Potion::getRandomPotion()} };
			 std::cout << "You have found a mythical potion! Do you want to drink it?  [y/n]: ";
			 char choice {};
			 std::cin >> choice;
			 if (choice == 'y' || choice == 'Y')
			 {
				 std::cout << "You drank a potion of " << pPotion->getName();
				 getPotionEffect( pPotion->getPotionType(), player );
				 delete pPotion;
				 if (player.isDead())
				 {
					 std::cout << " you died at level " << player.getLevel() << " and with " << player.getGold() << " gold.\n";
					 std::cout << " too bad you can't take it with you\n";
					 return;
				 }

			 }
			 else if (choice == 'n' || choice == 'N')
				 delete pPotion;
		 }

	}
}

// This function handles the monster attacking the player
void attackPlayer( const Monster& monster, Player& player )
{
	// If the monster is dead, it can't attack the player
	if (monster.isDead())
		return;

	// Reduce the player's health by the monster's damage
	player.reduceHealth( monster.getDamage() );
	std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage.\n";
}

void fightMonster( Player& player )
{
	Monster monster { Monster::getRandomMonster() };
	std::cout << " You ahve encountered a " << monster.getName() << " (" << monster.getSymbol() << "). \n";
	
	// While the monster isn't dead and the player isn't dead, the fight continues
	while (!monster.isDead() && !player.isDead())
	{
		std::cout << "(R)un or (F)ight: ";
		char input {};
		std::cin >> input;
		if (input == 'R' || input == 'r')
		{
			// 50% chance of fleeing successfully
			if (PRNGClass {}( 1, 2 ) == 1)
			{
				std::cout << "You successfully fled.\n";
				return; // success ends the encounter
			}
			else
			{
				// Failure to flee gives the monster a free attack on the player
				std::cout << "You failed to flee.\n";
				attackPlayer( monster, player );
				continue;
			}
		}

		if (input == 'F' || input == 'f')
		{
			// Player attacks first, monster attacks second
			attackMonster( player, monster );
			attackPlayer( monster, player );
		}
	}
}

int main()
{
	std::cout << "Enter your name; ";
	std::string playerName;
	std::cin >> playerName;

	Player player { playerName };
	std::cout << "Welcome, " << player.getName() << '\n';

	// If the player isn't dead and hasn't won yet, the game continues
	while (!player.isDead() && !player.hasWon())
		fightMonster( player );
	//At this point the palyer is alrteady dead or won
	if (player.isDead())
	{
		std::cout << " you died at level " << player.getLevel() << " and with " << player.getGold() << " gold.\n";
		std::cout << " too bad you can't take it with you\n";
	}
	else
	{
		std::cout << " You won the game with " << player.getGold() << " gold!\n";

	}
	return 0;
}