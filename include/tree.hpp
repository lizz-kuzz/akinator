#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

const int MAX_SIZE = 40;

typedef char* tree_elem_t;

struct Node {
    tree_elem_t elem_tree;
    Node *left;
    Node *right;
    Node *parent;
};

struct Tree {
    Node *root_tree;
};

#endif