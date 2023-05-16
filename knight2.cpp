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
  
}

void Antidote::use(BaseKnight *knight)
{
    
}
// NixI
bool PhoenixDownI::canUse(BaseKnight *knight)
{
    if (knight->hp <= 0)
        return true;
    else
        return false;
}

void PhoenixDownI::use(BaseKnight *knight)
{
    knight->hp = knight->maxhp;
}
// Nix2
bool PhoenixDownII::canUse(BaseKnight *knight)
{
    if (knight->hp < knight->maxhp / 3)
        return true;
    else
        return false;
}

void PhoenixDownII::use(BaseKnight *knight)
{
    knight->hp = knight->maxhp;
}
// nIX3
bool PhoenixDownIII::canUse(BaseKnight *knight)
{
    if (knight->hp < knight->maxhp / 3)
        return true;
    else
        return false;
}

void PhoenixDownIII::use(BaseKnight *knight)
{
    if (knight->hp <= 0)
        knight->hp = knight->maxhp / 3;
    else
        knight->hp += knight->maxhp / 4;
}
// NIX4
bool PhoenixDownIV::canUse(BaseKnight *knight)
{
    if (knight->hp < knight->maxhp / 2)
        return true;
    else
        return false;
}

void PhoenixDownIV::use(BaseKnight *knight)
{
    if (knight->hp <= 0)
        knight->hp = knight->maxhp / 2;
    else
        knight->hp += knight->maxhp / 5;
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

        knights[i] = BaseKnight::create(id, a, b, c, d, e);
        id++;
    }

    army_in.close();
    PaladinShield=0;
    Lancelotspear=0;
    GuineverHair=0;
    ExcaliburSword=0;
    meet_Omega=false;
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


bool ArmyKnights::fight(BaseOpponent *opponent){}  //need done
    bool ArmyKnights::adventure(Events *events){}      //need done



    bool ArmyKnights::hasPaladinShield() const{}    //need done
    bool ArmyKnights::hasLancelotSpear() const{}    //need done
    bool ArmyKnights::hasGuinevereHair() const{}    //need done
    bool ArmyKnights::hasExcaliburSword() const{}

    void ArmyKnights::insert_gil(int n) {
    int over_gil = 0;

    
    for (int i = num - 1; i >= 0; i--) {
        knights[i]->gil += n + over_gil;  

   
        if (knights[i]->gil > 999) {
            over_gil = knights[i]->gil - 999;  
            knights[i]->gil = 999;  
        } else {
            over_gil = 0;  
        }
    }
}

    void ArmyKnights::insert_item(BaseItem *item){}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
}

/* * * END implementation of class KnightAdventure * * */


//event class
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




// opponet

