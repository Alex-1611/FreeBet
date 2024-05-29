#include "roulette.h"

std::ostream &operator<<(std::ostream &out, const NumberColor &c) {
    switch (c) {
        case NumberColor::red:
            out << "Red";
            break;
        case NumberColor::black:
            out << "Black";
            break;
        case NumberColor::green:
            out << "Green";
            break;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const NumberParity &p) {
    switch (p) {
        case NumberParity::even:
            out << "Even";
            break;
        case NumberParity::odd:
            out << "Odd";
            break;
        case NumberParity::zero:
            out << "Zero (no parity)";
            break;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const Roulette &r) {
    out << "Last drawn number: " << *r.last_drawn.back() << std::endl;
    out << "Numbers before that: ";
    for (unsigned int i = r.last_drawn.size() - 1; i > 0; i--)
        out << *r.last_drawn[i] << " ";
    return out;
}

Roulette::Roulette() {
    std::string balance_choice;
    roulette_numbers.reserve(36);
    last_drawn.reserve(25);
    for (int i = 0; i < 37; i++)
        roulette_numbers.emplace_back(i);
    while (true) {
        std::cout << "Enter your balance (positive integer) : ";
        std::cin >> balance_choice;
        try {
            balance = std::stoi(balance_choice);
            if (balance < 0)
                throw std::invalid_argument("Invalid number choice.");
            break;
        } catch (std::invalid_argument &) {
            std::cout << "Invalid number choice. Please try again." << std::endl;
        }
    }
}

int Roulette::add_balance(int amount) {
    balance += amount;
    return balance;
}

void Roulette::play() {
    std::unique_ptr<RouletteRound> r = nullptr;
    bool should_continue = true;
    int menu_choice, bet_choice, amount;
    std::string aux;
    while (true) {
        std::cout << "Menu: " << std::endl;
        std::cout << "1. Bet" << std::endl;
        std::cout << "2. Update balance" << std::endl;
        std::cout << "3. Show previous numbers" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> menu_choice;
        switch (menu_choice) {
            case 1:
                r = std::make_unique<RouletteRound>(this);
                enter_amount:
                std::cout << "Enter amount: ";
                std::cin >> amount;
                //check if amount is int
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Invalid amount. Please try again." << std::endl;
                    goto enter_amount;
                }
                choose_bet:
                std::cout << "Choose bet type: " << std::endl;
                std::cout << "1. Color" << std::endl;
                std::cout << "2. Parity" << std::endl;
                std::cout << "3. Dozen" << std::endl;
                std::cout << "4. Column" << std::endl;
                std::cout << "5. Number" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> bet_choice;
                try {
                    std::unique_ptr<Bet> b = BetFactory::create_bet(amount, bet_choice);
                    r->add_bet(std::move(b));
                } catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                    goto choose_bet;
                }
                add_bet:
                std::cout<<"Add another bet? (y/n): ";
                std::cin >> aux;
                if (aux == "y")
                    goto enter_amount;
                else if (aux != "n") {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    goto add_bet;
                }
                else {
                    int win=r->start_round();
                    if(win>0)
                        std::cout << "You won " << win << "!" << std::endl;
                    else
                        std::cout << "You lost " << -win << "!" << std::endl;
                }
                break;
            case 2:
                std::cout << "Enter new balance: ";
                std::cin >> balance;
                break;
            case 3:
                std::cout << *this << std::endl;
                break;
            case 4:
                should_continue = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                continue;
        }
        if (!should_continue) {
            break;
        }
    }
}

Roulette::Number::Number(int value) {
    this->value = value;
    if (value == 0)
        color = NumberColor::green;
    else if ((value >= 1 && value <= 10) || (value >= 19 && value <= 28))
        color = value % 2 == 0 ? NumberColor::black : NumberColor::red;
    else if ((value >= 11 && value <= 18) || (value >= 29 && value <= 36))
        color = value % 2 == 0 ? NumberColor::red : NumberColor::black;
    if (value != 0) {
        dozen = value / 12 + 1;
        parity = value % 2 == 0 ? NumberParity::even : NumberParity::odd;
        column = value % 3 == 0 ? 3 : value % 3;
    } else {
        dozen = 0;
        parity = NumberParity::zero;
        column = 0;
    }
}

NumberColor Roulette::Number::get_color() const {
    return color;
}

NumberParity Roulette::Number::get_parity() const {
    return parity;
}

int Roulette::Number::get_dozen() const {
    return dozen;
}

int Roulette::Number::get_column() const {
    return column;
}

int Roulette::Number::get_value() const {
    return value;
}

std::ostream &operator<<(std::ostream &out, const Roulette::Number &n) {
    out << n.value << " Color: " << n.color;
    return out;
}

Roulette::Number *Roulette::spin_wheel() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> ball(0, 36);
    int nr = ball(g);
    last_drawn.push_back(&roulette_numbers[nr]);
    return &roulette_numbers[nr];
}

Roulette::Bet::Bet(int amount) : amount(amount) {}

int Roulette::Bet::notify_win(const Number &nr) const {
    if (check_win(nr)) {
        return get_win();
    } else {
        return -amount;
    }
}

// CLASS ColorBet

ColorBet::ColorBet(int amount) : Bet(amount) {
    std::string color_choice;
    while (true) {
        std::cout << "Choose color (red, black, green): ";
        std::cin >> color_choice;
        if (color_choice == "red") {
            color = NumberColor::red;
            break;
        } else if (color_choice == "black") {
            color = NumberColor::black;
            break;
        } else if (color_choice == "green") {
            color = NumberColor::green;
            break;
        } else {
            std::cout << "Invalid color choice. Please try again." << std::endl;
        }
    }
}

int ColorBet::get_win() const {
    return amount * win_multiplier;
}

bool ColorBet::check_win(const Roulette::Number &nr) const {
    return nr.get_color() == color;
}

// CLASS ParityBet

ParityBet::ParityBet(int amount) : Bet(amount) {
    std::string parity_choice;
    while (true) {
        std::cout << "Choose parity (even, odd): ";
        std::cin >> parity_choice;
        if (parity_choice == "even") {
            parity = NumberParity::even;
            break;
        } else if (parity_choice == "odd") {
            parity = NumberParity::odd;
            break;
        } else {
            std::cout << "Invalid parity choice. Please try again." << std::endl;
        }
    }
}

int ParityBet::get_win() const {
    return amount * win_multiplier;
}

bool ParityBet::check_win(const Roulette::Number &nr) const {
    return nr.get_parity() == parity;
}

//CLASS DozenBet

DozenBet::DozenBet(int amount) : Bet(amount) {
    std::string dozen_choice;
    while (true) {
        std::cout << "Choose dozen (1, 2, 3): ";
        std::cin >> dozen_choice;
        if (dozen_choice == "1") {
            dozen = 1;
            break;
        } else if (dozen_choice == "2") {
            dozen = 2;
            break;
        } else if (dozen_choice == "3") {
            dozen = 3;
            break;
        } else {
            std::cout << "Invalid dozen choice. Please try again." << std::endl;
        }
    }
}

int DozenBet::get_win() const {
    return amount * win_multiplier;
}

bool DozenBet::check_win(const Roulette::Number &nr) const {
    return nr.get_dozen() == dozen;
}

//CLASS ColumnBet

ColumnBet::ColumnBet(int amount) : Bet(amount) {
    std::string column_choice;
    while (true) {
        std::cout << "Choose column (1, 2, 3): ";
        std::cin >> column_choice;
        if (column_choice == "1") {
            column = 1;
            break;
        } else if (column_choice == "2") {
            column = 2;
            break;
        } else if (column_choice == "3") {
            column = 3;
            break;
        } else {
            std::cout << "Invalid column choice. Please try again." << std::endl;
        }
    }
}

int ColumnBet::get_win() const {
    return amount * win_multiplier;
}

bool ColumnBet::check_win(const Roulette::Number &nr) const {
    return nr.get_column() == column;
}

//CLASS NumberBet

NumberBet::NumberBet(int amount) : Bet(amount) {
    std::string number_choice;
    while (true) {
        std::cout << "Choose number (0-36): ";
        std::cin >> number_choice;
        try {
            number = std::stoi(number_choice);
            if (number < 0 || number > 36)
                throw std::invalid_argument("Invalid number choice.");
            break;
        } catch (std::invalid_argument &) {
            std::cout << "Invalid number choice. Please try again." << std::endl;
        }
    }
}

int NumberBet::get_win() const {
    return amount * win_multiplier;
}

bool NumberBet::check_win(const Roulette::Number &nr) const {
    return nr.get_value() == number;
}

std::unique_ptr<Roulette::Bet> BetFactory::create_bet(int amount, int choice) {
    switch (choice) {
        case 1:
            return std::make_unique<ColorBet>(amount);
        case 2:
            return std::make_unique<ParityBet>(amount);
        case 3:
            return std::make_unique<DozenBet>(amount);
        case 4:
            return std::make_unique<ColumnBet>(amount);
        case 5:
            return std::make_unique<NumberBet>(amount);
        default:
            throw std::invalid_argument("Invalid choice for bet type. Please try again.\n");
    }
}

RouletteRound::RouletteRound(Roulette* r){
    total_win = 0;
    this->r = r;
    winning_number = nullptr;
}

void RouletteRound::add_bet(std::unique_ptr<Roulette::Bet> bet) {
    bets.push_back(std::move(bet));
}

void RouletteRound::notify() {
    for (auto &b: bets) {
        total_win += b->notify_win(*winning_number);
    }
    r->add_balance(total_win);
}

int RouletteRound::start_round() {
    winning_number = r->spin_wheel();
    notify();
    return total_win;
}

//win multipliers
int ColorBet::win_multiplier = 2;
int ParityBet::win_multiplier = 2;
int DozenBet::win_multiplier = 3;
int ColumnBet::win_multiplier = 3;
int NumberBet::win_multiplier = 35;
