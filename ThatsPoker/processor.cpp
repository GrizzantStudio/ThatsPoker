#include "processor.h"
#include "maths.h"
#include <iostream>
#include <displaycardsetsstrategy.h>
#include <handcategorizerstrategy.h>
#include <handcategory.h>
#include <evaluator.h>
#include <evaluatecardsetwithhandstrategy.h>
#include <QXmlStreamWriter>
#include <cardsetbrowser.h>
#include <QFile>

Processor::Processor(QString a_filepath)
    : m_isProcessing(false)
    , m_filepath(a_filepath)
{

}

Processor::~Processor()
{

}

bool Processor::isProcessing()
{
    return m_isProcessing;
}

void Processor::run ()
{
    m_isProcessing = true;
    emit onProcessStart();

    QFile file(m_filepath);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter writer(& file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();

    HandCategorizerStrategy * handCategorizerStrategy = new HandCategorizerStrategy();
    CardSetBrowser <2> handBrowser(handCategorizerStrategy);
    handBrowser.browse();
    double browsedHandCount = handBrowser.getBrowsedHandCount();

    const HandCategorizerStrategy::HandCategories & handCategories = handCategorizerStrategy->getCategories();

    double processedHandCount = 0.;
    int categoryIndex = 0;
    for(const auto & categoryEntry : handCategories)
    {
        emit onCategoryStart(categoryIndex);

        writer.writeStartElement("Category");
        writer.writeAttribute("id", QString("%1").arg(categoryIndex));

        for(const auto & hand : categoryEntry)
        {
            emit onHandStart(hand.first, hand.second);
            writer.writeStartElement("Hand");
            writer.writeAttribute("card1", QString("%1").arg(hand.first));
            writer.writeAttribute("card2", QString("%1").arg(hand.second));

            EvaluateCardSetWithHandStrategy <3> * evaluateFlopWithHandStrategy = new EvaluateCardSetWithHandStrategy <3> (hand.first, hand.second);
            CardSetBrowser <3> flopBoardBrowser(evaluateFlopWithHandStrategy);
            flopBoardBrowser.addForbiddenCard(hand.first);
            flopBoardBrowser.addForbiddenCard(hand.second);
            flopBoardBrowser.browse();

            writer.writeStartElement("Flop");
            writer.writeTextElement("HighCard", QString("%1").arg(evaluateFlopWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::HIGH_CARD)));
            writer.writeTextElement("Pair", QString("%1").arg(evaluateFlopWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::PAIR)));
            writer.writeTextElement("DoublePair", QString("%1").arg(evaluateFlopWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::DOUBLE_PAIR)));
            writer.writeTextElement("ThreeOfAKind", QString("%1").arg(evaluateFlopWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::THREE_OF_A_KIND)));
            writer.writeTextElement("Straight", QString("%1").arg(evaluateFlopWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::STRAIGHT)));
            writer.writeTextElement("Flush", QString("%1").arg(evaluateFlopWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::FLUSH)));
            writer.writeTextElement("FullHouse", QString("%1").arg(evaluateFlopWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::FULL_HOUSE)));
            writer.writeTextElement("FourOfAKind", QString("%1").arg(evaluateFlopWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::FOUR_OF_A_KIND)));
            writer.writeTextElement("StraightFlush", QString("%1").arg(evaluateFlopWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::STRAIGHT_FLUSH)));
            writer.writeEndElement();

            delete evaluateFlopWithHandStrategy;

            EvaluateCardSetWithHandStrategy <4> * evaluateFlopTurnWithHandStrategy = new EvaluateCardSetWithHandStrategy <4> (hand.first, hand.second);
            CardSetBrowser <4> flopTurnBoardBrowser(evaluateFlopTurnWithHandStrategy);
            flopTurnBoardBrowser.addForbiddenCard(hand.first);
            flopTurnBoardBrowser.addForbiddenCard(hand.second);
            flopTurnBoardBrowser.browse();

            writer.writeStartElement("FlopTurn");
            writer.writeTextElement("HighCard", QString("%1").arg(evaluateFlopTurnWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::HIGH_CARD)));
            writer.writeTextElement("Pair", QString("%1").arg(evaluateFlopTurnWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::PAIR)));
            writer.writeTextElement("DoublePair", QString("%1").arg(evaluateFlopTurnWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::DOUBLE_PAIR)));
            writer.writeTextElement("ThreeOfAKind", QString("%1").arg(evaluateFlopTurnWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::THREE_OF_A_KIND)));
            writer.writeTextElement("Straight", QString("%1").arg(evaluateFlopTurnWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::STRAIGHT)));
            writer.writeTextElement("Flush", QString("%1").arg(evaluateFlopTurnWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::FLUSH)));
            writer.writeTextElement("FullHouse", QString("%1").arg(evaluateFlopTurnWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::FULL_HOUSE)));
            writer.writeTextElement("FourOfAKind", QString("%1").arg(evaluateFlopTurnWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::FOUR_OF_A_KIND)));
            writer.writeTextElement("StraightFlush", QString("%1").arg(evaluateFlopTurnWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::STRAIGHT_FLUSH)));
            writer.writeEndElement();

            delete evaluateFlopTurnWithHandStrategy;

            EvaluateCardSetWithHandStrategy <5> * evaluateFlopTurnRiverWithHandStrategy = new EvaluateCardSetWithHandStrategy <5> (hand.first, hand.second);
            CardSetBrowser <5> flopTurnRiverBoardBrowser(evaluateFlopTurnRiverWithHandStrategy);
            flopTurnRiverBoardBrowser.addForbiddenCard(hand.first);
            flopTurnRiverBoardBrowser.addForbiddenCard(hand.second);
            flopTurnRiverBoardBrowser.browse();

            writer.writeStartElement("FlopTurnRiver");
            writer.writeTextElement("HighCard", QString("%1").arg(evaluateFlopTurnRiverWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::HIGH_CARD)));
            writer.writeTextElement("Pair", QString("%1").arg(evaluateFlopTurnRiverWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::PAIR)));
            writer.writeTextElement("DoublePair", QString("%1").arg(evaluateFlopTurnRiverWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::DOUBLE_PAIR)));
            writer.writeTextElement("ThreeOfAKind", QString("%1").arg(evaluateFlopTurnRiverWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::THREE_OF_A_KIND)));
            writer.writeTextElement("Straight", QString("%1").arg(evaluateFlopTurnRiverWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::STRAIGHT)));
            writer.writeTextElement("Flush", QString("%1").arg(evaluateFlopTurnRiverWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::FLUSH)));
            writer.writeTextElement("FullHouse", QString("%1").arg(evaluateFlopTurnRiverWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::FULL_HOUSE)));
            writer.writeTextElement("FourOfAKind", QString("%1").arg(evaluateFlopTurnRiverWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::FOUR_OF_A_KIND)));
            writer.writeTextElement("StraightFlush", QString("%1").arg(evaluateFlopTurnRiverWithHandStrategy->getCombinaisonProbaInPercent(CombinaisonType::STRAIGHT_FLUSH)));
            writer.writeEndElement();

            delete evaluateFlopTurnRiverWithHandStrategy;

            processedHandCount += 1.;

            writer.writeEndElement();
            emit onHandEnd();

            double percentDone = Maths::roundf(processedHandCount / browsedHandCount * 100. * 10.) / 10.;
            emit onPercentageChange(percentDone);
        }

        ++ categoryIndex;

        writer.writeEndElement();
        emit onCategoryEnd();
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

    writer.writeEndDocument();
    m_isProcessing = false;
    emit onProcessDone();
}


