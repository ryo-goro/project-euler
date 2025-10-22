// Poker Hands
// 376

// This code is solely for showing the details of each game

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

const char *suit_str[] = {
    "S",
    "C",
    "D",
    "H",
};

const char *hand_str[] = {
    "High Card",
    "One Pair",
    "Two Pair",
    "Three Of A Kind",
    "Straight",
    "Flush",
    "Full House",
    "Four Of A Kind",
    "Straight Flush",
    "Royal Flush",
};

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

    // From [1, 2, 3, 4, 5] to [9, 10, 11, 12, 13]
    if (sorted_cards[1].number - sorted_cards[0].number == 1) {
        return 1;
    }

    // [1, 10, 11, 12, 13]
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

int has_ThreeOfAKind(const Card *sorted_cards)
{
    for (int i = 0; i < NUM_OF_CARDS - 2; i++) {
        if (sorted_cards[i].number == sorted_cards[i + 2].number) {
            return 1;
        }
    }

    return 0;
}

int has_TwoPair(const Card *sorted_cards)
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

int has_OnePair(const Card *sorted_cards)
{
    for (int i = 0; i < NUM_OF_CARDS - 1; i++) {
        if (sorted_cards[i].number == sorted_cards[i + 1].number) {
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

    if (has_ThreeOfAKind(sorted_cards)) {
        return ThreeOfAKind;
    }

    if (has_TwoPair(sorted_cards)) {
        return TwoPair;
    }

    if (has_OnePair(sorted_cards)) {
        return OnePair;
    }

    return HighCard;
}


void make_numbers_for_HighCard_Straight_StraightFlush(const Card *sorted_cards, int *numbers)
{
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
}

void make_numbers_for_OnePair(const Card *sorted_cards, int *numbers)
{
    int main_idx, low_idx, mid_idx, high_idx;

    if (sorted_cards[0].number == sorted_cards[1].number) {
        main_idx = 0;
        low_idx = 2;
        mid_idx = 3;
        high_idx = 4;
    } else if (sorted_cards[1].number == sorted_cards[2].number) {
        main_idx = 1;
        low_idx = 0;
        mid_idx = 3;
        high_idx = 4;
    } else if (sorted_cards[2].number == sorted_cards[3].number) {
        main_idx = 2;
        low_idx = 0;
        mid_idx = 1;
        high_idx = 4;
    } else {
        main_idx = 3;
        low_idx = 0;
        mid_idx = 1;
        high_idx = 2;
    }

    int main = sorted_cards[main_idx].number;

    if (main == 1) {
        main = 14;
    }

    int low_kicker = sorted_cards[low_idx].number;
    int mid_kicker = sorted_cards[mid_idx].number;
    int high_kicker = sorted_cards[high_idx].number;

    if (low_kicker == 1) {
        low_kicker = mid_kicker;
        mid_kicker = high_kicker;
        high_kicker = 14;
    }

    numbers[0] = numbers[1] = main;
    numbers[2] = high_kicker;
    numbers[3] = mid_kicker;
    numbers[4] = low_kicker;
}

void make_numbers_for_TwoPair(const Card *sorted_cards, int *numbers)
{
    int main = sorted_cards[3].number;
    int sub = sorted_cards[1].number;

    if (sub == 1) {
        sub = main;
        main = 14;
    }

    int kicker;

    if (sorted_cards[0].number != sorted_cards[1].number) {
        kicker = sorted_cards[0].number;
    } else if (sorted_cards[2].number != sorted_cards[3].number) {
        kicker = sorted_cards[2].number;
    } else {
        kicker = sorted_cards[4].number;
    }

    if (kicker == 1) {
        kicker = 14;
    }

    numbers[0] = numbers[1] = main;
    numbers[2] = numbers[3] = sub;
    numbers[4] = kicker;
}

void make_numbers_for_ThreeOfAKind(const Card *sorted_cards, int *numbers)
{
    int main = sorted_cards[2].number;

    if (main == 1) {
        main = 14;
    }

    int low_kicker;

    if (sorted_cards[0].number != sorted_cards[1].number) {
        low_kicker = sorted_cards[0].number;
    } else {
        low_kicker = sorted_cards[3].number;
    }

    int high_kicker;

    if (sorted_cards[3].number != sorted_cards[4].number) {
        high_kicker = sorted_cards[4].number;
    } else {
        high_kicker = sorted_cards[1].number;
    }

    if (low_kicker == 1) {
        low_kicker = high_kicker;
        high_kicker = 14;
    }

    numbers[0] = numbers[1] = numbers[2] = main;
    numbers[3] = high_kicker;
    numbers[4] = low_kicker;
}

void make_numbers_for_Flush(const Card *sorted_cards, int *numbers)
{
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

void make_numbers_for_FullHouse(const Card *sorted_cards, int *numbers)
{
    int main = sorted_cards[2].number;

    if (main == 1) {
        main = 14;
    }

    int sub;

    if (sorted_cards[0].number == sorted_cards[2].number) {
        sub = sorted_cards[3].number;
    } else {
        sub = sorted_cards[0].number;
    }

    if (sub == 1) {
        sub = 14;
    }

    numbers[0] = numbers[1] = numbers[2] = main;
    numbers[3] = numbers[4] = sub;
}

void make_numbers_for_FourOfAKind(const Card *sorted_cards, int *numbers)
{
    int main = sorted_cards[1].number;

    if (main == 1) {
        main = 14;
    }

    int kicker;

    if (sorted_cards[0].number == sorted_cards[1].number) {
        kicker = sorted_cards[NUM_OF_CARDS - 1].number;
    } else {
        kicker = sorted_cards[0].number;
    }

    if (kicker == 1) {
        kicker = 14;
    }

    for (int i = 0; i < NUM_OF_CARDS - 1; i++) {
        numbers[i] = main;
    }
    numbers[NUM_OF_CARDS - 1] = kicker;
}

void make_numbers_for_RoyalFlush(int *numbers)
{
    for (int i = 0; i < NUM_OF_CARDS; i++) {
        numbers[i] = 14 - i;
    }
}

void make_numbers(const Card *sorted_cards, Hand hand, int *numbers)
{
    switch (hand) {
        case HighCard:
        case Straight:
        case StraightFlush:
            make_numbers_for_HighCard_Straight_StraightFlush(sorted_cards, numbers);
            break;

        case OnePair:
            make_numbers_for_OnePair(sorted_cards, numbers);
            break;
        
        case TwoPair:
            make_numbers_for_TwoPair(sorted_cards, numbers);
            break;
        
        case ThreeOfAKind:
            make_numbers_for_ThreeOfAKind(sorted_cards, numbers);
            break;
        
        case Flush:
            make_numbers_for_Flush(sorted_cards, numbers);
            break;
        
        case FullHouse:
            make_numbers_for_FullHouse(sorted_cards, numbers);
            break;
        
        case FourOfAKind:
            make_numbers_for_FourOfAKind(sorted_cards, numbers);
            break;
        
        case RoyalFlush:
            make_numbers_for_RoyalFlush(numbers);
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

    Card cards1[NUM_OF_CARDS];
    Card cards2[NUM_OF_CARDS];

    int win_count1 = 0;
    int win_count2 = 0;

    for (int game = 0; game < NUM_OF_GAMES; game++) {
        for (int i = 0; i < NUM_OF_CARDS; i++) {
            read_card(fp, &cards1[i]);
        }
        for (int i = 0; i < NUM_OF_CARDS; i++) {
            read_card(fp, &cards2[i]);
        }

        insertion_sort(cards1, NUM_OF_CARDS);
        insertion_sort(cards2, NUM_OF_CARDS);

        printf("Game %d\n", game + 1);
        printf("Player1: ");
        for (int i = 0; i < NUM_OF_CARDS; i++) {
            printf("%2d(%s) ", cards1[i].number, suit_str[cards1[i].suit]);
        }
        printf(" -> %s\n", hand_str[get_hand(cards1)]);

        printf("Player2: ");
        for (int i = 0; i < NUM_OF_CARDS; i++) {
            printf("%2d(%s) ", cards2[i].number, suit_str[cards2[i].suit]);
        }
        printf(" -> %s\n", hand_str[get_hand(cards2)]);

        int comp = compare(cards1, cards2);

        if (comp > 0) {
            puts("Player1 wins\n");
            win_count1++;
        } else if (comp < 0) {
            puts("Player2 wins\n");
            win_count2++;
        } else {
            puts("Draw\n");
        }
    }

    printf("Player1 won %d times\n", win_count1);
    printf("Player2 won %d times\n", win_count2);
    printf("%d draws\n", NUM_OF_GAMES - win_count1 - win_count2);

    fclose(fp);

    return 0;
}
