#include "bot1.h"
/*
Precondition: two strings of the players' names, a node pointer to the BST root and array of the number of spells left depending on the letter of size 26
Postcondition: return 0 if player 1 wins and 1 if player 2 wins
*/
int runGame(char player1[], char player2[], node *spellsTreeRoot, int spellsLeft[])
{

    char prev = ' ';
    char move[50];

    // starting the game with first player
    printf("\n%s starts!\nEnter your first move: ", player1);
    scanf("%s", move);
    int result1 = checkMove(spellsTreeRoot, prev, move, spellsLeft);
    // int result1 = checkMove(spell, row, prev, move);

    // continuing the game with second player
    while (result1 == 1)
    {
        printf("%s's turn!\n", player2);
        prev = move[strlen(move) - 1];
        printf("%s! Enter your next move: ", player2);
        scanf("%s", move);
        int result2 = checkMove(spellsTreeRoot, prev, move, spellsLeft);
        prev = move[strlen(move) - 1];
        if (result2 == -1)
        {
            printf("%s loses! %s wins! congratulations!", player2, player1);
            return 0; // player 1 wins
        }
        else
        {
            printf("%s!\nEnter your next move: ", player1);
            scanf("%s", move);
            result1 = checkMove(spellsTreeRoot, prev, move, spellsLeft);
            prev = move[strlen(move) - 1];
        }
    }
    printf("%s loses! %s wins! congratulations!", player1, player2); // player 2 wins
    return 1;
}
/*
Precondition: one string of the player's name, a node pointer to the BST root and array of the number of spells left depending on the letter of size 26
Postcondition: returns 0 if player 1 wins and 1 if bot wins
*/
int runGame2(char player1[], node *spellsTreeRoot, int spellsLeft[])
{ // modified version with the bot
    char prev = ' ';
    char move[50];
    printf("%s\nEnter your first move: ", player1);
    scanf("%s", move);
    int result1 = checkMove(spellsTreeRoot, prev, move, spellsLeft);
    while (result1 == 1)
    {
        printf("bot's turn!\n");
        prev = move[strlen(move) - 1];
        node *spell = modifiedSearch(spellsTreeRoot, prev, spellsLeft); // spell returned by the bot
        printf("bot chose: %s\n", spell->spell);
        int result2 = checkMove(spellsTreeRoot, prev, spell->spell, spellsLeft);
        prev = spell->spell[strlen(spell->spell) - 1];
//for testing only
printf("\nTEST: bot's last char: %c\n", prev);
        if (result2 == -1)
        {
            printf("bot loses! %s wins! congratulations!", player1);
            return 0; // player 1 wins
        }
        else
        {
            printf("%s!\nEnter your next move: ", player1);
            scanf("%s", move);
            result1 = checkMove(spellsTreeRoot, prev, move, spellsLeft);
            prev = move[strlen(move) - 1];
        }
    }
    printf("%s loses! bot wins! congratulations!", player1);
    return 1;
}
