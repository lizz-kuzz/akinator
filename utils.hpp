#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
enum COMMAND {
    GUESSING = 1,
    DEFINITION = 2,
    COMPARATION = 3,
    TREE_OUTPUT = 4,
    EXIT = 5,
};

typedef char* tree_elem_t;

struct Node {
    tree_elem_t elem_tree;
    Node *left;
    Node *right;
};

struct Tree {
    Node *root_tree;
};



#endif