#ifndef COMPUTEHANDPROBASTEP2_H
#define COMPUTEHANDPROBASTEP2_H

#include <cardsetbrowserstrategy.h>

class ComputeHandProbaStep2 : public CardSetBrowserStrategy <3>
{
private :

    unsigned int m_hand1;
    unsigned int m_hand2;

    double m_boardCount;
    double m_onePairCount;
    double m_doublePairCount;
    double m_brelanCount;
    double m_carreCount;
    double m_fullCount;

public:
    ComputeHandProbaStep2(unsigned int a_hand1, unsigned int a_hand2);
    ~ComputeHandProbaStep2();

public :

    void processCardSet(unsigned int a_cardSet [3]);


};

#endif // COMPUTEHANDPROBASTEP2_H
