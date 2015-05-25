#include "handcategorizerstrategy.h"

const unsigned int HandCategorizerStrategy::PAIR = 0;
const unsigned int HandCategorizerStrategy::SORTED_CONNECTORS = 1;
const unsigned int HandCategorizerStrategy::SORTED_1_GAPPERS = 2;
const unsigned int HandCategorizerStrategy::SORTED_2_GAPPERS = 3;
const unsigned int HandCategorizerStrategy::SORTED_3_GAPPERS = 4;
const unsigned int HandCategorizerStrategy::SORTED_MISC = 5;
const unsigned int HandCategorizerStrategy::UNSORTED_CONNECTORS = 6;
const unsigned int HandCategorizerStrategy::UNSORTED_1_GAPPERS = 7;
const unsigned int HandCategorizerStrategy::UNSORTED_2_GAPPERS = 8;
const unsigned int HandCategorizerStrategy::UNSORTED_3_GAPPERS = 9;
const unsigned int HandCategorizerStrategy::UNSORTED_MISC = 10;

HandCategorizerStrategy::HandCategorizerStrategy()
{

}

HandCategorizerStrategy::~HandCategorizerStrategy()
{

}

const HandCategorizerStrategy::HandCategories & HandCategorizerStrategy::getCategories()
{
    return m_handCategories;
}

void HandCategorizerStrategy::processCardSet(unsigned int a_cardSet [2])
{
    int value1 = a_cardSet[0] % 13;
    int color1 = a_cardSet[0] / 13;

    int value2 = a_cardSet[1] % 13;
    int color2 = a_cardSet[1] / 13;

    bool pair = value1 == value2;

    QPair <unsigned int, unsigned int> hand(a_cardSet[0], a_cardSet[1]);

    if(pair)
    {
        m_handCategories[PAIR].push_back(hand);
    }
    else
    {
        bool sorted = color1 == color2;

        bool connectors = (value2 - value1 == 1) || (value1 == 0 && value2 == 12);

        if(connectors)
        {
            if(sorted)
                m_handCategories[SORTED_CONNECTORS].push_back(hand);
            else
                m_handCategories[UNSORTED_CONNECTORS].push_back(hand);
        }
        else
        {
            bool gappers1 = (value2 - value1 == 2) || (value1 == 1 && value2 == 12);

            if(gappers1)
            {
                if(sorted)
                    m_handCategories[SORTED_1_GAPPERS].push_back(hand);
                else
                    m_handCategories[UNSORTED_1_GAPPERS].push_back(hand);
            }
            else
            {
                bool gappers2 = (value2 - value1 == 3) || (value1 == 2 && value2 == 12);

                if(gappers2)
                {
                    if(sorted)
                        m_handCategories[SORTED_2_GAPPERS].push_back(hand);
                    else
                        m_handCategories[UNSORTED_2_GAPPERS].push_back(hand);
                }
                else
                {
                    bool gappers3 = (value2 - value1 == 4) || (value1 == 3 && value2 == 12);

                    if(gappers3)
                    {
                        if(sorted)
                            m_handCategories[SORTED_3_GAPPERS].push_back(hand);
                        else
                            m_handCategories[UNSORTED_3_GAPPERS].push_back(hand);
                    }
                    else
                    {
                        if(sorted)
                            m_handCategories[SORTED_MISC].push_back(hand);
                        else
                            m_handCategories[UNSORTED_MISC].push_back(hand);
                    }
                }
            }
        }
    }
}
