#ifndef DISPLAYCARDSETSSTRATEGY_H
#define DISPLAYCARDSETSSTRATEGY_H

#include <cardsetbrowserstrategy.h>
#include <iostream>

template <unsigned int CARD_COUNT>
class DisplayCardSetsStrategy : public CardSetBrowserStrategy <CARD_COUNT>
{
public:
    DisplayCardSetsStrategy() {}
    ~DisplayCardSetsStrategy() {}

protected :

    void processCardSet(unsigned int a_cardSet [CARD_COUNT])
    {
        for(int i = 0; i < CARD_COUNT; ++ i)
            std::cout << a_cardSet[i] << " ";

        std::cout << std::endl;
    }
};

#endif // DISPLAYCARDSETSSTRATEGY_H
