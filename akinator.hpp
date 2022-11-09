#ifndef AKINATOR_HPP_INCLUDED
#define AKINATOR_HPP_INCLUDED

#include <stdio.h>
#include <string.h>
#include "utils.hpp"
#include "stack/utils_stk.hpp"
#include "stack/stack.hpp"
#include "stack/debug.hpp"
#include "file.hpp"

void  create_tree(const char *FILE_INPUT, Tree *tree);
Node *create_tree_from_text(Node *node, Node *parent, char **text_buf);
Node *tree_add_elem(Node *node, Node *parent, tree_elem_t elem);

void clear_input_buff(); 

Node *find_elem(Node *node, tree_elem_t search_elem);
void create_defin(Node *node, tree_elem_t elem);
void create_comparation(const Node *node_1, const Node *node_2, const tree_elem_t elem_1, const tree_elem_t elem_2);

void create_path(const Node *node, stack* defin);
void printf_tree(Node *node);
void graph_dump(FILE *dot_file, Node *node, Node *node_son);
void dump(Node *root);

void dtor(Node *node);

#endif