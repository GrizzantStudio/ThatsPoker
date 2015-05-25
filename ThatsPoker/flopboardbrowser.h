#ifndef FLOPBOARDBROWSER_H
#define FLOPBOARDBROWSER_H

#include <cardsetbrowser.h>

class FlopBoardBrowser : public CardSetBrowser <3>
{
public:
    FlopBoardBrowser(CardSetBrowserStrategy <3> * a_strategy);
    ~FlopBoardBrowser();
};

#endif // FLOPBOARDBROWSER_H
