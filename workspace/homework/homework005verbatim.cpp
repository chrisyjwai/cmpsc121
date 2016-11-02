/*------------------------------------------------------------------------------
main:
Simulate multiple games of Go Fish, as many as the user desires
Inputs (from the keyboard) :
    yesNo   (char) whether the user whishes to play again
Calls: playGoFish

playGoFish:
Simulates one complete game of Go Fish
Player and computer draw 8 cards
then player starts by asking for a rank
Parameters:
    cardAsk (input int) Card ask value
    deck    (int array) Deck of cards
    playerHand  (int array) Player hand
    computerHand    (int array) Computer hand
Calls: initializeDeck, initializeHand, evaluate, passCard

initializeDeck:
Creates an array to store the cards.
Parameters:
    deck    (int array) Deck of cards
Passes by reference an array representing a deck of 32 cards.

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

passCard:
Passing a card from one hand to another.
Parameters:
    passHand  (int array) Hand to recieve cards
    recieveHand    (int array) Hand to pass cards
    card    (int) Card to pass
Calls: clearNthPos
Returns by reference the modified hands.

evaluate:
Evaluates whether a hand has a winning condition
Parameters:
    hand    (int array) Hand of cards
Calls: none
------------------------------------------------------------------------------*/