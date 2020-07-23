#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include "predeclarations.h"

/* A Blackjack game motivated by LearnCpp.com

Here are the rules for my version of Blackjack (also set by LearnCpp.com):

    The dealer gets one card to start (in real life, the dealer gets two, but one is face down so it doesn’t matter at this point).
    The player gets two cards to start.
    The player goes first.
    A player can repeatedly “hit” or “stand”.
    If the player “stands”, their turn is over, and their score is calculated based on the cards they have been dealt.
    If the player “hits”, they get another card and the value of that card is added to their total score.
    An ace normally counts as a 1 or an 11 (whichever is better for the total score). For simplicity, ’ll count it as an 11 here.
    If the player goes over a score of 21, they bust and lose immediately.
    The dealer goes after the player.
    The dealer repeatedly draws until they reach a score of 17 or more, at which point they stand.
    If the dealer goes over a score of 21, they bust and the player wins immediately.
    Otherwise, if the player has a higher score than the dealer, the player wins. Otherwise, the player loses (we’ll consider ties as dealer wins for simplicity).

*/

using namespace std; // Again, sorry :P

typedef array<Card, 52> deck_type; // So common

void printCard(const Card& card) // Prints rank/suit representation of a card
{
  switch (card.rank)
  {
    case CardRank::RANK_2:
        std::cout << '2';
        break;
    case CardRank::RANK_3:
        std::cout << '3';
        break;
    case CardRank::RANK_4:
        std::cout << '4';
        break;
    case CardRank::RANK_5:
        std::cout << '5';
        break;
    case CardRank::RANK_6:
        std::cout << '6';
        break;
    case CardRank::RANK_7:
        std::cout << '7';
        break;
    case CardRank::RANK_8:
        std::cout << '8';
        break;
    case CardRank::RANK_9:
        std::cout << '9';
        break;
    case CardRank::RANK_10:
        std::cout << 'T';
        break;
    case CardRank::RANK_JACK:
        std::cout << 'J';
        break;
    case CardRank::RANK_QUEEN:
        std::cout << 'Q';
        break;
    case CardRank::RANK_KING:
        std::cout << 'K';
        break;
    case CardRank::RANK_ACE:
        std::cout << 'A';
        break;
    default:
        std::cout << '?';
        break;
  }

  switch (card.suit)
  {
    case CardSuit::SUIT_CLUB:
        std::cout << 'C';
        break;
    case CardSuit::SUIT_DIAMOND:
        std::cout << 'D';
        break;
    case CardSuit::SUIT_HEART:
        std::cout << 'H';
        break;
    case CardSuit::SUIT_SPADE:
        std::cout << 'S';
        break;
    default:
        std::cout << '?';
        break;
  }
}

CardSuit getCardSuit(int inner_index) { // We are using enum class, so yeah we have to do that
    switch(inner_index) {
            case 0:
                return CardSuit::SUIT_CLUB;
            case 1:
                return CardSuit::SUIT_DIAMOND;
            case 2:
                return CardSuit::SUIT_HEART;
            case 3:
                return CardSuit::SUIT_SPADE;
    }
}

CardRank getCardRank(int outer_index) {
    switch(outer_index) {
            case 0:
                return CardRank::RANK_2;
            case 1:
                return CardRank::RANK_3;
            case 2:
                return CardRank::RANK_4;
            case 3:
                return CardRank::RANK_5;
            case 4:
                return CardRank::RANK_6;
            case 5:
                return CardRank::RANK_7;
            case 6:
                return CardRank::RANK_8;
            case 7:
                return CardRank::RANK_9;
            case 8:
                return CardRank::RANK_10;
            case 9:
                return CardRank::RANK_JACK;
            case 10:
                return CardRank::RANK_QUEEN;
            case 11:
                return CardRank::RANK_KING;
            case 12:
                return CardRank::RANK_ACE;

    }
}



deck_type createDeck() { // Initializes the deck with 52 cards
    deck_type cards{};

    int main_index = 0;

    const int max_cards = (int)CardRank::MAX_RANKS;
    const int max_suit = (int)CardSuit::MAX_SUITS;

    for (int i = 0; i < max_cards; i++) {
        for (int j = 0; j < max_suit; j++) {
            int new_index = i + j;

            Card current_card{getCardRank(i), getCardSuit(j)};

            cards[main_index] = current_card;

            ++main_index;
        }
    }

    return cards;
}

void printDeck(deck_type &deck) { // Makes use of the printCard func
    for (Card &current_card : deck) {
        printCard(current_card);
        cout << " ";
    }
}

void shuffleDeck(deck_type &deck) { // Shuffles using mersenne twister, current time as a seed
    std::mt19937 generator (time(nullptr));

    shuffle(deck.begin(), deck.end(), generator);
}

int getCardValue(Card &current_card) {
    if (current_card.rank < CardRank::RANK_10) {
        return (int)current_card.rank + 2;
    }

    switch (current_card.rank)
    {
        case CardRank::RANK_JACK:
        case CardRank::RANK_QUEEN:
        case CardRank::RANK_KING:
            return 10;
        case CardRank::RANK_ACE:
            return 11;
  }
}

void playBlackJack(deck_type &deck) { // Deck should be shuffled
    // For easier use, cards are represented by their values, via getCardValue() function.

    int current_card_index = 0; // Used to give/spread consecutive cards
    int player_score = getCardValue(deck[current_card_index++]) + getCardValue(deck[current_card_index++]); // 1st and 2rd card goes to the player
    int dealer_score = getCardValue(deck[current_card_index++]); // 3nd card goes to the dealer

    cout << "Your score:  " << player_score << endl;
    cout << "Dealer score:  " << dealer_score << endl;



    cout << "Hit or stand:  "; // PLayer's turn
    string guess;
    cin >> guess;

    if (guess == "hit") { // PLayer hits

        int current_card_value = getCardValue(deck[current_card_index++]);
        player_score += current_card_value; // Draws one card
        cout << "Player draws " << current_card_value << endl;

        if (player_score >= 21) { // Check for bust
            cout << "Player busts with " << player_score << " points." << endl;
            cout << "House wins";
            return;
        }
    }
    while (dealer_score <= 17) { // Dealer draws
        int current_card_value = getCardValue(deck[current_card_index++]);
        dealer_score += current_card_value;
        cout << "Dealer draws " << current_card_value << endl;
    }

    if (dealer_score >= 21) { // Dealer busts
        cout << "Dealer busts with " << dealer_score << " points." << endl;
        cout << "Player wins";
        return;
    } else {
        if (player_score > dealer_score) { // Player wins
            cout << "Player wins with " << player_score << " points, " << player_score - dealer_score << " higher than the dealer" << endl;
            return;
        } else { // Dealer wins
            cout << "House wins with " << dealer_score << " points, " << dealer_score - player_score << " higher than the player" << endl;
            return;
        }
    }
}

int main()
{
    deck_type deck{createDeck()};

    shuffleDeck(deck);

    playBlackJack(deck);

    return 0;
}
