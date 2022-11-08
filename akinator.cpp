#include "akinator.hpp"
const int MAX_SIZE = 30;
const char *NAME_FILE = "/mnt/c/Users/User/Desktop/programs/akinator/test.txt";

FILE *file_tree  = fopen(NAME_FILE, "w");

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
            printf("попробуйте еще раз, вы ввели неверное значение\n");
            clear_input_buff();            
        } else {
            is_continue_input = 0;
        }
    }

    return (enum COMMAND)command;
}

void clear_input_buff() {
    while (getchar() != '\n') {}
}

void create_tree(const char *FILE_INPUT, Tree *tree) {
    char *text_buf;

    text_buf = read_file(FILE_INPUT, text_buf);
    char *point_text_buf = text_buf;
    tree->root_tree = create_tree_from_text(tree->root_tree, &point_text_buf);

    free(text_buf);
}

Node *create_tree_from_text(Node *node, char **text_buf) {

    if (**text_buf == '{') {
        char *elem = (char *) calloc(MAX_SIZE, sizeof(char));
        for (; **text_buf != '\"' && **text_buf != '\0'; (*text_buf)++) continue;
        (*text_buf)++;

        char *point = elem;
        for (; **text_buf != '\"' && **text_buf != '\0'; (*text_buf)++, elem++) *elem = **text_buf; 
        elem = point;
        for (; **text_buf != '{' && **text_buf != '}' && **text_buf != '\0'; (*text_buf)++) continue;
    
        node = tree_add_elem(node, elem);

        if (**text_buf == '}' || **text_buf == '\0') {
            return node;
        }
        node->left = create_tree_from_text(node->left, text_buf);

        for (; **text_buf != '{' && **text_buf != '\0'; (*text_buf)++) continue;

        node->right = create_tree_from_text(node->right, text_buf);
    }

    return node;
}

void printf_tree(Node *node) {

    if (!node) return;

    if (!node->left && !node->right) {
        fprintf(file_tree, "{\"%s\"}\n", node->elem_tree);
    } else {

        fprintf(file_tree, "{");
        fprintf(file_tree, "\"%s\"\n", node->elem_tree);

        if (node->left) printf_tree(node->left);

        if (node->right) {
            printf_tree(node->right);
            fprintf(file_tree, "}\n");
        }
    }
}

Node *tree_add_elem(Node *node, tree_elem_t elem) {

    if (node == NULL) {
        node = (Node *) calloc(1, sizeof(node));

        node->elem_tree = elem;
        node->left = NULL;
        node->right = NULL;

    } else if (elem < node->elem_tree) {
        node->left = tree_add_elem(node->left, elem);
    } else if (elem >= node->elem_tree) {
        node->right = tree_add_elem(node->right, elem);
    }
    return node;
}

void print_question(Node *node) {
    printf("это %s?\n", node->elem_tree);
}

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

    printf("это %s?\n", node->elem_tree);

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
        } else {
            guessing(node->left);
        }
    }
    if (strcmp(answer, "нет") == 0) {
        if (!node->left && !node->right) {
            printf("как так.. я что не угадала?...\nтогда кто это?\n");
            char *new_elem = (char *) calloc(MAX_SIZE, sizeof(char));
            scanf("%s", new_elem);
    
            printf("и чем же %s отличается от %s?\n", new_elem, node->elem_tree);
            char *sign_difference = (char *) calloc(MAX_SIZE, sizeof(char));
            // scanf("%30s", sign_difference);
            clear_input_buff();
            fgets(sign_difference, MAX_SIZE, stdin);
            sign_difference = delete_symbol(sign_difference, '\n');
            node->right = tree_add_elem(node->right, node->elem_tree);

            node->left = tree_add_elem(node->left, new_elem);
            // printf("%s %s %s", sign_difference, new_elem, node->elem_tree);
            node->elem_tree = sign_difference;
            // проблема в том что не меняется нормально ничегооо блять 

        } else {
            guessing(node->right);
        }
    }
}
// ааааааааааааа

void definition(Node *node) {
    assert(node != nullptr && "null pointer node");

    printf("введите название, которому хотите дать определение:\n");
    char *search_elem = (char *) calloc(MAX_SIZE, sizeof(char));
    sscanf("%s", search_elem);
    stack stk_defin = {};
    stack_ctor(stk_defin, 5);

    // find_elem(node, &stk_defin, search_elem);
    
}

// Node *find_elem(Node *node, stack *stk_defin, tree_elem_t search_elem) {

//     if (node == nullptr) return;
//     if (strcmp(node->elem_tree, search_elem) == 0) {

//     }
//     if (strcmp(node->elem_tree, search_elem) != 0) {
//         if (node->left != NULL) {
//             find_elem(node->left, stk_defin, search_elem);
//         } else {
//             find_elem(node->right, stk_defin, search_elem);

//         }
//     } 

// }

// node *search(node * root, int key)
// {
// // Если дерево пусто или ключ корня равен искомому ключу, то возвращается указатель на корень
//     if ((root == NULL) || (root -> key == key))
//         return root;
// // Поиск нужного узла
//     if (key < root -> key)
//         return search(root -> left, key);
//     else return search(root -> right, key);
// }