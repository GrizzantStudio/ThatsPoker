#include "handcategorizerstrategy.h"
#include <handcategory.h>

HandCategorizerStrategy::HandCategorizerStrategy()
{
    m_handCategories = HandCategories(11, HandList());
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

    if(value1 > value2)
    {
        int valueTmp = value1;
        int colorTmp = color1;

        value1 = value2;
        color1 = color2;

        value2 = valueTmp;
        color2 = colorTmp;
    }

    bool pair = value1 == value2;

    QPair <unsigned int, unsigned int> hand(a_cardSet[0], a_cardSet[1]);

    if(pair)
    {
        m_handCategories[HandCategory::PAIR].push_back(hand);
    }
    else
    {
        bool sorted = color1 == color2;

        bool connectors = (value2 - value1 == 1) || (value1 == 0 && value2 == 12);

        if(connectors)
        {
            if(sorted)
                m_handCategories[HandCategory::SORTED_CONNECTORS].push_back(hand);
            else
                m_handCategories[HandCategory::UNSORTED_CONNECTORS].push_back(hand);
        }
        else
        {
            bool gappers1 = (value2 - value1 == 2) || (value1 == 1 && value2 == 12);

            if(gappers1)
            {
                if(sorted)
                    m_handCategories[HandCategory::SORTED_1_GAPPERS].push_back(hand);
                else
                    m_handCategories[HandCategory::UNSORTED_1_GAPPERS].push_back(hand);
            }
            else
            {
                bool gappers2 = (value2 - value1 == 3) || (value1 == 2 && value2 == 12);

                if(gappers2)
                {
                    if(sorted)
                        m_handCategories[HandCategory::SORTED_2_GAPPERS].push_back(hand);
                    else
                        m_handCategories[HandCategory::UNSORTED_2_GAPPERS].push_back(hand);
                }
                else
                {
                    bool gappers3 = (value2 - value1 == 4) || (value1 == 3 && value2 == 12);

                    if(gappers3)
                    {
                        if(sorted)
                            m_handCategories[HandCategory::SORTED_3_GAPPERS].push_back(hand);
                        else
                            m_handCategories[HandCategory::UNSORTED_3_GAPPERS].push_back(hand);
                    }
                    else
                    {
                        if(sorted)
                            m_handCategories[HandCategory::SORTED_MISC].push_back(hand);
                        else
                            m_handCategories[HandCategory::UNSORTED_MISC].push_back(hand);
                    }
                }
            }
        }
    }
}
