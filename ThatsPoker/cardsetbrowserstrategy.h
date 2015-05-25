#ifndef CARDSETBROWSERSTRATEGY
#define CARDSETBROWSERSTRATEGY

template <unsigned int CARD_COUNT>
class CardSetBrowserStrategy
{
public :

    virtual void processCardSet(unsigned int a_cardSet [CARD_COUNT]) = 0;
};

#endif // CARDSETBROWSERSTRATEGY

