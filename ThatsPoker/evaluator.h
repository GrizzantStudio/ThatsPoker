#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include <combinaison.h>

#include <memory>

template <unsigned int CARD_COUNT>
class Evaluator
{
public :

    class EvaluatorResult
    {
    public :
        EvaluatorResult()
            : combinaison(nullptr)
        {
            for(int i = 0; i < CARD_COUNT; ++ i)
                cardUsed[i] = false;
        }

    public :
        CombinaisonPtr combinaison;
        bool cardUsed[CARD_COUNT];
    };

private :

    int m_colors [CARD_COUNT];
    int m_values [CARD_COUNT];
    std::vector <unsigned int> m_cardIndexPerColor [4];
    std::vector <unsigned int> m_cardIndexPerValue [13];


public:
    Evaluator() {}
    ~Evaluator() {}

private :

    void initialize(unsigned int a_cards[CARD_COUNT])
    {
        for(int i = 0; i < CARD_COUNT; ++ i)
        {
            m_colors[i] = a_cards[i] / 13;
            m_values[i] = a_cards[i] % 13;

            m_cardIndexPerColor[m_colors[i]].push_back(i);
            m_cardIndexPerValue[m_values[i]].push_back(i);
        }

        for(int i = 0; i < 4; ++ i)
        {
            bool ordered = false;
            int arraySize = m_cardIndexPerColor[i].size();
            while(! ordered)
            {
                ordered = true;
                for(int j = 0 ; j < arraySize - 1 ; ++ j)
                {
                    int value1 = m_values[m_cardIndexPerColor[i][j]];
                    int value2 = m_values[m_cardIndexPerColor[i][j+1]];

                    if(value1 < value2)
                    {
                        unsigned int temp = m_cardIndexPerColor[i][j];
                        m_cardIndexPerColor[i][j] = m_cardIndexPerColor[i][j+1];
                        m_cardIndexPerColor[i][j+1] = temp;
                        ordered = false;
                    }
                }

                -- arraySize;
             }
        }

        /*
                for(int i = 0; i < 4; ++ i)
                {
                    std::cout << "= m_values with color " << i << std::endl;
                    for(unsigned int j = 0; j < m_cardIndexPerColor[i].size(); ++ j)
                        std::cout << m_values[m_cardIndexPerColor[i][j]] << std::endl;
                }
        */
    }

    EvaluatorResult checkStraightFlush()
    {
        EvaluatorResult result;

        bool straightFlush = false;
        int straightFlushColor = -1;
        int straightFlushValue = -1;

        for(int i = 0; i < 4; ++ i)
        {
            //std::cout << "= Check straight flush color " << i << std::endl;

            if(m_cardIndexPerColor[i].size() < 5)
            {
                //std::cout << "== not enough cards with color " << i << std::endl;
                continue;
            }

            bool hasAce = m_values[m_cardIndexPerColor[i][0]] == 12;

            //if(hasAce)
            //    std::cout << "== Ace detected" << std::endl;

            for(unsigned int j = 0; ! straightFlush && j < m_cardIndexPerColor[i].size(); ++ j)
            {
                //std::cout << "== Check straight flush from index " << j << std::endl;

                bool straight = true;
                int straightCardCount = 1;

                for(int k = 0; k < CARD_COUNT; ++ k)
                    result.cardUsed[k] = (k == m_cardIndexPerColor[i][j]);

                for(unsigned int k = j; ! straightFlush && straight && k < m_cardIndexPerColor[i].size(); ++ k)
                {
                    //std::cout << "=== check index " << k << " (value1 : " << m_values[m_cardIndexPerColor[i][k]] << ", value2 : " << m_values[m_cardIndexPerColor[i][k+1]] << ")" << std::endl;
                    if(k == m_cardIndexPerColor[i].size() - 1)
                        straight = m_values[m_cardIndexPerColor[i][k]] == 0 && hasAce;
                    else
                        straight = m_values[m_cardIndexPerColor[i][k]] == m_values[m_cardIndexPerColor[i][k+1]] + 1;

                    if(straight)
                    {
                        //std::cout << "=== " << straightCardCount << " straight cards" << std::endl;

                        result.cardUsed[m_cardIndexPerColor[i][(k == m_cardIndexPerColor[i].size() - 1) ? 0 : k + 1]] = true;

                        ++ straightCardCount;
                        if(straightCardCount == 5)
                        {
                            straightFlush = true;
                            straightFlushColor = i;
                            straightFlushValue = m_values[m_cardIndexPerColor[i][j]];
                        }
                    }
                    else
                    {
                        //std::cout << "=== straight broken" << std::endl;
                    }
                }
            }
        }

        result.combinaison = straightFlush ? CombinaisonPtr(new StraightFlushCombinaison(straightFlushValue)) : nullptr;
        return result;
    }

    EvaluatorResult checkFourOfAKind()
    {
        EvaluatorResult result;

        bool carre = false;
        int carreValue = -1;
        int kickerValue = -1;

        for(int i = 12; ! carre && i >= 0; -- i)
        {
            if(m_cardIndexPerValue[i].size() == 4)
            {
                for(int j = 0; j < 4; ++ j)
                    result.cardUsed[m_cardIndexPerValue[i][j]] = true;

                carreValue = i;
                carre = true;
            }
        }

        if(carre)
        {
            for(int i = 12; kickerValue == -1 && i >= 0; -- i)
            {
                if(i != carreValue && ! m_cardIndexPerValue[i].empty())
                    kickerValue = i;
            }
        }

        result.combinaison = carre ? CombinaisonPtr(new FourOfAKindCombinaison(carreValue, kickerValue)) : nullptr;
        return result;
    }

    EvaluatorResult checkFullHouse()
    {
        EvaluatorResult result;

        bool full = false;
        int fullMainValue = -1;
        int fullSecondaryValue = -1;

        for(int i = 12; fullMainValue == -1 && i >= 0; -- i)
        {
            if(m_cardIndexPerValue[i].size() == 3)
            {
                for(int j = 0; j < 3; ++ j)
                    result.cardUsed[m_cardIndexPerValue[i][j]] = true;

                fullMainValue = i;
            }
        }

        if(fullMainValue != -1)
        {
            for(int i = 12; fullSecondaryValue == -1 && i >= 0; -- i)
            {
                if(i != fullMainValue && m_cardIndexPerValue[i].size() >= 2)
                {
                    for(unsigned int j = 0; j < m_cardIndexPerValue[i].size(); ++ j)
                        result.cardUsed[m_cardIndexPerValue[i][j]] = true;

                    fullSecondaryValue = i;
                }
            }
        }

        full = fullMainValue != -1 && fullSecondaryValue != -1;

        result.combinaison = full ? CombinaisonPtr(new FullHouseCombinaison(fullMainValue, fullSecondaryValue)) : nullptr;
        return result;
    }

    EvaluatorResult checkFlush()
    {
        EvaluatorResult result;

        bool flush = false;
        int flush_values [5] = {-1, -1, -1, -1, -1};
        int flushColor = -1;

        for(int i = 0; ! flush && i < 4; ++ i)
        {
            if(m_cardIndexPerColor[i].size() >= 5)
            {
                flush = true;

                for(int j = 0; j < 5; ++ j)
                {
                    flush_values[j] = m_values[m_cardIndexPerColor[i][j]];
                    result.cardUsed[m_cardIndexPerColor[i][j]] = true;
                }
                flushColor = i;
            }
        }

        result.combinaison = flush ? CombinaisonPtr(new FlushCombinaison(flush_values)) : nullptr;
        return result;
    }

    EvaluatorResult checkStraight()
    {
        EvaluatorResult result;

        bool straight = false;
        int straightValue = -1;

        bool hasAce = false;

        for(int i = 0; ! hasAce && i < 4; ++ i)
        {
            if(m_cardIndexPerColor[i].empty())
                continue;

            hasAce = m_values[m_cardIndexPerColor[i][0]] == 12;
        }

        for(int i = 12; ! straight && i >= 0; -- i)
        {
            if(m_cardIndexPerValue[i].empty())
                continue;

            //std::cout << "== Check straight from value " << i << std::endl;

            bool continueStraight = true;
            int straightCardCount = 1;

            for(int j = 0; j < CARD_COUNT; ++ j)
            {
                result.cardUsed[j] = m_values[j] == i;
            }

            for(int j = i; ! straight && continueStraight && j >= 0; -- j)
            {
                if(j == 0)
                {
                    continueStraight = hasAce;
                    //std::cout << "=== check value " << j << " : " << hasAce << std::endl;
                }
                else
                {
                    continueStraight = ! m_cardIndexPerValue[j-1].empty();
                    //std::cout << "=== check value " << j << " : " << ! m_cardIndexPerValue[j-1].empty() << std::endl;
                }

                if(continueStraight)
                {  
                    for(int k = 0; k < CARD_COUNT; ++ k)
                    {
                        if(m_values[k] == (j == 0) ? 12 : j - 1)
                            result.cardUsed[k] = true;
                    }

                    ++ straightCardCount;
                    //std::cout << "=== " << straightCardCount << " straight cards" << std::endl;

                    if(straightCardCount == 5)
                    {
                        straight = true;
                        straightValue = i;
                    }
                }
                else
                {
                    //std::cout << "=== straight broken" << std::endl;
                }
            }
        }

        result.combinaison = straight ? CombinaisonPtr(new StraightCombinaison(straightValue)) : nullptr;
        return result;
    }

    EvaluatorResult checkThreeOfAKind()
    {
        EvaluatorResult result;

        bool brelan = false;
        int brelanValue = -1;
        int kickersValue [2] = {-1, -1};

        for(int i = 12; ! brelan && i >= 0; -- i)
        {
            if(m_cardIndexPerValue[i].size() == 3)
            {
                for(int j = 0; j < 3; ++ j)
                    result.cardUsed[m_cardIndexPerValue[i][j]] = true;

                brelanValue = i;
                brelan = true;
            }
        }

        if(brelan)
        {
            int kickerIndex = 0;

            for(int i = 12; kickersValue[1] == -1 && i >= 0; -- i)
            {
                if(i != brelanValue && ! m_cardIndexPerValue[i].empty())
                {
                    kickersValue[kickerIndex] = i;
                    ++ kickerIndex;
                }
            }
        }

        result.combinaison = brelan ? CombinaisonPtr(new ThreeOfAKindCombinaison(brelanValue, kickersValue)) : nullptr;
        return result;
    }

    EvaluatorResult checkDoublePair()
    {
        EvaluatorResult result;

        bool doublePair = false;
        int doublePairValue1 = -1;
        int doublePairValue2 = -1;
        int kickerValue = -1;

        for(int i = 12; ! doublePair && i >= 0; -- i)
        {
            if(m_cardIndexPerValue[i].size() == 2)
            {
                if(doublePairValue1 == -1)
                {
                    for(int j = 0; j < 2; ++ j)
                        result.cardUsed[m_cardIndexPerValue[i][j]] = true;

                    doublePairValue1 = i;
                }
                else if(doublePairValue2 == -1)
                {
                    for(int j = 0; j < 2; ++ j)
                        result.cardUsed[m_cardIndexPerValue[i][j]] = true;

                    doublePairValue2 = i;
                    doublePair = true;
                }
            }
        }

        if(doublePair)
        {
            for(int i = 12; kickerValue == -1 && i >= 0; -- i)
            {
                if(i != doublePairValue1 && i != doublePairValue2 && ! m_cardIndexPerValue[i].empty())
                    kickerValue = i;
            }
        }

        result.combinaison = doublePair ? CombinaisonPtr(new DoublePairCombinaison(doublePairValue1, doublePairValue2, kickerValue)) : nullptr;
        return result;
    }

    EvaluatorResult checkPair()
    {
        EvaluatorResult result;

        bool pair = false;
        int pairValue = -1;
        int kickersValue [3] = {-1, -1, -1};

        for(int i = 12; ! pair && i >= 0; -- i)
        {
            if(m_cardIndexPerValue[i].size() == 2)
            {
                for(int j = 0; j < 2; ++ j)
                    result.cardUsed[m_cardIndexPerValue[i][j]] = true;

                pairValue = i;
                pair = true;
            }
        }

        if(pair)
        {
            int kickerIndex = 0;
            for(int i = 12; kickersValue[2] == -1 && i >= 0; -- i)
            {
                if(i != pairValue && ! m_cardIndexPerValue[i].empty())
                {
                    kickersValue[kickerIndex] = i;
                    ++ kickerIndex;
                }
            }
        }

        result.combinaison = pair ? CombinaisonPtr(new PairCombinaison(pairValue, kickersValue)) : nullptr;
        return result;
    }

    EvaluatorResult checkHighCard()
    {
        EvaluatorResult result;

        int highCards [5] = {-1, -1, -1, -1, -1};

        int highCardIndex = 0;
        for(int i = 12; highCards[4] == -1 && i >= 0; -- i)
        {
            if(! m_cardIndexPerValue[i].empty())
            {
                highCards[highCardIndex] = i;

                Q_ASSERT(m_cardIndexPerValue[i].size() == 0);
                result.cardUsed[m_cardIndexPerValue[i][0]] = true;

                ++ highCardIndex;
            }
        }

        result.combinaison = CombinaisonPtr(new HighCardCombinaison(highCards));
        return result;
    }

public :

    EvaluatorResult evaluate(unsigned int a_cards[CARD_COUNT])
    {
        EvaluatorResult result;

        initialize(a_cards);

        if(result.combinaison == nullptr)
            result = checkStraightFlush();

        if(result.combinaison == nullptr)
            result = checkFourOfAKind();

        if(result.combinaison == nullptr)
            result = checkFullHouse();

        if(result.combinaison == nullptr)
            result = checkFlush();

        if(result.combinaison == nullptr)
            result = checkStraight();

        if(result.combinaison == nullptr)
            result = checkThreeOfAKind();

        if(result.combinaison == nullptr)
            result = checkDoublePair();

        if(result.combinaison == nullptr)
            result = checkPair();

        if(result.combinaison == nullptr)
            result = checkHighCard();

        return result;
    }

};

#endif // EVALUATOR_H
