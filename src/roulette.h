#ifndef ROULETTE_H
#define ROULETTE_H

#include "includes.h"

enum class NumberColor {
    red,
    black,
    green
};

enum class NumberParity {
    even,
    odd,
    zero
};

class Roulette {
    int balance;
public:

    Roulette();

    ~Roulette() = default;

    friend std::ostream &operator<<(std::ostream &out, const Roulette &r);

    void play();

    class Number {

        int value;
        NumberColor color;
        NumberParity parity;
        int dozen, column;
    public:
        explicit Number(int value);

        friend std::ostream &operator<<(std::ostream &out, const Number &n);

        [[nodiscard]] int get_value() const;

        [[nodiscard]] NumberColor get_color() const;

        [[nodiscard]] NumberParity get_parity() const;

        [[nodiscard]] int get_dozen() const;

        [[nodiscard]] int get_column() const;

    };

    class Bet {
    protected:
        int amount;

    public:
        explicit Bet(int amount);

        [[nodiscard]] int get_amount() const;

        virtual ~Bet() = default;

        [[nodiscard]] virtual bool check_win(const Number &nr) const = 0;

        [[nodiscard]] virtual int get_win() const = 0;
    };

private:
    std::vector<Number> roulette_numbers;
    std::vector<Number *> last_drawn;

    Number* spin_wheel();

};

class ColorBet : public Roulette::Bet {
    NumberColor color;
    static int win_multiplier;
public:
    ColorBet(int amount);

    [[nodiscard]] int get_win() const override;

    [[nodiscard]] bool check_win(const Roulette::Number &nr) const override;
};

class ParityBet : public Roulette::Bet {
    NumberParity parity;
    static int win_multiplier;
public:
    ParityBet(int amount);

    [[nodiscard]] int get_win() const override;

    [[nodiscard]] bool check_win(const Roulette::Number &nr) const override;
};

class DozenBet : public Roulette::Bet {
    int dozen;
    static int win_multiplier;
public:
    DozenBet(int amount);

    [[nodiscard]] int get_win() const override;

    [[nodiscard]] bool check_win(const Roulette::Number &nr) const override;
};

class ColumnBet : public Roulette::Bet {
    int column;
    static int win_multiplier;
public:
    ColumnBet(int amount);

    [[nodiscard]] int get_win() const override;

    [[nodiscard]] bool check_win(const Roulette::Number &nr) const override;
};

class NumberBet : public Roulette::Bet {
    int number;
    static int win_multiplier;
public:
    NumberBet(int amount);

    [[nodiscard]] int get_win() const override;

    [[nodiscard]] bool check_win(const Roulette::Number &nr) const override;
};

#endif //ROULETTE_H
