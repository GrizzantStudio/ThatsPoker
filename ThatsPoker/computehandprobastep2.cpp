#include "computehandprobastep2.h"

#include <iostream>

ComputeHandProbaStep2::ComputeHandProbaStep2(unsigned int a_hand1, unsigned int a_hand2)
    : m_hand1(a_hand1)
    , m_hand2(a_hand2)
    , m_boardCount(0.)
    , m_onePairCount(0.)
    , m_doublePairCount(0.)
    , m_brelanCount(0.)
    , m_fullCount(0.)
    , m_carreCount(0.)
{

}

ComputeHandProbaStep2::~ComputeHandProbaStep2()
{

}

void ComputeHandProbaStep2::processCardSet(unsigned int a_cardSet [3])
{
    //std::cout << m_hand1 << " " << m_hand2 << " " << a_cardSet[0] << " " << a_cardSet[1] << " " << a_cardSet[2] << std::endl;

    int handValue1 = m_hand1 % 13;
    int handValue2 = m_hand2 % 13;
    int boardValue1 = a_cardSet[0] % 13;
    int boardValue2 = a_cardSet[1] % 13;
    int boardValue3 = a_cardSet[2] % 13;

    bool boardContainsABrelan = false;
    int boardBrelanValue = -1;

    if(boardValue1 == boardValue2 && boardValue2 == boardValue3)
    {
        boardContainsABrelan = true;
        boardBrelanValue = boardValue1;
    }

    bool boardContainsAPair = false;
    int boardPairValue = -1;
    int boardOtherValueWithPair = -1;

    if(! boardContainsABrelan)
    {
        if(boardValue1 == boardValue2)
        {
            boardContainsAPair = true;
            boardPairValue = boardValue1;
            boardOtherValueWithPair = boardValue3;
        }
        else if(boardValue2 == boardValue3)
        {
            boardContainsAPair = true;
            boardPairValue = boardValue2;
            boardOtherValueWithPair = boardValue1;
        }
        else if(boardValue1 == boardValue3)
        {
            boardContainsAPair = true;
            boardPairValue = boardValue1;
            boardOtherValueWithPair = boardValue2;
        }
    }

    bool servedPair = handValue1 == handValue2;

    bool combinaisonSpotted = false;

    // Carre ?
    bool carre = (servedPair && boardContainsAPair && handValue1 == boardPairValue)
                    || (! servedPair && boardContainsABrelan && (handValue1 == boardBrelanValue || handValue2 == boardBrelanValue));


    if(carre)
    {
        m_carreCount += 1.;
        combinaisonSpotted = true;
    }

    // Full ?

    /*if(! combinaisonSpotted)
    {
        bool full = (servedPair )
    }*/


}
