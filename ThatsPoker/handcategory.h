#ifndef HANDCATEGORY_H
#define HANDCATEGORY_H

class HandCategory
{
public :

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
    static const unsigned int COUNT;

private :
    HandCategory();
    ~HandCategory();
};

#endif // HANDCATEGORY_H
