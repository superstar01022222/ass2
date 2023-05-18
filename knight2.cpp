#include "knight2.h"

int num;
int index;
bool is_prime(int a)
{
    if (a == 1)
        return false;
    if (a == 2)
        return true;
    for (int i = 2; i <= sqrt(a); i++)
    {
        if (a % i == 0)
            return false;
    }
    return true;
}

bool is_dragon(int n)
{
    if (n < 100)
        return false;
    else
    {

        int a = n % 10;
        int b = (n / 10) % 10;
        int c = n / 100;

        if (a * a == b * b + c * c || b * b == a * a + c * c || c * c == a * a + b * b)
            return true;
        else
            return false;
    }
}
/* * * BEGIN implementation of class BaseBag * * */
bool Antidote::canUse(BaseKnight *knight)
{
    return true;
}

void Antidote::use(BaseKnight *knight)
{
    return;
}
// NixI
bool PhoenixDownI::canUse(BaseKnight *knight)
{
    if ( knight->hp > 0)
        return false;

    return true;
}

void PhoenixDownI::use(BaseKnight *knight)
{
    knight->hp = knight->maxhp;
    knight->bag->remove_item();
    return;
}
// Nix2
bool PhoenixDownII::canUse(BaseKnight *knight)
{
    if ( knight->hp >= knight->maxhp / 4)
        return false;

    return true;
}

void PhoenixDownII::use(BaseKnight *knight)
{
    knight->hp = knight->maxhp;
    knight->bag->remove_item();
}
// nIX3
bool PhoenixDownIII::canUse(BaseKnight *knight)
{
    if (knight->hp >= knight->maxhp / 3)
   
        return false;
    
        return true;
}

void PhoenixDownIII::use(BaseKnight *knight)
{
    if (knight->hp <= 0)
        knight->hp = knight->maxhp / 3;
    else
        knight->hp += knight->maxhp / 4;
    knight->bag->remove_item();
}
// NIX4
bool PhoenixDownIV::canUse(BaseKnight *knight)
{
       if (knight->hp >= knight->maxhp / 2)
   
        return false;
    
        return true;
}

void PhoenixDownIV::use(BaseKnight *knight)
{
    if (knight->hp <= 0)
        knight->hp = knight->maxhp / 2;
    else
        knight->hp += knight->maxhp / 5;

    knight->bag->remove_item();
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    return s;
}

BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{   
    if (antidote>=5) antidote=5;
    if (phoenixdownI>=5) phoenixdownI=5;
    BaseKnight *knight = nullptr;
    if (is_prime(maxhp))
    {   
        knight = new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        return knight;
    }
    if (is_dragon(maxhp))
    {
        knight = new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        return knight;
    }
    if (maxhp == 888)
    {
        knight = new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        return knight;
    }
    knight = new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    return knight;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const
{
    cout << "No. knights: " << this->count();
    if (this->count() > 0)
    {
        BaseKnight *lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
         << ";LancelotSpear:" << this->hasLancelotSpear()
         << ";GuinevereHair:" << this->hasGuinevereHair()
         << ";ExcaliburSword:" << this->hasExcaliburSword()
         << endl
         << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const
{
    cout << (win ? "WIN" : "LOSE") << endl;
}

ArmyKnights::ArmyKnights(const string &file_armyknights) : num(0), knights(nullptr)
{
    ifstream army_in(file_armyknights);
    army_in >> num;
    knights = new BaseKnight *[num];
    int id = 1;

    for (int i = 0; i < num; i++)
    {
        int a, b, c, d, e;
        army_in >> a >> b >> c >> d >> e;

        knights[i] = BaseKnight::create(id, a, b, d, e, c);
        id++;
    }

    army_in.close();
    PaladinShield = 0;
    Lancelotspear = 0;
    GuineverHair = 0;
    ExcaliburSword = 0;
    meet_Omega = false;
}

ArmyKnights::~ArmyKnights()
{

    if (knights != nullptr)
    {
        for (int i = 0; i < num; i++)
        {
            delete knights[i];
        }
        delete[] knights;
        knights = nullptr;
    }
}

int ArmyKnights::count() const
{
    return num;
}

BaseKnight *ArmyKnights::lastKnight() const
{
    if (num == 0)
        return nullptr;
    else
        return knights[num - 1];
}




bool ArmyKnights::hasPaladinShield() const
{
    return (PaladinShield == 1);
} // need done
bool ArmyKnights::hasLancelotSpear() const
{
    return (Lancelotspear == 1);
} // need done
bool ArmyKnights::hasGuinevereHair() const
{
    return (GuineverHair == 1);
} // need done
bool ArmyKnights::hasExcaliburSword() const
{
    return (ExcaliburSword == 1);
}

void ArmyKnights::insert_gil(int n)
{
    int over_gil = 0;

    for (int i = num - 1; i >= 0; i--)
    {
        knights[i]->gil += n + over_gil;

        if (knights[i]->gil > 999)
        {
            over_gil = knights[i]->gil - 999;
            knights[i]->gil = 999;
        }
        else
        {
            over_gil = 0;
        }
    }
}
void ArmyKnights::insert_item(BaseItem *item)
{
    int i = num - 1;

    while (i >= 0)
    {
        if (knights[index]->bag->insertFirst(item))
        {

            break;
        }

        index--;

        if (index < 0)
        {
            delete item;
        }
    }
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
}

bool ArmyKnights::adventure(Events *events)
{
    for (int i = 0; i < events->count(); i++)
    {
        if (events->get(i) == 1)
        {
            fight(new Madbear(i, lastKnight()->level));
        }
        if (events->get(i) == 2)
        {
            fight(new Bandit(i, lastKnight()->level));
        }
        if (events->get(i) == 3)
        {
            fight(new LordLupin(i, lastKnight()->level));
        }
        if (events->get(i) == 4)
        {
            fight(new Elf(i, lastKnight()->level));
        }
        if (events->get(i) == 5)
        {
            fight(new Troll(i, lastKnight()->level));
        }
        if (events->get(i) == 6)
        {
            fight(new Torberry(i));
        }
        if (events->get(i) == 7)
        {
            fight(new Queen(i, lastKnight()->gil));
        }
        if (events->get(i) == 8)
        {
            fight(new Nina());
        }
        if (events->get(i) == 9)
        {
            fight(new DurianG());
        }
        if (events->get(i) == 10)
        {
            fight(new Omega());
        }
        if (events->get(i) == 11)
        {
            fight(new Hades());
        }
        if (events->get(i) == 112)
        {
            insert_item(new PhoenixDownII()); // phoenixII
        }
        if (events->get(i) == 113)
        {
            insert_item(new PhoenixDownIII()); // phoenixIII
        }
        if (events->get(i) == 114)
        {
            insert_item(new PhoenixDownIV()); // phoenixIv
        }
        if (events->get(i) == 95)
        {
            if (PaladinShield == 0)
            {
                PaladinShield = 1;
            }
        }
        if (events->get(i) == 96)
        {
            if (Lancelotspear == 0)
            {
                Lancelotspear = 1;
            }
        }
        if (events->get(i) == 97)
        {
            if (GuineverHair == 0)
            {
                GuineverHair = 1;
            }
        }

        if (events->get(i) == 98)
        {
            if (ExcaliburSword == 0 && PaladinShield == 1 && Lancelotspear == 1 && GuineverHair == 1)
            {
                ExcaliburSword = 1;
            }
        }
        if (events->get(i) == 99)
        {
            fight_Ultimecia(); // ultimecia
        }
        printInfo();
    }
    return win_Ultimecia;
}

/* * * END implementation of class KnightAdventure * * */

// event class
Events::Events(const string &file_events)
{
    ifstream event_in(file_events);
    event_in >> s_events;
    i_event = new int[s_events];
    for (int i = 0; i < s_events; i++)
    {
        event_in >> i_event[i];
    }
    event_in.close();
}
Events::~Events()
{
    delete[] i_event;
}

int Events::count() const
{
    return s_events;
}

int Events::get(int i) const
{
    return i_event[i];
}

KnightAdventure::~KnightAdventure() {} // TODO:

void KnightAdventure::loadArmyKnights(const string &s)
{
    armyKnights = new ArmyKnights(s);
}
void KnightAdventure::loadEvents(const string &s)
{
    events = new Events(s);
}
void KnightAdventure::run()
{
    armyKnights->adventure(events);
    armyKnights->printResult(armyKnights->win_Ultimecia);
}
// opponet
void BaseKnight::after_fight()
{
    BaseItem *current = this->bag->head;
    while (current != nullptr && current->item == anti)
    {
        if (current->item == pho1 && current->canUse(this))
        {
            this->bag->get(pho1)->use(this);
            this->bag->remove_item();
            return;
        }
        if (current->item == pho2 && current->canUse(this))
        {
            this->bag->get(pho2)->use(this);
            this->bag->remove_item();
            return;
        }
        if (current->item == pho3 && current->canUse(this))
        {
            this->bag->get(pho3)->use(this);
            this->bag->remove_item();
            return;
        }
        if (current->item == pho4 && current->canUse(this))
        {
            this->bag->get(pho4)->use(this);
            this->bag->remove_item();
            return;
        }
        current = current->next_item;
    }
    if (this->hp <= 0)
    {
        if (this->gil >= 100)
        {
            this->hp = this->maxhp / 2;
            return;
        }
        else
        {
            this->hp=-1;
            return;
        }
    }
}

bool ArmyKnights::fight(BaseOpponent *a)
{   
    BaseKnight *lknight=lastKnight();
    if (lknight->knightType == PALADIN)
    {
        if (a->id >= 1 && a->id <= 5)
        {
            insert_gil(a->plus_gil);
        }
        if (a->id == 6)
        {
            if (lknight->level < a->level && lknight->bag->get(anti) == NULL)
            {
                for (int i = 0; i < 3; i++)
                {
                    lknight->bag->remove_item();
                }
                lknight->hp -= 10;
            }
            if (lknight->level < a->level && lknight->bag->get(anti) != NULL)
            {
                lknight->bag->remove_item();
            }
            if (lknight->level >= a->level)
            {
                lknight->level = min(10, lknight->level++);
            }
        }
        if (a->id == 7)
        {
            if (lknight->level >= a->level)
            {
                insert_gil(a->plus_gil);
            }
        }
        if (a->id == 8)
        {
            if (lknight->hp < lknight->maxhp / 3)
            {
                lknight->hp += lknight->maxhp / 5;
            }
        }
        if (a->id == 9)
        {
            lknight->hp = lknight->maxhp;
        }
        if (a->id == 10 && !meet_Omega)
        {
            if (lknight->level == 10 && lknight->hp == lknight->maxhp)
            {
                lknight->gil = 999;
                meet_Omega = true;
            }
            else
                lknight->hp = 0;
        }
        if (a->id == 11 && !meet_Hades)
        {
            if (lknight->level >= 8)
                PaladinShield = 1;

            else
                lknight->hp = 0;
        }
    }

    if (lknight->knightType == DRAGON)
    {
        if (a->id >= 1 && a->id <= 5)
        {
            if (lknight->level >= a->level)
                insert_gil(a->plus_gil);
            if (lknight->level < a->level)
                lknight->hp -= a->DMG;
        }
        if (a->id == 6)
        {

            if (lknight->level >= a->level)
            {
                lknight->level = min(10, lknight->level++);
            }
        }
        if (a->id == 7)
        {
            if (lknight->level >= a->level)
            {
                insert_gil(a->plus_gil);
            }
            if (lknight->level < a->level)
                lknight->gil /= 2;
        }
        if (a->id == 8)
        {
            if (lknight->hp < lknight->maxhp / 3 && lknight->gil >= 50)
            {
                lknight->hp += lknight->maxhp / 5;
                lknight->gil -= 50;
            }
        }
        if (a->id == 9)
        {
            lknight->hp = lknight->maxhp;
        }
        if (a->id == 10 && !meet_Omega)
        {
            lknight->level = 10;
            lknight->gil = 999;
            meet_Omega = true;
        }
        if (a->id == 11 && !meet_Hades)
        {
            if (lknight->level == 10)
                PaladinShield = 1;

            else
                lknight->hp = 0;
        }
    }

    if (lknight->knightType == LANCELOT)
    {
        if (a->id >= 1 && a->id <= 5)
        {
            insert_gil(a->plus_gil);
        }
        if (a->id == 6)
        {
            if (lknight->level < a->level && lknight->bag->get(anti) == NULL)
            {
                for (int i = 0; i < 3; i++)
                {
                    lknight->bag->remove_item();
                }
                lknight->hp -= 10;
            }
            if (lknight->level < a->level && lknight->bag->get(anti) != NULL)
            {
                lknight->bag->remove_item();
            }
            if (lknight->level >= a->level)
            {
                lknight->level = min(10, lknight->level++);
            }
        }
        if (a->id == 7)
        {
            if (lknight->level >= a->level)
            {
                insert_gil(a->plus_gil);
            }
            if (lknight->level < a->level)
                lknight->gil /= 2;
        }
        if (a->id == 8)
        {
            if (lknight->hp < lknight->maxhp / 3 && lknight->gil >= 50)
            {
                lknight->hp += lknight->maxhp / 5;
                lknight->gil -= 50;
            }
        }
        if (a->id == 9)
        {
            lknight->hp = lknight->maxhp;
        }
        if (a->id == 10 && !meet_Omega)
        {
            if (lknight->level == 10 && lknight->hp == lknight->maxhp)
            {
                lknight->gil = 999;
                meet_Omega = true;
            }
            else
                lknight->hp = 0;
        }
        if (a->id == 11 && !meet_Hades)
        {
            if (lknight->level == 10)
                PaladinShield = 1;

            else
                lknight->hp = 0;
        }
    }

    if (lknight->knightType == NORMAL)
    {
        if (a->id >= 1 && a->id <= 5)
        {
            insert_gil(a->plus_gil);
        }
        if (a->id == 6)
        {
            if (lknight->level < a->level && lknight->bag->get(anti) == NULL)
            {
                for (int i = 0; i < 3; i++)
                {
                    lknight->bag->remove_item();
                }
                lknight->hp -= 10;
            }
            if (lknight->level < a->level && lknight->bag->get(anti) != NULL)
            {
                lknight->bag->remove_item();
            }
            if (lknight->level >= a->level)
            {
                lknight->level = min(10, lknight->level++);
            }
        }
        if (a->id == 7)
        {
            if (lknight->level >= a->level)
            {
                insert_gil(a->plus_gil);
            }
            if (lknight->level < a->level)
                lknight->gil /= 2;
        }
        if (a->id == 8)
        {
            if (lknight->hp < lknight->maxhp / 3 && lknight->gil >= 50)
            {
                lknight->hp += lknight->maxhp / 5;
                lknight->gil -= 50;
            }
        }
        if (a->id == 9)
        {
            lknight->hp = lknight->maxhp;
        }
        if (a->id == 10 && !meet_Omega)
        {
            if (lknight->level == 10 && lknight->hp == lknight->maxhp)
            {
                lknight->gil = 999;
                meet_Omega = true;
            }
            else
                lknight->hp = 0;
        }
        if (a->id == 11 && !meet_Hades)
        {
            if (lknight->level == 10)
                PaladinShield = 1;

            else
                lknight->hp = 0;
        }
    }

    lknight->after_fight();

    if (lknight->hp=-1){
        delete lastKnight();
        return false;
    }
    else return true;
    
}

void ArmyKnights::fight_Ultimecia()
{
    if (hasExcaliburSword())
    {
        win_Ultimecia = true;
        return;
    }
    if (!hasPaladinShield())
    {
        num = 0;
        return;
    };
    if (!hasLancelotSpear())
    {
        num = 0;
        return;
    }
    if (!hasGuinevereHair())
    {
        num = 0;
        return;
    }

    BaseKnight *knight_fight = nullptr;
    int HP_boss = 5000;
    for (int i = num; i >= 0; --i)
    {
        knight_fight = knights[i];
        if (knight_fight->knightType == LANCELOT)
        {

            int DMG = knight_fight->hp * knight_fight->level * 0.06;
            HP_boss -= DMG;
            if (HP_boss > 0)
            {
                delete knights[i];
                num--;
            }
        }
        if (knight_fight->knightType == DRAGON)
        {

            int DMG = knight_fight->hp * knight_fight->level * 0.075;
            HP_boss -= DMG;
            if (HP_boss > 0)
            {
                delete knights[i];
                num--;
            }
        }
        if (knight_fight->knightType == LANCELOT)
        {

            int DMG = knight_fight->hp * knight_fight->level * 0.05;
            HP_boss -= DMG;

            if (HP_boss > 0)
            {
                delete knights[i];
                num--;
            }
        }
        if (HP_boss <= 0)
        {
            win_Ultimecia = true;
            return;
        }
    }

}