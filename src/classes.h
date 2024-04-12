#ifndef CLASSES_H
#define CLASSES_H

#include "includes.h"

class Roulette {

    std::vector<int> last_drawn;

public:

    Roulette() {
        roulette_numbers.reserve(36);
        for (int i = 0; i < 37; i++)
            roulette_numbers.emplace_back(i);
        bet();
    }

    ~Roulette() = default;

    friend std::ostream &operator<<(std::ostream &out, const Roulette &r) {
        out << "Last drawn number: " << r.last_drawn.back() << std::endl;
        out << "Numbers before that: ";
        for (unsigned int i = r.last_drawn.size() - 1; i > 0; i--)
            out << r.last_drawn[i] << " ";
        return out;
    }

    class number {
        int value;
        std::string color;
        int dozen, parity, column;
    public:
        explicit number(int value) {
            this->value = value;
            if (value == 0)
                color = "Green";
            else if ((value >= 1 && value <= 10) || (value >= 19 && value <= 28))
                color = value % 2 == 0 ? "Black" : "Red";
            else if ((value >= 11 && value <= 18) || (value >= 29 && value <= 36))
                color = value % 2 == 0 ? "Red" : "Black";
            if (value != 0) {
                dozen = value / 12 + 1;
                parity = value % 2 == 0 ? 2 : 1;
                column = value % 3 == 0 ? 3 : value % 3;
            } else {
                dozen = 0;
                parity = 0;
                column = 0;
            }
        }

        friend std::ostream &operator<<(std::ostream &out, const number &n) {
            out << n.value << " Color: " << n.color;
            return out;
        }

        [[nodiscard]]  std::string getColor() const { return color; }
    };

    void bet() {
        while (true) {
            std::string color;
            int bet_size;
            system("CLS");
            std::cout << "\n\n\n\n\n\n\n\t\tYou bet on color: ";
            std::cin >> color;
            std::cout << "\n\n\t\tBet size: ";
            std::cin >> bet_size;
            //system("CLS");
            std::cout << "\n\n\n\n\n\n\n\t\tSpinning the wheel" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            //system("CLS");
            std::cout << "\n\n\n\n\n\n\n\t\tSpinning the wheel ." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            //system("CLS");
            std::cout << "\n\n\n\n\n\n\n\t\tSpinning the wheel .." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            //system("CLS");
            std::cout << "\n\n\n\n\n\n\n\t\tSpinning the wheel ..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            //system("CLS");
            number *drawn_number = &roulette_numbers[spin_wheel()];
            std::cout << "\n\n\n\n\n\n\n\t\tIt landed on: " << *drawn_number << std::endl;
            if (color == drawn_number->getColor()) {
                if (color == "Green")
                    std::cout << "You won: " << bet_size * 36 << std::endl;
                else
                    std::cout << "You won: " << bet_size * 2 << std::endl;
            } else
                std::cout << "You lost: " << bet_size << std::endl;
            std::cout << "Do you want to play again? (y/n): ";
            char c;
            std::cin >> c;
            if (c == 'n')
                break;
        }
    }

    int spin_wheel() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::uniform_int_distribution<int> ball(0, 36);
        int nr = ball(g);
        last_drawn.push_back(nr);
        return nr;
    }

private:
    std::vector<number> roulette_numbers;
};


class Deck {

    class Card {
        int value;
        std::string suit;
        static const std::map<int, std::string> FACE;
        static const std::map<std::tuple<int, std::string>, Texture> deck_sprites;
    public:
        static const std::vector<std::string> SUITES;

        Card(const int value, std::string suit) : value(value), suit(std::move(suit)) {}

        Card(const Card &c) = default;

        ~Card() = default;

        Card &operator=(const Card &c) = default;

        friend std::ostream &operator<<(std::ostream &os, const Card &c) {
            os << Card::FACE.at(c.value) << " of " << c.suit;
            return os;
        }
    };

    std::vector<Card> cards;

public:
    Deck(Deck &d) = default;

    explicit Deck(int nr_decks) {
        this->cards.reserve(nr_decks * 52);
        for (int i = 0; i < 4; i++)
            for (int j = 2; j < 15; j++)
                cards.emplace_back(j, Card::SUITES[i]);
        for (int i = 52; i < nr_decks * 52; i++)
            cards.emplace_back(cards[i % 52]);
    }

    friend std::ostream &operator<<(std::ostream &out, const Deck &d) {
        for (auto &c: d.cards)
            out << c << std::endl;
        return out;
    }

    void shuffle_cards() {
        std::random_device rd;
        std::mt19937 g(rd());
        shuffle(cards.begin(), cards.end(), g);
    }

    Card draw_card() {
        Card c = cards.back();
        cards.pop_back();
        return c;
    }

};

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
        {14, "King"}};

const std::vector<std::string> Deck::Card::SUITES = {"Hearts", "Diamonds", "Clubs", "Spades"};

const std::map<std::tuple<int, std::string>, Texture> deck_sprites={};


#endif //CLASSES_H
