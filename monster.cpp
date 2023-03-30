#include "monster.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>


monster::monster(std::string monster_name)
{
    name = monster_name;
    strength = rand() % 10;
    dexterity = rand() % 10;
    endurance = rand() % 10;
    intelligence = rand() % 10;
    charisma = rand() % 10;
    HP = 20+endurance;
    exp = 20;
}

void monster::stat_display()
{
    std::cout << name << "'s stats:" << std::endl;
    std::cout << "HP: " << HP << std::endl;
    std::cout << "1. Strength: " << strength << std::endl;
    std::cout << "2. Dexterity: " << dexterity << std::endl;
    std::cout << "3. Endurance: " << endurance << std::endl;
    std::cout << "4. Intelligence: " << intelligence << std::endl;
    std::cout << "5. Charisma: " << charisma << std::endl;
}

void monster::save(std::fstream& file)
{
        
        file << name << std::endl
        << strength << std::endl
        << dexterity << std::endl
        << endurance << std::endl
        << intelligence << std::endl
        << charisma << std::endl;
}
int monster::attack()
{
    int demage;
    demage = strength/2 + rand() % 5;
    return demage;
}

