#include "card_games.h"

enum class BaccaratBet {
    UNDECIDED,
    BANKER,
    PLAYER,
    TIE
};

std::ostream &operator<<(std::ostream &os, const BaccaratBet &b) {
    switch (b) {
        case BaccaratBet::UNDECIDED:
            os << "Undecided";
            break;
        case BaccaratBet::BANKER:
            os << "Banker";
            break;
        case BaccaratBet::PLAYER:
            os << "Player";
            break;
        case BaccaratBet::TIE:
            os << "Tie";
            break;
    }
    return os;
}

CardGame::CardGame() : balance(0), nr_decks(0) {}

void CardGame::update_balance() {
    int new_balance;
    while (true) {
        std::cout << "Enter new balance: ";
        std::cin >> new_balance;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer." << std::endl;
        } else if (new_balance <= 0)
            std::cout << "Balance must be greater than 0. Please enter a valid balance." << std::endl;
        else
            break;
    }
    this->balance = new_balance;
    std::cout<<this->get_balance()<<std::endl;
}

int CardGame::get_balance() const { return balance; }

Deck::Card *CardGame::draw_card() {
    return deck.draw_card();
}

Hand::Hand() : total(0) {}

void Hand::add_card(Deck::Card *card) {
    cards.push_back(card);
    int value = card->get_value();
    if (value == 11)
        total = (total + 1) % 10;
    else if (value == 10 || value == 12 || value == 13 || value == 14)
        total += 0;
    else
        total = (total + value) % 10;
}

int Hand::get_total() const { return total; }

std::ostream &operator<<(std::ostream &os, const Hand &h) {
    for (auto const& c: h.cards)
        os << *c << std::endl;
    os << "Total: " << h.total << std::endl;
    return os;
}

BankerHand::BankerHand() : Hand() {
    cards.reserve(3);
}

bool BankerHand::third_card_rule(int player_third_card_value) {
    if (total <= 2)
        return true;
    if (total == 3) {
        if (player_third_card_value != 8)
            return true;
    }
    if (total == 4) {
        if (player_third_card_value >= 2 && player_third_card_value <= 7)
            return true;
    }
    if (total == 5) {
        if (player_third_card_value >= 4 && player_third_card_value <= 7)
            return true;
    }
    if (total == 6) {
        if (player_third_card_value == 6 || player_third_card_value == 7)
            return true;
    }
    return false;
}

void BankerHand::add_card(Deck::Card *card) {
    cards.push_back(card);
    int value = card->get_value();
    if (value == 11)
        total = (total + 1) % 10;
    else if (value == 10 || value == 12 || value == 13 || value == 14)
        total += 0;
    else
        total = (total + value) % 10;
}

PlayerHand::PlayerHand() : Hand() {
    cards.reserve(3);
}

bool PlayerHand::third_card_rule() {
    return total <= 5;
}

void PlayerHand::add_card(Deck::Card *card) {
    cards.push_back(card);
    int value = card->get_value();
    if (value == 11)
        total = (total + 1) % 10;
    else if (value == 10 || value == 12 || value == 13 || value == 14)
        total += 0;
    else
        total = (total + value) % 10;
}

Baccarat::Baccarat() {
    std::cout << "Welcome to Baccarat!\n";
    while (true) {
        std::cout << "Enter balance: ";
        std::cin >> balance;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer." << std::endl;
        } else if (balance <= 0)
            std::cout << "Balance must be greater than 0. Please enter a valid balance." << std::endl;
        else
            break;
    }
    while (true) {
        std::cout << "Enter number of decks (1 - 10): ";
        std::cin >> nr_decks;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer." << std::endl;
        } else if (nr_decks <= 0 || nr_decks > 10)
            std::cout << "Number of decks must be between 1 and 10. Please enter a valid number of decks."
                      << std::endl;
        else
            break;
    }
    deck = Deck(nr_decks);
    deck.shuffle_cards();
    banker = nullptr;
    player = nullptr;
}

void Baccarat::bet() {
    int bet_size;
    BaccaratBet bet_type, winner;
    while (true) {
        std::cout << "Enter bet size: ";
        std::cin >> bet_size;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer." << std::endl;
        } else if (bet_size <= 0 || bet_size > balance)
            std::cout
                    << "Bet size must be greater than 0 and less than or equal to balance. Please enter a valid bet size."
                    << std::endl;
        else
            break;
    }
    while (true) {
        std::cout << "Enter bet type (1. Banker, 2. Player, 3. Tie): ";
        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer." << std::endl;
        } else if (choice < 1 || choice > 3)
            std::cout << "Invalid choice. Please enter a valid choice." << std::endl;
        else {
            switch (choice) {
                case 1:
                    bet_type = BaccaratBet::BANKER;
                    break;
                case 2:
                    bet_type = BaccaratBet::PLAYER;
                    break;
                case 3:
                    bet_type = BaccaratBet::TIE;
                    break;
                default:
                    bet_type = BaccaratBet::UNDECIDED;
                    break;
            }
            break;
        }
    }
    BaccaratRound round(*this);
    winner = round.get_winner();
    round.update_winner(winner);
    round.show_hands();
    std::cout << "Winner: " << winner << std::endl;
    if (winner == bet_type) {
        switch (bet_type) {
            case BaccaratBet::BANKER:
                std::cout << "You won " << (int) (bet_size * 0.95) << "!" << std::endl << "Balance: "
                          << balance + (int) (bet_size * 0.95) << std::endl;
                balance += (int) (bet_size * 0.95);
                break;
            case BaccaratBet::PLAYER:
                std::cout << "You won " << bet_size << "!" << std::endl << "Balance: " << balance + bet_size
                          << std::endl;
                balance += bet_size;
                break;
            case BaccaratBet::TIE:
                std::cout << "You won " << bet_size * 8 << "!" << std::endl << "Balance: " << balance + bet_size * 8
                          << std::endl;
                balance += bet_size * 8;
                break;
            default:
                break;
        }
    } else if (winner != BaccaratBet::TIE) {
        std::cout << "You lost " << bet_size << "!" << std::endl << "Balance: " << balance - bet_size << std::endl;
        balance -= bet_size;
    } else
        std::cout << "Banker and Player Tied. Balance Unchanged " << std::endl << "Balance: " << balance << std::endl;

}

void Baccarat::play() {
    int choice;
    bool should_continue = true;
    while (true) {
        while (true) {
            std::cout << "Menu:\n1. Play\n2. Exit\n3. Update balance\nChoice: ";
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter an integer.\n\n" << std::endl;
            } else if (choice < 1 || choice > 3)
                std::cout << "Invalid choice. Please enter a valid choice.\n\n";
            else
                break;
        }
        switch (choice) {
            case 1:
                bet();
                break;
            case 2:
                std::cout << "Exiting game..." << std::endl;
                should_continue = false;
                break;
            case 3:
                update_balance();
                break;
            default:
                break;
        }
        if (!should_continue)
            break;
    }

}

Round::Round() : winner(BaccaratBet::UNDECIDED), player(nullptr), dealer(nullptr) {}

void Round::update_winner(BaccaratBet w) {
    this->winner = w;
}

void BaccaratRound::show_hands() const {
    std::cout << "Player hand:\n" << *player << std::endl;
    std::cout << "Dealer hand:\n" << *dealer << std::endl;
}

BaccaratBet BaccaratRound::get_winner() const {
    if (player->get_total() == dealer->get_total())
        return BaccaratBet::TIE;
    else if (player->get_total() > dealer->get_total())
        return BaccaratBet::PLAYER;
    else
        return BaccaratBet::BANKER;
}

BaccaratRound::BaccaratRound(Baccarat &game) {
    player = new PlayerHand();
    dealer = new BankerHand();
    auto *dealerHand = dynamic_cast<BankerHand *>(dealer);
    auto *playerHand = dynamic_cast<PlayerHand *>(player);
    player->add_card(game.draw_card());
    dealer->add_card(game.draw_card());
    player->add_card(game.draw_card());
    dealer->add_card(game.draw_card());
    if (!(player->get_total() == 8 || player->get_total() == 9 || dealer->get_total() == 8 ||
          dealer->get_total() == 9)) {
        if (playerHand->third_card_rule()) {
            Deck::Card *player_third_card = game.draw_card();
            player->add_card(player_third_card);
            if (dealerHand->third_card_rule(player_third_card->get_value()))
                dealerHand->add_card(game.draw_card());
        } else if (dealerHand->third_card_rule())
            dealerHand->add_card(game.draw_card());
    }
}


