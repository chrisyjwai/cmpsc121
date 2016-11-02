#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;

// User interface functions.
void playGoFish(); // Function to simulate one round of the game.
void playerTurn(bool deck[4][8],bool playerHand[4][8],bool computerHand[4][8]); // Simulates one player turn.
void computerTurn(bool deck[4][8],bool playerHand[4][8],bool computerHand[4][8]); //Simulates one computer turn.
bool checkGameEnd(bool deck[4][8],bool playerHand[4][8],bool computerHand[4][8]); // Checks if the game has ended.

// Computation fuctions.
void initializeTrue(bool array[4][8]); // Initialize all elements in an array to be true.
void initializeFalse(bool array[4][8]); // Initialize all elements in an array to be false.
void initializeHand(bool deck[4][8],bool hand[4][8]); // Draws 5 cards from the deck and places them in a hand.
int rollDie(int);  // Picks a random integer >= 0 and < the provided argument.
int numberOfCards(bool array[4][8]); // Used to count number of cards in deck or hand.
void passCard(bool passHand[4][8],bool recieveHand[4][8],int); // Searches and passes all cards of that rank to recieving hand.
int rankSearch(bool array[4][8],int); // Searches hand and counts for rank input.
void deckDraw(bool deck[4][8],bool hand[4][8],int&,int&); // Draws from the deck into the hand.
int checkSetDiscard(bool hand[4][8]);  // Checks how many sets there are in a hand and discards said sets.
int computerAskRank(bool hand[4][8]); // Picks a rank for the computer to ask for from the player.

/*------------------------------
    User interface functions
------------------------------*/

int main() {
    char yesNo = 'y';
    cout << "Welcome to Go Fish!" << endl << endl;
    while (yesNo == 'y') {
        playGoFish(); // Calls the game simulation.
        cout << endl;
        do {
            cout << "Would you like to play again?" << endl;
            cin >> yesNo;
        } while (yesNo != 'y' && yesNo != 'n');
        if (yesNo == 'n') {
            cout << "Thank you for playing Go Fish! Bye!" << endl;
            return 0;
        }
    }
}

void playGoFish() { // Function to simulate one round of the game.
    bool deck[4][8]; // Remaining deck array.
    bool playerHand[4][8]; // Player hand array.
    bool computerHand[4][8]; // Computer hand array.
    initializeTrue(deck); // Initializes the entire deck of have all cards.
    initializeFalse(playerHand); // Initializes player hand to have no cards.
    initializeFalse(computerHand); // Initializes computer hand to have no cards.
    initializeHand(deck,playerHand); // Initializes player hand to have five cards.
    initializeHand(deck,computerHand); // Initializes computer hand to have five cards.
    int deckNumber = numberOfCards(deck); // Initializes the number cards in the deck.
    int playerNumber = numberOfCards(playerHand); // Initializes the number cards in the player's hand.
    int computerNumber = numberOfCards(computerHand); // Initializes the number cards in the computer's hand.
    while (deckNumber != 0 && playerNumber != 0 && computerNumber != 0) { // The games runs as long as
        playerTurn(deck,playerHand,computerHand); // there are cards
        deckNumber = numberOfCards(deck); // in the deck,
        playerNumber = numberOfCards(playerHand); // in the player's hand,
        computerNumber = numberOfCards(computerHand); // or in the computer's hand.
    }
}

void playerTurn(bool deck[4][8],bool playerHand[4][8],bool computerHand[4][8]) {  // Simulates one player turn.
    string suits[4] = {"Spades", "Hearts", "Clubs", "Diamonds"}; // String array for names of suits.
    string ranks[8] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"}; // String array for names of ranks.
    cout << "You have: | ";
    for (int rank = 0; rank < 8; rank = rank + 1) { // The loop and the nested loop and the if statement
        for (int suit = 0; suit < 4; suit = suit + 1) { // Prints the name of the card if it exists in the hand.
            if (playerHand[suit][rank] == true) {
                cout << ranks[rank] << " of " << suits[suit] << " | ";
            }
        }
    }
    cout << endl;
    if (int sets = checkSetDiscard(playerHand) != 0) { // If sets have been completed.
        if (sets == 1) { // If one set is completed.
            cout << "You have completed a set." << endl;
        }
        else { // Multiple sets are completed.
            cout << "You have completed " << sets << " sets." << endl;
        }
    }
    if (checkGameEnd(deck,playerHand,computerHand) == true) { // If the game has ended.
        return;
    }
    int rankAsked;
    do {
        do {
            cout << "You ask if I have any: ";
            cin >> rankAsked;
        } while (rankAsked < 2 || rankAsked > 9); // User input validation.
    } while (rankSearch(playerHand,rankAsked) == 0); // Makes sure the player has the card being asked for.
    int computerInHand = rankSearch(computerHand,rankAsked); // The variable stores how many of that rank being asked the computer has in hand.
    if (computerInHand != 0) { // If the computer has the card being asked for.
        cout << "Yes I do. I have " << computerInHand << "." << endl;
        passCard(computerHand,playerHand,rankAsked); // The computer is obligated to pass all it's cards being asked for to the player.
        if (int sets = checkSetDiscard(playerHand) != 0) { // If sets have been completed.
            if (sets == 1) { // If one set is completed.
                cout << "You have completed a set." << endl;
            }
            else { // Multiple sets are completed.
                cout << "You have completed " << sets << " sets." << endl;
            }
        }
        if (checkGameEnd(deck,playerHand,computerHand) == true) { // If the game has ended.
            return;
        }
    }
    else { // If the computer doesn't have the card being asked for.
        int drawSuit = 0; 
        int drawRank = 0;
        cout << "No I don't! Go Fish!" << endl;
        deckDraw(deck,playerHand,drawSuit,drawRank); // Player draws a card from the deck.
        if (checkGameEnd(deck,playerHand,computerHand) == true) { // If the game has ended.
            return;
        }
        cout << "You draw a " << ranks[drawRank] << " of " << suits[drawSuit] << "." << endl;
        if (int sets = checkSetDiscard(playerHand) != 0) { // If sets have been completed.
            if (sets == 1) { // If one set is completed.
                cout << "You have completed a set." << endl;
            }
            else { // Multiple sets are completed.
                cout << "You have completed " << sets << " sets." << endl;
            }
        }
        if (checkGameEnd(deck,playerHand,computerHand) == true) { // If the game has ended.
            return;
        }
        if (rankAsked - 2 != drawRank) { // If card drawn is not what was asked for.
            computerTurn(deck,playerHand,computerHand); // End turn. Begin computer turn.
        }
    }
}

void computerTurn(bool deck[4][8],bool playerHand[4][8],bool computerHand[4][8]) {
    string suits[4] = {"Spades", "Hearts", "Clubs", "Diamonds"}; // String array for names of suits.
    string ranks[8] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"}; // String array for names of ranks.
    cout << "My turn!" << endl;
    if (int sets = checkSetDiscard(computerHand) != 0) { // If sets have been completed.
        if (sets == 1) { // If one set is completed.
            cout << "I have completed a set." << endl;
        }
        else { // Multiple sets are completed.
            cout << "I have completed " << sets << " sets." << endl;
        }
    }
    if (checkGameEnd(deck,playerHand,computerHand) == true) { // If the game has ended.
        return;
    }
    int rankAsked = computerAskRank(computerHand);
    if (rankAsked == 6) {
        cout << "I ask: Do you have any " << ranks[rankAsked - 2] << "es?" << endl;
    }
    else {
        cout << "I ask: Do you have any " << ranks[rankAsked - 2] << "s?" << endl;
    }
    int playerInHand = rankSearch(playerHand,rankAsked); // The variable stores how many of that rank being asked the player has in hand.
    if (playerInHand != 0) { // If the player has the card being asked for.
        cout << "Yes you do. You have " << playerInHand << "." << endl;
        passCard(playerHand,computerHand,rankAsked); // The player is obligated to pass all it's cards being asked for to the computer.
        if (int sets = checkSetDiscard(computerHand) != 0) { // If sets have been completed.
            if (sets == 1) { // If one set is completed.
                cout << "I have completed a set." << endl;
            }
            else { // Multiple sets are completed.
                cout << "I have completed " << sets << " sets." << endl;
            }
        }
        if (checkGameEnd(deck,playerHand,computerHand) == true) { // If the game has ended.
            return;
        }
    }
    else { // If the player doesn't have the card being asked for.
        int drawSuit = 0; 
        int drawRank = 0;
        cout << "You don't! I Go Fish!" << endl;
        deckDraw(deck,computerHand,drawSuit,drawRank); // Player draws a card from the deck.
        if (checkGameEnd(deck,playerHand,computerHand) == true) { // If the game has ended.
            return;
        }
        if (int sets = checkSetDiscard(computerHand) != 0) { // If sets have been completed.
            if (sets == 1) { // If one set is completed.
                cout << "I have completed a set." << endl;
            }
            else { // Multiple sets are completed.
                cout << "I have completed " << sets << " sets." << endl;
            }
            
        }
        if (checkGameEnd(deck,playerHand,computerHand) == true) { // If the game has ended.
            return;
        }
        if (rankAsked - 2 != drawRank) { // If card drawn is not what was asked for.
            cout << "I don't have in hand the card I drew. It's your turn again!" << endl;;
            return; // End turn.
        }
    }
}

bool checkGameEnd(bool deck[4][8],bool playerHand[4][8],bool computerHand[4][8]) {  // Checks if the game has ended.
    if (numberOfCards(playerHand) == 0) { // The game ends if the the player has no more cards in hand.
        cout << "You have no more cards in hand! You win!" << endl;
        return true;
    }
    if (numberOfCards(computerHand) == 0) { // The game ends if the the computer has no more cards in hand.
        cout << "The computer has no more cards in hand! The computer wins!" << endl;
        return true;
    }
    if (numberOfCards(playerHand) == 0) { // The game ends if the the ocean has no more fish.
        cout << "The ocean has no more fish! You draw with the computer!" << endl;
        return true;
    }
}

/*---------------------------
    Computation functions
---------------------------*/

void initializeTrue(bool array[4][8]) { // Initialize all elements in an array to be true.
    for (int suit = 0; suit < 4; suit = suit + 1) {
        for (int rank = 0; rank < 8; rank = rank + 1) {
            array[suit][rank] = true; // For every suit and rank, the element is true.
        }
    }
}

void initializeFalse(bool array[4][8]) { // Initialize all elements in an array to be false.
    for (int suit = 0; suit < 4; suit = suit + 1) {
        for (int rank = 0; rank < 8; rank = rank + 1) {
            array[suit][rank] = false; // For every suit and rank, the element is false.
        }
    }
}

void initializeHand(bool deck[4][8],bool hand[4][8]) { // Draws 5 cards from the deck and places them in a hand.
    int suit = rollDie(4); // Initialize a random suit.
    int rank = rollDie(8); // Initialize a random rank.
    for (int i = 0; i < 5; i = i + 1) { // For five cards being drawn.
        while (deck[suit][rank] == false) { // Keep rolling the dice until an existing card is found.
            suit = rollDie(4);
            rank = rollDie(8);
        }
        hand[suit][rank] = true; // The card now exists in the hand.
        deck[suit][rank] = false; // The card now ceases to exist in the deck.
    }
}

void deckDraw(bool deck[4][8],bool hand[4][8],int& suit,int& rank) { // Draws from the deck into the hand.
    suit = rollDie(4); // Initialize a randome suit. The suit will later be passed by reference.
    rank = rollDie(8); // Initialize a randome rank. The rank will later be passed by reference.
    while (deck[suit][rank] == false) { // Keep rolling the dice until an existing card is found.
        suit = rollDie(4);
        rank = rollDie(8);
    }
    hand[suit][rank] = true; // The card now exists in the hand.
    deck[suit][rank] = false; // The card now ceases to exist in the deck.
}

int rollDie(int sides) { // Picks a random integer >= 0 and < the provided argument.
    return rand() % sides;
}

int numberOfCards(bool array[4][8]) { // Used to count number of cards in deck or hand.
    int cardsInArray = 0; // Variable to count number of cards in array.
    for (int suit = 0; suit < 4; suit = suit + 1) { // For every suit.
        for (int rank = 0; rank < 4; rank = rank+ 1) { // For every rank.
            if (array[suit][rank] == true) { // If the card exists,
                cardsInArray = cardsInArray + 1; // Increment the counter.
            }
        }
    }
    return cardsInArray; // Returns the number cards in the array.
}

void passCard(bool passHand[4][8],bool recieveHand[4][8],int card) { // Searches and passes all cards of that rank to recieving hand.
    int rank = card - 2; // The position of the card's rank is two less than the rank being passed.
    for (int suit = 0; suit < 4; suit = suit + 1) { // For every suit in the rank being passed.
        if (passHand[suit][rank] == true) { // If the suit exists for that rank.
            recieveHand[suit][rank] = true; // The card now exists in the recieving hand.
            passHand[suit][rank] = false; // The card now ceases to exist in the passing hand.
        }
    }
}

int rankSearch(bool array[4][8],int card) { // Searches hand and counts for rank input.
    int rank = card - 2; // The position of the card's rank is two less than the rank being searched.
    int cardsInRank = 0; // Counter for number of cards in the rank.
    for (int suit = 0; suit < 4; suit = suit + 1) { // For every suit in the rank.
        if (array[suit][rank] == true) { // If the suit exists for that rank.
            cardsInRank = cardsInRank + 1; // Increment the counter.
        }
    }
    return cardsInRank; // Return the value of the counter.
}

int checkSetDiscard(bool hand[4][8]) {  // Checks how many sets there are in a hand and discards said sets.
    int cardCount = 0; // Counts how many cards of a rank in the hand.
    int setCount = 0; // Counts the number of sets formed..
    for (int rank = 0; rank < 8; rank = rank + 1) { // For every rank.
        for (int suit = 0; suit < 4; suit = suit + 1) { // For every suit.
            if (hand[suit][rank] == true) { // If the card exitsts.
                cardCount = cardCount + 1; // Increment the card counter.
            }
        }
        if (cardCount == 4) { // If a rank is complete.
            setCount = setCount + 1; // Increment the set counter.
            for (int suit = 0; suit < 4; suit = suit + 1) { // For every suit in the rank.
                hand[suit][rank] = false; // Discards the cards in the set.
            }
        }
        cardCount = 0; // Reset the card counter to zero.
    }
    return setCount; // Return the number of sets formed.
    // N.B. In Go Fish! The setCount will never be greater than 1 but I have done this for self future reference.
    // As well as in the game simulation. The else clause that informs the player multiple sets have been completed
    // will never be used. It is only for future reference and possible modularization.
}

int computerAskRank(bool hand[4][8]) { // Picks a rank for the computer to ask for from the player.
    int suit = rollDie(4); // Initialize a random suit.
    int rank = rollDie(8); // Initialize a random rank.
    while (hand[suit][rank] == false) { // Keep rolling the dice until an existing card is found.
        suit = rollDie(4);
        rank = rollDie(8);
    }
    return (rank + 2);
}