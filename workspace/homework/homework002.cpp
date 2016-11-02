#include<iostream>
#include<cstdlib>

using namespace std;

int game(); // Where the game is run.
void playerCardDraw(); // Draws and and checks face cards and aces for the player.
void dealerCardDraw(); // Draws and and checks face cards and aces for the dealer.
int playerCards(int);  // Adds to and keeps track of players hand, total and aces.
int dealerCards(int);  // Adds to and keeps track of dealers hand, total and aces.
int playerCheck();  // Checks various outcomes for the player.
int dealerCheck();  // Checks various outcomes for the dealer.

int playerTotal = 0; // Value of players hand.
int dealerTotal = 0; // Value of dealers hand.
int playerAces = 0;  // How many aces player has.
int dealerAces = 0;  // How many aces dealer has.
double playerMoney = 100; // Players bank roll.
double bet;  // Players bet for hand.
char contYesNo = 'a'; // To check if player wants to continue playing or not.
char hitStick = 'a';  // To check if player wants to hit or stick.
bool gameEnd = false; // To check if the game has ended.


int main() {
    
    cout << "Welcome to Blackjack!" << endl;
    
    cout << "You start with $100" << endl;
    
    game();
    
    return 0;
}

int game() {
    
while (playerMoney != 0) { // Loops when player has bankroll of more than zero.
    
    if (gameEnd == true) { // Endgame check.. Makes sure program terminates.
        
        return 0;
        
    }
    
    else if (gameEnd == false) { // Endgame check.. Makes sure program terminates.
    
    cout << "You have $" << playerMoney << ", please place a bet." << endl;
    
    cin >> bet;
    
    while (bet > playerMoney) { // Does not allow bets greater than bankroll.
        
        cout << "Sorry, you don't have enough money to place this bet. Please place another bet." << endl;
        
        cin >> bet;
        
    }
    
    cout << "Thanks for placing a bet." << endl;
    
    playerMoney = playerMoney - bet; // Takes value of bet from playter bankroll.
    
    cout << "You have been dealt a ";
    
    playerCardDraw(); // Draws a card for player.
    
    cout << " and a ";
    
    playerCardDraw(); // Draws a card for player.
    
    cout << "." << endl;
    
    cout << "Dealer is showing a ";
    
    dealerCardDraw(); // Draws a card for dealer.
    
    cout << "." << endl;
    
    cout << "Your current total value is " << playerTotal << "." << endl;
    
    playerCheck(); // Runs outcomes for player after initial draw.
    }
    }
    
    cout << "Acutally. Sorry. You have run out of money. Thanks for playing Blackjack. Bye bye." << endl; // End of bankroll.

    return 0;
}

void playerCardDraw() {
    
    int card = 1 + (rand() % 13); // Random value from 1 to 13.
    
    if (card == 1) { // Ace output.
    
    cout << "A";
    
    playerCards(card); // Call function with value of card.
    
    }
    
    else if (card == 11) {  // Face card output.
    
    cout << "J";
    
    playerCards(card); // Call function with value of card.
    
    }
    
    else if (card == 12) {  // Face card output.
    
    cout << "Q";
    
    playerCards(card); // Call function with value of card.
    
    }
    
    else if (card == 13) {  // Face card output.
    
    cout << "K";
    
    playerCards(card); // Call function with value of card.
    
    }
    
    else {
    
    cout << card; // Value card output.
    
    playerCards(card); // Call function with value of card.
    
    }
    
}

void dealerCardDraw() { // Same as player function but calls dealer card counter.
    
    int card = 1 + (rand() % 13);
    
    if (card == 1) {
    
    cout << "A";
    
    dealerCards(card);
    
    }
    
    else if (card == 11) {
    
    cout << "J";
    
    dealerCards(card);
    
    }
    
    else if (card == 12) {
    
    cout << "Q";
    
    dealerCards(card);
    
    }
    
    else if (card == 13) {
    
    cout << "K";
    
    dealerCards(card);
    
    }
    
    else {
    
    cout << card;
    
    dealerCards(card);
    
    }
    
}

int playerCards(int n) {
    
    if (n == 11||n == 12||n == 13) {  // Adds face cards to player total.
         
        playerTotal = playerTotal + 10;
        
    }
    
    else if (n == 1) { // Adds Aces to player total and counts aces.
        
        playerTotal = playerTotal + 11;
        
        playerAces = playerAces + 1;
    }
    
    else { // Adds value to player total.
        
        playerTotal = playerTotal + n;
        
    }
}

int dealerCards(int n) {
    
    if (n == 11||n == 12||n == 13) {  // Adds face cards to dealer total.
         
        dealerTotal = dealerTotal + 10;
        
    }
    
    else if (n == 1) { // Adds Aces to dealer total and counts aces.
        
        dealerTotal = dealerTotal + 11;
        
        dealerAces = dealerAces + 1;
    }
    
    else { // Adds value to dealer total.
        
        dealerTotal = dealerTotal + n;
        
    }
}

int playerCheck() {
    
    if (playerTotal > 21) { // Cases if player total greater than 21.
        
        if (playerAces > 0) { // Checks for soft aces and takes ten off for every ace so the pla
        
        playerTotal = playerTotal - 10;
        
        cout << "Soft aces. You don't bust. Your total is now " << playerTotal << "." << endl;
        
        playerAces = playerAces - 1; // Takes on off the soft aces player has.
        
        playerCheck(); // Checks player again
        
        }
        
        else { // Busts if there are no soft aces to play.
        
        cout << "Sorry, you've busted." << endl;
        
        playerTotal = 0; // Hand reset.
        dealerTotal = 0;
        playerAces = 0;
        dealerAces = 0;
        
        while (contYesNo != 'y'&&contYesNo != 'n') {
            
            if (gameEnd == true) {  // Endgame check.
                
                return 0;
                
            }
        
        cout << "Would you like to continue playing? (Press y or n)" << endl; // Asks player if they want to be dealt another hand.
        
        cin >> contYesNo;
        
        if (contYesNo == 'y') {
            
            cout << "Great! Let's continue." << endl;
            
            contYesNo = 'a'; // Reset ask counter.
            
            if (playerMoney == 0) {  // Endgame check.
            
            game();
            
            gameEnd = true;
            
            return 0;
            
            }
            
            else {
                
                game();
                
            }
            
        }
        
        else if (contYesNo == 'n') { // Game ends
            
            cout << "Thanks for playing Blackjack. You walk away from the table with $" << playerMoney << ". Bye bye." << endl;
            
            gameEnd = true;
            
        }
        
    }
    
        }
    
    }
    
    else if (playerTotal == 21) { // Checks for player blackjack.
        
        cout << "Blackjack! You win!" << endl;
        
        playerTotal = 0; // Hand reset.
        dealerTotal = 0;
        playerAces = 0;
        dealerAces = 0;
        
        playerMoney = playerMoney + (2 * bet); // Adds money to player bankroll.
        
        while (contYesNo != 'y'&&contYesNo != 'n') {
            
            if (gameEnd == true) {
                
                return 0;
                
            }
        
        cout << "Would you like to continue playing? (Press y or n)" << endl;  // Asks player if they want to be dealt another hand.
        
        cin >> contYesNo;
        
        if (contYesNo == 'y') {
            
            cout << "Great! Let's continue." << endl;
            
            contYesNo = 'a'; // Reset ask counter.
            
            if (playerMoney == 0) { // Endgame check.
            
            game();
            
            gameEnd = true;
            
            return 0;
            
            }
            
            else {
                
                game();
                
            }
            
        }
        
        else if (contYesNo == 'n') {
            
            cout << "Thanks for playing Blackjack. You walk away from the table with $" << playerMoney << ". Bye bye." << endl;
            
            gameEnd = true;
            
        }
       
        }
    }
    
    
    else if (playerTotal < 21) {
        
        while (hitStick != 'h'&&hitStick != 's') {
            
            if (gameEnd == true) { // End game check.
                
                return 0;
                
            }
        
        cout << "Would you like to hit or stick? (Press h or s)" << endl; // Asks player if they want to hit or stick.
        
        cin >> hitStick;
        
        if (hitStick == 'h') { // Player hit option
            
            cout << "You recieve a ";
            
            playerCardDraw(); // Player draws card.
            
            cout << " bringing your total to " << playerTotal << "." << endl;
            
            hitStick = 'a'; // Reset ask counter.
            
            playerCheck(); // Rechecks player
            
        }
        
        else if (hitStick == 's') { // Player stick option.
            
            cout << "Sticking at " << playerTotal << ".." << endl;
            
            hitStick = 'a'; // Reset ask counter.
            
            cout << "Dealer shows his other card, a ";
            
            dealerCardDraw(); // Dealer shows other card.
            
            cout << ". Dealer's total is " << dealerTotal << "." << endl;
            
            dealerCheck(); // Checks dealer's cases. Dealer begins hand after player sticks.
        }
        
        
    }
        
        
    }
}

int dealerCheck() {
    
    if (dealerTotal > 21) { // Cases if dealer total greater than 21.
    
    if (dealerAces > 0) { // Checks for soft aces and takes ten off for every ace so the dealer doesnt bust
        
        dealerTotal = dealerTotal - 10;
        
        cout << "Soft aces. Dealer doesn't bust. Dealer total is now " << dealerTotal << "." << endl;
        
        dealerAces = dealerAces - 1; // Takes on off the soft aces dealer has.
        
        dealerCheck(); // Rechecks dealer.
        
        }
        
        else { // This case the dealer busts. There are no soft aces to play.
            
        cout << "Dealer busts! You win!" << endl;
        
        playerMoney = playerMoney + (2 * bet); // Adds money to player bankroll
        
        playerTotal = 0; // Hand reset
        dealerTotal = 0;
        playerAces = 0;
        dealerAces = 0;
        
        while (contYesNo != 'y'&&contYesNo != 'n') {
            
            if (gameEnd == true) { // Endgame check.
                
                return 0;
                
            }
        
        cout << "Would you like to continue playing? (Press y or n)" << endl; // Asks player if they want to be dealt another hand.
        
        cin >> contYesNo;
        
        if (contYesNo == 'y') {
            
            cout << "Great! Let's continue." << endl;
            
            contYesNo = 'a'; // Reset ask counter.
            
            if (playerMoney == 0) {  // Endgame check.
            
            game();
            
            gameEnd = true;
            
            return 0;
            
            }
            
            else {
                
                game();
                
            }
            
        }
        
        else if (contYesNo == 'n') {
            
            cout << "Thanks for playing Blackjack. You walk away from the table with $" << playerMoney << ". Bye bye." << endl;
            
            gameEnd = true;
            
            }
        
        }
        }
}
    
    else if (dealerTotal == 21) { // This case the dealer gets blackjack. You must stick at some value less than 21 for this to occur
        
        cout << "Dealer Blackjack! You lose!" << endl;
        
        playerTotal = 0; // Hand reset.
        dealerTotal = 0;
        playerAces = 0;
        dealerAces = 0;
        
        while (contYesNo != 'y'&&contYesNo != 'n') {
            
            if (gameEnd == true) { // Endgame check.
                
                return 0;
                
            }
        
        cout << "Would you like to continue playing? (Press y or n)" << endl; // Asks player if they want to be dealt another hand.
        
        cin >> contYesNo;
        
        if (contYesNo == 'y') {
            
            cout << "Great! Let's continue." << endl;
            
            contYesNo = 'a'; // Reset ask counter.
            
            if (playerMoney == 0) {  // Endgame check.
            
            game();
            
            gameEnd = true;
            
            return 0;
            
            }
            
            else {
                
                game();
                
            }
            
        }
        
        else if (contYesNo == 'n') {
            
            cout << "Thanks for playing Blackjack. You walk away from the table with $" << playerMoney << ". Bye bye." << endl;
            
            gameEnd = true;
            
        }
       
        }
    }
    
    else if (dealerTotal < 21 && dealerTotal >= 17) { // When dealer stops dealing to themselves without busting, check who has a total.
        
        if (playerTotal > dealerTotal) { // Player wins.
            cout << "You win!" << endl;
        
        playerMoney = playerMoney + (2 * bet); // Adds money to player bankroll.
        
        playerTotal = 0; // Hand reset
        dealerTotal = 0;
        playerAces = 0;
        dealerAces = 0;
        
        while (contYesNo != 'y'&&contYesNo != 'n') {
            
            if (gameEnd == true) { // Endgame check.
                
                return 0;
                
            }
        
        cout << "Would you like to continue playing? (Press y or n)" << endl; // Asks player if they want to be dealt another hand.
        
        cin >> contYesNo;
        
        if (contYesNo == 'y') {
            
            cout << "Great! Let's continue." << endl;
            
            contYesNo = 'a'; // Reset ask counter.
            
            if (playerMoney == 0) {  // Endgame check.
            
            game();
            
            gameEnd = true;
            
            return 0;
            
            }
            
            else {
                
                game();
                
            }
            
        }
        
        else if (contYesNo == 'n') {
            
            cout << "Thanks for playing Blackjack. You walk away from the table with $" << playerMoney << ". Bye bye." << endl;
            
            gameEnd = true;
            
        }
        }
    }
    
    else if (playerTotal < dealerTotal) { // Neitehr bust or blackjack. Dealer has higher total.
        cout << "Sorry, you've lost to the dealer." << endl;
        
        playerTotal = 0; // Hand reset.
        dealerTotal = 0;
        playerAces = 0;
        dealerAces = 0;
        
        while (contYesNo != 'y'&&contYesNo != 'n') {
            
            if (gameEnd == true) {  // Endgame check.
                
                return 0;
                
            }
        
        cout << "Would you like to continue playing? (Press y or n)" << endl; // Asks player if they want to be dealt another hand.
        
        cin >> contYesNo;
        
        if (contYesNo == 'y') {
            
            cout << "Great! Let's continue." << endl;
            
            contYesNo = 'a'; // Reset ask counter.
            
            if (playerMoney == 0) {  // Endgame check.
            
            game();
            
            gameEnd = true;
            
            return 0;
            
            }
            
            else {
                
                game();
                
            }
            
        }
        
        else if (contYesNo == 'n') {
            
            cout << "Thanks for playing Blackjack. You walk away from the table with $" << playerMoney << ". Bye bye." << endl;
            
            gameEnd = true;
            
        }
    }
    
}
    else if (playerTotal == dealerTotal) { // Dealer player tie.
        cout << "You tie with the dealer!" << endl;
        
        playerMoney = playerMoney + bet; // Player gets recredited the bet placed.
        
        playerTotal = 0; // Hand reset.
        dealerTotal = 0;
        playerAces = 0;
        dealerAces = 0;
        
        while (contYesNo != 'y'&&contYesNo != 'n') {
            
            if (gameEnd == true) {  // Endgame check.
                
                return 0;
                
            }
        
        cout << "Would you like to continue playing? (Press y or n)" << endl; // Asks player if they want to be dealt another hand.
        
        cin >> contYesNo;
        
        if (contYesNo == 'y') {
            
            cout << "Great! Let's continue." << endl;
            
            contYesNo = 'a'; // Reset ask counter.
            
            if (playerMoney == 0) {  // Endgame check.
            
            game();
            
            gameEnd = true;
            
            return 0;
            
            }
            
            else {
                
                game();
                
            }
            
        }
        
        else if (contYesNo == 'n') {
            
            cout << "Thanks for playing Blackjack. You walk away from the table with $" << playerMoney << ". Bye bye." << endl;
            
            gameEnd = true;
            
        }
    }
    
}
}
    
    else {
    
    while (dealerTotal < 17) { // Dealer draws another card if dealer total is less than 17.
        
        cout << "Dealer draws a ";
        
        dealerCardDraw(); // Dealer draws card.
        
        cout << ". Total is now " << dealerTotal << "." << endl;
        
        }
        dealerCheck(); // Rechecks cases for dealer every card draw.
    }

}
