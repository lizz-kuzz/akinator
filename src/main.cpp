#include <stdio.h>
#include "../include/tree_function.hpp"
#include "../include/akinator.hpp"


int main(int argc, char *argv[]) {

    char *path = "/mnt/c/Users/User/Desktop/programs/akinator/res/";
    char *name_file = argv[1];
    char *FILE_INPUT = (char *) calloc(strlen(path) + strlen(name_file), sizeof(char));
    create_file_path(FILE_INPUT, path, name_file);

    akinator(FILE_INPUT);
 
    return 0;
}