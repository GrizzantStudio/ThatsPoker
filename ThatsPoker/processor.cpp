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

    for(const auto & categoryEntry : handCategories)
    {
        for(const auto & hand : categoryEntry)
        {
            ComputeFlopHandProbaStrategy * computeFlopHandProbaStrategy = new ComputeFlopHandProbaStrategy(hand.first, hand.second);
            FlopBoardBrowser flopBoardBrowser(computeFlopHandProbaStrategy);
            flopBoardBrowser.addForbiddenCard(hand.first);
            flopBoardBrowser.addForbiddenCard(hand.second);
            flopBoardBrowser.browse();

            //std::cout << "Brelan proba : " << computeFlopHandProbaStrategy->getCombinaisonProbaInPercent(CombinaisonType::DOUBLE_PAIR) << " %" << std::endl;

            delete computeFlopHandProbaStrategy;
        }
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


