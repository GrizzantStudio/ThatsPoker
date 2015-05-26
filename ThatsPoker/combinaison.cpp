#include "combinaison.h"

Combinaison::Combinaison(unsigned int a_type, unsigned int a_strength)
    : m_type(a_type)
    , m_strength(a_strength)
{

}

Combinaison::~Combinaison()
{

}

int Combinaison::compare(Combinaison * a_otherCombinaison)
{
    if(m_strength < a_otherCombinaison->m_strength)
        return -1;
    else if(m_strength > a_otherCombinaison->m_strength)
        return 1;
    else
        return compareImpl(a_otherCombinaison);
}

int StraightFlushCombinaison::compareImpl(Combinaison * a_otherCombinaison)
{
    StraightFlushCombinaison * otherCombinaison = dynamic_cast <StraightFlushCombinaison *> (a_otherCombinaison);

    if(m_value > otherCombinaison->m_value)
        return 1;
    else if(m_value < otherCombinaison->m_value)
        return -1;
    else
        return 0;
}

int FourOfAKindCombinaison::compareImpl(Combinaison * a_otherCombinaison)
{
    FourOfAKindCombinaison * otherCombinaison = dynamic_cast <FourOfAKindCombinaison *> (a_otherCombinaison);

    if(m_value > otherCombinaison->m_value)
        return 1;
    else if(m_value < otherCombinaison->m_value)
        return -1;
    else
    {
        if(m_kickerValue > otherCombinaison->m_kickerValue)
            return 1;
        else if(m_kickerValue < otherCombinaison->m_kickerValue)
            return -1;
        else
            return 0;
    }
}

int FullHouseCombinaison::compareImpl(Combinaison * a_otherCombinaison)
{
    FullHouseCombinaison * otherCombinaison = dynamic_cast <FullHouseCombinaison *> (a_otherCombinaison);

    if(m_value1 > otherCombinaison->m_value1)
        return 1;
    else if(m_value1 < otherCombinaison->m_value1)
        return -1;
    else
    {
        if(m_value2 > otherCombinaison->m_value2)
            return 1;
        else if(m_value2 < otherCombinaison->m_value2)
            return -1;
        else
            return 0;
    }
}

int FlushCombinaison::compareImpl(Combinaison * a_otherCombinaison)
{
    FlushCombinaison * otherCombinaison = dynamic_cast <FlushCombinaison *> (a_otherCombinaison);

    for(int i = 0; i < 5; ++ i)
    {
        if(m_values[i] > otherCombinaison->m_values[i])
            return 1;
        else if(m_values[i] < otherCombinaison->m_values[i])
            return -1;
    }

    return 0;
}

int StraightCombinaison::compareImpl(Combinaison * a_otherCombinaison)
{
    StraightCombinaison * otherCombinaison = dynamic_cast <StraightCombinaison *> (a_otherCombinaison);

    if(m_value > otherCombinaison->m_value)
        return 1;
    else if(m_value < otherCombinaison->m_value)
        return -1;
    else
        return 0;
}

int ThreeOfAKindCombinaison::compareImpl(Combinaison * a_otherCombinaison)
{
    ThreeOfAKindCombinaison * otherCombinaison = dynamic_cast <ThreeOfAKindCombinaison *> (a_otherCombinaison);

    if(m_value > otherCombinaison->m_value)
        return 1;
    else if(m_value < otherCombinaison->m_value)
        return -1;
    else
    {
        for(int i = 0; i < 2; ++ i)
        {
            if(m_kickersValue[i] > otherCombinaison->m_kickersValue[i])
                return 1;
            else if(m_kickersValue[i] < otherCombinaison->m_kickersValue[i])
                return -1;
        }

        return 0;
    }
}

int DoublePairCombinaison::compareImpl(Combinaison * a_otherCombinaison)
{
    DoublePairCombinaison * otherCombinaison = dynamic_cast <DoublePairCombinaison *> (a_otherCombinaison);

    if(m_value1 > otherCombinaison->m_value1)
        return 1;
    else if(m_value1 < otherCombinaison->m_value1)
        return -1;
    else
    {
        if(m_value2 > otherCombinaison->m_value2)
            return 1;
        else if(m_value2 < otherCombinaison->m_value2)
            return -1;
        else
        {
            if(m_kickerValue > otherCombinaison->m_kickerValue)
                return 1;
            else if(m_kickerValue < otherCombinaison->m_kickerValue)
                return -1;
            else
                return 0;
        }
    }
}

int PairCombinaison::compareImpl(Combinaison * a_otherCombinaison)
{
    PairCombinaison * otherCombinaison = dynamic_cast <PairCombinaison *> (a_otherCombinaison);

    if(m_value > otherCombinaison->m_value)
        return 1;
    else if(m_value < otherCombinaison->m_value)
        return -1;
    else
    {
        for(int i = 0; i < 3; ++ i)
        {
            if(m_kickersValue[i] > otherCombinaison->m_kickersValue[i])
                return 1;
            else if(m_kickersValue[i] < otherCombinaison->m_kickersValue[i])
                return -1;
        }

        return 0;
    }
}

int HighCardCombinaison::compareImpl(Combinaison * a_otherCombinaison)
{
    HighCardCombinaison * otherCombinaison = dynamic_cast <HighCardCombinaison *> (a_otherCombinaison);

    for(int i = 0; i < 5; ++ i)
    {
        if(m_values[i] > otherCombinaison->m_values[i])
            return 1;
        else if(m_values[i] < otherCombinaison->m_values[i])
            return -1;
    }

    return 0;
}

