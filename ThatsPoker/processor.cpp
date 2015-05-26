#include "processor.h"
#include "maths.h"
#include <iostream>
#include <handbrowser.h>
#include <displaycardsetsstrategy.h>
#include <flopboardbrowser.h>
#include <computehandprobastep1.h>
#include <computeflophandprobastrategy.h>
#include <handcategorizerstrategy.h>
#include <handcategory.h>
#include <evaluator.h>
#include <computeflopturnriverhandprobastrategy.h>
#include <flopturnriverboardbrowser.h>

Processor::Processor()
{

}

Processor::~Processor()
{

}

void Processor::process()
{
    /*
    Evaluator <7> evaluator;
    unsigned int cards [7] = {10, 21, 25, 0, 7, 47, 50};
    evaluator.evaluate(cards);
*/

    HandCategorizerStrategy * handCategorizerStrategy = new HandCategorizerStrategy();
    HandBrowser handBrowser(handCategorizerStrategy);
    handBrowser.browse();

    const HandCategorizerStrategy::HandCategories & handCategories = handCategorizerStrategy->getCategories();

    int categoryIndex = 0;
    for(const auto & categoryEntry : handCategories)
    {

        unsigned int hand1 = categoryEntry[0].first;
        unsigned int hand2 = categoryEntry[0].second;


        ComputeFlopHandProbaStrategy * computeFlopHandProbaStrategy = new ComputeFlopHandProbaStrategy(hand1, hand2);
        FlopBoardBrowser flopBoardBrowser(computeFlopHandProbaStrategy);
        flopBoardBrowser.addForbiddenCard(hand1);
        flopBoardBrowser.addForbiddenCard(hand2);
        flopBoardBrowser.browse();

        ComputeFlopTurnRiverHandProbaStrategy * computeFlopTurnRiverHandProbaStrategy = new ComputeFlopTurnRiverHandProbaStrategy(hand1, hand2);
        FlopTurnRiverBoardBrowser flopTurnRiverBoardBrowser(computeFlopTurnRiverHandProbaStrategy);
        flopTurnRiverBoardBrowser.addForbiddenCard(hand1);
        flopTurnRiverBoardBrowser.addForbiddenCard(hand2);
        flopTurnRiverBoardBrowser.browse();

        std::cout << "===================" << std::endl;
        std::cout << "Category : " << categoryIndex << std::endl;
        std::cout << "High card proba : [FLOP " << computeFlopHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::HIGH_CARD) << " %] [FLOP+TURN+RIVER " << computeFlopTurnRiverHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::HIGH_CARD) << " %]" << std::endl;
        std::cout << "Pair proba : [FLOP " << computeFlopHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::PAIR) << " %] [FLOP+TURN+RIVER " << computeFlopTurnRiverHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::PAIR) << " %]" << std::endl;
        std::cout << "Double pair proba : [FLOP " << computeFlopHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::DOUBLE_PAIR) << " %] [FLOP+TURN+RIVER " << computeFlopTurnRiverHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::DOUBLE_PAIR) << " %]" << std::endl;
        std::cout << "Three of a kind proba : [FLOP " << computeFlopHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::THREE_OF_A_KIND) << " %] [FLOP+TURN+RIVER " << computeFlopTurnRiverHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::THREE_OF_A_KIND) << " %]" << std::endl;
        std::cout << "Straight proba : [FLOP " << computeFlopHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::STRAIGHT) << " %] [FLOP+TURN+RIVER " << computeFlopTurnRiverHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::STRAIGHT) << " %]" << std::endl;
        std::cout << "Flush proba : [FLOP " << computeFlopHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::FLUSH) << " %] [FLOP+TURN+RIVER " << computeFlopTurnRiverHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::FLUSH) << " %]" << std::endl;
        std::cout << "Full house proba : [FLOP " << computeFlopHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::FULL_HOUSE) << " %] [FLOP+TURN+RIVER " << computeFlopTurnRiverHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::FULL_HOUSE) << " %]" << std::endl;
        std::cout << "Four of a kind proba : [FLOP " << computeFlopHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::FOUR_OF_A_KIND) << " %] [FLOP+TURN+RIVER " << computeFlopTurnRiverHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::FOUR_OF_A_KIND) << " %]" << std::endl;
        std::cout << "Straight flush proba : [FLOP " << computeFlopHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::STRAIGHT_FLUSH) << " %] [FLOP+TURN+RIVER " << computeFlopTurnRiverHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::STRAIGHT_FLUSH) << " %]" << std::endl;

        delete computeFlopHandProbaStrategy;
        delete computeFlopTurnRiverHandProbaStrategy;

        /*for(const auto & hand : categoryEntry)
        {
            ComputeFlopHandProbaStrategy * computeFlopHandProbaStrategy = new ComputeFlopHandProbaStrategy(hand.first, hand.second);
            FlopBoardBrowser flopBoardBrowser(computeFlopHandProbaStrategy);
            flopBoardBrowser.addForbiddenCard(hand.first);
            flopBoardBrowser.addForbiddenCard(hand.second);
            flopBoardBrowser.browse();

            //std::cout << "Brelan proba : " << computeFlopHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::DOUBLE_PAIR) << " %" << std::endl;

            delete computeFlopHandProbaStrategy;
        }*/

        ++ categoryIndex;
    }

    delete handCategorizerStrategy;

    /*DisplayCardSetsStrategy <2> * displayCardSetsStrategy = new DisplayCardSetsStrategy <2> ();
    HandBrowser handBrowser(displayCardSetsStrategy);
    handBrowser.browse();
    delete displayCardSetsStrategy;
    */

    /*DisplayCardSetsStrategy <3> * displayCardSetsStrategy = new DisplayCardSetsStrategy <3> ();
    FlopBoardBrowser flopBoardBrowser(displayCardSetsStrategy);
    flopBoardBrowser.addForbiddenCard(15);
    flopBoardBrowser.addForbiddenCard(35);
    flopBoardBrowser.browse();
    delete displayCardSetsStrategy;
    */

    /*ComputeHandProbaStep1 * computeHandProbaStep1 = new ComputeHandProbaStep1();
    HandBrowser handBrowser(computeHandProbaStep1);
    handBrowser.browse();
    delete computeHandProbaStep1;*/
}


