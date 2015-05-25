#include "processor.h"
#include "maths.h"
#include <iostream>
#include <handbrowser.h>
#include <displaycardsetsstrategy.h>
#include <flopboardbrowser.h>
#include <computehandprobastep1.h>

Processor::Processor()
{

}

Processor::~Processor()
{

}

void Processor::process()
{
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

    ComputeHandProbaStep1 * computeHandProbaStep1 = new ComputeHandProbaStep1();
    HandBrowser handBrowser(computeHandProbaStep1);
    handBrowser.browse();
    delete computeHandProbaStep1;
}


