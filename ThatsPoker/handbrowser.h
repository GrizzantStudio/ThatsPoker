#ifndef HANDBROWSER_H
#define HANDBROWSER_H

#include <cardsetbrowser.h>
#include <cardsetbrowserstrategy.h>

class HandBrowser : public CardSetBrowser <2>
{
public:
    HandBrowser(CardSetBrowserStrategy <2> * a_strategy);
    ~HandBrowser();
};

#endif // HANDBROWSER_H
