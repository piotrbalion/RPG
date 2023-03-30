#ifndef hero_hpp
#define hero_hpp
#include "character.hpp"

class hero : public character
{
    public:
    std::string name;
    std::string profession;
    int level;
	int strength;
    int str_bonus;
	int dexterity;
    int dex_bonus;
	int endurance;
    int end_bonus;
	int intelligence;
    int int_bonus;
	int charisma;
    int ch_bonus;
    int exp;

    hero(std::string chara_name);
    void stat_display();
    void bonus_update();
    int add_points();
    int set_stats(int choice);
    int stat_loop();
    void save(std::fstream& file);
    void load_stat(int stat, int n);
    void profession_load(std::string prof);
    int attack();

    friend class mage;
	friend class warrior;
	friend class berserker;
	friend class thief;

};

#endif