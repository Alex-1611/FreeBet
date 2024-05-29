#include "../include/playing_cards.h"

std::ostream &operator<<(std::ostream &out, const Suit &s) {
    switch (s) {
        case Suit::HEARTS:
            out << "Hearts";
            break;
        case Suit::DIAMONDS:
            out << "Diamonds";
            break;
        case Suit::CLUBS:
            out << "Clubs";
            break;
        case Suit::SPADES:
            out << "Spades";
            break;
    }
    return out;
}

Deck::Card::Card(int value, Suit suit) : value(value), suit(suit) {}

Deck::Card::Card(const Card &c) {
    value = c.value;
    suit = c.suit;
}

Deck::Card &Deck::Card::operator=(const Card &c) {
    if (this == &c)
        return *this;
    value = c.value;
    suit = c.suit;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Deck::Card &c) {
    os << Deck::Card::FACE.at(c.value) << " of " << c.suit;
    return os;
}

int Deck::Card::get_value() const { return value; }

Deck::Deck(int nr_decks) {
    this->cards.reserve(nr_decks * 52);
    for (int i = 0; i < 4; i++)
        for (int j = 2; j < 15; j++)
            cards.push_back(new Card(j, static_cast<Suit>(i)));
    for (int i = 52; i < nr_decks * 52; i++)
        cards.emplace_back(cards[i % 52]);
}

std::ostream &operator<<(std::ostream &out, const Deck &d) {
    for (auto &c: d.cards)
        out << c << std::endl;
    return out;
}

void Deck::shuffle_cards() {
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(cards.begin(), cards.end(), g);
}

Deck::Card *Deck::draw_card() {
    Deck::Card *c = cards.back();
    Deck::cards.pop_back();
    return c;
}

const std::map<int, std::string> Deck::Card::FACE = {
        {2,  "2"},
        {3,  "3"},
        {4,  "4"},
        {5,  "5"},
        {6,  "6"},
        {7,  "7"},
        {8,  "8"},
        {9,  "9"},
        {10, "10"},
        {11, "Ace"},
        {12, "Jack"},
        {13, "Queen"},
        {14, "King"}
};