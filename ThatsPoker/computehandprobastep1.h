#ifndef COMPUTEHANDPROBASTEP1_H
#define COMPUTEHANDPROBASTEP1_H

#include <cardsetbrowserstrategy.h>

class ComputeHandProbaStep1 : public CardSetBrowserStrategy <2>
{
public:
    ComputeHandProbaStep1();
    ~ComputeHandProbaStep1();

public :

    void processCardSet(unsigned int a_cardSet [2]);
};

#endif // COMPUTEHANDPROBASTEP1_H
