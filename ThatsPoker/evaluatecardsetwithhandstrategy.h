#ifndef EVALUATECARDSETWITHHANDSTRATEGY_H
#define EVALUATECARDSETWITHHANDSTRATEGY_H

#include <cardsetbrowserstrategy.h>
#include <QVector>
#include <evaluator.h>
#include <maths.h>

template <unsigned int CARD_COUNT>
class EvaluateCardSetWithHandStrategy : public CardSetBrowserStrategy <CARD_COUNT>
{
private :

    unsigned int m_hand1;
    unsigned int m_hand2;

    double m_cardSetCount;
    double m_combinaisonsCount [9];

public:
    EvaluateCardSetWithHandStrategy(unsigned int a_hand1, unsigned int a_hand2)
        : m_hand1(a_hand1)
        , m_hand2(a_hand2)
    {
    }

    ~EvaluateCardSetWithHandStrategy() {}

public :

    void processCardSet(unsigned int a_cardSet [CARD_COUNT])
    {
        ++ m_cardSetCount;

        unsigned int * cards = new unsigned int[CARD_COUNT + 2];

        cards[0] = m_hand1;
        cards[1] = m_hand2;

        for(int i = 0; i < CARD_COUNT; ++ i)
            cards[i + 2] = a_cardSet[i];

        Evaluator <CARD_COUNT + 2> evaluator;
        CombinaisonPtr combinaison = evaluator.evaluate(cards);

        m_combinaisonsCount[combinaison->getType()] += 1.;

        delete [] cards;
    }

    double getCombinaisonProbaInPercent(unsigned int a_combinaisonType)
    {
        return Maths::roundProba(m_combinaisonsCount[a_combinaisonType] / m_cardSetCount * 100.);
    }
};

#endif // EVALUATECARDSETWITHHANDSTRATEGY_H
