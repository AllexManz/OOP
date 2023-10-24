#ifndef DECK_STATIC_H
#define DECK_STATIC_H
#include "../Card/card.h"


namespace Deck{

    class Deck{
    private:
        int card_n;
        static const int card_max = 64;
        Card::Card cards[card_max];

        Card::Card& pop(int n = -1);
        Deck& push_back(Card::Card card);
    public:
        // Constructors
        explicit Deck ();
        explicit Deck (int n, int seed);

        // Getters
        [[nodiscard]] int get_card_n() const { return card_n; }
        [[nodiscard]] const Card::Card* get_cards() const { return cards; }
        [[nodiscard]] const Card::Card& get_card(int n) const { return cards[n]; }

        // Overloading
        Card::Card& operator[](int index);
        friend Deck& operator>>(Deck& l, Deck& r);
        friend std::ostream& operator<<(std::ostream &s, const Deck &deck);
        friend Deck& operator+(const Deck& l, const Deck& r);


        void resize(int new_size);
        void sort(int flag = 1);
        bool duplicate();
        Deck& separate(int suit);

        // Destructor
        ~Deck();
    };

}

#endif //DECK_STATIC_H
