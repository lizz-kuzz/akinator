#include "input_output.hpp"



static char *delete_symbol(char *s, char c) {
    assert(s != NULL && "null pointer");
    char *point = s;

    for (; *point != '\0'; point++) {
        if (*point == c) {
            *point = '\0';
        }
    }
    return s;
}
void guessing(Node *node) {

    if (!node) return;

    print_question(node);

    char answer[MAX_SIZE] = "";

    int is_continue_input = 1;

    while (is_continue_input) {
        if (scanf("%s", answer) != 1 || (strcmp(answer, "да") != 0 && strcmp(answer, "нет") != 0)) {
            printf("попробуйте еще раз, вы ввели неверное значение\n");
            clear_input_buff();            
        } else {
            is_continue_input = 0;
        }
    }
    
    if (strcmp(answer, "да") == 0) {
        if (!node->left && !node->right) {
            printf("ура, я как всегда права!\n");
            clear_input_buff();            
        } else {
            guessing(node->left);
        }
    }

    if (strcmp(answer, "нет") == 0) {
        if (!node->left && !node->right) {
            printf("как так.. я что не угадала?...\nтогда кто это?\n");
            clear_input_buff();            

            char *new_elem = (char *) calloc(MAX_SIZE, sizeof(char));
            char *sign_difference = (char *) calloc(MAX_SIZE, sizeof(char));

            // scanf("%s", new_elem);
            new_elem = fgets(new_elem, MAX_SIZE, stdin);
            new_elem = delete_symbol(new_elem, '\n');
    
            printf("и чем же %s отличается от %s?\n", new_elem, node->elem_tree);
            printf("вместо пробелов, пожалуйста, используйте \'_\' (функция графического дампа в разработке)\n");
            // scanf("%40s", sign_difference);

            fgets(sign_difference, MAX_SIZE, stdin);
            sign_difference = delete_symbol(sign_difference, '\n');

            node->right = tree_add_elem(node->right, node, node->elem_tree);
            node->left = tree_add_elem(node->left, node, new_elem);
            node->elem_tree = strcpy(node->elem_tree, sign_difference);
            
            // printf("%s %s %s\n", sign_difference, new_elem, node->elem_tree);
            // printf("%s\n", node->elem_tree);

            free(new_elem);
            free(sign_difference);
        } else {
            guessing(node->right);
        }
    }
}
// ааааааааааааа

void definition(Node *node) {
    assert(node != nullptr && "null pointer node");

    printf("введите название объекта, которому хотите дать определение:\n");
    char *search_elem = (char *) calloc(MAX_SIZE, sizeof(char));
    scanf("%40s", search_elem);
    
    Node *node_search = find_elem(node, search_elem);
    
    if (node_search == NULL) {
        printf("чел, походу ты сам не знаешь, что ищешь!\nв моей базе нет такого объекта\n");
    } else {
        create_defin(node_search, search_elem);
    }

    free(search_elem);
}

void print_mode() {
    printf("Выбери режим работы:\n");
    printf("\t[1]угадывание\n");
    printf("\t[2]определение\n");
    printf("\t[3]сравнение\n");
    printf("\t[4]вывод дерева\n");
    printf("\t[5]выход\n");
}

COMMAND input_comand() {

    int command = 0;
    int is_continue_input = 1;

    while (is_continue_input) {

        print_mode();

        if (scanf("%d", &command) != 1 || command < GUESSING || command > EXIT) {
            printf("попробуйте еще раз, вы ввели неверное значение(научись читать)\n");
            clear_input_buff();            
        } else {
            is_continue_input = 0;
        }
    }

    return (enum COMMAND)command;
}

void print_question(Node *node) {
    if (node->left == NULL && node->right == NULL) {
        printf("это %s?????\nскажи, что да скажи, что да скажи, что да!!!\n", node->elem_tree);
    } else {
        printf("это %s?\n", node->elem_tree);
    }
}
