#ifndef TREE_FUNC_HPP_INCLUDED
#define TREE_FUNC_HPP_INCLUDED

#include "akinator.hpp"
#include "file.hpp"
#include "tree.hpp"

void  create_tree(const char *FILE_INPUT, Tree *tree);
Node *create_tree_from_text(Node *node, Node *parent, char **text_buf);
Node *tree_add_elem(Node *node, Node *parent, tree_elem_t elem);
void printf_tree(Node *node);
Node *tree_find_elem(Node *node, stack *stk_search, tree_elem_t search_elem);
void dtor(Node *node);
void close_file();

#endif