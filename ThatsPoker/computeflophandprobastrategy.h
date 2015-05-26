#ifndef COMPUTEFLOPHANDPROBASTRATEGY_H
#define COMPUTEFLOPHANDPROBASTRATEGY_H

#include <cardsetbrowserstrategy.h>
#include <QVector>

class ComputeFlopHandProbaStrategy : public CardSetBrowserStrategy <3>
{
private :

    unsigned int m_hand1;
    unsigned int m_hand2;

    double m_boardCount;
    double m_combinaisonsCount [9];


public:
    ComputeFlopHandProbaStrategy(unsigned int a_hand1, unsigned int a_hand2);
    ~ComputeFlopHandProbaStrategy();

public :

    void processCardSet(unsigned int a_cardSet [3]);
    double getCombinaisonProbaInPercent(unsigned int a_combinaisonType);

};

#endif // COMPUTEFLOPHANDPROBASTRATEGY_H
