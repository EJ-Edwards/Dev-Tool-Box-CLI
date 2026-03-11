#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <limits>

class Card {
public:
    enum Suit { Hearts, Diamonds, Clubs, Spades };
    enum Rank { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

    Card(Suit suit, Rank rank) : suit(suit), rank(rank) {}

    int getValue() const {
        if (rank >= Two && rank <= Nine) return rank + 2;
        if (rank >= Ten && rank <= King) return 10;
        return 11; // Ace
    }

    std::string toString() const {
        static const char* suitNames[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        static const char* rankNames[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10",
                                           "Jack", "Queen", "King", "Ace" };
        return std::string(rankNames[rank]) + " of " + suitNames[suit];
    }

    Rank getRank() const { return rank; }

private:
    Suit suit;
    Rank rank;
};

static std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

enum BJDifficulty { BJ_EASY = 1, BJ_MODERATE = 2, BJ_HARD = 3 };

static std::vector<Card> buildDeck(int numDecks = 1) {
    std::vector<Card> deck;
    for (int d = 0; d < numDecks; ++d)
        for (int s = Card::Hearts; s <= Card::Spades; ++s)
            for (int r = Card::Two; r <= Card::Ace; ++r)
                deck.emplace_back(static_cast<Card::Suit>(s), static_cast<Card::Rank>(r));
    std::shuffle(deck.begin(), deck.end(), rng());
    return deck;
}

// Returns true if dealer should hit based on difficulty
static bool dealerShouldHit(const std::vector<Card>& hand, BJDifficulty diff) {
    int total = handValue(hand);
    switch (diff) {
        case BJ_EASY:
            // Dealer stands on 15+ (plays poorly)
            return total < 15;
        case BJ_MODERATE:
            // Standard: hits below 17
            return total < 17;
        case BJ_HARD: {
            // Hits on soft 17 (hand has ace counted as 11 and total is 17)
            if (total < 17) return true;
            if (total == 17) {
                // Check for soft 17: at least one ace still counted as 11
                int rawTotal = 0;
                int aces = 0;
                for (const auto& c : hand) {
                    rawTotal += c.getValue();
                    if (c.getRank() == Card::Ace) ++aces;
                }
                int reduced = 0;
                while (rawTotal > 21 && reduced < aces) {
                    rawTotal -= 10;
                    ++reduced;
                }
                // Soft 17 means there's still an unreduced ace
                return reduced < aces;
            }
            return false;
        }
    }
    return total < 17;
}

static std::string bjDifficultyName(BJDifficulty d) {
    switch (d) {
        case BJ_EASY:     return "Easy";
        case BJ_MODERATE: return "Moderate";
        case BJ_HARD:     return "Hard";
    }
    return "Unknown";
}

static Card dealCard(std::vector<Card>& deck) {
    Card card = deck.back();
    deck.pop_back();
    return card;
}

static int handValue(const std::vector<Card>& hand) {
    int total = 0;
    int aces = 0;
    for (const auto& c : hand) {
        total += c.getValue();
        if (c.getRank() == Card::Ace) ++aces;
    }
    while (total > 21 && aces > 0) {
        total -= 10;
        --aces;
    }
    return total;
}

static void showHand(const std::string& name, const std::vector<Card>& hand, bool hideFirst = false) {
    std::cout << "  " << name << ": ";
    for (size_t i = 0; i < hand.size(); ++i) {
        if (i == 0 && hideFirst)
            std::cout << "[hidden]";
        else
            std::cout << hand[i].toString();
        if (i + 1 < hand.size()) std::cout << ", ";
    }
    if (!hideFirst)
        std::cout << "  (value: " << handValue(hand) << ")";
    std::cout << "\n";
}

void run_blackjack() {
    std::cout << "\n  === BLACKJACK ===\n\n";
    std::cout << "  Select difficulty:\n";
    std::cout << "    1. Easy     (dealer stands on 15+, you can see dealer's card)\n";
    std::cout << "    2. Moderate (standard rules)\n";
    std::cout << "    3. Hard     (6-deck shoe, dealer hits soft 17, ties lose)\n";
    std::cout << "  >> ";

    BJDifficulty diff = BJ_MODERATE;
    std::string diffInput;
    if (std::getline(std::cin, diffInput) && !diffInput.empty()) {
        if (diffInput == "1" || diffInput == "easy" || diffInput == "e")        diff = BJ_EASY;
        else if (diffInput == "2" || diffInput == "moderate" || diffInput == "m") diff = BJ_MODERATE;
        else if (diffInput == "3" || diffInput == "hard" || diffInput == "h")    diff = BJ_HARD;
    }

    std::cout << "\n  Difficulty: " << bjDifficultyName(diff) << "\n\n";

    int numDecks = (diff == BJ_HARD) ? 6 : 1;
    auto deck = buildDeck(numDecks);
    std::vector<Card> player, dealer;

    // Initial deal
    player.push_back(dealCard(deck));
    dealer.push_back(dealCard(deck));
    player.push_back(dealCard(deck));
    dealer.push_back(dealCard(deck));

    // Check for natural blackjack
    bool playerBJ = (handValue(player) == 21);
    bool dealerBJ = (handValue(dealer) == 21);
    if (playerBJ || dealerBJ) {
        showHand("You   ", player);
        showHand("Dealer", dealer);
        if (playerBJ && dealerBJ)      std::cout << "\n  Both have Blackjack — Push!\n";
        else if (playerBJ)             std::cout << "\n  Blackjack! You win!\n";
        else                           std::cout << "\n  Dealer has Blackjack. You lose.\n";
        return;
    }

    // Player turn
    bool hideDealerCard = (diff != BJ_EASY);
    while (true) {
        showHand("Dealer", dealer, hideDealerCard);
        showHand("You   ", player);

        if (handValue(player) > 21) {
            std::cout << "\n  Bust! You lose.\n";
            return;
        }

        std::cout << "\n  (h)it or (s)tand? ";
        char choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 'h' || choice == 'H') {
            player.push_back(dealCard(deck));
            std::cout << "  Hit: " << player.back().toString() << "\n\n";
        } else if (choice == 's' || choice == 'S') {
            break;
        }
    }

    // Dealer turn
    if (hideDealerCard)
        std::cout << "\n  Dealer reveals: " << dealer[0].toString() << "\n";
    else
        std::cout << "\n";
    while (dealerShouldHit(dealer, diff)) {
        dealer.push_back(dealCard(deck));
        std::cout << "  Dealer hits: " << dealer.back().toString() << "\n";
    }

    // Result
    std::cout << "\n";
    showHand("You   ", player);
    showHand("Dealer", dealer);

    int pv = handValue(player), dv = handValue(dealer);
    if (dv > 21)         std::cout << "\n  Dealer busts! You win!\n";
    else if (pv > dv)    std::cout << "\n  You win!\n";
    else if (pv < dv)    std::cout << "\n  Dealer wins.\n";
    else if (diff == BJ_HARD)
                         std::cout << "\n  Tie goes to dealer — you lose.\n";
    else                 std::cout << "\n  Push — it's a tie.\n";
}

