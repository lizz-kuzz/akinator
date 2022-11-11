#include "../include/akinator.hpp"
#include "../include/tree.hpp"

const char *NAME_GRAPH_FILE = "/mnt/c/Users/User/Desktop/programs/akinator/res/graph.dot";
static int number_png = 0;

void create_file_path(char *FILE_PROG, char *path, char *name_file) {
    assert(path      != nullptr && "null pointer");
    assert(name_file != nullptr && "null pointer");
    assert(FILE_PROG != nullptr && "null pointer");

    char *save_point = FILE_PROG;

    for (; *path != '\0'; path++, save_point++) {
        *save_point = *path;
    }
    for (; *name_file != '\0'; name_file++, save_point++) {
        *save_point = *name_file;
    }
    *save_point = '\0';

}

void clear_input_buff() {
    while (getchar() != '\n') {}
}

void create_defin(Node *node, tree_elem_t elem) {
    assert(node != nullptr && "null pointer node");
    stack defin = {};
    
    create_path(node, &defin);

    printf("%s - это ", elem);
    
    while (defin.size) {
        path_search_elem path = stack_pop(&defin);

        if (path.answer ==  true) {
            printf("%s", path.node->elem_tree);
        } else {
            printf("не %s", path.node->elem_tree);
        }

        if (defin.size == 0) printf(".\n");
        else printf(", ");
    }
}

void create_path(const Node *node, stack* defin) {

    assert(node != nullptr && "null pointer node");
    assert(defin != nullptr && "null pointer node");

    stack_ctor(*defin, 5);

    while (node->parent != NULL) {
        path_search_elem path = {};
        path.node = node->parent;

        if (node == path.node->left) path.answer = true;
        else path.answer = false;

        stack_push(defin, path);

        node = node->parent;
    }
}

void create_comparation(const Node *node_1, const Node *node_2, const tree_elem_t elem_1, const tree_elem_t elem_2) {
    assert(node_1 != nullptr && "null pointer node");
    assert(node_2 != nullptr && "null pointer node");
    
    stack defin_1 = {};
    stack defin_2 = {};

    create_path(node_1, &defin_1);
    create_path(node_2, &defin_2);
    printf("я провела очень сложный анализ и выяснила, что %s и %s\n", elem_1, elem_2);

    path_search_elem path_1 = stack_pop(&defin_1);
    path_search_elem path_2 = stack_pop(&defin_2);

    if (path_1.answer == path_2.answer && path_1.node == path_2.node) {

        printf("похожи тем, что оба:");

        while (path_1.answer == path_2.answer && path_1.node == path_2.node) {
            if (path_1.answer ==  true) {
                printf(" %s,", path_1.node->elem_tree);
            } else {
                printf(" не %s,", path_1.node->elem_tree);
            }
            path_1 = stack_pop(&defin_1);
            path_2 = stack_pop(&defin_2);
        }
        printf("\n");
    } else {
        printf("ничем не похожи\n");
    }       

    printf("но первый элемент:\n");

    if (path_1.answer ==  true) {
            printf("%s", path_1.node->elem_tree);
        } else {
            printf("не %s", path_1.node->elem_tree);
        }

    if (defin_1.size == 0) printf(".\n");
    else printf(", ");

    while (defin_1.size != 0) {
        path_1 = stack_pop(&defin_1);
        if (path_1.answer ==  true) {
            printf("%s", path_1.node->elem_tree);
        } else {
            printf("не %s", path_1.node->elem_tree);
        }

        if (defin_1.size == 0) printf(".\n");
        else printf(", ");
    }

    printf("а второй элемент:\n");

    if (path_2.answer ==  true) {
        printf("%s", path_2.node->elem_tree);
    } else {
        printf("не %s", path_2.node->elem_tree);
    }

    if (defin_2.size == 0) printf(".\n");
    else printf(", ");

    while (defin_2.size != 0) {
        path_2 = stack_pop(&defin_2);
        if (path_2.answer ==  true) {
            printf("%s", path_2.node->elem_tree);
        } else {
            printf("не %s", path_2.node->elem_tree);
        }

        if (defin_2.size == 0) printf(".\n");
        else printf(", ");
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
    
    sprintf(cmd, "dot res/graph.dot -Tpng -o res/output%d.png 2>text_error.txt", number_png);

    number_png++;
    system(cmd);
    
}

void graph_dump(FILE *dot_file, Node *node, Node *node_son) {

    if (!node_son) {
        return;
    }

    if (node) {
        fprintf(dot_file, "\t\"%s\" -> \"%s\"\n", node->elem_tree, node_son->elem_tree);

        graph_dump(dot_file, node_son, node_son->left);
        graph_dump(dot_file, node_son, node_son->right);
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

void comparation(Node *node) {
    assert(node != nullptr && "null pointer node");

    printf("введите названия объектов, которые хотите сравнить:\n");
    char *compare_elem_1 = (char *) calloc(MAX_SIZE, sizeof(char));
    char *compare_elem_2 = (char *) calloc(MAX_SIZE, sizeof(char));

    scanf("%40s", compare_elem_1);
    scanf("%40s", compare_elem_2);
    
    Node *node_search_elem_1 = find_elem(node, compare_elem_1);
    Node *node_search_elem_2 = find_elem(node, compare_elem_2);
    
    if (!node_search_elem_1 || !node_search_elem_2) {
        printf("чел, походу ты сам не знаешь, что ищешь!\nв моей базе нет такого объекта\n");
    } else {
        create_comparation(node_search_elem_1, node_search_elem_2, compare_elem_1, compare_elem_2);
    }

    clear_input_buff(); 

    free(compare_elem_1);
    free(compare_elem_2);
}
