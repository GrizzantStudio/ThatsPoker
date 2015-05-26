#ifndef FLOPTURNRIVERBOARDBROWSER_H
#define FLOPTURNRIVERBOARDBROWSER_H

#include <cardsetbrowser.h>

class FlopTurnRiverBoardBrowser : public CardSetBrowser <5>
{
public:
    FlopTurnRiverBoardBrowser(CardSetBrowserStrategy <5> * a_strategy);
    ~FlopTurnRiverBoardBrowser();
};

#endif // FLOPTURNRIVERBOARDBROWSER_H
