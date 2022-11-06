#ifndef AKINATOR_HPP_INCLUDED
#define AKINATOR_HPP_INCLUDED

#include <stdio.h>
#include <string.h>
#include "utils.hpp"
#include "file.hpp"

void  create_tree(const char *FILE_INPUT, Tree *tree);
Node *create_tree_from_text(Node *node, char **text_buf);
Node *tree_add_elem(Node *node, tree_elem_t elem);

COMMAND input_comand();
void print_hello();
void print_question(Node *node);
void printf_tree(Node *node);
void guessing(Node *node);
void clear_input_buff(); 

#endif