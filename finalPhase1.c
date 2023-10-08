/*
clueless ~ Mira Hussein, Haya Mouneimne, Mariam Sonji
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//defining a custom datatype to store the spells and whether they have been used
typedef struct Element elements;
struct Element
{
    char name[50];
    int used;
};

int getRowNumber(char fileName[])
{
    FILE *sptr;
    sptr = fopen(fileName, "r");
    if (sptr == NULL)
    {
        perror("fopen");
        exit(1);
    }
    int lines = 0;
    int ch;
    int prev = EOF;                   // Initialize to end of file
    while ((ch = fgetc(sptr)) != EOF) // To get the number of lines in the file
    {
        if (ch == '\n')
        {
            lines++;
        }
        prev = ch;
    }
    if (prev != '\n' && prev != EOF) // to get the last element
    {
        lines++;
    }
    fclose(sptr);
    return lines;
}

elements *createAndFill(char fileName[], int rowNumber)
{

    FILE *sptr;
    int maxLength = 50; // string maximum number of character
    elements *spell = (elements *)malloc(sizeof(elements) * rowNumber);
    sptr = fopen("spells.txt", "r");
    if (sptr == NULL)
    {
        perror("fopen");
        exit(1);
    }
    int i = 0;

    while (i < rowNumber && fscanf(sptr, "%s", spell[i].name) == 1) // returns 1 if the scan is succesful so if file was not read 0 will be returned instead
    {
        spell[i].used = 0;
        i++;
    }
    fclose(sptr);
    return spell;
}

void printArray(elements *spell, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        printf("%s\t", spell[i].name);
        if ((i + 1) % columns == 0)
        {
            printf("\n");
        }
    }
}

int checkMove(elements *spell, int spellCount, char previousChar, char move[])
{
    // looping through the rows (spells); checks if it was found and if it was cast
    for (int i = 0; i < spellCount; i++)
    {
        // checking if the spell cast is in the list
        if (strcmp(spell[i].name, move) == 0)
        {                // if the spell is found, goes on to check if it has been used
            if (spell[i].used == 1)
            {                // if the spell has been used before
                printf("spell was already used! you lose!\n");
                return -1;
            }
            else
            {
                spell[i].used = 1; // if the spell was not used before, modifies array to update it
                if (move[0] != previousChar && previousChar != ' ') // checks the first char against the previous char
                {                      
                    printf("spell starts with the wrong character! you lose!\n");
                    return -1;
                }else{
                    printf("valid spell!\n");
                    return 1; //returns 1 for valid spell
                }
            }
        }
    }
    printf("spell is not in the list! you lose!\n");
    return -1;

}
int coinToss() { //function to decide which player goes first by 'tossing a coin' by generating a random number
    srand(time(NULL)); //seed with the current time to get different results at different runs
    int randomnumber;
    randomnumber = rand() % 2;
    return randomnumber;
}

int runGame(char player1[], char player2[], elements *spell, int row){

    char prev = ' ';
    char move[50];
    
    //starting the game with first player
    printf("%s starts!\nEnter your first move: ", player1);
    scanf("%s", move);
    int result1 = checkMove(spell, row, prev, move);

    //continuing the game with second player
    while (result1 == 1)
    {
        printf("%s's turn!\n", player2);
        prev = move[strlen(move)-1];
        printf("%s! Enter your next move: ", player2);
        scanf("%s", move);
        int result2 = checkMove(spell, row, prev, move);
        if(result2 == -1){
            printf("%s loses! %s wins! congratulations!", player2, player1);
            return 0; //player 1 wins
        }else{
            printf("%s!\nEnter your next move: ", player1);
            scanf("%s", move);
        }
    }
    printf("%s loses! %s wins! congratulations!", player1, player2); //player 2 wins
    return 1;

}


int main()
{

    printf("Welcome to the Spell Master game!\n"); //welcome message

    //inputting player names
    char player1[20];
    char player2[20];
    printf("Player 1, enter your name: ");
    scanf("%s",player1);
    printf("Player 2, enter your name: ");
    scanf("%s",player2);

    //printing table of spells
    printf("below is a list of spells you may use:\n");
    int row = getRowNumber("spells.txt");
    elements *spell = createAndFill("spells.txt,", row);
    printArray(spell, row, 5);

    //tossing the coin to decide which player begins
    int randNum = coinToss();
    if(randNum == 0){
        runGame(player1, player2, spell, row);
    }else{
        runGame(player2, player1, spell, row);
    }

    return 0;

}
