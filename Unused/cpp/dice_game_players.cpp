#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

class Dice {
public:
    Dice(int sides) : sides(sides) {}

    int roll() const {
        return rand() % sides + 1;
    }

private:
    int sides;
};

class Player {
public:
    Player(std::string name) : name(name), score(0) {}

    void increaseScore(int points) {
        score += points;
    }

    int getScore() const {
        return score;
    }

    std::string getName() const {
        return name;
    }

private:
    std::string name;
    int score;
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::vector<std::string> players = {"Alice", "Bob", "Charlie"};
    std::vector<Player> gamePlayers;
    for (const auto& player : players) {
        gamePlayers.push_back(Player(player));
    }

    Dice dice(6);

    for (int i = 0; i < 10; ++i) {
        std::cout << "Round " << i + 1 << ":" << std::endl;
        for (auto& player : gamePlayers) {
            int roll = dice.roll();
            std::cout << player.getName() << " rolls: " << roll << std::endl;
            player.increaseScore(roll);
        }
        std::cout << std::endl;
    }

    std::cout << "Game Over!" << std::endl;
    for (const auto& player : gamePlayers) {
        std::cout << player.getName() << "'s final score: " << player.getScore() << std::endl;
    }

    return 0;
}
