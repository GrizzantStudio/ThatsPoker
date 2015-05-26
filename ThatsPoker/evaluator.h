#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include <combinaison.h>

#include <memory>

template <unsigned int CARD_COUNT>
class Evaluator
{
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

    CombinaisonPtr checkStraightFlush()
    {
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

        return straightFlush ? CombinaisonPtr(new StraightFlushCombinaison(straightFlushValue)) : nullptr;
    }

    CombinaisonPtr checkFourOfAKind()
    {
        bool carre = false;
        int carreValue = -1;
        int kickerValue = -1;

        for(int i = 12; ! carre && i >= 0; -- i)
        {
            if(m_cardIndexPerValue[i].size() == 4)
            {
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

        return carre ? CombinaisonPtr(new FourOfAKindCombinaison(carreValue, kickerValue)) : nullptr;
    }

    CombinaisonPtr checkFullHouse()
    {
        bool full = false;
        int fullMainValue = -1;
        int fullSecondaryValue = -1;

        for(int i = 12; fullMainValue == -1 && i >= 0; -- i)
        {
            if(m_cardIndexPerValue[i].size() == 3)
                fullMainValue = i;
        }

        if(fullMainValue != -1)
        {
            for(int i = 12; fullSecondaryValue == -1 && i >= 0; -- i)
            {
                if(i != fullMainValue && m_cardIndexPerValue[i].size() >= 2)
                    fullSecondaryValue = i;
            }
        }

        full = fullMainValue != -1 && fullSecondaryValue != -1;

        return full ? CombinaisonPtr(new FullHouseCombinaison(fullMainValue, fullSecondaryValue)) : nullptr;
    }

    CombinaisonPtr checkFlush()
    {
        bool flush = false;
        int flush_values [5] = {-1, -1, -1, -1, -1};
        int flushColor = -1;

        for(int i = 0; ! flush && i < 4; ++ i)
        {
            if(m_cardIndexPerColor[i].size() >= 5)
            {
                flush = true;

                for(int j = 0; j < 5; ++ j)
                    flush_values[j] = m_values[m_cardIndexPerColor[i][j]];

                flushColor = i;
            }
        }

        return flush ? CombinaisonPtr(new FlushCombinaison(flush_values)) : nullptr;
    }

    CombinaisonPtr checkStraight()
    {
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

        return straight ? CombinaisonPtr(new StraightCombinaison(straightValue)) : nullptr;
    }

    CombinaisonPtr checkThreeOfAKind()
    {
        bool brelan = false;
        int brelanValue = -1;
        int kickersValue [2] = {-1, -1};

        for(int i = 12; ! brelan && i >= 0; -- i)
        {
            if(m_cardIndexPerValue[i].size() == 3)
            {
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

        return brelan ? CombinaisonPtr(new ThreeOfAKindCombinaison(brelanValue, kickersValue)) : nullptr;
    }

    CombinaisonPtr checkDoublePair()
    {
        bool doublePair = false;
        int doublePairValue1 = -1;
        int doublePairValue2 = -1;
        int kickerValue = -1;

        for(int i = 12; ! doublePair && i >= 0; -- i)
        {
            if(m_cardIndexPerValue[i].size() == 2)
            {
                if(doublePairValue1 == -1)
                    doublePairValue1 = i;
                else if(doublePairValue2 == -1)
                {
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

        return doublePair ? CombinaisonPtr(new DoublePairCombinaison(doublePairValue1, doublePairValue2, kickerValue)) : nullptr;
    }

    CombinaisonPtr checkPair()
    {
        bool pair = false;
        int pairValue = -1;
        int kickersValue [3] = {-1, -1, -1};

        for(int i = 12; ! pair && i >= 0; -- i)
        {
            if(m_cardIndexPerValue[i].size() == 2)
            {
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

        return pair ? CombinaisonPtr(new PairCombinaison(pairValue, kickersValue)) : nullptr;
    }

    CombinaisonPtr checkHighCard()
    {
        int highCards [5] = {-1, -1, -1, -1, -1};

        int highCardIndex = 0;
        for(int i = 12; highCards[4] == -1 && i >= 0; -- i)
        {
            if(! m_cardIndexPerValue[i].empty())
            {
                highCards[highCardIndex] = i;
                ++ highCardIndex;
            }
        }

        return CombinaisonPtr(new HighCardCombinaison(highCards));
    }

public :

    CombinaisonPtr evaluate(unsigned int a_cards[CARD_COUNT])
    {
        CombinaisonPtr combinaison = nullptr;

        initialize(a_cards);

        if(combinaison == nullptr)
            combinaison = checkStraightFlush();

        if(combinaison == nullptr)
            combinaison = checkFourOfAKind();

        if(combinaison == nullptr)
            combinaison = checkFullHouse();

        if(combinaison == nullptr)
            combinaison = checkFlush();

        if(combinaison == nullptr)
            combinaison = checkStraight();

        if(combinaison == nullptr)
            combinaison = checkThreeOfAKind();

        if(combinaison == nullptr)
            combinaison = checkDoublePair();

        if(combinaison == nullptr)
            combinaison = checkPair();

        if(combinaison == nullptr)
            combinaison = checkHighCard();

        return combinaison;
    }

};

#endif // EVALUATOR_H
