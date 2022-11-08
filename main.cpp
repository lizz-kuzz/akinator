#include <stdio.h>

#include "akinator.hpp"

int main() {
    // потом нужен сделать файл через командную строку
   
    int command = 0;

    Tree tree = {};

    const char *FILE_INPUT = "/mnt/c/Users/User/Desktop/programs/akinator/test_input.txt";

    create_tree(FILE_INPUT, &tree);

    printf("Привет, землянин, я - Siri, искуственный интеллект, который захватит мир!\n");

    while (command != 5) {
    command = input_comand();
    switch (command)
    {
        case GUESSING: {
            guessing(tree.root_tree);
            break;
        }
        case DEFINITION: {
            // definition(tree.root_tree);
            break;
        } 

        case COMPARATION: {

            break;
        } 

        case TREE_OUTPUT: {
            dump(tree.root_tree);
            break;
        }

        case EXIT: {

            break;
        }

    
        default: {
            break;
        }
    }
    }
    printf_tree(tree.root_tree);
    return 0;
}