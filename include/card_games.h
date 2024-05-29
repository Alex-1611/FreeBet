#ifndef CARD_GAMES_H
#define CARD_GAMES_H

#include "includes.h"
#include "playing_cards.h"

enum class BaccaratBet;

class CardGame {
protected:
    int balance, nr_decks;
    Deck deck;
public:
    CardGame();

    virtual ~CardGame() = default;

    void update_balance();

    virtual void bet() = 0;
    [[nodiscard]] int get_balance() const;
    Deck::Card *draw_card();
};

class Hand {
protected:
    std::vector<Deck::Card *> cards;
    int total;
public:
    Hand();

    virtual ~Hand() = default;

    virtual void add_card(Deck::Card *card) = 0;

    [[nodiscard]] int get_total() const;

    friend std::ostream &operator<<(std::ostream &os, const Hand &h);

};

class BankerHand : public Hand {
public:
    BankerHand();

    bool third_card_rule(int player_third_card_value = 7);

    void add_card(Deck::Card *card) override;
};

class PlayerHand : public Hand {

public:
    PlayerHand();

    bool third_card_rule();

    void add_card(Deck::Card *card) override;
};

class Baccarat : public CardGame {
    Hand *banker;
    Hand *player;
public:
    Baccarat();

    void bet() override;

    void play();
};

class Round {
    BaccaratBet winner;
protected:
    Hand *player, *dealer;
public:
    Round();

    virtual ~Round() = default;

    void update_winner(BaccaratBet winner);

    [[nodiscard]] virtual BaccaratBet get_winner() const = 0;

    virtual void show_hands() const = 0;
};

class BaccaratRound : public Round {
public:
    explicit BaccaratRound(Baccarat &game);

    [[nodiscard]] BaccaratBet get_winner() const override;

    void show_hands() const override;
};

#endif //CARD_GAMES_H
