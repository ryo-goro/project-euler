// Poker Hands
// 376

#include <stdio.h>

#define NUM_OF_CARDS 5
#define NUM_OF_GAMES 1000

typedef enum { Spade, Club, Diamond, Heart } Suit;

typedef struct {
    int number;
    Suit suit;
} Card;

typedef enum {
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush,
} Hand;

int read_card(FILE *fp, Card *card)
{
    int raw_number;
    while ((raw_number = fgetc(fp)) == ' ' || raw_number == '\n')
        ;
    
    if (raw_number == EOF) {
        return 1;
    }

    switch (raw_number) {
        case 'T':
            card->number = 10;
            break;
        
        case 'J':
            card->number = 11;
            break;
        
        case 'Q':
            card->number = 12;
            break;
        
        case 'K':
            card->number = 13;
            break;
        
        case 'A':
            card->number = 1;
            break;
        
        default:
            card->number = raw_number - '0';
    }

    int raw_suit = fgetc(fp);
    
    switch (raw_suit) {
        case 'S':
            card->suit = Spade;
            break;
        
        case 'C':
            card->suit = Club;
            break;
        
        case 'D':
            card->suit = Diamond;
            break;
        
        case 'H':
            card->suit = Heart;
            break;
    }

    return 0;
}

void insertion_sort(Card *cards, int n)
{
    for (int i = 1; i < n; i++) {
        if (cards[i].number < cards[i - 1].number) {
            int j = i;
            Card card = cards[i];

            do {
                cards[j] = cards[j - 1];
                j--;
            } while (j > 0 && cards[j - 1].number > card.number);

            cards[j] = card;
        }
    }
}

int has_Flush(const Card *cards)
{
    Suit suit = cards[0].suit;

    for (int i = 1; i < NUM_OF_CARDS; i++) {
        if (cards[i].suit != suit) {
            return 0;
        }
    }

    return 1;
}

int has_Straight(const Card *sorted_cards)
{
    for (int i = 1; i < NUM_OF_CARDS - 1; i++) {
        if (sorted_cards[i + 1].number - sorted_cards[i].number != 1) {
            return 0;
        }
    }

    if (sorted_cards[1].number - sorted_cards[0].number == 1) {
        return 1;
    }

    if (sorted_cards[0].number == 1 && sorted_cards[1].number == 10) {
        return 1;
    }

    return 0;
}

int has_StraightFlush(const Card *sorted_cards)
{
    return has_Flush(sorted_cards) && has_Straight(sorted_cards);
}

int is_RoyalFlush(const Card *sorted_cards)
{
    return sorted_cards[0].number == 1 && sorted_cards[1].number == 10 && has_StraightFlush(sorted_cards);
}

int is_FourOfAKind(const Card *sorted_cards)
{
    return sorted_cards[0].number == sorted_cards[3].number || sorted_cards[1].number == sorted_cards[4].number;
}

int is_FullHouse(const Card *sorted_cards)
{
    if (
        sorted_cards[0].number == sorted_cards[2].number
        && sorted_cards[2].number != sorted_cards[3].number
        && sorted_cards[3].number == sorted_cards[4].number
    ) {
        return 1;
    }

    if (
        sorted_cards[0].number == sorted_cards[1].number
        && sorted_cards[1].number != sorted_cards[2].number
        && sorted_cards[2].number == sorted_cards[4].number
    ) {
        return 1;
    }

    return 0;
}

int is_ThreeOfAKind(const Card *sorted_cards)
{
    if (sorted_cards[0].number == sorted_cards[2].number) {
        if (sorted_cards[2].number == sorted_cards[3].number) {
            return 0;
        }
        if (sorted_cards[3].number == sorted_cards[4].number) {
            return 0;
        }
        return 1;
    }

    if (sorted_cards[1].number == sorted_cards[3].number) {
        if (sorted_cards[3].number == sorted_cards[4].number) {
            return 0;
        }
        return 1;
    }

    if (sorted_cards[2].number == sorted_cards[4].number) {
        if (sorted_cards[0].number == sorted_cards[1].number) {
            return 0;
        }
        return 1;
    }

    return 0;
}

int is_TwoPair(const Card *sorted_cards)
{
    if (sorted_cards[0].number == sorted_cards[1].number) {
        if (sorted_cards[1].number == sorted_cards[2].number) {
            return 0;
        }
        if (sorted_cards[2].number == sorted_cards[3].number) {
            return sorted_cards[3].number != sorted_cards[4].number;
        }
        return sorted_cards[3].number == sorted_cards[4].number;
    }

    if (
        sorted_cards[1].number == sorted_cards[2].number
        && sorted_cards[2].number != sorted_cards[3].number
        && sorted_cards[3].number == sorted_cards[4].number
    ) {
        return 1;
    }

    return 0;
}

int is_OnePair(const Card *sorted_cards)
{
    for (int i = 0; i < NUM_OF_CARDS - 1; i++) {
        if (sorted_cards[i].number == sorted_cards[i + 1].number) {
            for (int j = i + 1; j < NUM_OF_CARDS - 1; j++) {
                if (sorted_cards[j].number == sorted_cards[j + 1].number) {
                    return 0;
                }
            }
            return 1;
        }
    }

    return 0;
}

Hand get_hand(const Card *sorted_cards)
{
    if (is_RoyalFlush(sorted_cards)) {
        return RoyalFlush;
    }

    if (has_StraightFlush(sorted_cards)) {
        return StraightFlush;
    }

    if (is_FourOfAKind(sorted_cards)) {
        return FourOfAKind;
    }

    if (is_FullHouse(sorted_cards)) {
        return FullHouse;
    }

    if (has_Flush(sorted_cards)) {
        return Flush;
    }

    if (has_Straight(sorted_cards)) {
        return Straight;
    }

    if (is_ThreeOfAKind(sorted_cards)) {
        return ThreeOfAKind;
    }

    if (is_TwoPair(sorted_cards)) {
        return TwoPair;
    }

    if (is_OnePair(sorted_cards)) {
        return OnePair;
    }

    return HighCard;
}

void make_numbers(const Card *sorted_cards, Hand hand, int *numbers)
{
    switch (hand) {
        case HighCard:
            if (sorted_cards[0].number == 1) {
                numbers[0] = 14;
                for (int i = 1; i < NUM_OF_CARDS; i++) {
                    numbers[i] = sorted_cards[NUM_OF_CARDS - i].number;
                }
            } else {
                for (int i = 0; i < NUM_OF_CARDS; i++) {
                    numbers[i] = sorted_cards[NUM_OF_CARDS - 1 - i].number;
                }
            }
            break;

        case OnePair:
            if (sorted_cards[0].number == sorted_cards[1].number) {
                if (sorted_cards[0].number == 1) {
                    numbers[0] = numbers[1] = 14;
                } else {
                    numbers[0] = numbers[1] = sorted_cards[0].number;
                }
                for (int i = 2; i < NUM_OF_CARDS; i++) {
                    numbers[i] = sorted_cards[NUM_OF_CARDS + 1 - i].number;
                }
            } else if (sorted_cards[1].number == sorted_cards[2].number) {
                numbers[0] = numbers[1] = sorted_cards[1].number;
                if (sorted_cards[0].number == 1) {
                    numbers[2] = 14;
                    numbers[3] = sorted_cards[4].number;
                    numbers[4] = sorted_cards[3].number;
                } else {
                    numbers[2] = sorted_cards[4].number;
                    numbers[3] = sorted_cards[3].number;
                    numbers[4] = sorted_cards[0].number;
                }
            } else if (sorted_cards[2].number == sorted_cards[3].number) {
                numbers[0] = numbers[1] = sorted_cards[2].number;
                if (sorted_cards[0].number == 1) {
                    numbers[2] = 14;
                    numbers[3] = sorted_cards[4].number;
                    numbers[4] = sorted_cards[1].number;
                } else {
                    numbers[2] = sorted_cards[4].number;
                    numbers[3] = sorted_cards[1].number;
                    numbers[4] = sorted_cards[0].number;
                }
            } else {
                numbers[0] = numbers[1] = sorted_cards[3].number;
                if (sorted_cards[0].number == 1) {
                    numbers[2] = 14;
                    numbers[3] = sorted_cards[2].number;
                    numbers[4] = sorted_cards[1].number;
                } else {
                    numbers[2] = sorted_cards[2].number;
                    numbers[3] = sorted_cards[1].number;
                    numbers[4] = sorted_cards[0].number;
                }
            }
            break;
        
        case TwoPair:
            if (sorted_cards[0].number == sorted_cards[1].number) {
                if (sorted_cards[0].number == 1) {
                    numbers[0] = numbers[1] = 14;
                    numbers[2] = numbers[3] = sorted_cards[3].number;
                } else {
                    numbers[0] = numbers[1] = sorted_cards[3].number;
                    numbers[2] = numbers[3] = sorted_cards[0].number;
                }
                if (sorted_cards[2].number == sorted_cards[3].number) {
                    numbers[4] = sorted_cards[4].number;
                } else {
                    numbers[4] = sorted_cards[2].number;
                }
            } else {
                numbers[0] = numbers[1] = sorted_cards[3].number;
                numbers[2] = numbers[3] = sorted_cards[1].number;
                if (sorted_cards[0].number == 1) {
                    numbers[4] = 14;
                } else {
                    numbers[4] = sorted_cards[0].number;
                }
            }
            break;
        
        case ThreeOfAKind: {
            int three = sorted_cards[2].number;
            if (three == 1) {
                numbers[0] = numbers[1] = numbers[2] = 14;
            } else {
                numbers[0] = numbers[1] = numbers[2] = three;
            }

            if (three == sorted_cards[0].number) {
                numbers[3] = sorted_cards[4].number;
                numbers[4] = sorted_cards[3].number;
            } else if (three == sorted_cards[1].number) {
                if (sorted_cards[0].number == 1) {
                    numbers[3] = 14;
                    numbers[4] = sorted_cards[4].number;
                } else {
                    numbers[3] = sorted_cards[4].number;
                    numbers[4] = sorted_cards[0].number;
                }
            } else {
                if (sorted_cards[0].number == 1) {
                    numbers[3] = 14;
                    numbers[4] = sorted_cards[1].number;
                } else {
                    numbers[3] = sorted_cards[1].number;
                    numbers[4] = sorted_cards[0].number;
                }
            }
        }
            break;
        
        case Straight:
            if (sorted_cards[0].number == 1) {
                numbers[0] = 14;
                for (int i = 1; i < NUM_OF_CARDS; i++) {
                    numbers[i] = sorted_cards[NUM_OF_CARDS - i].number;
                }
            } else {
                for (int i = 0; i < NUM_OF_CARDS; i++) {
                    numbers[i] = sorted_cards[NUM_OF_CARDS - 1 - i].number;
                }
            }
            break;
        
        case Flush: {
            int i;
            for (i = 0; i < NUM_OF_CARDS; i++) {
                if (sorted_cards[i].number == 1) {
                    numbers[i] = 14;
                } else {
                    break;
                }
            }

            for (int j = NUM_OF_CARDS - 1; i < NUM_OF_CARDS; i++, j--) {
                numbers[i] = sorted_cards[j].number;
            }
        }
            break;
        
        case FullHouse:
            for (int i = 0; i < NUM_OF_CARDS; i++) {
                numbers[i] = sorted_cards[NUM_OF_CARDS - 1 - i].number;
            }
            break;
        
        case FourOfAKind:
            if (sorted_cards[0].number == sorted_cards[1].number) {
                for (int i = 0; i < NUM_OF_CARDS; i++) {
                    if (sorted_cards[i].number == 1) {
                        numbers[i] = 14;
                    } else {
                        numbers[i] = sorted_cards[i].number;
                    }
                }
            } else {
                for (int i = 0; i < NUM_OF_CARDS - 1; i++) {
                    numbers[i] = sorted_cards[i + 1].number;
                }
                if (sorted_cards[0].number == 1) {
                    numbers[NUM_OF_CARDS - 1] = 14;
                } else {
                    numbers[NUM_OF_CARDS - 1] = sorted_cards[0].number;
                }
            }
            break;
        
        case StraightFlush:
            if (sorted_cards[0].number == 1) {
                numbers[0] = 14;
                for (int i = 1; i < NUM_OF_CARDS; i++) {
                    numbers[i] = sorted_cards[NUM_OF_CARDS - i].number;
                }
            } else {
                for (int i = 0; i < NUM_OF_CARDS; i++) {
                    numbers[i] = sorted_cards[NUM_OF_CARDS - 1 - i].number;
                }
            }
            break;
        
        case RoyalFlush:
            for (int i = 0; i < NUM_OF_CARDS; i++) {
                numbers[i] = 14 - i;
            }
            break;
    }
}

int compare_arr(const int *arr1, const int *arr2, int n)
{
    for (int i = 0; i < n; i++) {
        if (arr1[i] > arr2[i]) {
            return 1;
        }
        if (arr1[i] < arr2[i]) {
            return -1;
        }
    }

    return 0;
}

int compare(const Card *sorted_cards1, const Card *sorted_cards2)
{
    Hand hand1 = get_hand(sorted_cards1);
    Hand hand2 = get_hand(sorted_cards2);

    if (hand1 > hand2) {
        return 1;
    }

    if (hand1 < hand2) {
        return -1;
    }

    Hand hand = hand1;
    int numbers1[NUM_OF_CARDS];
    int numbers2[NUM_OF_CARDS];

    make_numbers(sorted_cards1, hand, numbers1);
    make_numbers(sorted_cards2, hand, numbers2);
    
    return compare_arr(numbers1, numbers2, NUM_OF_CARDS);
}

int main(void)
{
    FILE *fp = fopen("../text/problem054.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open ../text/problem054.txt\n");
        return 1;
    }

    Card p1[NUM_OF_CARDS];
    Card p2[NUM_OF_CARDS];

    int count = 0;

    for (int game = 0; game < NUM_OF_GAMES; game++) {
        for (int i = 0; i < NUM_OF_CARDS; i++) {
            read_card(fp, &p1[i]);
        }
        for (int i = 0; i < NUM_OF_CARDS; i++) {
            read_card(fp, &p2[i]);
        }

        insertion_sort(p1, NUM_OF_CARDS);
        insertion_sort(p2, NUM_OF_CARDS);

        if (compare(p1, p2) > 0) {
            count++;
        }
    }

    printf("%d\n", count);

    fclose(fp);

    return 0;
}
