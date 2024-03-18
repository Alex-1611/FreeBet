#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <random>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

class roulette{
    vector<int> last_drawn;
public:
    ~roulette() = default;
    roulette(){
        roulette_numbers.reserve(36);
        for (int i = 0; i < 37; i++)
            roulette_numbers.emplace_back(i);
        bet();
    }
    friend ostream& operator<<(ostream &out, const roulette &r) {
        out<<"Last drawn number: "<<r.last_drawn.back()<<endl;
        out<<"Numbers before that: ";
        for (int i = r.last_drawn.size()-1; i > 0; i--)
            out << r.last_drawn[i] << " ";
        return out;
    }
    class number{
        int value;
        string color;
        int dozen, parity, column;
    public:
        number(int value) {
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
            }
            else {
                dozen = 0;
                parity = 0;
                column = 0;
            }
        }
        friend ostream& operator<<(ostream &out, const number &n) {
            out << n.value << " Color: " << n.color;
            return out;
        }
        string getColor() const { return color; }
    };
    void bet(){
        while (true) {
            string color;
            int bet_size;
            system("CLS");
            cout << "\n\n\n\n\n\n\n\t\tYou bet on color: ";
            cin >> color;
            cout << "\n\n\t\tBet size: ";
            cin >> bet_size;
            //system("CLS");
            cout << "\n\n\n\n\n\n\n\t\tSpinning the wheel" << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
            //system("CLS");
            cout << "\n\n\n\n\n\n\n\t\tSpinning the wheel ." << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
            //system("CLS");
            cout << "\n\n\n\n\n\n\n\t\tSpinning the wheel .." << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
            //system("CLS");
            cout << "\n\n\n\n\n\n\n\t\tSpinning the wheel ..." << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
            //system("CLS");
            number* drawn_number = &roulette_numbers[spin_wheel()];
            cout << "\n\n\n\n\n\n\n\t\tIt landed on: " << *drawn_number << endl;
            if (color == drawn_number->getColor()) {
                if (color == "Green")
                    cout << "You won: " << bet_size * 36 << endl;
                else
                    cout << "You won: " << bet_size * 2 << endl;
            } else
                cout << "You lost: " << bet_size << endl;
            cout << "Do you want to play again? (y/n): ";
            char c;
            cin >> c;
            if (c == 'n')
                break;
        }
    }
    int spin_wheel(){
        random_device rd;
        mt19937 g(rd());
        uniform_int_distribution<int> ball(0, 36);
        int nr = ball(g);
        last_drawn.push_back(nr);
        return nr;
    }
private:
    vector<number> roulette_numbers;
};

class card{
    int value;
    string suit;
    map<int, string> face = {
            {2, "2"},
            {3, "3"},
            {4, "4"},
            {5, "5"},
            {6, "6"},
            {7, "7"},
            {8, "8"},
            {9, "9"},
            {10, "10"},
            {11, "Ace"},
            {12, "Jack"},
            {13, "Queen"},
            {14, "King"}};
public:
    card(int value, const string &suit) : value(value), suit(suit){}
    card() = default;
    card(const card &c) = default;
    ~card() = default;
    card& operator=(const card &c) = default;
    friend ostream& operator<<(ostream &os, const card &c) {
        os << c.face.at(c.value) << " of " << c.suit;
        return os;
    }
};
class deck{
    const vector<string> suites = {"Hearts", "Diamonds", "Clubs", "Spades"};
    vector<card> cards;
public:
    void shuffle_cards(){
        random_device rd;
        mt19937 g(rd());
        shuffle(cards.begin(), cards.end(), g);
    }
    card draw_card(){
        card c = cards.back();
        cards.pop_back();
        return c;
    }
    deck() = default;
    deck(deck &d) = default;
    deck(int nr_decks) {
        this->cards.reserve(nr_decks * 52);
        for (int i = 0; i < 4; i++)
            for (int j = 2; j < 15; j++)
                cards.emplace_back(j, suites[i]);
        for (int i = 52; i < nr_decks; i++)
            cards.insert(cards.end(), cards.begin(), cards.begin() + 52);
    }
    friend ostream& operator<<(ostream &out, const deck &d) {
        for (auto &c : d.cards)
            out << c << endl;
        return out;
    }
};

int main() {
    cout<<"1. Roulette\n2. Deck of cards\n";
    int choice;
    cin>>choice;
    switch (choice) {
        case 1: {
            roulette r;
            break;
        }
        case 2: {
            deck d(1);
            d.shuffle_cards();
            cout << d;
            break;
        }
        default:
            cout << "Invalid choice";
    }
    return 0;
}
