#ifndef INPUT_OUTPUT_HPP_INCLUDED
#define INPUT_OUTPUT_HPP_INCLUDED

#include "akinator.hpp"
#include "file.hpp"
#include "utils.hpp"

COMMAND input_comand();

void print_mode();
void print_question(Node *node);


void guessing(Node *node);
void definition(Node *node);



#endif