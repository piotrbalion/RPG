#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "hero.hpp" 
    
    
hero::hero(std::string chara_name)
{
    name = chara_name;
    level = 1;
    HP = 50;
    strength = 0;
    str_bonus = 0;
    dexterity = 0;
    dex_bonus = 0;
    endurance = 0;
    end_bonus = 0;
    intelligence = 0;
    int_bonus = 0;
    charisma = 0;
    ch_bonus = 0;
    exp = 50;
}

void hero::stat_display()
{
    std::cout << name << "'s (" << profession << " [" << level << "lvl]" << ")" << " stats:" << std::endl;
    std::cout << "EXP points: " << exp << std::endl;
    std::cout << "1. Strength: " << strength << std::endl;
    std::cout << "2. Dexterity: " << dexterity << std::endl;
    std::cout << "3. Endurance: " << endurance << std::endl;
    std::cout << "4. Intelligence: " << intelligence << std::endl;
    std::cout << "5. Charisma: " << charisma << std::endl;
    std::cout << "7. HP: " << HP << std::endl;
}

void hero::bonus_update()
{
    strength += str_bonus;
    dexterity += dex_bonus;
    endurance += end_bonus;
    intelligence += int_bonus;
    charisma += ch_bonus;
}

int hero::add_points()
{
    int points;
    std::cout << "How much points dou you want to add:" << std::endl;
    std::cin >> points;
    if(points > exp)
    {
        std::cout << "Not enough EXP" << std::endl;
        return 0;
    }
    else
    {  
        return points;
    }

}

int hero::set_stats(int choice)
{
    int result = 1;
    switch(choice)
    {
        case 1:
            result = add_points();
            if(result == 0)
            {
                return 0;
            }
            else
            {
                strength += result;
                exp -= result;
            }
            break;
        case 2:
            result = add_points();
            if(result == 0)
            {
                return 0;
            }
            else
            {
                dexterity += result;
                exp -= result;
            }
            break;
        case 3:
            result = add_points();
            if(result == 0)
            {
                return 0;
            }
            else
            {
                endurance += result;
                HP += result;
                exp -= result;
            }
            break;
        case 4:
            result = add_points();
            if(result == 0)
            {
                return 0;
            }
            else
            {
                intelligence += result;
                exp -= result;
            }
            break;
        case 5:
            result = add_points();
            if(result == 0)
            {
                return 0;
            }
            else
            {
                charisma += result;
                exp -= result;
            }
            break;

    }
}

int hero::stat_loop()
{
    int create = 1;
    int loop;
    int choice;
    while(create == 1)
            {
                std::cout << "Select the stat that you want add points to:" << std::endl;
                stat_display();
                if(exp > 0)
                {
                    std::cin >> choice;
                    if(choice >= 1 && choice <= 7)
                    {
                        set_stats(choice);
                    }
                    else
                    {
                        std::cout << "There is no such stat" << std::endl;
                    }
                }
                else if(exp == 0)
                {
                    std::cout << "You have spent all your exp\n\nDo you want to save your hero?" << std::endl;
                    std::cout << "1. Yes" << std::endl;
                    std::cout << "2. No" << std::endl;
                    std::cin >> choice;
                    if(choice == 1)
                    {
                        std::fstream file;
                        std::string file_name = name+".txt";
                        file.open(file_name.c_str(), std::ios::out); 
                        save(file);
                        file.close(); 
                        std::cout << "The hero has been saved\n";

                        return 1;
                    }
                    else if(choice == 2)
                    {
                        return 1;
                    }
                }
            }
}

void hero::save(std::fstream& file)
{
        
        file << name << std::endl
        << profession << std::endl
        << strength << std::endl
        << dexterity << std::endl
        << endurance << std::endl
        << intelligence << std::endl
        << charisma << std::endl
        << exp << std::endl
        << HP << std::endl
        << level << std::endl;
}

void hero::load_stat(int stat, int n)
{
    switch(n)
    {
        case 1:
            strength = stat;
            break;
        case 2:
            dexterity = stat;
            break;
        case 3:
            endurance = stat;
            break;
        case 4:
            intelligence = stat;
            break;
        case 5:
            charisma = stat;
            break;
        case 6:
            exp = stat;
            break;
        case 7:
            HP = stat;
            break;
        case 8:
            level = stat;
            break;
    }
}

void hero::profession_load(std::string prof)
{
    profession = prof;
}

int hero::attack()
{
    int demage;
    if(profession == "berserker")
    {
        demage = strength + rand() % 5;
    }
    else if(profession == "thief")
    {
        demage = dexterity + rand() % 5;
    }
    else if(profession == "mage")
    {
        demage = intelligence + rand() % 5;
    }
    else if(profession == "warrior")
    {
        demage = strength + rand() % 5;
    }
    return demage;
}

