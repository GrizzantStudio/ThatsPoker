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

    class CombinaisonCount
    {
    public :

        CombinaisonCount()
            : usingHigherHandCardCount(0.)
            , usingLowerHandCardCount(0.)
            , usingBothHandCardCount(0.)
            , usingNoHandCardCount(0.)
            , totalCount(0.)
        {}

    public :
        double usingHigherHandCardCount;
        double usingLowerHandCardCount;
        double usingBothHandCardCount;
        double usingNoHandCardCount;
        double totalCount;
    };

private :

    unsigned int m_hand1;
    unsigned int m_hand2;

    double m_cardSetCount;
    CombinaisonCount m_combinaisonsCount [9];

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

        if(m_hand1 % 13 > m_hand2 % 13)
        {
            cards[0] = m_hand1;
            cards[1] = m_hand2;
        }
        else
        {
            cards[0] = m_hand2;
            cards[1] = m_hand1;
        }

        for(int i = 0; i < CARD_COUNT; ++ i)
            cards[i + 2] = a_cardSet[i];

        Evaluator <CARD_COUNT + 2> evaluator;
        Evaluator <CARD_COUNT + 2>::EvaluatorResult result = evaluator.evaluate(cards);

        if(result.cardUsed[0] && ! result.cardUsed[1])
            m_combinaisonsCount[result.combinaison->getType()].usingHigherHandCardCount += 1.;
        else if(! result.cardUsed[0] && result.cardUsed[1])
            m_combinaisonsCount[result.combinaison->getType()].usingLowerHandCardCount += 1.;
        else if(result.cardUsed[0] && result.cardUsed[1])
            m_combinaisonsCount[result.combinaison->getType()].usingBothHandCardCount += 1.;
        else
            m_combinaisonsCount[result.combinaison->getType()].usingNoHandCardCount += 1.;

        m_combinaisonsCount[result.combinaison->getType()].totalCount += 1.;

        delete [] cards;
    }

    double getCombinaisonProbaInPercent(unsigned int a_combinaisonType)
    {
        return Maths::roundProba(m_combinaisonsCount[a_combinaisonType].totalCount / m_cardSetCount * 100.);
    }
};

#endif // EVALUATECARDSETWITHHANDSTRATEGY_H
