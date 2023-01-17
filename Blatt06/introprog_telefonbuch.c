#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "introprog_telefonbuch.h"

/*
 * Inserts a node with the given phone number and name into the binary
 * search tree bst. The binary search tree should have the property that
 * all left children have a value less than or equal to (<=) and all
 * right children have a value greater than (>) the parent node.
 */
void bst_insert_node(bstree* bst, unsigned long phone, char *name) {
    // Check if a node with the given phone number already exists in the tree
    bst_node* existing_node = find_node(bst, phone);
    if (existing_node != NULL) {
        printf("Fehler: Telefonnummer entspricht nicht den Vorgaben oder Telefonnummer bereits vorhanden\n");
        return;
    }

    // Allocate memory for a new string containing the name of the new node
    // and copy the name into the newly allocated string
    int len = strlen(name) + 1;
    char *newname = (char*)malloc(len * sizeof(char));
    snprintf(newname, len, "%s", name);

    // Create a new bst_node with the given phone and name
    bst_node* new_node = (bst_node*)malloc(sizeof(bst_node));
    new_node->phone = phone;
    new_node->name = newname;
    new_node->left = NULL;
    new_node->right = NULL;

    // If the tree is empty, set the root of the tree to the new node
    if (bst->root == NULL) {
        bst->root = new_node;
        return;
    }

    // Otherwise, insert the new node into the tree
    bst_node* curr = bst->root;
    while (1) {
        // If the new node's phone is less than or equal to the current node's
        // phone, insert it into the left subtree
        if (new_node->phone <= curr->phone) {
            if (curr->left == NULL) {
                curr->left = new_node;
                return;
            }
            curr = curr->left;
        }
        // If the new node's phone is greater than the current node's phone,
        // insert it into the right subtree
        else {
            if (curr->right == NULL) {
                curr->right = new_node;
                return;
            }
            curr = curr->right;
        }
    }
}


/*
 * This function searches for a node in the binary search tree containing the given phone number
 * and returns a pointer to the node if it exists.
 * If no such node exists, the function returns NULL.
 */
bst_node* find_node(bstree* bst, unsigned long phone) {
    
  // Check if the phone number is within the valid range
  if (phone < 1 || phone > 9999) {
    return NULL;
  }

  // Set temp to the root of the binary search tree
  bst_node *temp = bst -> root;

  // If the current node is not NULL and the phone number is not equal to the one
  // stored in the current node, recursively call find_node on the left or right
  // subtree of the current node, depending on whether the phone number is less than
  // or greater than the one stored in the current node.
  // If the phone number is equal to the one stored in the current node, return the
  // current node.
  // If temp is NULL, the function will return NULL.
  while (temp && phone != temp -> phone) {
    temp = (phone <= temp -> phone) ? temp -> left : temp -> right;
  }
  return temp;
}



/* Prints the subtree of node in "in-order" order */
void bst_in_order_walk_node(bst_node* node) {
    // If the given node is not NULL, traverse its left subtree
    // in-order, then visit the node itself, and finally traverse
    // its right subtree in-order.
    if (node != NULL) {
        bst_in_order_walk_node(node->left);
        print_node(node);
        bst_in_order_walk_node(node->right);
    }
}





/* Traverses the binary search tree in "in-order" order and
   prints out the nodes in the tree. */
void bst_in_order_walk(bstree* bst) {
    // If the given bstree is not NULL, traverse its root
    // node's subtree in-order.
    if (bst) {
        bst_in_order_walk_node(bst->root);
    }
}




/*
 * Recursively deletes the binary search tree starting from the given node
 * using a post-order traversal.
 *
 * In a post-order traversal, the left and right subtrees of the given node
 * are deleted first, and then the given node itself is deleted.
 *
 * This is a common approach for deleting a binary search tree, as it
 * ensures that all nodes in the subtree are deleted before the root
 * of the subtree is deleted.
 */
void bst_free_subtree(bst_node* node) {

    // If the given node is not NULL, delete its left and right subtrees
    // using a recursive call to this function.
    if (node) {
        bst_free_subtree(node -> left);
        bst_free_subtree(node -> right);

        // Free the memory associated with the "name" field of the node.
        free(node -> name);

        // Finally, free the memory associated with the given node itself.
        free(node);
    }
}


/* 
 * Löscht den gesamten Baum bst und gibt den entsprechenden
 * Speicher frei.
 */
void bst_free_tree(bstree* bst) {
    if(bst != NULL && bst->root != NULL) {
        bst_free_subtree(bst->root);
        bst->root = NULL;
    }
}
