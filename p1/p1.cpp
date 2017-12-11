/**
 *
 * @file p1.cpp
 * @author John Poulos, jpoulos2
 *
 * Project 1 for ITCS 3112. Simple Tic-Tac-Toe game.
 *
 *
 */
#include <iostream>


using namespace std;

//Function declarations.
void draw (char* ttt);
void playTicTacToe(char *ttt);
bool gameComplete (char *ttt);

/* Boolean keeping track of whose turn it is */
bool playerATurn;

/**
 *
 * All game logic is contained in this function.
 * Players go back and forth making moves until a winner is declared.
 * After each player makes a move the game checks for a winner. Any invalid
 * inputs (characters or numbers outside of the range) results in a loss of turn.
 *
 * @param *ttt
 *      Pointer to the Tic-Tac-Toe gameboard array.
 *
 */
void playTicTacToe (char *ttt) {
    
    //printf("SWITCHING TURNS\n");
    char guessChar = '\0';
    int guess = 0;
    char temp = '-';
    
    //Player A's turn to make a move.
    if (playerATurn){
        //Get inputs
        cout << "Player A's turn. Please select a number 1-9: ";
        cin >> guessChar;
        guess = guessChar - '0';
        //Invalid guess
        if (guess < 1 || guess > 9){
            cout << "Invalid guess! You lose your turn...\n";
            playerATurn = false;
            playTicTacToe(ttt);
        }
        temp = ttt[guess - 1];
        //printf("VALUE: %c\n", temp);
        if (temp == '-'){
            //printf("Player A VALID\n");
            //ttt[guess - 1] = 'X';
            *(ttt+(guess-1)) = 'X';
            //Check if anyone has won the game.
            if (gameComplete(ttt)){
                draw(ttt);
                cout << "Player A WINS! \n" << endl;
                exit(0);
            } else {
                playerATurn = false;
                draw(ttt);
                playTicTacToe(ttt);
            }
        } else {
            //Space is already occupied.
            cout << "That space is taken! You lose your turn..." << endl;
            playerATurn = false;
            playTicTacToe(ttt);
        }
    }
    
    //Player B's turn to make a move.
    if (!playerATurn){
        //Get inputs
        cout << "Player B's turn. Please select a number 1-9: ";
        cin >> guessChar;
        guess = guessChar - '0';
        //Invalid guess
        if (guess < 1 || guess > 9){
            cout << "Invalid guess! You lose your turn...\n";
            playerATurn = true;
            playTicTacToe(ttt);
        }
        temp = ttt[guess - 1];
        //printf("VALUE: %c\n", temp);
        if (temp == '-'){
            //printf("Player B VALID\n");
            //ttt[guess - 1] = 'O';
            *(ttt+(guess-1)) = 'O';
            //Check if anyone has won the game.
            if (gameComplete(ttt)){
                draw(ttt);
                cout << "Player B WINS! \n" << endl;
                exit(0);
            } else {
                playerATurn = true;
                draw(ttt);
                playTicTacToe(ttt);
            }
        } else {
            //Space is already occupied.
            cout << "That space is taken! You lose your turn..." << endl;
            playerATurn = true;
            playTicTacToe(ttt);
        }
    }
}

/**
 *
 * This function draws the game board to the screen.
 *
 * @param *ttt
 *      Pointer to the Tic-Tac-Toe gameboard array.
 *
 */
void draw(char *ttt) {
    
    for (int k = 0; k < 9; k++) {
        cout << ttt[k];
        if (k == 2 || k == 5 || k == 8){
            cout << "\n";
        }
    }
    cout << endl;
}


/**
 *
 * This function checks whether a player has won the game. 
 * It checks for horizontal, vertical, and diagonal victories. 
 *
 * @param *ttt
 *      Pointer to the Tic-Tac-Toe gameboard array.
 *
 */
bool gameComplete(char *ttt) {
    
    if (ttt[0] == 'X' && ttt[1] == 'X' && ttt[2] == 'X') {
        return true;
    } else if (ttt[3] == 'X' && ttt[4] == 'X' && ttt[5] == 'X') {
        return true;
    } else if (ttt[6] == 'X' && ttt[7] == 'X' && ttt[8] == 'X') {
        return true;
    } else if (ttt[0] == 'X' && ttt[3] == 'X' && ttt[6] == 'X') {
        return true;
    } else if (ttt[1] == 'X' && ttt[4] == 'X' && ttt[7] == 'X') {
        return true;
    } else if (ttt[2] == 'X' && ttt[5] == 'X' && ttt[8] == 'X') {
        return true;
    } else if (ttt[0] == 'X' && ttt[4] == 'X' && ttt[8] == 'X') {
        return true;
    } else if (ttt[2] == 'X' && ttt[4] == 'X' && ttt[6] == 'X') {
        return true;
    } else if (ttt[0] == 'O' && ttt[1] == 'O' && ttt[2] == 'O') {
        return true;
    } else if (ttt[3] == 'O' && ttt[4] == 'O' && ttt[5] == 'O') {
        return true;
    } else if (ttt[6] == 'O' && ttt[7] == 'O' && ttt[8] == 'O') {
        return true;
    } else if (ttt[0] == 'O' && ttt[3] == 'O' && ttt[6] == 'O') {
        return true;
    } else if (ttt[1] == 'O' && ttt[4] == 'O' && ttt[7] == 'O') {
        return true;
    } else if (ttt[2] == 'O' && ttt[5] == 'O' && ttt[8] == 'O') {
        return true;
    } else if (ttt[0] == 'O' && ttt[4] == 'O' && ttt[8] == 'O') {
        return true;
    } else if (ttt[2] == 'O' && ttt[4] == 'O' && ttt[6] == 'O') {
        return true;
    } else {
        return false;
    }
    
}


/*
 *
 * Main function for the program. Initializes the gameboard
 * and displays the welcome message and instructions.
 *
 */
int main() {
    
    //Initialize the actual gameboard
    char tic_tac_toe[9] = {'-','-','-','-','-','-','-','-','-'};
    //Create a gameboard for instructional purposes.
    char tic_tac_toe_initial[9] = {'1','2','3','4','5','6','7','8','9'};
    
    //Set pointers to each arrray so they can be passed to other functions.
    char *ttt = tic_tac_toe;
    char *initial = tic_tac_toe_initial;
    
    //Welcome and instructions.
    cout << "WELCOME TO TIC-TAC-TOE" << endl;
    cout << "Player A is 'X' and player B is 'O' " << endl;
    cout << "Select your position based on this number grid." << endl;
    cout << "Good luck and have fun! \n" << endl;
    
    draw(initial);
    
    playerATurn = true;
    playTicTacToe(ttt);
    
    return 0;
}
