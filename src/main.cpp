#include <stdio.h>
#include "../include/tree.hpp"
#include "../include/akinator.hpp"


int main(int argc, char *argv[]) {

    char *path = "/mnt/c/Users/User/Desktop/programs/akinator/res/";
    char *name_file = argv[1];
    char *FILE_INPUT = (char *) calloc(strlen(path) + strlen(name_file), sizeof(char));
    create_file_path(FILE_INPUT, path, name_file);

    int command = 0;

    Tree tree = {};

    // const char *FILE_INPUT = "/mnt/c/Users/User/Desktop/programs/akinator/res/test_input.txt";

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
                definition(tree.root_tree);
                break;
            } 

            case COMPARATION: {
                comparation(tree.root_tree);                
                break;
            } 

            case TREE_OUTPUT: {
                dump(tree.root_tree);
                break;
            }

            case EXIT: {
                printf_tree(tree.root_tree);
                dtor(tree.root_tree);
                close_file();
                break;
            }
            default:
                break;
        }
    }
 
    return 0;
}