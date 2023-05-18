#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

// opponent
class BaseKnight;
class Events;
class BaseOpponent
{
public:
    int id;
    int level;
    int DMG = 0;
    int plus_gil = 0;
};

class Madbear : public BaseOpponent
{
public:
    Madbear(int index, int k_level)
    {
        id = 1;
        level = (index + id) % 10 + 1;
        DMG = 10 * ( level-k_level);
        plus_gil = 100;
    }
};

class Bandit : public BaseOpponent
{
public:
    Bandit(int index, int k_level)
    {
        id = 2;
        level = (index + id) % 10 + 1;
        DMG = 15 * (level-k_level);
        plus_gil = 150;
    }
};

class LordLupin : public BaseOpponent
{
public:
    LordLupin(int index, int k_level)
    {
        id = 3;
        level = (index + id) % 10 + 1;
        DMG = 45 * (level-k_level);
        plus_gil = 450;
    }
};
class Elf : public BaseOpponent
{
public:
    Elf(int index, int k_level)
    {
        id = 4;
        level = (index + id) % 10 + 1;
        DMG = 75 * (level-k_level);
        plus_gil = 750;
    }
};
class Troll : public BaseOpponent
{
public:
    Troll(int index, int k_level)
    {
        id = 5;
        level = (index + id) % 10 + 1;
        DMG = 95 * (level-k_level);
        plus_gil = 800;
    }
};
class Torberry : public BaseOpponent
{
public:
    Torberry(int index)
    {
        id = 6;
        level = (index + id) % 10 + 1;
        plus_gil=0;
        DMG=0;
    }
};
class Queen : public BaseOpponent
{
public:
    Queen(int index, int now_gil)
    {
        id = 7;
        level = (index + id) % 10 + 1;
        plus_gil = now_gil;
        DMG=0;
    }
};
class Nina : public BaseOpponent
{
public:
    Nina()
    {
        id = 8;
    }
};
class DurianG : public BaseOpponent
{
public:
    DurianG()
    {
        id = 9;
    }
};
class Omega : public BaseOpponent
{
public:
    Omega()
    {
        id = 10;
    }
};
class Hades : public BaseOpponent
{
public:
    Hades()
    {
        id = 11;
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
        BaseItem *pre = nullptr;
        current = head;
        if (current->item == itemType && current == head)
        {

            return current;
        }

        while (current != nullptr)
        {
            if (current->item == itemType)
            {

                BaseItem *temp = current->next_item;
                current->next_item = head->next_item;
                pre->next_item = head;
                head->next_item = temp;
                head = current;
                return head;
            }
            pre = current;
            current = current->next_item;
        }
        return nullptr;
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
                s += "PhoenixI";
                break;
            case pho2:
                s += "PhoenixII";
                break;
            case pho3:
                s += "PhoenixIII";
                break;
            case pho4:
                s+="PhoenixIV";
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
    void remove_item()
    {
        if (head == nullptr)
            return;

        BaseItem *remove = head;
        head = head->next_item;
        delete remove;
        c--;
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
    void after_fight();
    friend class Antidote;
    friend class PhoenixDownI;
    friend class PhoenixDownII;
    friend class PhoenixDownIII;
    friend class PhoenixDownIV;

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

    int PaladinShield = 0;
    int Lancelotspear;
    int GuineverHair;
    int ExcaliburSword;
    bool meet_Omega = false;
    bool win_Ultimecia = false;
    bool meet_Hades = false;
    bool fight_Ultimecia();

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

