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
        } catch (std::invalid_argument &e) {
            std::cout << "Invalid number choice. Please try again." << std::endl;
        }
    }
}

void Roulette::play() {
    bool should_continue = true;
    int menu_choice, bet_choice, amount;
    std::string aux;
    Number *nr;
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
                std::cout << "Your balance: " << balance << std::endl;
                std::cout << "Choose bet type: " << std::endl;
                std::cout << "1. Color" << std::endl;
                std::cout << "2. Parity" << std::endl;
                std::cout << "3. Dozen" << std::endl;
                std::cout << "4. Column" << std::endl;
                std::cout << "5. Number" << std::endl;
                std::cin >> bet_choice;
                switch (bet_choice) {
                    case 1: {
                        while (true) {
                            std::cout << "Choose bet amount: ";
                            std::cin >> aux;
                            try {
                                amount = std::stoi(aux);
                                if (amount < 0 || amount > balance)
                                    throw std::invalid_argument("Invalid number choice.");
                                break;
                            } catch (std::invalid_argument &e) {
                                std::cout << "Invalid number choice. Please try again." << std::endl;
                            }
                        }
                        ColorBet bet(amount);
                        balance -= bet.get_amount();
                        nr = spin_wheel();
                        std::cout << "It landed on: " << nr->get_value() << std::endl;
                        if (bet.check_win(*nr)) {
                            balance += bet.get_win();
                            std::cout << "You won! Your balance is now: " << balance << std::endl;
                        } else {
                            std::cout << "You lost! Your balance is now: " << balance << std::endl;
                        }
                        break;
                    }
                    case 2: {
                        while (true) {
                            std::cout << "Choose bet amount: ";
                            std::cin >> aux;
                            try {
                                amount = std::stoi(aux);
                                if (amount < 0 || amount > balance)
                                    throw std::invalid_argument("Invalid number choice.");
                                break;
                            } catch (std::invalid_argument &e) {
                                std::cout << "Invalid number choice. Please try again." << std::endl;
                            }
                        }
                        ParityBet bet(amount);
                        balance -= bet.get_amount();
                        nr = spin_wheel();
                        std::cout << "It landed on: " << nr->get_value() << std::endl;
                        if (bet.check_win(*nr)) {
                            balance += bet.get_win();
                            std::cout << "You won! Your balance is now: " << balance << std::endl;
                        } else {
                            std::cout << "You lost! Your balance is now: " << balance << std::endl;
                        }
                        break;
                    }
                    case 3: {
                        while (true) {
                            std::cout << "Choose bet amount: ";
                            std::cin >> aux;
                            try {
                                amount = std::stoi(aux);
                                if (amount < 0 || amount > balance)
                                    throw std::invalid_argument("Invalid number choice.");
                                break;
                            } catch (std::invalid_argument &e) {
                                std::cout << "Invalid number choice. Please try again." << std::endl;
                            }
                        }
                        DozenBet bet(amount);
                        balance -= bet.get_amount();
                        nr = spin_wheel();
                        std::cout << "It landed on: " << nr->get_value() << std::endl;
                        if (bet.check_win(*nr)) {
                            balance += bet.get_win();
                            std::cout << "You won! Your balance is now: " << balance << std::endl;
                        } else {
                            std::cout << "You lost! Your balance is now: " << balance << std::endl;
                        }
                        break;
                    }
                    case 4: {
                        while (true) {
                            std::cout << "Choose bet amount: ";
                            std::cin >> aux;
                            try {
                                amount = std::stoi(aux);
                                if (amount < 0 || amount > balance)
                                    throw std::invalid_argument("Invalid number choice.");
                                break;
                            } catch (std::invalid_argument &e) {
                                std::cout << "Invalid number choice. Please try again." << std::endl;
                            }
                        }
                        ColumnBet bet(amount);
                        balance -= bet.get_amount();
                        nr = spin_wheel();
                        std::cout << "It landed on: " << nr->get_value() << std::endl;
                        if (bet.check_win(*nr)) {
                            balance += bet.get_win();
                            std::cout << "You won! Your balance is now: " << balance << std::endl;
                        } else {
                            std::cout << "You lost! Your balance is now: " << balance << std::endl;
                        }
                        break;
                    }
                    case 5: {
                        while (true) {
                            std::cout << "Choose bet amount: ";
                            std::cin >> aux;
                            try {
                                amount = std::stoi(aux);
                                if (amount < 0 || amount > balance)
                                    throw std::invalid_argument("Invalid number choice.");
                                break;
                            } catch (std::invalid_argument &e) {
                                std::cout << "Invalid number choice. Please try again." << std::endl;
                            }
                        }
                        NumberBet bet(amount);
                        balance -= bet.get_amount();
                        nr = spin_wheel();
                        std::cout << "It landed on: " << nr->get_value() << std::endl;
                        if (bet.check_win(*nr)) {
                            balance += bet.get_win();
                            std::cout << "You won! Your balance is now: " << balance << std::endl;
                        } else {
                            std::cout << "You lost! Your balance is now: " << balance << std::endl;
                        }
                        break;
                    }
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                        continue;
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

int Roulette::Bet::get_amount() const {
    return amount;
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
    std::cout << "Color: " << nr.get_color() << std::endl;
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
    std::cout << "Parity: " << nr.get_parity() << std::endl;
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
    std::cout << "Dozen: " << nr.get_dozen() << std::endl;
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
    std::cout << "Column: " << nr.get_column() << std::endl;
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
        } catch (std::invalid_argument &e) {
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

//win multipliers
int ColorBet::win_multiplier = 2;
int ParityBet::win_multiplier = 2;
int DozenBet::win_multiplier = 3;
int ColumnBet::win_multiplier = 3;
int NumberBet::win_multiplier = 35;
