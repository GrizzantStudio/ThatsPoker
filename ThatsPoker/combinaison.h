#ifndef COMBINAISON_H
#define COMBINAISON_H

#include <combinaisontype.h>
#include <memory>

class Combinaison
{
private :

    unsigned int m_type;
    unsigned int m_strength;

protected :

    Combinaison(unsigned int a_type, unsigned int a_strength);

public :

    virtual ~Combinaison();

public :

    unsigned int getType() { return m_type; }
    unsigned int getStrength() { return m_strength; }

    int compare(Combinaison * a_otherCombinaison);

protected :

    virtual int compareImpl(Combinaison * a_otherCombinaison) = 0;
};

typedef std::shared_ptr <Combinaison> CombinaisonPtr;

class StraightFlushCombinaison : public Combinaison
{
private :
    int m_value;

public :
    StraightFlushCombinaison(int a_value)
        : Combinaison(CombinaisonType::STRAIGHT_FLUSH, 8)
        , m_value(a_value)
    {}

    int compareImpl(Combinaison * a_otherCombinaison);
};

class FourOfAKindCombinaison : public Combinaison
{
private :
    int m_value;
    int m_kickerValue;

public :
    FourOfAKindCombinaison(int a_value, int a_kickerValue)
        : Combinaison(CombinaisonType::FOUR_OF_A_KIND, 7)
        , m_value(a_value)
        , m_kickerValue(a_kickerValue)
    {}

    int compareImpl(Combinaison * a_otherCombinaison);
};

class FullHouseCombinaison : public Combinaison
{
private :
    int m_value1;
    int m_value2;

public :
    FullHouseCombinaison(int a_value1, int a_value2)
        : Combinaison(CombinaisonType::FULL_HOUSE, 6)
        , m_value1(a_value1)
        , m_value2(a_value2)
    {}

    int compareImpl(Combinaison * a_otherCombinaison);
};

class FlushCombinaison : public Combinaison
{
private :
    int m_values [5];

public :
    FlushCombinaison(int a_values [5])
        : Combinaison(CombinaisonType::FLUSH, 5)
    {
        for(int i = 0; i < 5; ++ i)
           m_values[i] = a_values[i];
    }

    int compareImpl(Combinaison * a_otherCombinaison);
};

class StraightCombinaison : public Combinaison
{
private :
    int m_value;

public :
    StraightCombinaison(int a_value)
        : Combinaison(CombinaisonType::STRAIGHT, 4)
        , m_value(a_value)
    {}

    int compareImpl(Combinaison * a_otherCombinaison);
};

class ThreeOfAKindCombinaison : public Combinaison
{
private :
    int m_value;
    int m_kickersValue [2];

public :
    ThreeOfAKindCombinaison(int a_value, int a_kickersValue [2])
        : Combinaison(CombinaisonType::THREE_OF_A_KIND, 3)
        , m_value(a_value)
    {
        for(int i = 0; i < 2; ++ i)
            m_kickersValue[i] = a_kickersValue[i];
    }

    int compareImpl(Combinaison * a_otherCombinaison);
};

class DoublePairCombinaison : public Combinaison
{
private :
    int m_value1;
    int m_value2;
    int m_kickerValue;

public :
    DoublePairCombinaison(int a_value1, int a_value2, int a_kickerValue)
        : Combinaison(CombinaisonType::DOUBLE_PAIR, 2)
        , m_value1(a_value1)
        , m_value2(a_value2)
        , m_kickerValue(a_kickerValue)
    {}

    int compareImpl(Combinaison * a_otherCombinaison);
};

class PairCombinaison : public Combinaison
{
private :
    int m_value;
    int m_kickersValue [3];

public :
    PairCombinaison(int a_value, int a_kickersValue [3])
        : Combinaison(CombinaisonType::PAIR, 1)
        , m_value(a_value)
    {
        for(int i = 0; i < 3; ++ i)
            m_kickersValue[i] = a_kickersValue[i];
    }

    int compareImpl(Combinaison * a_otherCombinaison);
};

class HighCardCombinaison : public Combinaison
{
private :
    int m_values [5];

public :
    HighCardCombinaison(int a_values [5])
        : Combinaison(CombinaisonType::HIGH_CARD, 0)
    {
        for(int i = 0; i < 5; ++ i)
            m_values[i] = a_values[i];
    }

    int compareImpl(Combinaison * a_otherCombinaison);
};

#endif // COMBINAISON_H
