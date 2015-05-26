#ifndef HANDCAEGORIZERSTRATEGY_H
#define HANDCAEGORIZERSTRATEGY_H

#include <cardsetbrowserstrategy.h>
#include <QVector>
#include <QPair>

class HandCategorizerStrategy : public CardSetBrowserStrategy <2>
{
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
