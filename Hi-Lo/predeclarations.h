#ifndef PREDECLARATIONS_H_INCLUDED
#define PREDECLARATIONS_H_INCLUDED

unsigned int getRandomNumber(); // Declarations
void playGame();

namespace Vars {
    int guesses = 1;
    const int max_guesses = 7;
    int game_number = getRandomNumber(); // Gets the random number
}

#endif // PREDECLARATIONS_H_INCLUDED
