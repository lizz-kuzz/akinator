#ifndef AKINATOR_HPP_INCLUDED
#define AKINATOR_HPP_INCLUDED

#include <stdio.h>
#include <string.h>
#include "tree.hpp"
#include "../stack/utils_stk.hpp"
#include "../stack/stack.hpp"
#include "../stack/debug.hpp"
#include "file.hpp"

enum COMMAND {
    GUESSING = 1,
    DEFINITION = 2,
    COMPARATION = 3,
    TREE_OUTPUT = 4,
    EXIT = 5,
};

void akinator(const char *FILE_INPUT);

COMMAND input_comand();

void print_mode();
void print_question(Node *node);

void comparation(Node *node);
void guessing(Node *node);
void definition(Node *node);

void clear_input_buff(); 
int check_answer(char *new_elem);
int find_char(char * text, char symbol);

void create_defin(Node *node, tree_elem_t elem, stack *stk_defin);
void create_comparation(const Node *node_1, const Node *node_2, stack *stk_defin1, stack *stk_defin2);

void graph_dump(FILE *dot_file, Node *node, Node *node_son);
void dump(Node *root);


#endif