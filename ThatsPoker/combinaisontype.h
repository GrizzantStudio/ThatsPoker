#ifndef COMBINAISONTYPE_H
#define COMBINAISONTYPE_H


class CombinaisonType
{
public :

    static const unsigned int STRAIGHT_FLUSH;
    static const unsigned int FOUR_OF_A_KIND;
    static const unsigned int FULL_HOUSE;
    static const unsigned int FLUSH;
    static const unsigned int STRAIGHT;
    static const unsigned int THREE_OF_A_KIND;
    static const unsigned int DOUBLE_PAIR;
    static const unsigned int PAIR;
    static const unsigned int HIGH_CARD;

private :
    CombinaisonType() {}
    ~CombinaisonType() {}
};

#endif // COMBINAISONTYPE_H
