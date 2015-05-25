#ifndef HANDCAEGORIZERSTRATEGY_H
#define HANDCAEGORIZERSTRATEGY_H

#include <cardsetbrowserstrategy.h>
#include <QVector>
#include <QPair>

class HandCategorizerStrategy : public CardSetBrowserStrategy <2>
{
private :

    static const unsigned int PAIR;
    static const unsigned int SORTED_CONNECTORS;
    static const unsigned int SORTED_1_GAPPERS;
    static const unsigned int SORTED_2_GAPPERS;
    static const unsigned int SORTED_3_GAPPERS;
    static const unsigned int SORTED_MISC;
    static const unsigned int UNSORTED_CONNECTORS;
    static const unsigned int UNSORTED_1_GAPPERS;
    static const unsigned int UNSORTED_2_GAPPERS;
    static const unsigned int UNSORTED_3_GAPPERS;
    static const unsigned int UNSORTED_MISC;

public :

    typedef QPair <unsigned int, unsigned int> Hand;
    typedef QVector <Hand> HandList;
    typedef QVector <HandList> HandCategories;

private :

     HandCategories m_handCategories;

public:
    HandCategorizerStrategy();
    ~HandCategorizerStrategy();

public :

    const HandCategories & getCategories();

public :

    void processCardSet(unsigned int a_cardSet [2]);

};

#endif // HANDCAEGORIZERSTRATEGY_H
