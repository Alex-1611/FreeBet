#include "card_games.h"
#include "roulette.h"

int main() {
    while(true){
        std::cout << "Manu:" << std::endl;
        std::cout << "1. Roulette" << std::endl;
        std::cout << "2. Baccarat" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout<< "Enter your choice: ";
        int choice;
        std::cin >> choice;
        switch(choice){
            case 1: {
                Roulette r;
                r.play();
                break;
            }
            case 2: {
                Baccarat b;
                b.play();
                break;
            }
            case 3:
                return 0;
            default:
                std::cout << "Invalid choice" << std::endl;
        }
    }
    return 0;
}
