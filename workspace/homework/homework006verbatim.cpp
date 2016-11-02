/*------------------------------------------------------------------------------
main:
Simulates multiple games of BlackJack, as many as the user desires
Inputs (from the keyboard) :
    yesNo   (char) whether the user whishes to play again
Calls: playBlackJack

playBlackJack:
Simulates one complete game of BlackJack
Player and computer draw 2 cards
then player starts by deciding to do something.
Parameters:
    decisionVal (input int) A value is assigned to a decision to make a funciton call
    deck    (int array) Deck of cards
    playerHand  (int array) Player hand
    computerHand    (int array) Computer hand
Calls: initializeDeck, initializeHand, evaluate

initializeDeck:
Creates an array to store the cards.
Parameters:
    deck    (int array) Deck of cards
Passes by reference an array representing a deck of 208 cards.

initializeHand:
Draws random hands from the deck
Parameters:
    deck    (int array) Deck of cards
    hand    (int array) Hand of cards
Calls: rollDie, clearNthPos
Returns by reference an array representing a starting hand and remaining deck

rollDie:
Picks a random position in the deck to pick a card from
Parameters:
    sides   (input int) Indicates how many cards left.
Returns an integer value from 0 to one minus size of remaining deck

clearNthPos:
Clears the Nth position in the array 
and moves all non-zero values to the front.
Parameters:
    size   (input int) Indicates size of array to be cleared.
Calls: none

playerCheck:
Checks various outcomes for the player.
Parameters:
    hand    (int array) Hand of cards
Calls: none

dealerCheck:
Checks various outcomes for the dealer.
Parameters:
    hand    (int array) Hand of cards
Calls: none

deckDraw:
Draws random cards from the deck into the hands
Parameters:
    deck    (int array) Deck of cards
    hand    (int array) Hand of cards
Calls: rollDie, clearNthPos
Returns by reference an array representing a starting hand and remaining deck

handValue:
Calculates the value of the hand.
Parameters:
    hand (int array) Hand of cards
Calls: none
Passes by reference the hand.

hit:
Simulates the hit decision.
Parameters:
    hand (int array) Hand of cards
Calls: deckDraw
Passes by reference the hand.

stick:
Simulates the stick decision.
Parameters:
    hand (int array) Hand of cards
Calls: none
Passes by reference the hand.

doubleDown:
Simulates doubling down.
Parameters:
    hand (int array) Hand of cards
Calls: deckDraw
Passes by reference the hand.

split:
Simulates splitting.
Parameters:
    hand (int array) Hand of cards
Calls: deckDraw
Passes by reference the hand.

bankRoll:
Keeps track of the player bank roll and adds winnings and subtracts bets.
Parameters:
    playerMoney (int) Total value of players money.
Calls: none
Returns by reference playerMoney.

------------------------------------------------------------------------------*/