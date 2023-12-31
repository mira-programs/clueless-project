#include "createSpellsTree.h"
/*
Precondition: pointer to the root node of BST not equal to null, char previousChar, String of the spell to be checked and array of the number of spells left depending on the letter of size 26
Postcondition: return 1 if spell is valid and -1 if spell is invalid (cast before, starts with wrong character or not in list)
*/
int checkMove(node *spellTree, char previousChar, char *spell, int spellsLeft[])
{
    // searching the tree for the spell that was cast
    node *move = search(spellTree, spell);
    if (move != NULL)
    { // if found...
        if (move->used == 1)
        { // if spell was cast before (invalid)
            printf("spell was already used! you lose!\n");
            return -1;
        }
        else
        { // if spell was not cast before (valid)
            move->used = 1;
            // this part updates the array keeping track of the spells left of each character
            char firstLetter = move->spell[0];
            if ('a' <= firstLetter && firstLetter <= 'z') // ensures it is in right range
            {
                // update the count, subtract one
                spellsLeft[firstLetter - 'a']--;
            }
            // continues checks
            if (spell[0] != previousChar && previousChar != ' ')
            { // if spell starts with the wrong char (invalid)
                printf("spell starts with the wrong character! you lose!\n");
                return -1;
            }
            else
            { // if spell is valid
                printf("valid spell!\n");
                return 1; // returns 1 for valid spell
            }
        }
    }
    else
    { // if the spell is not found
        printf("spell is not in the list! you lose!\n");
        return -1;
    }
}
