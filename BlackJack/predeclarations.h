#ifndef PREDECLARATIONS_H_INCLUDED
#define PREDECLARATIONS_H_INCLUDED

enum class CardSuit
{
  SUIT_CLUB,
  SUIT_DIAMOND,
  SUIT_HEART,
  SUIT_SPADE,

  MAX_SUITS
};

enum class CardRank
{
  RANK_2,
  RANK_3,
  RANK_4,
  RANK_5,
  RANK_6,
  RANK_7,
  RANK_8,
  RANK_9,
  RANK_10,
  RANK_JACK,
  RANK_QUEEN,
  RANK_KING,
  RANK_ACE,

  MAX_RANKS
};

struct Card {
    CardRank rank{};
    CardSuit suit{};
};


#endif // PREDECLARATIONS_H_INCLUDED

