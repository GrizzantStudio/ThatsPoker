#include "computeflophandprobastrategy.h"
#include <evaluator.h>
#include <maths.h>

ComputeFlopHandProbaStrategy::ComputeFlopHandProbaStrategy(unsigned int a_hand1, unsigned int a_hand2)
    : m_hand1(a_hand1)
    , m_hand2(a_hand2)
    , m_boardCount(0.)
{
    for(int i = 0; i < 9; ++ i)
        m_combinaisonsCount[i] = 0.;
}

ComputeFlopHandProbaStrategy::~ComputeFlopHandProbaStrategy()
{

}

void ComputeFlopHandProbaStrategy::processCardSet(unsigned int a_cardSet [3])
{
    ++ m_boardCount;

    unsigned int cards[5] = {m_hand1, m_hand2, a_cardSet[0], a_cardSet[1], a_cardSet[2]};

    Evaluator <5> evaluator;
    CombinaisonPtr combinaison = evaluator.evaluate(cards);

    m_combinaisonsCount[combinaison->getType()] += 1.;
}

double ComputeFlopHandProbaStrategy::getCombinaisonProbaInPercent(unsigned int a_combinaisonType)
{
    return Maths::roundProba(m_combinaisonsCount[a_combinaisonType] / m_boardCount * 100.);
}
