#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;

const int DECKS = 4; // Constant for number of decks in the shoe.
const int CARDS = 5; // Constant for maximum number of cards in the hand.
const int TABLE = 5; // Constant for the number of seats at the table.

struct person { // Structure of a person.
    int hand[2][CARDS][3];
    double bankRoll;
    double bet[2];
    int cardNum[2];
    bool atTable;
};

// User Interface Functions
void playBlackjack(); // The game simulation.
void playerTurn(bool shoe[DECKS][4][13],person& player,int
playerNumber,person& dealer); // Player turn simuation.
void playerHitStick(bool shoe[DECKS][4][13],person& player,int
playerNumber,int playerHand,person& dealer); // Hit/Stick cycle simulation.
bool continuePlay(person& player,int splits); // Checks whether to continue
playing.
void dealerTurn(bool shoe[DECKS][4][13],person& dealer); // Dealer turn
simulation.
void playerDealerCheck(person& player,person& dealer); // Checks player
against the dealer.

// Computation Functions
void initializeShoe(bool shoe[DECKS][4][13]); // Initialize all elements in the
shoe to be true.
void initializeZero(int hand[CARDS][3]); // Initialize all elements in the hand
to be zero.
void initializeHand(bool shoe[DECKS][4][13],int hand[CARDS][3],int&
cardNum); // Draws 5 cards from the deck and places them in a hand.
void shoeDraw(bool shoe[DECKS][4][13],int hand[CARDS][3],int& cardNum); //
Draws from the deck into the hand.
int rollDie(int sides);  // Picks a random integer >= 0 and < the
provided argument.
int numberOfCards(bool shoe[DECKS][4][13]); // Used to count number of cards in
the shoe.
int numberOfAces(int hand[CARDS][3],int cardNum); // Used to cound the number
of aces in the hand.
int handTotal(int hand[CARDS][3],int cardNum); // Used to find the total sum of
cards in the hand.

/*-------------------------------
    User Interface Functions
-------------------------------*/

int main() {
    char yesNo = 'y'; // Ask variable
    cout << "Welcome to Blackjack!" << endl << endl;
    while (yesNo == 'y') { // Repeats game as user desires.
        playBlackjack(); // Calls the game simulation.
        cout << endl;
        do { // User input validation.
            cout << "Would you like to play again? (y/n): ";
            cin >> yesNo;
        } while (yesNo != 'y' && yesNo != 'n');
        if (yesNo == 'n') { // Leave game as user desires.
            cout << "Thank you for playing Blackjack! Bye!" << endl;
            return 0;
        }
    }
}

void playBlackjack() { // The game simulation.
    char yesNo; // Ask variable.
    person player[TABLE]; // One person can sit at each seat of the table of
constant size.
    person dealer; // The dealer is initialized
    string numbers[TABLE] = {"One", "Two", "Three", "Four", "Five"}; // Player
names/numbers.
    int people; // Variable for how many people join the table.
    do { // User input validation.
        cout << "How many people are playing? (1 - " << TABLE
<< " players): ";
        cin >> people;
    } while (people < 1 || people > TABLE);
    bool shoe[DECKS][4][13];
    for (int i = 0; i < TABLE; i = i + 1) {
        player[i].atTable = false; // Originally, there is no one at the table.
    }
    initializeShoe(shoe); // Initialize the shoe.
    for (int i = 0; i < people; i = i + 1) { // People join the table.
        player[i].bankRoll = 100; // They get a hundred dollar bank roll.
        player[i].atTable = true; // They sit down.
    }
    while (people > 0) { // While there are still people at the table.
        if (numberOfCards(shoe) < 50) { // If the shoe is depleting.
            cout << "There were less than 50 cards left in the shoe. A
new shoe has been reshuffled." << endl;
            initializeShoe(shoe); // Reinitialize the shoe.
        }
        for (int i = 0; i < people; i = i + 1) { // For each player at the
table.
            if (player[i].atTable == true) {
                for (int splits = 0; splits < 2; splits = splits + 1) { //
For each hand.
                    initializeZero(player[i].hand[splits]); // The new array is
intialized to zero.
                    player[i].cardNum[splits] = 0; // The player has no cards
to start with.
                    player[i].bet[splits] = 0; // The player's bet is zero to
start with.
                }
                initializeHand(shoe,player[i].hand[0],player[i].cardNum[0]); //
Each player's hand is drawn.
            }
        }
        for (int i = 0; i < people; i = i + 1) { // For each player at the
table.
            if (player[i].atTable == true) {
                if (player[i].bankRoll > 0) { // If they have enough money
to play.
                    do { // User input validation.
                        cout << "Player " << numbers[i] << ",
you have $" << player[i].bankRoll << ". "; // Informs player of
money he/she has.
                        cout << "Please place a valid bet: $";
                        cin >> player[i].bet[0]; // Bet placed
                    } while (player[i].bet[0] < 0 || player[i].bet[0] >
player[i].bankRoll);
                    player[i].bankRoll = player[i].bankRoll - player[i].bet[0];
// The bet is taken from the bank roll of the player.
                }
                else { // Otherwise,
                    cout << "Sorry Player " << numbers[i] <<
", you've run out of money." << endl;
                    player[i].atTable = false; // They leave the table
                    people = people - 1; // One less person.
                }
            }
        }
        initializeHand(shoe,dealer.hand[0],dealer.cardNum[0]); // The dealer's
hand is intialized.
        cout << "The dealer peeks at the hole card..." << endl;
        if (handTotal(dealer.hand[0],dealer.cardNum[0]) == 21) { // The dealer
automatically wins here unless it's a push.
            cout << "The dealer has a Blackjack!" << endl;
        }
        else {
            for (int i = 0; i < people; i = i + 1) { // For each player at
the table.
                if (player[i].atTable == true) {
                    playerTurn(shoe,player[i],i,dealer); // Player's turn.
                }
            }
        }
        int openHands = 0; // Counter for how many hands are left.
        for (int i = 0; i < people; i = i + 1) { // For every person at the
table.
            for (int splits = 0; splits < 2; splits = splits + 1) { // For
every split.
                if (player[i].cardNum[splits] != 0) { // If the hand is active.
                    openHands = openHands + 1; // Increment the number of open
hands.
                }
            }
        }
        if (openHands > 0) { // If there are still open hands.
            dealerTurn(shoe,dealer); // The dealer's turn after all the
player's turns.
            for (int i = 0; i < people; i = i + 1) { // For each player at
the table.
                if (player[i].atTable == true) {
                    cout << "Looking at Player " << numbers[i]
<< "'s cards against the dealer's cards." << endl;
                    playerDealerCheck(player[i],dealer); // Pitting the
player's total against the dealers total.
                }
            }
        }
        for (int i = 0; i < TABLE; i = i + 1) { // The for loop asks if
players want to cash out now.
            if (player[i].atTable == true) {
                do { // User input validation.
                    cout << "Player " << numbers[i] << ",
would you like to cash out? (y/n): ";
                    cin >> yesNo;
                } while (yesNo != 'y' && yesNo != 'n');
                if (yesNo == 'y') {
                    cout << "Player " << numbers[i] << ", you
walk away with $" << player[i].bankRoll << "." << endl;
                    player[i].atTable = false; // Player leaves the table.
                    people = people - 1; // One less person.
                }
            }
        }
    }
}

void playerTurn(bool shoe[DECKS][4][13],person& player,int
playerNumber,person& dealer) { // Player turn simuation.
    char yesNo; // Ask varible.
    string numbers[TABLE] = {"One", "Two", "Three", "Four", "Five"}; // Player
names/numbers.
    string suits[4] = {"Spades", "Hearts", "Clubs", "Diamonds"}; // String
array for names of suits.
    string ranks[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
"Eight", "Nine", "Ten", "Jack", "Queen", "King"}; // String array for names of
ranks.
    cout << "Player " << numbers[playerNumber] << "'s Turn:"
<< endl;
    cout << "Your hand: | ";
    for (int card = 0; card < player.cardNum[0]; card = card + 1) {
        cout << ranks[player.hand[0][card][2]] << " of " <<
suits[player.hand[0][card][1]] << " | ";
    }
    cout << endl;
    cout << "The dealer is showing a " <<
ranks[dealer.hand[0][0][2]] << " of " <<
suits[dealer.hand[0][0][1]] << "." << endl;
    cout << "Your total is " <<
handTotal(player.hand[0],player.cardNum[0]) << "." << endl;
    if (continuePlay(player,0) == false) { // Checks if the player has a
winning condition.
        return;
    }
    if (player.hand[0][0][2] == player.hand[0][1][2]) {
        do { // User input validation.
            cout << "You can split. Would you like to split? (y/n): ";
            cin >> yesNo;
        } while (yesNo != 'y' && yesNo != 'n');
        if (yesNo == 'y') {
            if (player.bankRoll < (2 * player.bet[0])) { // Split only
possible if the player has enough to match original bet.
                cout << "Sorry. You don't have enough money to split."
<< endl;
            }
            else if (player.bankRoll < (2 * player.bet[0])) {
                for (int value = 0; value < 3; value = value + 1) {
                    player.hand[1][1][value] = player.hand[0][1][value];
                    player.hand[0][1][value] = 0; // Second card is moved from
the hand to the split hand.
                }
                player.bet[1] = player.bet[0]; // The split bet is now equal
the original bet.
                player.bankRoll = player.bankRoll - player.bet[1]; // The split
bet is taken from the player's bank roll.
                player.cardNum[1] = 1; // The split hand now has one card.
                shoeDraw(shoe,player.hand[0],player.cardNum[0]); // A card is
drawn to recomplete the original hand.
                shoeDraw(shoe,player.hand[1],player.cardNum[1]); // A card is
drawn to recomplete the split hand.
                if (player.hand[0][player.cardNum[0] - 1][2] == 0 ||
player.hand[0][player.cardNum[0] - 1][2] == 7) {
                    cout << "An " <<
ranks[player.hand[0][player.cardNum[0] - 1][2]] << " of " <<
suits[player.hand[0][player.cardNum[0] - 1][1]] << " is drawn for your
original hand." << endl;
                }
                else {
                    cout << "A " <<
ranks[player.hand[0][player.cardNum[0] - 1][2]] << " of " <<
suits[player.hand[0][player.cardNum[0] - 1][1]] << " is drawn for your
original hand." << endl;
                } // Shows card drawn to orignal hand.
                cout << "Your original hand is now: | ";
                for (int card = 0; card < player.cardNum[0]; card = card +
1) {
                    cout << ranks[player.hand[0][card][2]] << " of
" << suits[player.hand[0][card][1]] << " | ";
                } // Shows the original hand.
                cout << endl;
                cout << "The total of the original hand is " <<
handTotal(player.hand[0],player.cardNum[0]) << "." << endl; //
Shows total of original hand.
                if (player.hand[1][player.cardNum[1] - 1][2] == 0 ||
player.hand[1][player.cardNum[1] - 1][2] == 7) {
                    cout << "An " <<
ranks[player.hand[1][player.cardNum[1] - 1][2]] << " of " <<
suits[player.hand[1][player.cardNum[1] - 1][1]] << " is drawn for your
split hand." << endl;
                }
                else {
                    cout << "A " <<
ranks[player.hand[1][player.cardNum[1] - 1][2]] << " of " <<
suits[player.hand[1][player.cardNum[1] - 1][1]] << " is drawn for your
split hand." << endl;
                } // Shows card drawn to split hand.
                cout << "Your split hand is: | ";
                for (int card = 0; card < player.cardNum[1]; card = card +
1) {
                    cout << ranks[player.hand[1][card][2]] << " of
" << suits[player.hand[1][card][1]] << " | ";
                } // Shows the split hand.
                cout << endl;
                cout << "The total of you split hand is " <<
handTotal(player.hand[1],player.cardNum[1]) << "." << endl; //
Shows total of split hand.
                if (continuePlay(player,0) == true) { // Checks if the player
has a winning condition.
                    cout << "For original hand:" << endl;
                    playerHitStick(shoe,player,playerNumber,0,dealer); // Calls
hitStick of not won or lost.
                }
                if (continuePlay(player,1) == true) { // Checks if the player
has a winning condition.
                    cout << "For split hand:" << endl;
                    playerHitStick(shoe,player,playerNumber,1,dealer); // Calls
hitStick of not won or lost.
                }
                return; // Leaves functions if conditions are met.
            }
        }
    }
    else { // Otherwise a double down is possible.
        if (player.bankRoll == 0) { // If the player has no extra money to
double down.
            playerHitStick(shoe,player,playerNumber,0,dealer); // Proceed
normally.
            return; // Leave function to next player or dealer turn.
        }
        do { // User input validation.
            cout << "Would you like to double down? (y/n): ";
            cin >> yesNo;
        } while (yesNo != 'y' && yesNo != 'n');
        if (yesNo == 'y') {
            double extraBet; // Variable for extra bet to be placed
            do { // User input validation.
                cout << "You have $" << player.bankRoll;
                cout << " and your current bet is $" <<
player.bet[0] << "." << endl;
                cout << "How much extra would you like to bet? (Up to as
much as your existing bet): $";
                cin >> extraBet;
            } while (extraBet > player.bankRoll && extraBet >
player.bet[0]); // The extra bet must be less than or equal to original bet.
            player.bankRoll = player.bankRoll - extraBet; // The extra bet is
taken from the player's bankroll.
            player.bet[0] = player.bet[0] + extraBet; // The extra bet is is
added to the original bet.
            cout << "Your total bet is now $" << player.bet[0]
<< ". One more card is drawn for you." << endl;
            shoeDraw(shoe,player.hand[0],player.cardNum[0]); // Draws one more
card for the player.
            if (player.hand[0][player.cardNum[0] - 1][2] == 0 ||
player.hand[0][player.cardNum[0] - 1][2] == 7) {
                cout << "An " <<
ranks[player.hand[0][player.cardNum[0] - 1][2]] << " of " <<
suits[player.hand[0][player.cardNum[0] - 1][1]] << " is drawn for you."
<< endl;
            }
            else {
                cout << "A " <<
ranks[player.hand[0][player.cardNum[0] - 1][2]] << " of " <<
suits[player.hand[0][player.cardNum[0] - 1][1]] << " is drawn for you."
<< endl;
            } // Shows the card drawn to the hand.
            cout << "Your hand is now: | ";
            for (int card = 0; card < player.cardNum[0]; card = card + 1) {
                cout << ranks[player.hand[0][card][2]] << " of "
<< suits[player.hand[0][card][1]] << " | ";
            } // Shows current hand
            cout << endl;
            cout << "Your total is " <<
handTotal(player.hand[0],player.cardNum[0]) << "." << endl; //
Shows new total.
            continuePlay(player,0);  // Checks if the player has a winning
condition.
            return; // Leave because only one more card can be drawn
        }
        else { // Otherwise, proceed to play normally.
        playerHitStick(shoe,player,playerNumber,0,dealer);
        return; // Leave function to next player or dealer turn.
        }
    }
}

void playerHitStick(bool shoe[DECKS][4][13],person& player,int
playerNumber,int playerHand,person& dealer) { // Hit/Stick cycle simulation.
    string suits[4] = {"Spades", "Hearts", "Clubs", "Diamonds"}; // String
array for names of suits.
    string ranks[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
"Eight", "Nine", "Ten", "Jack", "Queen", "King"}; // String array for names of
ranks.
    char hitStick; // Ask variable
    do { // User input validation.
        cout << "Would you like to hit or stick? (h/s): ";
        cin >> hitStick;
    } while (hitStick != 'h' && hitStick != 's');
    while (hitStick == 'h') { // Player asks to hit.
        shoeDraw(shoe,player.hand[0],player.cardNum[0]); // Card is drawn to
player's hand
        if (player.hand[0][player.cardNum[0] - 1][2] == 0 ||
player.hand[0][player.cardNum[0] - 1][2] == 7) {
            cout << "An " << ranks[player.hand[0][player.cardNum[0]
- 1][2]] << " of " << suits[player.hand[0][player.cardNum[0] -
1][1]] << " is drawn for you." << endl;
        }
        else {
            cout << "A " << ranks[player.hand[0][player.cardNum[0]
- 1][2]] << " of " << suits[player.hand[0][player.cardNum[0] -
1][1]] << " is drawn for you." << endl;
        } // Shows the card drawn.
        cout << "Your hand is now: | ";
        for (int card = 0; card < player.cardNum[0]; card = card + 1) {
            cout << ranks[player.hand[0][card][2]] << " of "
<< suits[player.hand[0][card][1]] << " | ";
        } // Shows the current hand.
        cout << endl;
        cout << "Your total is " <<
handTotal(player.hand[0],player.cardNum[0]) << "." << endl; //
Shows the new total.
        if (continuePlay(player,0) == false) { // Checks the winning condition.
            return;
        }
        do { // User input validation.
            cout << "Would you like to hit or stick? (h/s): ";
            cin >> hitStick;
        } while (hitStick != 'h' && hitStick != 's');
    }
    if (hitStick == 's') { // Player chooses to stick.
        cout << "You stick with a total of " <<
handTotal(player.hand[0],player.cardNum[0]) << "." << endl;
        return;
    }
}

bool continuePlay(person& player,int splits) { // Checks whether to
continue playing.
    if (handTotal(player.hand[splits],player.cardNum[splits]) < 21) { //
Continues if the player hasn't busted.
        return true;
    }
    else if (handTotal(player.hand[splits],player.cardNum[splits]) < 21
&& player.cardNum[splits] >= 4) { // If player has 5 cards and
hasn't busted.
        cout << "You have five cards and haven't busted! You win!"
<< endl;
        player.bankRoll = player.bankRoll + (2.0 * player.bet[splits]); //
Money is added to the bank roll at the pay out rate.
        cout << "You win $" << player.bet[splits] << " from a
1:1 payout." << endl;
        cout << "You now have $" << player.bankRoll << "."
<< endl;
        initializeZero(player.hand[splits]); // Reinitializes hands.
        player.cardNum[splits] = 0; // Reinitializes number cards in the hand.
        player.bet[splits] = 0; // Reinitializes the bet placed.
        return false;
    }
    else if (handTotal(player.hand[splits],player.cardNum[splits]) == 21) { //
If player gets Blackjack.
        cout << "Blackjack! You win!" << endl;
        player.bankRoll = player.bankRoll + (2.5 * player.bet[splits]); //
Money is added to the bank roll at the pay out rate.
        cout << "You win $" << (1.5 * player.bet[splits]) <<
" from a 3:2 payout." << endl;
        cout << "You now have $" << player.bankRoll << "."
<< endl;
        initializeZero(player.hand[splits]); // Reinitializes hands.
        player.cardNum[splits] = 0; // Reinitializes number cards in the hand.
        player.bet[splits] = 0; // Reinitializes the bet placed.
        return false;
    }
    else if (handTotal(player.hand[splits],player.cardNum[splits]) > 21) {
// If player busts.
        cout << "Sorry! Busted!" << endl;
        cout << "You lose $" << player.bet[splits] << "."
<< endl;
        cout << "You now have $" << player.bankRoll << "."
<< endl;
        initializeZero(player.hand[splits]); // Reinitializes hands.
        player.cardNum[splits] = 0; // Reinitializes number cards in the hand.
        player.bet[splits] = 0; // Reinitializes the bet placed.
        return false;
    }
}

void dealerTurn(bool shoe[DECKS][4][13],person& dealer) { // Dealer turn
simulation.
    if (handTotal(dealer.hand[0],dealer.cardNum[0]) == 21) {
        return; // Skips the dealer turn if the dealer already has Blackjack.
    }
    string suits[4] = {"Spades", "Hearts", "Clubs", "Diamonds"}; // String
array for names of suits.
    string ranks[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
"Eight", "Nine", "Ten", "Jack", "Queen", "King"}; // String array for names of
ranks.
    cout << "Now it's the dealer's turn. The dealer flips his hole card."
<< endl;
    while (handTotal(dealer.hand[0],dealer.cardNum[0]) < 17) {
        cout << "The dealer is now showing: | ";
        for (int card = 0; card < dealer.cardNum[0]; card = card + 1) {
            cout << ranks[dealer.hand[0][card][2]] << " of "
<< suits[dealer.hand[0][card][1]] << " | ";
        } // Shows dealer's hand.
        cout << endl;
        cout << "The dealer has a total of " <<
handTotal(dealer.hand[0],dealer.cardNum[0]) << "." << endl; //
Shows dealer total.
        cout << "The dealer has less than a total of 17. The dealer
hits." << endl;
        shoeDraw(shoe,dealer.hand[0],dealer.cardNum[0]); // The dealer draws a
card.
        if (dealer.hand[0][dealer.cardNum[0] - 1][2] == 0 ||
dealer.hand[0][dealer.cardNum[0] - 1][2] == 7) {
            cout << "The dealer draws an " <<
ranks[dealer.hand[0][dealer.cardNum[0] - 1][2]] << " of " <<
suits[dealer.hand[0][dealer.cardNum[0] - 1][1]] << "." << endl;
        }
        else {
            cout << "The dealer draws a " <<
ranks[dealer.hand[0][dealer.cardNum[0] - 1][2]] << " of " <<
suits[dealer.hand[0][dealer.cardNum[0] - 1][1]] << "." << endl;
        } // Show the card the dealer drew.
    }
    cout << "The dealer is now showing: | ";
    for (int card = 0; card < dealer.cardNum[0]; card = card + 1) {
        cout << ranks[dealer.hand[0][card][2]] << " of " <<
suits[dealer.hand[0][card][1]] << " | ";
    } // Shows the dealer's final cards
    cout << endl;
    cout << "The dealer has a total of " <<
handTotal(dealer.hand[0],dealer.cardNum[0]) << "." << endl; //
Shows the final dealer total.
    cout << "The dealer has more than a total of 17. The dealer sticks."
<< endl;
    return;
}

void playerDealerCheck(person& player,person& dealer) { // Checks
player against the dealer.
    for (int splits = 0; splits < 2; splits = splits + 1) {
        if (player.cardNum[splits] != 0) {
            if (splits == 1) {
                cout << "And for your split hand: " << endl;
            }
            if(handTotal(player.hand[splits],player.cardNum[splits]) ==
handTotal(dealer.hand[0],dealer.cardNum[0])) { // Player pushes with the dealer.
                cout << "You tie with the dealer! It's a push!" <<
endl;
                player.bankRoll = player.bankRoll + player.bet[splits]; // Bet
is returned to the bank roll at the pay out rate.
                cout << "You get your $" << player.bet[splits]
<< " back." << endl;
                cout << "You now have $" << player.bankRoll
<< "." << endl;
                initializeZero(player.hand[splits]); // Reinitializes hands.
                player.cardNum[splits] = 0; // Reinitializes number cards in
the hand.
                player.bet[splits] = 0; // Reinitializes the bet placed.
                return;
            }
            else if (handTotal(player.hand[splits],player.cardNum[splits]) >
handTotal(dealer.hand[0],dealer.cardNum[0])) { // Player wins against dealer.
                cout << "You beat the dealer! You win!" << endl;
                player.bankRoll = player.bankRoll + (2.0 * player.bet[splits]);
// Money is added to the bank roll at the pay out rate.
                cout << "You win $" << player.bet[splits] <<
" from a 1:1 payout." << endl;
                cout << "You now have $" << player.bankRoll
<< "." << endl;
                initializeZero(player.hand[splits]); // Reinitializes hands.
                player.cardNum[splits] = 0; // Reinitializes number cards in
the hand.
                player.bet[splits] = 0; // Reinitializes the bet placed.
                return;
            }
            else if (handTotal(player.hand[splits],player.cardNum[splits]) <
handTotal(dealer.hand[0],dealer.cardNum[0])) { // Player loses to dealer.
                cout << "Sorry! The dealer beat you! You lose!" <<
endl;
                cout << "You lost $" << player.bet[splits] <<
"." << endl;
                cout << "You now have $" << player.bankRoll
<< "." << endl;
                initializeZero(player.hand[splits]); // Reinitializes hands.
                player.cardNum[splits] = 0; // Reinitializes number cards in
the hand.
                player.bet[splits] = 0; // Reinitializes the bet placed.
                return;
            }
        }
    }
}

/*---------------------------
    Computation Functions
---------------------------*/

void initializeShoe(bool shoe[DECKS][4][13]) { // Initialize all elements in
the shoe to be true.
    for (int deck = 0; deck < DECKS; deck = deck + 1) {    
        for (int suit = 0; suit < 4; suit = suit + 1) {
            for (int rank = 0; rank < 13; rank = rank + 1) {
                shoe[deck][suit][rank] = true; // For every deck, suit and
rank, the element is true.
            }
        }
    }
}

void initializeZero(int hand[CARDS][3]) { // Initialize all elements in the
hand to be zero.
    for (int card = 0; card < CARDS; card = card + 1) { // For every card,
        for (int value = 0; value < 3; value = value + 1) { // For every
data value,
            hand[card][value] = 0; // The card is zero.
        }
    }
}

void initializeHand(bool shoe[DECKS][4][13],int hand[CARDS][3],int&
cardNum) { // Draws 2 cards from the shoe and places them in a hand.
    cardNum = 0;
    int deck = rollDie(4); // Initialize a random deck.
    int suit = rollDie(4); // Initialize a random suit.
    int rank = rollDie(13); // Initialize a random rank.
    for (int i = 0; i < 2; i = i + 1) { // For two cards being drawn.
        while (shoe[deck][suit][rank] == false) { // Keep rolling the dice
until an existing card is found.
            deck = rollDie(4);
            suit = rollDie(4);
            rank = rollDie(13);
        }
        hand[i][0] = deck; // The card now exists in the hand.
        hand[i][1] = suit;
        hand[i][2] = rank;
        shoe[deck][suit][rank] = false; // The card now ceases to exist in the
shoe.
        cardNum = cardNum + 1; // Number of cards in hand is incremented.
    }
}

void shoeDraw(bool shoe[DECKS][4][13],int hand[CARDS][3],int& cardNum) { //
Draws from the shoe into the hand.
    int deck = rollDie(DECKS); // Initialize a randome deck.
    int suit = rollDie(4); // Initialize a randome suit.
    int rank = rollDie(13); // Initialize a randome rank.
    while (shoe[deck][suit][rank] == false) { // Keep rolling the dice until an
existing card is found.
        deck = rollDie(DECKS);
        suit = rollDie(4);
        rank = rollDie(13);
    }
    hand[cardNum][0] = deck; // The card now exists in the hand.
    hand[cardNum][1] = suit;
    hand[cardNum][2] = rank;
    shoe[deck][suit][rank] = false; // The card now ceases to exist in the shoe.
    cardNum = cardNum + 1; // Number of cards in hand is incremented.
}

int rollDie(int sides) { // Picks a random integer >= 0 and < the
provided argument.
    return rand() % sides;
}

int numberOfCards(bool shoe[DECKS][4][13]) { // Used to count number of cards
in shoe.
    int cardsInShoe = 0; // Variable to count number of cards in array.
    for (int deck = 0; deck < DECKS; deck = deck + 1) { // For every deck.  
 
        for (int suit = 0; suit < 4; suit = suit + 1) { // For every suit.
            for (int rank = 0; rank < 13; rank = rank+ 1) { // For every
rank.
                if (shoe[deck][suit][rank] == true) { // If the card exists,
                    cardsInShoe = cardsInShoe + 1; // Increment the counter.
                }
            }
        }
    }
    return cardsInShoe; // Returns the number cards in the array.
}

int numberOfAces(int hand[CARDS][3],int cardNum) { // Used to cound the number
of aces in the hand.
    int total = 0; // Number of aces is intialized to be zero.
    for (int card = 0; card < cardNum; card = card + 1) { // For every card.
        if (hand[card][2] ==  0) { // If the card is an ace.
            total = total + 1; // Increment the number of aces.
        }
    }
    return total; // Returns the total.
}

int handTotal(int hand[CARDS][3],int cardNum) { // Used to find the total sum
of cards in the hand.
    int total = 0; // The total is initialized to be zero.
    int aces = numberOfAces(hand,cardNum); // The number of aces in the hand.
    for (int card = 0; card < cardNum; card = card + 1) { // For every card
in the hand.
        if (hand[card][2] < 9) { // If it's less than 10.
            total = total + hand[card][2] + 1; // Add the card value to the
total.
        }
        else if (hand[card][2] >= 9) { // If it's greather than 10.
            total = total + 10; // Add 10 to the total.
        }
    }
    total = total + (10 * aces); // The hard total is when the aces have a
value of 11.
    while (total > 21 && aces > 0) { // Take 10 from the total
repeatedly.
        total = total - 10; // For as many aces there are.
        aces = aces - 1; // Until the soft total is reached.
    }
    return total; // Returns the total value.
}
 