#ifndef monster_hpp
#define monster_hpp
#include "character.hpp"

class monster : public character
{
    public:
    monster(std::string monster_name);
    void stat_display();
    void save(std::fstream& file);
    int attack();
};



#endif