#ifndef COMPUTEFLOPTURNRIVERHANDPROBASTRATEGY_H
#define COMPUTEFLOPTURNRIVERHANDPROBASTRATEGY_H

#include <cardsetbrowserstrategy.h>
#include <QVector>

class ComputeFlopTurnRiverHandProbaStrategy : public CardSetBrowserStrategy <5>
{
private :

    unsigned int m_hand1;
    unsigned int m_hand2;

    double m_boardCount;
    double m_combinaisonsCount [9];

public:
    ComputeFlopTurnRiverHandProbaStrategy(unsigned int a_hand1, unsigned int a_hand2);
    ~ComputeFlopTurnRiverHandProbaStrategy();

public :

    void processCardSet(unsigned int a_cardSet [5]);
    double getCombinaisonProbaInPercent(unsigned int a_combinaisonType);
};

#endif // COMPUTEFLOPTURNRIVERHANDPROBASTRATEGY_H
