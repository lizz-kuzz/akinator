#ifndef INPUT_OUTPUT_HPP_INCLUDED
#define INPUT_OUTPUT_HPP_INCLUDED

#include "akinator.hpp"
#include "file.hpp"
#include "utils.hpp"

void  create_tree(const char *FILE_INPUT, Tree *tree);
Node *create_tree_from_text(Node *node, Node *parent, char **text_buf);
Node *tree_add_elem(Node *node, Node *parent, tree_elem_t elem);
void printf_tree(Node *node);
Node *find_elem(Node *node, tree_elem_t search_elem);

void dtor(Node *node);

void close_file();

#endif