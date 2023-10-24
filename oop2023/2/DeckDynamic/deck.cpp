#include "deck.h"
#include <ctime>
#include <algorithm>


namespace Deck{
    Deck::Deck() {
        cards = new Card::Card[52];
        card_n = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++){
                cards[card_n].set_suits(i);
                cards[card_n].set_rang(j);
                card_n ++;
            }
        }
    }

    Deck::Deck(int n) {
        if (n < 0 || n > 52){
            throw std::invalid_argument("Number of cards should lesser than 53"
                                        "and be positive number");
        }

        srand((unsigned) time(nullptr));

        cards = new Card::Card[n];
        card_n = 0;
        Card::Card temp_card;

        for (int i = 0; i < n; i++){

            while (true){
                int flag = 0;

                temp_card.set_suits(rand() % 4);
                temp_card.set_rang(rand() % 13);

                for (int j = 0; j < card_n; j++){
                    if (cards[j].get_rang() == temp_card.get_rang() &&
                        cards[j].get_suits() == temp_card.get_suits()) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                    break;
            }


            cards[card_n].set_suits(temp_card.get_suits());
            cards[card_n].set_rang(temp_card.get_rang());
            card_n ++;
        }
    }


    std::ostream &operator<<(std::ostream &s, const Deck &deck) {
        if (deck.get_card_n() == 0){
            s << "Deck is Empty\n";
            return s;
        }

        s << "\n\nDECK:\n";
        for (int i = 0; i < deck.get_card_n(); i++){
            s << deck.get_card(i);
        }
        s << '\n';
        return s;
    }

    Card::Card &Deck::pop(int n) {
        if (get_card_n() == 0)
            throw std::out_of_range("The deck is empty");

        if (n == -1)
            n = this->get_card_n() - 1;

        if (n < 0 || n >= this->get_card_n())
            throw std::invalid_argument("The element does not exist");

        auto card = new Card::Card;
        card->set_rang(this->cards[n].get_rang());
        card->set_suits(this->cards[n].get_suits());

        this->resize(this->card_n - 1);

        return (*card);
    }

    void Deck::resize(int new_size) {
        int old_size = this->card_n;
        this->card_n = new_size;
        try {
            Card::Card* tmp = this->cards;
            this->cards = new Card::Card[new_size];
            if (new_size >= old_size)
                std::copy(tmp, tmp + old_size, this->cards);
            else
                std::copy(tmp, tmp + new_size, this->cards);
            delete[] tmp;
        }
        catch(...) {
            this->card_n = old_size;
            throw;
        }
    }

    Card::Card &Deck::operator[](int index) {
        return this->cards[index];
    }

    Deck &operator+(const Deck &l, const Deck &r) {
        Deck* deck = new Deck{l.card_n + r.card_n};

        int cnt = 0;
        for (int i = 0; i < l.card_n; i++){
            deck->cards[cnt].set_rang(l.cards[i].get_rang());
            deck->cards[cnt].set_suits(l.cards[i].get_suits());
        }

        for (int i = 0; i < r.card_n; i++){
            deck->cards[cnt].set_rang(r.cards[i].get_rang());
            deck->cards[cnt].set_suits(r.cards[i].get_suits());
        }

        return (*deck);
    }

    Deck &operator>>(Deck &l, Deck &r) {
        try {
            r.resize(r.card_n + 1);
            r.cards[r.card_n - 1] = l.cards[l.card_n - 1];
            l.resize(l.card_n - 1);
        }
        catch (...) {
            throw;
        }
        return l;
    }

    Deck &Deck::push_back(Card::Card card) {
        try {
            this->resize(this->card_n + 1);
            this->cards[this->card_n - 1] = card;
        }
        catch (...) {
            throw;
        }
        return *this;
    }

    void Deck::sort(int flag) {
        if (flag == -1){
            std::sort(this->get_cards(), this->get_cards() + this->get_card_n(),
                      [](Card::Card l, Card::Card r){
                          if (l.get_suits() < r.get_suits())
                              return 0;
                          if (l.get_suits() > r.get_suits())
                              return 1;

                          return l > r;}
            );
            return;
        }
        if (flag == 1){
            std::sort(this->get_cards(), this->get_cards() + this->get_card_n(),
                      [](Card::Card l, Card::Card r){
                          if (l.get_suits() < r.get_suits())
                              return 1;
                          if (l.get_suits() > r.get_suits())
                              return 0;

                          return l < r;}
            );
            return;
        }
        throw std::invalid_argument("Wrong value of flag");
    }

    bool Deck::duplicate() {
        Deck* deck = new Deck{this->card_n};

        for (int i = 0; i < this->card_n; i++){
            deck->cards[i].set_suits(this->cards[i].get_suits());
            deck->cards[i].set_rang(this->cards[i].get_rang());
        }

        deck->sort();
        for (int i = 1; i < deck->card_n; i++){
            if (deck->cards[i].get_rang() == deck->cards[i - 1].get_rang() &&
                deck->cards[i].get_suits() == deck->cards[i - 1].get_suits()){
                delete deck;
                return true;
            }
        }

        delete deck;
        return false;
    }

    Deck &Deck::separate(int suit) {
        if (suit < 0 || suit > 3)
            throw std::invalid_argument("Suit value should be positive and less than 4");

        Deck* deck = new Deck;

        for (int i = 0; i < this->card_n; i++){
            if (this->cards[i].get_suits() == suit){
                deck->push_back(Card::Card{this->cards[i].get_rang(), this->cards[i].get_suits()});
                std::cout << deck->cards[deck->card_n - 1];
            }
        }


        return (*deck);
    }

    Deck::~Deck() {
        delete[] cards;
    }

    const Card::Card *Deck::getCards() const {
        return cards;
    }
}