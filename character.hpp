#ifndef character_hpp
#define character_hpp
#include <string>

class character
{
public:
    std::string name;
	int HP;
	int exp;
	int strength;
	int dexterity;
	int endurance;
	int intelligence;
	int charisma;

    virtual void save(std::fstream& file)=0;
    virtual void stat_display()=0; 
	virtual int attack()=0; 
};

#endif