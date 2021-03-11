//Dawid Urbanik
#include <iostream>

using namespace std;

class PLAYER_CLASS
{
public:
    unsigned int maximum_health;
    unsigned int current_health;
    unsigned int attack;
    unsigned int agility;

    virtual unsigned int getRemainingHealth()=0;
    virtual unsigned int getDamage()=0;
    virtual unsigned int getAgility()=0;
    virtual void takeDamage(unsigned int health)=0;
    virtual void applyWinnerReward()=0;
    virtual void cure()=0;
    virtual void printParams()=0;
protected:
    virtual void die()=0;

    friend class CAESAR_CLASS;
    friend class ARENA_CLASS;
};

class CAESAR_CLASS      // Do poprawy count!
{
public:
    int count=1;

    void judgeDeathOfLife(PLAYER_CLASS* player)
    {
        if(count % 3 == 0 ) {
            player->die();
        }
        count++;
    }
};

class ARENA_CLASS
{
private:
    CAESAR_CLASS* judge;

public:
    ARENA_CLASS(CAESAR_CLASS *in)
    {
        judge = in;
    }

    void fight(PLAYER_CLASS* player1,PLAYER_CLASS* player2)
    {
        if(!(player1->getRemainingHealth()==0 || player2->getRemainingHealth()==0))
        {
            if(player1->getAgility()<player2->getAgility())
                swap(&player1,&player2);

            player1->printParams();
            player2->printParams();

            // Atak pierwszego gracza
            int attack_counter=0;
            for(int i=0;i<40 && player1->getRemainingHealth()>=10 && player2->getRemainingHealth()>=10;i++)
            {
                if(player1->getRemainingHealth()!=0)
                {
                    player2->takeDamage(player1->getDamage());
                    player2->printParams();
                    attack_counter++;
                }
                if(attack_counter>=40 || player2->getRemainingHealth()<10)
                    break;
                if(player2->getRemainingHealth()!=0)
                {
                    player1->takeDamage(player2->getDamage());
                    player1->printParams();
                    attack_counter++;
                }
            }
            if(player1->getRemainingHealth()==0)
                player1->die();
            if(player2->getRemainingHealth()==0)
                player2->die();

            // SAD CEZARA

            if(player1->getRemainingHealth()!=0)
            {
                if(attack_counter%2==0)
                judge->judgeDeathOfLife(player1);
                player1->printParams();
            }
            if(player2->getRemainingHealth()!=0)
            {
                if(attack_counter%2==0)
                judge->judgeDeathOfLife(player2);
                player2->printParams();
            }

            // NAGRODY
            if(player1->getRemainingHealth()!=0)
            {
                player1->applyWinnerReward();
                player1->cure();
            }
            if(player2->getRemainingHealth()!=0)
            {
                player2->applyWinnerReward();
                player2->cure();
            }
            player1->printParams();
            player2->printParams();

        }
    }

    void swap(PLAYER_CLASS **a,PLAYER_CLASS **b)
    {
        PLAYER_CLASS *k=*a;
        *a=*b;
        *b=k;
    }
};

class HUMAN_CLASS : virtual public PLAYER_CLASS
{
public:
    string id;
    unsigned int defence;

    HUMAN_CLASS(string get_id)
    {
        id = get_id;
        PLAYER_CLASS::maximum_health = 200;
        PLAYER_CLASS::current_health = 200;
        PLAYER_CLASS::attack = 30;
        PLAYER_CLASS::agility = 10;
        defence = 10;
    }

    unsigned int getAgility(){
        return agility;
    }

    unsigned int getDamage(){
        return attack;
    }

    void takeDamage(unsigned int damage){
        if(damage>defence) {
            damage-=defence;
            if(damage>agility)
                damage-=agility;
            else damage = 0;
        }
        else
            damage = 0;
        if(current_health>damage)
            current_health-=damage;
        else
            die();
    }

    unsigned int getRemainingHealth(){
        return (100*current_health/maximum_health);
    }

    void printParams()
    {
        if(current_health==0)
            cout<<id<<":R.I.P."<<endl;
        else
            cout<<id<<":"<<maximum_health<<":"<<current_health<<":"<<getRemainingHealth()<<"%:"<<getDamage()<<":"<<getAgility()<<":"<<defence<<endl;
    }

    void applyWinnerReward()
    {
        attack=attack+2;
        agility=agility+2;
    }

    void cure(){
        current_health = maximum_health;
    }

    void die(){
        current_health = 0;
    }

};

class BEAST_CLASS : virtual public PLAYER_CLASS
{
public:
    string id;

    BEAST_CLASS(string get_id)
    {
        id = get_id;
        PLAYER_CLASS::maximum_health = 150;
        PLAYER_CLASS::current_health = 150;
        PLAYER_CLASS::attack = 40;
        PLAYER_CLASS::agility = 20;
    }

    unsigned int getAgility(){
        return agility;
    }

    unsigned int getDamage(){
        if(getRemainingHealth()<25)
            return (2*attack);
        return attack;
    }

    void takeDamage(unsigned int damage){
        if(damage>(agility / 2)) {
            damage-=agility/2;
        }
        else
            damage = 0;
        if(current_health>damage)
            current_health-=damage;
        else
            die();
    }

    unsigned int getRemainingHealth(){
        return (100*current_health/maximum_health);
    }

    void printParams()
    {
        if(current_health==0)
            cout<<id<<":R.I.P."<<endl;
        else
            cout<<id<<":"<<maximum_health<<":"<<current_health<<":"<<getRemainingHealth()<<"%:"<<getDamage()<<":"<<getAgility()<<endl;
    }

    void applyWinnerReward()
    {
        attack=attack+2;
        agility=agility+2;
    }

    void cure(){
        current_health = maximum_health;
    }

    void die(){
        current_health = 0;
    }
};

class BERSERKER_CLASS : public HUMAN_CLASS, public BEAST_CLASS
{
public:
    BERSERKER_CLASS(string get_id1,string get_id2): HUMAN_CLASS(get_id1), BEAST_CLASS(get_id2)
    {
        maximum_health = 200;
        current_health = 200;
        attack = 35;
        agility = 5;
        defence = 15;
    }

    unsigned int getRemainingHealth(){
        return (100*current_health/maximum_health);
    }

    void printParams() {
        if (getRemainingHealth() < 25 && getRemainingHealth() > 0)
            BEAST_CLASS::printParams();
        else
            HUMAN_CLASS::printParams();
    }

    unsigned int getAgility(){
        if (getRemainingHealth() < 25 )
            return BEAST_CLASS::getAgility();
        return HUMAN_CLASS::getAgility();
    }

    unsigned int getDamage(){
        if (getRemainingHealth() < 25 )
            return BEAST_CLASS::getDamage();
        return HUMAN_CLASS::getDamage();
    }

    void takeDamage(unsigned int health){
        if (getRemainingHealth() < 25 )
            BEAST_CLASS::takeDamage(health);
        else
          HUMAN_CLASS::takeDamage(health);
    }

    void applyWinnerReward()
    {
        attack=attack+2;
        agility=agility+2;
    }

    void cure(){
        current_health = maximum_health;
    }

    void die(){
        current_health = 0;
    }
};

class SQUAD_CLASS : public PLAYER_CLASS
{
public:
    string id;
    PLAYER_CLASS* tab[100000];
    int player_count = 0;

    SQUAD_CLASS(string get_id)
    {
        id = get_id;
        for(int i=0;i<100000;i++)
        {
            tab[i]=0;
        }
    }

    void addPlayer(PLAYER_CLASS * new_player)
    {
        for(int i=0;i<player_count;i++) {
            if(tab[i]==new_player) {
                return;
            }
        }
        /*if(new_player->current_health==0)
            return;*/
        tab[player_count] = new_player;
        if(tab[player_count]->current_health==0)
            ;
        else
        player_count++;
    }

    unsigned int getAgility()
    {
        unsigned int smallest_agility =tab[0]->getAgility();
        for(int i=1;i<player_count;i++)
        {
            if(smallest_agility>tab[i]->getAgility())
                smallest_agility=tab[i]->getAgility();
        }
        return smallest_agility;
    }

    unsigned int getDamage()
    {
        unsigned int damage_sum=0;
        for(int i=0;i<player_count;i++)
            damage_sum+=tab[i]->getDamage();
        return damage_sum;
    }

    void takeDamage(unsigned int damage)
    {
        int part_damage = damage/player_count;

        for(int i=0;i<player_count;i++)
        {
            tab[i]->takeDamage(part_damage);    //  spadaanie 0 rozstrzygaja indywidualne takeDamage'i
        }

        for(int i=0;i<player_count;i++) //  usuwamy ze squadu niezyjacych graczy
        {
            if(tab[i]->getRemainingHealth()==0)
            {
                for(int k=i;k<player_count-1;k++)
                {
                    tab[k]=tab[k+1];
                }
                player_count--;
                i=-1;
            }
        }
    }

    unsigned int getRemainingHealth() // Pozostale zdrowie zespolu
    {
        int highest_health=tab[0]->getRemainingHealth();
        for(int i=0;i<player_count;i++)
        {
            if(highest_health<tab[i]->getRemainingHealth())
                highest_health=tab[i]->getRemainingHealth();
        }
        return highest_health;
    }

    void printParams()
    {
        if(player_count==0)
            cout<<id<<":nemo"<<endl;
        else {
            cout << id << ":" << player_count << ":" << getRemainingHealth() << "%:" << getDamage() << ":"<< getAgility() << endl;
            for(int i=0;i<player_count;i++)
                tab[i]->printParams();
        }
    }

    void applyWinnerReward()
    {
        for(int i=0;i<player_count;i++) {
            tab[i]->attack = tab[i]->attack + 2;
            tab[i]->agility = tab[i]->agility + 2;
        }
    }

    void cure(){
        for(int i=0;i<player_count;i++)
        tab[i]->current_health = tab[i]->maximum_health;
    }

    void die(){
        for(int i=0;i<player_count;i++)
        tab[i]->current_health = 0;
    }
};

