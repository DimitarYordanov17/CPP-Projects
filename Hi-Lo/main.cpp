// Hi-Lo game
#include <iostream> // Communicate with the user
#include <random> // Random number generator
#include <ctime> // Random number generator seed
#include "predeclarations.h" // Vars namespace and functions declarations

using namespace std; // Sorry :D

unsigned int getRandomNumber() { // Gets the random number via Mersenne Twister
    int current_time = time(nullptr);
    mt19937 generator{current_time};

    uniform_int_distribution random{1, 100};

    return random(generator);
}

int getUserNumber() { // Gets user input, validation included
    cout << "Guess #" << Vars::guesses << ": ";

    int x;
    cin >> x;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        getUserNumber();
    }

    return x;
}


void introduce() { // Introduces the user, the game
    cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is." << endl;
}

bool check(int number) { // Checks for correct answer
    return number == Vars::game_number;
}

void endGame() { // Asks for another game, ends, valdiation included
    cout << "Would you like to play again (y/n)? ";

    char answer;
    cin >> answer;

    if (cin.fail() || (answer != 'y' and answer != 'n')) {
        cin.clear();
        cin.ignore(1000, '\n');
        endGame();
    }

    if (answer == 'y') {
        Vars::guesses = 1;
        Vars::game_number = getRandomNumber();
        playGame();
    } else {
        exit(0);
    }
}

void playGame() { // Runs the game
    introduce();
    while(Vars::guesses <= Vars::max_guesses) { // The user has the right of 7 tries
        int x = getUserNumber();
        Vars::guesses++;

        if (check(x)) {
            cout << "Correct! You win!" << endl;
            endGame();
        } else {
            cout << "Your guess is too " << ((x < Vars::game_number) ? "low" : "high") << endl;
        }
    }
    cout << "Sorry, you lose.  The correct number was " << Vars::game_number << '.' << endl;
    endGame();
}

int main () {
    playGame();
    return 0;
}
