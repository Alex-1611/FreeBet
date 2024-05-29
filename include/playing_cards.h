#ifndef PLAYING_CARDS_H
#define PLAYING_CARDS_H

#include "includes.h"

enum class Suit {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

class Deck {
public:
    class Card {
        int value;
        Suit suit;
        static const std::map<int, std::string> FACE;
        //static const std::map<std::tuple<int, std::string>, Texture> deck_sprites;

    public:

        Card(int value, Suit suit);

        ~Card() = default;

        Card(const Card &c);

        Card &operator=(const Card &c);

        friend std::ostream &operator<<(std::ostream &os, const Card &c);

        [[nodiscard]] int get_value() const;
    };

private:

    std::vector<Card *> cards;

    Deck(Deck &d) = default;

public:
    Deck() = default;

    Deck &operator=(const Deck &other) = default;

    explicit Deck(int nr_decks);

    friend std::ostream &operator<<(std::ostream &out, const Deck &d);

    void shuffle_cards();

    Card *draw_card();

};

#endif //PLAYING_CARDS_H
