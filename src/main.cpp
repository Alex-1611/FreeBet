#include "includes.h"
#include "classes.h"

int main() {
    std::cout<<"1. Roulette\n2. Deck of cards\n";
    int choice;
    std::cin>>choice;
    switch (choice) {
        case 1: {
            Roulette r;
            break;
        }
        case 2: {
            Deck d(1);
            d.shuffle_cards();
            std::cout << d;
            break;
        }
        default:
            std::cout << "Invalid choice";
    }
    return 0;
}
