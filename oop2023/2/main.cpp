#include <iostream>
#include "Card/card.h"
#include "DeckStatick/deck.h"


int main(){
    std::cout << "Hello World!\n";
    Card::Card card;

    std::cout << card.get_rang() << ' ';
    std::cout << card.get_suits() << '\n';
    std::cout << card << '\n';

    Card::Card new_card{3, 2};

    std::cout << new_card.get_rang() << ' ';
    std::cout << new_card.get_suits() << '\n';
    std::cout << new_card;


    card.set_suits(Card::hearts);
    card.set_rang(3);

    if (card == new_card )
        std::cout << "Equal\n";
    else
        std::cout << "Different\n";

    if (card < new_card )
        std::cout << "True\n";
    else
        std::cout << "False\n";

    if (card > new_card )
        std::cout << "True\n";
    else
        std::cout << "False\n";

    if (card <= new_card )
        std::cout << "True\n";
    else
        std::cout << "False\n";

    if (card >= new_card )
        std::cout << "True\n";
    else
        std::cout << "False\n";

    /*
    Deck::Deck old_deck{23};
    Deck::Deck new_deck{23};

    old_deck.sort();
    new_deck.sort();

    //std::cout << old_deck;
    //std::cout << new_deck;

    //old_deck >> new_deck;

    //std::cout << old_deck;
    //std::cout << new_deck;
    //std::cout << old_deck + new_deck;
    //std::cout << new_deck.duplicate();

    //std::cout << new_deck;

    std::cout << "Separated\n";
    new_deck = old_deck.separate(1);

    //std::cout << new_deck;

    */
    return 0;
}