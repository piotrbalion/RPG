#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "character.hpp"
#include "hero.hpp"
#include "monster.hpp"

class mage
{
    public:
	void add_bonus(hero& h){
		h.profession = "mage";
		h.int_bonus = 5;
	}
};

class warrior
{
    public:
	void add_bonus(hero& h){
		h.profession = "warrior";
		h.end_bonus = 5;
	}
};

class berserker
{
    public:
	void add_bonus(hero& h){
		h.profession = "berserker";
		h.str_bonus = 5;
	}
};

class thief
{
    public:
	void add_bonus(hero& h){
		h.profession = "thief";
		h.dex_bonus = 5;
	}
};

struct lst_el{
    lst_el * next;
    int key;
    std::string name;
};

class list{
    lst_el * head, * tail;
    int cnt;
public:
    list(){
        head = tail = NULL;
        cnt = 0;
    }

    unsigned size(){
		return cnt;
	}

    lst_el *push_head(lst_el *el){
		el = head -> next;
		head = el;
		if(!tail) tail = head;
		cnt++;
		return head;
	}

    lst_el *push_tail(lst_el *el){
		if(tail) tail -> next = el;
		el -> next = NULL;
		tail = el;
		if(!head) head=tail;
		cnt++;
		return tail;
    }
    lst_el *rmHead(){
		lst_el *el;
		
		if(head){
			el = head;
			head = head -> next;
			if(!head) tail = NULL;
			cnt--;
			return el;
		}
		else return NULL;
    }
    lst_el *rmTail(){
		lst_el *el;
		if(tail){
			el = tail;
			if(el == head) head = tail = NULL;
			else{
				tail = head;
				while(tail -> next != el) tail = tail -> next;
				tail -> next = NULL;
			}
			cnt--;
			return el;
		}
		else return NULL;
	}
    lst_el *index(int n){
		lst_el *el;
		
		if((!n) || (n>cnt)) return NULL;
		else if(n == cnt) return tail;
		else{
			el = head;
			while(--n) el = el -> next;
			return el;
		}
	}

    void showElements(){
		lst_el *el;
		
		if(!head){
			std::cout << "List is empty." << std::endl;
		} 
		else{
			el = head;
			while(el) {
				std::cout << el->key << ". " << el -> name << std::endl;
				el = el -> next;
			}
			std::cout << std::endl;
		}
	}

    lst_el *erase(lst_el *el){
		lst_el *el1;
		
		if(el==head) return rmHead();
		else{
			el1 = head;
			while(el1 -> next != el) el1 = el1 -> next;
			el1 -> next = el -> next;
			if(!(el1->next)) tail = el1;
			cnt--;
			return el;
		}
	}
};

void update_log(list &log, bool victory){
	lst_el *p;
	lst_el *el;
	int size = log.size();
	p = new lst_el;
    if(victory == 1)
	p -> name = "victory";
    else
    p -> name = "lose";
	
	if(size < 10){
		p -> key = ++size;
		log.push_tail(p);
	}
	else{
		el = new lst_el;
		p->key = 10;
		log.rmHead();
		for(int n = 1; n <= 10; n++){
			el = log.index(n);
			el->key = el->key - 1;
		}
		log.push_tail(p);
	}
}


struct node
{
    int id;
    int equipped;
    int quantity;
    struct node *next;
    struct node *prev;

}*start;

class double_llist
{
    public:
    void create_list(int value);
    void add_begin(int value);
    void display_dlist();
    int add_item(int item_id);
    node *get_item(int choice);
    void use_item(hero &h, node *i);
    void item_menu(hero &h, node *i);
    double_llist()
    {
        start = NULL;
    }
};

void double_llist::create_list(int value)
{
    struct node *s, *temp;
    temp = new(struct node);
    temp->id = value;
    temp->quantity = 1;
    temp->next = NULL;
    if (start == NULL)
    {
        temp->prev = NULL;
        start = temp;
    }
    else
    {
        s = start;
        while (s->next != NULL)
        s = s->next;
        s->next = temp;
        temp->prev = s;
    }
}


void double_llist::add_begin(int value)
{
    if (start == NULL)
    {
        create_list(value);
        return;
    }
    struct node *temp;
    temp = new(struct node);
    temp->prev = NULL;
    temp->id = value;
    temp->equipped = 0;
    temp->quantity = 1;
    temp->next = start;
    start->prev = temp;
    start = temp;
    std::cout<<"Element Inserted"<<std::endl;
}



void double_llist::display_dlist()
{
    struct node *q;
    if (start == NULL)
    {
        std::cout<<"Inventory is empty, nothing to display"<<std::endl;
        return;
    }
    q = start;
    std::cout<<"Inventory :"<<std::endl;
    while (q != NULL)
    {
        std::cout<<q->id<<" <-> ";
        q = q->next;
    }
    std::cout<<"NULL"<<std::endl;
}


node *double_llist::get_item(int choice){
	struct node *q;
	if(start == NULL){
		std::cout << "List empty, nothing to display" << std::endl;
	}
	q = start;
	if(q == NULL){
		std::cout << "NULL" << std::endl;	
	}
	else{
	    for(int n = 1; n < choice; n++){
		    q = q->next;
	    }
	    return q;
	}
}

int double_llist::add_item(int item_id){
	node *q;
    if(start == NULL) create_list(item_id);
	q = start;
	while(q!=NULL){
		if(q->id == item_id)
        {
            q->quantity += 1;
            return 0;
        }
		q = q->next;
	}
    add_begin(item_id);

    return 0;
}


void double_llist::item_menu(hero &h, node *i){
	int choice;
	if(i->equipped==0) std::cout << "1. Equip\n2. Back" << std::endl;
	else std::cout << "1. Unquip\n2. Back" << std::endl;
    std::cin >> choice;
    if(choice == 1){
        use_item(h, i);
    }
	else{
		std::cout << "Going back" << std::endl;
    }
}

void double_llist::use_item(hero &h, node *i)
{
	if(i->id==1 || i->id==2)
    {
        if(i->equipped == 0)
        {
            i->equipped = 1;
            h.HP += 20;
        }
        else if(i->equipped == 1)
        {
            i->equipped = 0;
            h.HP -= 20;
        }
	}
	else if(i->id==3 || i->id==4)
    {
        if(i->equipped == 0)
        {
            i->equipped = 1;
            h.strength += 5;
        }
        else if(i->equipped == 1)
        {
            i->equipped = 0;
            h.strength -= 5;
        }
	}	
}

template<class hero, class list>
void save_log(hero chara, list log){
	lst_el *p;
	std::fstream file;
	std::string file_name = chara.name + "_log.txt";
	
	file.open(file_name.c_str(), std::ios::out);
	
	for(int n = 1; n <= log.size(); n++){
		p = log.index(n);
		file << p -> key << " " << p -> name << std::endl;
	}
	file.close();
}

template<class hero, class monster> class battle
{
    public:
	bool battle_loop(hero &Chara, monster &Mon)
    {
        bool victory = 0;
        int choice;
        int demage;
        int task;
        int act_count = 0;
        int flee = 0;
        if(Chara.HP <= 0)
        {
            std::cout << "Your character is unable to battle :(\n" << std::endl;
            return 0;
        }
        std::cout << "It's a beautiful day outside..." << std::endl;
        std::cout << "Birds are singing, flowers are blooming" << std::endl;
        std::cout << "On days like this, kids like you" << std::endl;
        std::cout << "..." << std::endl;
        std::cout << "Should be burning in hell..." << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Enemy approaching" << std::endl;

        if(Mon.dexterity < Chara.dexterity)
        {
            task = 1;
        }
        else
        {
            task = 2;
        }

        while(Chara.HP > 0 && Mon.HP > 0 && flee == 0 && act_count < 3)
        {
            std::cout << "Your HP:" << Chara.HP << std::endl;
            std::cout << "\nMonster HP:" << Mon.HP << std::endl;

            switch(task)
            {
                // Hero turn
                case 1:
                        // Hero action menu
                    std::cout << "1. Attack" << std::endl;
                    std::cout << "2. Act" << std::endl;
                    std::cout << "3. FLEE!!!" << std::endl;
                    std::cin >> choice;

                    if(choice == 1)
                    {
                        demage = Chara.attack();
                        Mon.HP -= demage;
                        std::cout << "You dealt " << demage << " demage" << std::endl;
                        task = 2;
                    }
                    if(choice == 2)
                    {
                        act();
                        if(Mon.charisma < Chara.charisma)
                        {
                            std::cout << "They kinda liked it..." << std::endl;
                            act_count += 1;
                            task = 2;
                        }
                        else
                        {
                            std::cout << "They are kinda surprised, but it doesn't seem to be very effective" << std::endl;
                            task = 2;
                        }
                    }
                    else if(choice == 3)
                    {
                        Chara.HP -= Mon.attack();
                        flee = 1;
                        std::cout << "While you were running away, the monster attacked you for the last time" << std::endl;
                        task = 2;
                    }
                break;

                // Monster turn
                case 2:

                    demage = Mon.attack();
                    Chara.HP -= demage;
                    std::cout << "The monster dealt " << demage << " demage" << std::endl;
                    task = 1;
                break;        
            }
            
            
        }
        if(flee == 1)
        {
            std::cout << "You've run away from battle..." << std::endl;
        }
        if(Chara.HP > 0)
        {
            std::cout << "You survived the battle" << std::endl;
            Chara.exp += Mon.exp;
        }
        else if(Chara.HP <= 0)
        {
            std::cout << "YOU DIED" << std::endl;
        }
        if(act_count >= 3)
        {
            std::cout << "and the monster thinks you're a realy nice person, they won't cause any more trouble" << std::endl;
        }
        if(Chara.exp >= 50)
        {
            std::cout << "****LEVEL UP****" << std::endl;
            Chara.level += 1;
            Chara.exp -= 50;
        }
        if(Mon.HP <= 0)
        {
            victory = 1;
        }

        Chara.stat_display();
        std::fstream file;
        std::string file_name = Chara.name+".txt";
        file.open(file_name.c_str(), std::ios::out);                  
        Chara.save(file);
        file.close();
        return victory;
    }
    void act()
    {
        int act_randomizer = rand() % 3;
        if(act_randomizer == 0)
        {
            std::cout << "You hugged the monster" << std::endl;
        }
        else if(act_randomizer == 1)
        {
            std::cout << "You told the monster a compliment about their sharp teeth and claws" << std::endl;
        }
        else if(act_randomizer == 2)
        {
            std::cout << "You did a PAT PAT to the monster" << std::endl;
        }     
    }    
};

hero load()
{
    std::fstream file;
    std::string chara_name, profession;
    int stat;
    int n;
    std::cout << "Enter the name of the hero: " << std::endl;
    std::cin >> chara_name;
    chara_name = chara_name+".txt";
    file.open(chara_name.c_str(), std::ios::in);
    file >> chara_name;
    file >> profession;
    hero chara(chara_name);
    chara.profession_load(profession);
    for(n = 1; n<9; n++)
    {
        file >> stat;
        chara.load_stat(stat, n);
    }
    file.close();
    chara.stat_display();
    return chara;

}    

void display_menu()
{
   std::cout << "1. Load hero" << std::endl; 
   std::cout << "2. Create New hero" << std::endl;
   std::cout << "3. Create Monster List and Battle" << std::endl;
   std::cout << "4. Exit" << std::endl;
}

int cont()
{
    int choice;
    std::cout << "do you want to continue [1 - Yes; 2 - No]" << std::endl;
    std::cin >> choice;
    if(choice == 1)
    {
        return 0;
    }
    else if(choice == 2)
    {
        return 1;
    }
    return 0;
}

int randomItem()
{
    std::cout << "Monster dropped something" << std::endl; 
    int item_id = 1 + rand()%10;
    if(item_id <= 1)
    {
        return 1;
    }
    else if(item_id <= 3)
    {
        return 2;
    }
    else if(item_id <= 6)
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

void item_name(int id)
{
    switch(id){
        case 1:
            std::cout << "Gloryhammer";
            break;
        case 2:
            std::cout << "Pan";
            break;
        case 3:
            std::cout << "Someone else's hat";
            break;
        case 4:
            std::cout << "G.O.A.T coat";
            break;

    }
}

int main()
{
    int task = 1;
    int item_id;
    int choice;
    int idk = 1;
    int run = 1;
    std::string name, list_name;
    list log;
    double_llist items;
    struct node *q;

    while(run == 1)
    {
        switch(task)
        {
            case 1:
            {
                std::cout << "=========" << std::endl;
                std::cout << "Abovetale" << std::endl;
                std::cout << "=========" << std::endl;

                display_menu();

                std::cin >> choice;
                
                if(choice == 1)
                {
                    task = 2;
                }
                else if(choice == 2)
                {
                    task = 3;
                } 
                else if(choice == 3)
                {
                    task = 4;
                } 
                else if(choice == 4)
                {
                    run = 0;
                } 
                else
                {
                    std::cout << "WRONG OPTION" << std::endl;
                }
                break;
            }
            case 2:
            {
                load();
                task = 1;
                break;
            }
            case 3:
            {
                std::cout << "Creating hero" << std::endl;
                std::cout << "type your hero's name" << std::endl;
                std::cin >> name;
                hero chara(name);

                std::cout << "Select the profession:" << std::endl;
                std::cout << "1. Mage:" << std::endl;
                std::cout << "2. Warrior:" << std::endl;
                std::cout << "3. Berserker:" << std::endl;
                std::cout << "4. Thief:" << std::endl;
                std::cin >> choice;

                if(choice == 1)
                {
                    mage prof;
                    prof.add_bonus(chara);
                }
                else if(choice == 2)
                {
                    warrior prof;
                    prof.add_bonus(chara);
                }
                else if(choice == 3)
                {
                    berserker prof;
                    prof.add_bonus(chara);
                }
                else if(choice == 4)
                {
                    thief prof;
                    prof.add_bonus(chara);
                }
                chara.bonus_update();
                chara.stat_loop();
                task = 1;
                break;
            }
            case 4:
            {
                std::cout << "++++++++++++++" << std::endl;
                std::cout << "Your Monsters:" << std::endl;
                std::cout << "++++++++++++++" << std::endl;
                monster monster1("first_monster");
                monster1.stat_display();
                monster monster2("second_monster");
                monster2.stat_display();
                monster monster3("third_monster");
                monster3.stat_display();
                monster monster4("fourth_monster");
                monster4.stat_display();
                monster monster5("fifth_monster");
                monster5.stat_display();

                std::cout << "Write the monster list name" << std::endl;
                std::cin >> list_name;

                std::fstream file;
                list_name = list_name+".txt";
                file.open(list_name.c_str(), std::ios::out); 

                monster1.save(file);
                monster2.save(file);
                monster3.save(file);
                monster4.save(file);
                monster5.save(file);
                file.close(); 

                std::cout << "YOUR MONSTERS HAVE BEEN SAVED, WE WISH YOU A GOOD HUNT\n\n" << std::endl;
                hero chara("name");
                chara = load();
                task = 1;

                while(idk == 1)
                {
                    std::cout << "What equipment would you like to use" << std::endl;
                    q = start;
		            int n = 1;
                    while(q != NULL)
                    {
                        if(q->equipped==0)
                        {
                            std::cout << n << ". "; item_name(q->id); std::cout << " (" << q->quantity <<")" <<std::endl;
                        }
                        else 
                        {
                            std::cout << n << ". "; item_name(q->id); std::cout << " (" << q->quantity <<")" << " (equipped)" << std::endl;
                        }
                        q = q->next;
                        n++;
		            }
                    std::cout << n << ". Done" << std::endl;
                    std::cin >> choice;
                    if(choice == n)
                    {
                        idk = 0;
                    }
                    else
                    {
                        node *temp;
                        temp = items.get_item(choice);
                        items.item_menu(chara, temp);
                    }
                }

                idk = 1;

                battle<hero, monster> fight;
                update_log(log, fight.battle_loop(chara, monster1));
                save_log(chara, log);
                if(monster1.HP < 0)
                {
                    item_id = randomItem();

                    std::cout << "Monster dropped: "; item_name(item_id);  std::cout << "\nDo you want to pick it up: \n"<< "1 - Yes" << "2 - No" << std::endl;
                    std::cin >> choice;
                    if(choice == 1)
                    {
                        std::cout << "you took the item to your inventory" << std::endl;
                        items.add_item(item_id);
                    }
                    else if(choice == 2)
                    {
                        std::cout << "you left the item on the battlefield" << std::endl;
                    }
                }
                if(cont() == 1) break;
                update_log(log, fight.battle_loop(chara, monster2));
                save_log(chara, log);
                if(monster2.HP < 0)
                {
                    item_id = randomItem();

                    std::cout << "Monster dropped: "; item_name(item_id);  std::cout << "\nDo you want to pick it up: \n"<< "1 - Yes" << "2 - No" << std::endl;
                    std::cin >> choice;
                    if(choice == 1)
                    {
                        std::cout << "you took the item to your inventory" << std::endl;
                        items.add_item(item_id);
                    }
                    else if(choice == 2)
                    {
                        std::cout << "you left the item on the battlefield" << std::endl;
                    }
                }
                if(cont() == 1) break;
                update_log(log, fight.battle_loop(chara, monster3));
                save_log(chara, log);
                if(monster3.HP < 0)
                {
                    item_id = randomItem();

                    std::cout << "Monster dropped: "; item_name(item_id);  std::cout << "\nDo you want to pick it up: \n"<< "1 - Yes" << "2 - No" << std::endl;
                    std::cin >> choice;
                    if(choice == 1)
                    {
                        std::cout << "you took the item to your inventory" << std::endl;
                        items.add_begin(item_id);
                    }
                    else if(choice == 2)
                    {
                        std::cout << "you left the item on the battlefield" << std::endl;
                    }
                }
                if(cont() == 1) break;
                update_log(log, fight.battle_loop(chara, monster4));
                save_log(chara, log);
                if(monster4.HP < 0)
                {
                    item_id = randomItem();
                    
                    std::cout << "Monster dropped: "; item_name(item_id);  std::cout << "\nDo you want to pick it up: \n"<< "1 - Yes" << "2 - No" << std::endl;
                    std::cin >> choice;
                    if(choice == 1)
                    {
                        std::cout << "you took the item to your inventory" << std::endl;
                        items.add_item(item_id);
                    }
                    else if(choice == 2)
                    {
                        std::cout << "you left the item on the battlefield" << std::endl;
                    }
                }
                if(cont() == 1) break;
                update_log(log, fight.battle_loop(chara, monster5));
                save_log(chara, log);
                if(monster5.HP < 0)
                {
                    item_id = randomItem();

                    std::cout << "Monster dropped: "; item_name(item_id);  std::cout << "\nDo you want to pick it up: \n"<< "1 - Yes" << "2 - No" << std::endl;
                    std::cin >> choice;
                    if(choice == 1)
                    {
                        std::cout << "you took the item to your inventory" << std::endl;
                        items.add_item(item_id);
                    }
                    else if(choice == 2)
                    {
                        std::cout << "you left the item on the battlefield" << std::endl;
                    }
                }
                break;
            }
        }
    }
}