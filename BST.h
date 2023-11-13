#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{             // defines a BST node
    int used; // used variable indicates if spell was cast before. set to 1 if cast before, 0 otherwise
    struct node *left;
    struct node *right;
    int height;
    char *spell;
} node;

/*
precondition: a char pointer to the spell (string) we want to add to the tree.
postcondition: a new node containing the spell with nitialized needed data.
*/
node *newNode(char *s)
{                                           // creates a new node. s is the spell being added
    node *n = (node *)malloc(sizeof(node)); // creates pointer to new node n and allocates memory
    n->spell = s;                           // defines the new node with the new spell
    n->left = NULL;                         // initializes pointers to left and right children to NULL
    n->right = NULL;
    n->height = 1; // initializes height to 1
    n->used = 0;   // initializes used to 0, initially all spells are not cast yet
    return n;
}

/*
precondition: pointer to a node
postcondition: if the node doesn't exist (if the pointer is a null pointer) the height is 0, otherwise we give back the height from the node's data.
*/
int height(node *n)
{ // gets the height of a node
    if (n == NULL)
        return 0;
    return n->height;
}

/*
precondition: node pointer.
postcondition: will return the balance of the tree starting from the given node.
*/
int getBalance(node *n)
{ // calculates balance factor of node n
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

/*
precondition: given two integers a and b.
postcondition: returns which of the two (a or b) is larger (the maximum out of the two).
*/
int max(int a, int b)
{                           // max function, used to calculate height in insert function
    return (a > b) ? a : b; // returns the max of the two integers
}

/*
precondition: node pointer; a BST in which one of the nodes violates the BST conditions or on unbalanced trees.
postcondition: corrected BST in which every node's left child is smaller than it and every right child is larger than it. Correction is done by rotating the given node to the left.
*/
node *leftRotate(node *x)
{ // left-rotation performed on (sub)tree of root x
    // creating pointers to the relevent subtrees/nodes
    node *y = x->right;
    node *T2 = y->left;
    // performing rotation
    y->left = x;
    x->right = T2;
    // updating heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // returns y, the new root
}

/*
precondition: node pointer; a BST in which one of the nodes violates the BST conditions or on unbalanced trees.
postcondition: corrected BST in which every node's left child is smaller than it and every right child is larger than it. Correction is done by rotating the given node to the right.
*/
node *rightRotate(node *y)
{ // right-rotation performed on subtree of root y
    // creating pointers to the relevant subtrees/nodes
    node *x = y->left;
    node *T2 = x->right;
    // performing rotation
    x->right = y;
    y->left = T2;
    // updating heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // returns x, the new root
}

/*
precondition: node pointer to the root of the BST and a char pointer to the spell we wish to add.
postcondition: inserts the spell in lexicographical order in the tree.
*/
node *insert(node *root, char *spell)
{ // recursively insert a new node, passing root node and the spell to add
    // normal insertion of the node in the right place
    if (root == NULL)
        return newNode(spell);                  // base case: creates the node
    else if (strcmp(spell, root->spell) < 0)    // compares the spells of the root and new node
        root->left = insert(root->left, spell); // insert to the left if the new spell comes first
    else
        root->right = insert(root->right, spell); // insert to the right if the root spell comes first
    // updating height of the root nodes
    root->height = max(height(root->left), height(root->right)) + 1; 

    // balancing the tree
    int balance = getBalance(root);
    // left-left case
    if (balance > 1 && strcmp(spell, root->left->spell) < 0)
        return rightRotate(root);
    // right-right case
    if (balance < -1 && strcmp(spell, root->right->spell) > 0)
        return leftRotate(root);
    // left-right case
    if (balance > 1 && strcmp(spell, root->left->spell) > 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // right-left case
    if (balance < -1 && strcmp(spell, root->right->spell) < 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root; // returns the new root pointer
}

/*
precondition: node pointer to the root of the tree and a char pointer to the spell we're looking for.
postcondition: if the spell is in the tree, returns a node pointer to the node containing the spell, if it doesn't exist in the tree it returns null.
*/
node *search(node *root, char *spell)
{ // recursive search function to find a spell in the tree
    if (root == NULL || strcmp(root->spell, spell) == 0)
        return root; // returns the node with the spell if found, otherwise will be NULL
    if (strcmp(root->spell, spell) > 0)
        return search(root->left, spell);
    else
        return search(root->right, spell);
}

/*
precondition: node pointer to the root of the BST and a char pointer to the spell we wish to delete.
postcondition: deletes the node containing the target spell from the tree and makes the right adjustments to both keep the height values correct and to fix any violations of the BST conditions that resulted from the deletion.
*/
node *deleteNode(node *root, char *spell)
{
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key, then it is in left subtree
    if (strcmp(spell, root->spell) < 0)
    {
        root->left = deleteNode(root->left, spell);
        return root;
    }

    // If the key to be deleted is greater than the root's key, then it is in right subtree
    else if (strcmp(spell, root->spell) > 0)
    {
        root->right = deleteNode(root->right, spell);
        return root; 
    }
    // if key is same as root's key, then this is the node to be deleted
    else
    {
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            node *temp = root->left ? root->right : root->left;
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            // One child case
            else{
                *root = *temp; // Copy the contents of the non-empty child
            }
            return temp;
        }
        else
        {
            // node with two children: Get the inorder successor (smallest in the right subtree)
            node *temp = root->right;
            while (temp->right != NULL) 
            {
                temp = temp->right;
            }

            // Copy the inorder successor's data to this node
            strcpy(root->spell, temp->spell); 

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->spell);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // update height of current node
    root->height = 1 + max(height(root->left), height(root->right));

    // get balance factor (to check whether this node became unbalanced)
    int balance = getBalance(root);
    // If this node becomes unbalanced, then there are 4 cases:
   
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
