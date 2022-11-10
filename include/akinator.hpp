#ifndef AKINATOR_HPP_INCLUDED
#define AKINATOR_HPP_INCLUDED

#include <stdio.h>
#include <string.h>
#include "utils.hpp"
#include "../stack/utils_stk.hpp"
#include "../stack/stack.hpp"
#include "../stack/debug.hpp"
#include "file.hpp"

COMMAND input_comand();

void print_mode();
void print_question(Node *node);

void comparation(Node *node);
void guessing(Node *node);
void definition(Node *node);

void clear_input_buff(); 

void create_defin(Node *node, tree_elem_t elem);
void create_comparation(const Node *node_1, const Node *node_2, const tree_elem_t elem_1, const tree_elem_t elem_2);
void create_path(const Node *node, stack* defin);

void graph_dump(FILE *dot_file, Node *node, Node *node_son);
void dump(Node *root);


#endif