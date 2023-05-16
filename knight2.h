#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

class BaseOpponent;

//opponent 
class BaseOpponent
{
protected:
    int id;
    int level;
    
    virtual void win(BaseKnight *knight)=0;
    virtual void lose(BaseKnight *knight)=0;
};
class Madbear : public BaseOpponent
{
public:
    
    Madbear()
    {
        id = 1;
        level=(index+id)%10+1;
    }
    void win(BaseKnight*knight){
 
        knight->gil+=100; //need to make change soon
    }
    void lose(BaseKnight *knight){
        knight->hp-=10*(level-knight->level);
    }
};

class Bandit : public BaseOpponent
{   
    public:
    
    Bandit()
    {
        id = 2;
        level=(index+id)%10+1;
    }
    void win(BaseKnight*knight){
 
        knight->gil+=150; //need to make change soon
    }
    void lose(BaseKnight *knight){
        knight->hp-=15*(level-knight->level);
    }

};

class LordLupin : public BaseOpponent
{
    LordLupin()
    {
        id = 3;
        level=(index+id)%10+1;
    }
    void win(BaseKnight*knight){
 
        knight->gil+=450; //need to make change soon
    }
    void lose(BaseKnight *knight){
        knight->hp-=45*(level-knight->level);
    }

};
class Elf : public BaseOpponent
{
    Elf()
    {
        id = 4;
        level=(index+id)%10+1;
    }
    void win(BaseKnight*knight){
 
        knight->gil+=750; //need to make change soon
    }
    void lose(BaseKnight *knight){
        knight->hp-=75*(level-knight->level);
    }

};
class Troll : public BaseOpponent
{
    Troll()
    {
        id = 5;
     level=(index+id)%10+1;
    }
        void win(BaseKnight*knight){
 
        knight->gil+=800; //need to make change soon
    }
    void lose(BaseKnight *knight){
        knight->hp-=95*(level-knight->level);
    }
};
class Torberry : public BaseOpponent
{
    Torberry()
    {
        id = 6;
         level=(index+id)%10+1;
    }
    void win(BaseKnight*knight){
 
        knight->level=min(10,knight->level+1); //need to make change soon
    }
    void lose(BaseKnight *knight){
        poison(); //need define
    }

    


};
class Queen : public BaseOpponent
{
    Queen()
    {
        id = 7;
         level=(index+id)%10+1;
    }
      void win(BaseKnight*knight){
 
        knight->gil*=2; //need to make change soon
    }
    void lose(BaseKnight *knight){
        knight->gil/=2;
    }

};
class Nina : public BaseOpponent
{
    Nina()
    {
        id = 8;
    }
        void win(BaseKnight*knight){
 
        knight->hp+=knight->maxhp/5; //need to make change soon
    }
    void lose(BaseKnight *knight){
        return;
    }
    

};
class DurianG : public BaseOpponent
{
    DurianG()
    {
        id = 9;
    }
        void win(BaseKnight*knight){
 
        knight->hp=knight->maxhp; //need to make change soon
    }
    
    
};
class Omega : public BaseOpponent
{
    Omega()
    {
        id = 10;
    }
          void win(BaseKnight*knight){
        knight->level=10;
        knight->gil=999; 

        //never meet again
    }
    void lose(BaseKnight *knight){
        knight->hp=0;
    }

};
class Hades : public BaseOpponent{
    Hades(){
        id=11;
    }
          void win(BaseKnight*knight){
                //khien Palafin
       
    }
    void lose(BaseKnight *knight){
       knight->hp=0;
    }
};




enum ItemType
{
    anti,
    pho1,
    pho2,
    pho3,
    pho4
};
class BaseItem
{
public:
    virtual bool canUse(BaseKnight *knight) = 0;
    virtual void use(BaseKnight *knight) = 0;
    ItemType item;
    BaseItem *item_node;
    BaseItem *next_item;
};

class Antidote : public BaseItem
{
public:
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
    Antidote()
    {
        item = anti;
    }
};
class PhoenixDownI : public BaseItem
{
public:
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
    PhoenixDownI()
    {
        item = pho1;
    }
};
class PhoenixDownII : public BaseItem
{
public:
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
    PhoenixDownII()
    {
        item = pho2;
    }
};
class PhoenixDownIII : public BaseItem
{
public:
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
    PhoenixDownIII()
    {
        item = pho3;
    }
};
class PhoenixDownIV : public BaseItem
{
public:
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
    PhoenixDownIV()
    {
        item = pho4;
    }
};

class BaseBag
{
public:
    virtual bool insertFirst(BaseItem *item) = 0;
    virtual BaseItem *get(ItemType itemType)
    {
        BaseItem *current;
        current = head;
        if (current->item == itemType && current == head)
        {
            head = current->next_item;
            c--;
            return current;
        }

        while (current != nullptr)
        {
            if (current->item == itemType)
            {

                BaseItem *temp = current;
                current->item = head->item;
                head->item = temp->item;
                head = head->next_item;
                c--;
                return temp;
            }
            current = current->next_item;
        }
        return NULL;
    }
    virtual string toString() const
    {
        string s;
        if (c == 0)
            return "Bag[count=0]";
        BaseItem *current = head;
        s = "Bag[count=" + to_string(c) + ";";
        while (current != nullptr)
        {
            switch (current->item)
            {
            case anti:
                s += "Antidote";
                break;
            case pho1:
                s += "PHOENIXI";
                break;
            case pho2:
                s += "PHOENIXII";
                break;
            case pho3:
                s += "PHOENIXIII";
                break;

            default:
                break;
            }
            current = current->next_item;
            if (current != nullptr)
                s += ",";
        }
        s += "]";
        return s;
    }

    BaseItem *head;

protected:
    int c = 0; // count
};

class Paladin_bag : public BaseBag
{
public:
    bool insertFirst(BaseItem *item)
    {
        BaseItem *newNode = item;
        newNode->item_node = item;
        newNode->next_item = head;
        head = newNode;
        c++;
        return true;
    }

    Paladin_bag(int a, int b)
    {
        head = nullptr;
        if (a > 0)
        {
            for (int i = 0; i < a; i++)
            {
                BaseItem *new_item = new PhoenixDownI();
                new_item->next_item = head;
                head = new_item;
                c++;
            }
        }
        if (b > 0)
        {
            for (int i = 0; i < b; i++)
            {
                BaseItem *new_item = new Antidote();
                new_item->next_item = head;
                head = new_item;
                c++;
            }
        }
    }
};

class Lancelot_bag : public BaseBag
{

public:
    bool insertFirst(BaseItem *item)
    {
        if (c >= 16)
            return false;
        else
        {
            BaseItem *newNode = item;
            newNode->item_node = item;
            newNode->next_item = head;
            head = newNode;
            c++;
        }
        return true;
    }

    Lancelot_bag(int a, int b)
    {
        head = nullptr;
        if (a > 0)
        {
            for (int i = 0; i < a && c < 16; i++)
            {
                BaseItem *new_item = new PhoenixDownI();
                new_item->next_item = head;
                head = new_item;
                c++;
            }
        }
        if (b > 0)
        {
            for (int i = 0; i < b && c < 16; i++)
            {
                BaseItem *new_item = new Antidote();
                new_item->next_item = head;
                head = new_item;
                c++;
            }
        }
    }
};

class Dragon_bag : public BaseBag
{

public:
    bool insertFirst(BaseItem *item)
    {
        if (item->item == anti || c >= 14)
            return false;
        else
        {
            BaseItem *newNode = item;
            newNode->item_node = item;
            newNode->next_item = head;
            head = newNode;
            c++;
            return true;
        }
    }
    Dragon_bag(int a, int b)
    {
        head = nullptr;
        if (a > 0)
        {
            for (int i = 0; i < a && c < 14; i++)
            {
                BaseItem *new_item = new PhoenixDownI();
                new_item->next_item = head;
                head = new_item;
                c++;
            }
        }
    }
};

class Normal_bag : public BaseBag
{
public:
    bool insertFirst(BaseItem *item)
    {
        if (c >= 19)
            return false;
        else
        {
            BaseItem *newNode = item;
            newNode->item_node = item;
            newNode->next_item = head;
            head = newNode;
            c++;
            return true;
        }
    }

    Normal_bag(int a, int b)
    {
        head = nullptr;
        if (a > 0)
        {
            for (int i = 0; i < a && c < 19; i++)
            {
                BaseItem *new_item = new PhoenixDownI();
                new_item->next_item = head;
                head = new_item;
                c++;
            }
        }
        if (b > 0)
        {
            for (int i = 0; i < b && c < 19; i++)
            {
                BaseItem *new_item = new Antidote();
                new_item->next_item = head;
                head = new_item;
                c++;
            }
        }
    }
};
// done bag
enum KnightType
{
    PALADIN = 0,
    LANCELOT,
    DRAGON,
    NORMAL
};
class BaseKnight
{
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag *bag;
    KnightType knightType;

public:
    static BaseKnight *create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;

    friend class Antidote;
    friend class PhoenixDownI;
    friend class PhoenixDownII;
    friend class PhoenixDownIII;
    friend class PhoenixDownIV;
    friend class Madbear;
    friend class Bandit;
    friend class LordLupin;
    friend class Elf;
    friend class Troll;
    friend class Queen;
    friend class Nina;
    friend class Omega;
    friend class Hades;
    friend class DurianG;
    friend class Torberry;
    friend class ArmyKnights;
};

class PaladinKnight : public BaseKnight
{
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->hp = maxhp;
        this->gil = gil;
        bag = new Paladin_bag(phoenixdownI, antidote);
        knightType = PALADIN;
    }
};
class LancelotKnight : public BaseKnight
{
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->hp = maxhp;
        this->gil = gil;
        bag = new Lancelot_bag(phoenixdownI, antidote);
        knightType = LANCELOT;
    }
};
class DragonKnight : public BaseKnight
{
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->hp = maxhp;
        this->gil = gil;
        bag = new Dragon_bag(phoenixdownI, antidote);
        knightType = DRAGON;
    }
};
class NormalKnight : public BaseKnight
{
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->hp = maxhp;
        this->gil = gil;
        bag = new Normal_bag(phoenixdownI, antidote);
        knightType = NORMAL;
    }
};

class ArmyKnights
{
public:
    ArmyKnights(const string &file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent *opponent);
    bool adventure(Events *events);
    int count() const;
    BaseKnight *lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;


    void insert_gil(int n);
    void insert_item(BaseItem *item);

    int PaladinShield;
    int Lancelotspear;
    int GuineverHair;
    int ExcaliburSword;
    bool meet_Omega;
private:
    int num;
    BaseKnight **knights;
};

class Events
{
public:
    Events(const string &file_events);
    ~Events();
    int count() const;
    int get(int i) const;

private:
    int s_events = 0;
    int *i_event = NULL;
};

class KnightAdventure
{
private:
    ArmyKnights *armyKnights;
    Events *events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__