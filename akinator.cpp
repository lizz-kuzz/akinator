#include "akinator.hpp"
const int MAX_SIZE = 40;
const char *NAME_FILE = "/mnt/c/Users/User/Desktop/programs/akinator/test.txt";
const char *NAME_GRAPH_FILE = "/mnt/c/Users/User/Desktop/programs/akinator/graph.dot";
static int number_png = 0;

FILE *file_tree = fopen(NAME_FILE, "w");

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

void clear_input_buff() {
    while (getchar() != '\n') {}
}

void create_tree(const char *FILE_INPUT, Tree *tree) {
    char *text_buf;

    text_buf = read_file(FILE_INPUT, text_buf);
    char *point_text_buf = text_buf;
    tree->root_tree = create_tree_from_text(tree->root_tree, NULL, &point_text_buf);

    free(text_buf);
}

Node *create_tree_from_text(Node *node, Node *parent, char **text_buf) {

    if (**text_buf == '{') {

        char *elem = (char *) calloc(MAX_SIZE, sizeof(char));
        for (; **text_buf != '\"' && **text_buf != '\0'; (*text_buf)++) continue;

        (*text_buf)++;

        char *point = elem;

        for (; **text_buf != '\"' && **text_buf != '\0'; (*text_buf)++, elem++) *elem = **text_buf; 
        elem = point;

        for (; **text_buf != '{' && **text_buf != '}' && **text_buf != '\0'; (*text_buf)++) continue;
    
        node = tree_add_elem(node, parent, elem);


        if (**text_buf == '}' || **text_buf == '\0') {
            return node;
        }

        node->left = create_tree_from_text(node->left, node, text_buf);

        for (; **text_buf != '{' && **text_buf != '\0'; (*text_buf)++) continue;

        node->right = create_tree_from_text(node->right, node, text_buf);
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

Node *tree_add_elem(Node *node, Node *parent, tree_elem_t elem) {

    if (node == NULL) {
        node = (Node *) calloc(1, sizeof(Node));
        node->elem_tree = (tree_elem_t) calloc(MAX_SIZE, sizeof(char));
        node->elem_tree = strcpy(node->elem_tree, elem);

        // node->elem_tree = elem;
        printf("elem %s\n", node->elem_tree);
        node->left = NULL;
        node->right = NULL;
        node->parent = parent;
    }
    return node;
}

void print_question(Node *node) {
    if (node->left == NULL && node->right == NULL) {
        printf("это %s?????\nскажи, что да скажи, что да скажи, что да!!!\n", node->elem_tree);
    } else {
        printf("это %s?\n", node->elem_tree);
    }
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
            printf("вместо пробелов, пожалуйста, используйте \'_\' (функция в разработке)\n");
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

    printf("введите название, которому хотите дать определение:\n");
    char *search_elem = (char *) calloc(MAX_SIZE, sizeof(char));
    scanf("%s", search_elem);
    
    Node *node_search = find_elem(node, search_elem);
    
    if (node == NULL) {
        printf("ничего не нашли");
    } else printf("%s - это ", node_search->elem_tree);

    while (node_search->parent != NULL) {
        node_search = node_search->parent;
        printf("%s, ", node_search->elem_tree);
    }

    free(search_elem);
    
}

Node *find_elem(Node *node, tree_elem_t search_elem) {
    if (!node) return node;

    if (strcmp(node->elem_tree, search_elem) == 0) {
        printf("search %s\n", node->elem_tree);
        return node;
    }
    else if (strcmp(node->elem_tree, search_elem) != 0) {

        Node *tmp = find_elem(node->left, search_elem);

        if (tmp == NULL) {
            tmp = find_elem(node->right, search_elem);
            return tmp;
        }
    } 
}

void dump(Node *root) {

    assert(root != nullptr && "null pointer tree");
    FILE *dot_file = fopen(NAME_GRAPH_FILE, "w");

    fprintf(dot_file,"digraph {\n");
    graph_dump(dot_file, root, root->left);
    graph_dump(dot_file, root, root->right);
    fprintf(dot_file,"}\n");

    fclose(dot_file);
    const int size_cmd = 100; 
    char cmd[size_cmd] = "";
    sprintf(cmd, "dot graph.dot -Tpng -o output%d.png", number_png);

    number_png++;
    system(cmd);
    
}

void graph_dump(FILE *dot_file, Node *node, Node *node_son) {

    if (!node_son) {
        return;
    }
    if (node) {
        fprintf(dot_file, "\t%s -> %s\n", node->elem_tree, node_son->elem_tree);
        graph_dump(dot_file, node_son, node_son->left);
        graph_dump(dot_file, node_son, node_son->right);
    }
}

void dtor(Node *node) {
    if (!node) return;
    free(node->elem_tree);
    node->parent = NULL;

    if (node) {
        dtor(node->left);
        node->left = NULL;
        dtor(node->right);
        node->right = NULL;
        free(node);
    }
}