#include <iostream>
#include <cstdlib>
#include <ctime>

// Function to generate a random number between min and max
int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    std::cout << "*** Welcome to the Number Guessing Game ***" << std::endl;
    std::cout << "I'm thinking of a number between 1 and 100. Can you guess what it is?" << std::endl;

    int targetNumber = getRandomNumber(1, 100); // Generate the target number
    int guess;
    int attempts = 0;

    do {
        std::cout << "Enter your guess: ";
        std::cin >> guess;
        attempts++;

        if (guess < targetNumber) {
            std::cout << "Too low! Try again." << std::endl;
        } else if (guess > targetNumber) {
            std::cout << "Too high! Try again." << std::endl;
        } else {
            std::cout << "Congratulations! You guessed it in " << attempts << " attempts." << std::endl;
        }
    } while (guess != targetNumber);

    return 0;
}
