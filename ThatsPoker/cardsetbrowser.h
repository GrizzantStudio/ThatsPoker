#ifndef CARDSETBROWSER_H
#define CARDSETBROWSER_H

#include <set>
#include <maths.h>
#include <cardsetbrowserstrategy.h>

template <unsigned int CARD_COUNT>
class CardSetBrowser
{
private :

    CardSetBrowserStrategy <CARD_COUNT> * m_strategy;
    std::set <unsigned int> m_forbiddenCards;

protected:

    CardSetBrowser(CardSetBrowserStrategy <CARD_COUNT> * a_strategy)
        : m_strategy(a_strategy)
    {
    }

    virtual ~CardSetBrowser()
    {
    }

 public :

    void addForbiddenCard(unsigned int a_cardId)
    {
        m_forbiddenCards.insert(a_cardId);
    }

    void browse()
    {
        double setCount = Maths::binomialCoeff(52 - m_forbiddenCards.size(), CARD_COUNT);

        unsigned int * allowedValues = new unsigned int [52 - m_forbiddenCards.size()];

        unsigned int valueIndex = 0;
        for(int i = 0; i < 52; ++ i)
        {
            if(m_forbiddenCards.find(i) != m_forbiddenCards.end())
                continue;

            allowedValues[valueIndex] = i;
            ++ valueIndex;
        }

        unsigned int setValueIndex [CARD_COUNT];
        unsigned int setValues [CARD_COUNT];

        for(int i = 0; i < CARD_COUNT; ++ i)
            setValueIndex[i] = (i == 0) ? 0 : setValueIndex[i - 1] + 1;

        double setIndex = 0.;

        while(setIndex < setCount - 0.5)
        {
            if(m_strategy != nullptr)
            {
                for(int i = 0; i < CARD_COUNT; ++ i)
                {
                    setValues[i] = allowedValues[setValueIndex[i]];
                }

                m_strategy->processCardSet(setValues);
            }

            bool increment = true;
            unsigned int offset = 0;
            unsigned int reinitFromIndex = CARD_COUNT;

            for(int i = CARD_COUNT - 1; increment && i >= 0; --i)
            {
                ++ setValueIndex[i];
                increment = setValueIndex[i] > 52 - m_forbiddenCards.size() - 1 - offset;

                if(increment)
                {
                    -- reinitFromIndex;
                    ++ offset;
                }
            }

            for(int i = reinitFromIndex; i < CARD_COUNT; ++ i)
            {
                setValueIndex[i] = setValueIndex[i-1] + 1;
            }

            setIndex += 1.;
        }

        delete [] allowedValues;
    }
};

#endif // CARDSETBROWSER_H
