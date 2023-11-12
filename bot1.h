#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "freeTree.h"
#include "coinToss.h"
/*
Precondition: int min and int max with min < max and both < number of nodes in BST
Postcondition:returns random number, used for modified search
*/
int randomNum(int min, int max)
{
    int random_number = rand() % (max - min + 1) + min; //random number between min and max inclusive
    return random_number;
}
/*
Precondition: pointer to a node in BST, character prev not equal to null and array of the number of spells left depending on the letter of size 26
Postcondition: returns a node pointer to a spell in the tree
*/
node *modifiedSearch(node *root, char prev, int spellsLeft[])
{ 

    if (root == NULL)
    {
        fprintf(stderr, "Error: Root is NULL in modifiedSearch function.\n");
        // exit the program
        exit(EXIT_FAILURE);
    }

    if (root == NULL)
        return NULL; // should never be reached, possible error. might need to add print error
    if (root->left == NULL && root->right == NULL)
        return root;

    if (root->spell[0] == prev)
    {
        int randnum;
        randnum = randomNum(1, spellsLeft[prev - 'a']); // random num to decide which of the spells to use
        for (int i = 1; i <= randnum; i++)
        {
            if (root->left == NULL && root->right == NULL)
                break; // nowhere else to go, pick the root spell
            if (root->left == NULL)
                root = root->right; // can't go left, go right
            else if (root->right == NULL)
                root = root->left; // can't go right, go left
            else
            { // can go either way, random choice
                if (coinToss() == 0)
                {
                    root = root->right;
                }
                else
                {
                    root = root->left;
                }
            }
        }
        return root;
    }
    else if (root->spell[0] > prev)
        return modifiedSearch(root->left, prev, spellsLeft);
    else
        return modifiedSearch(root->right, prev, spellsLeft);
}
