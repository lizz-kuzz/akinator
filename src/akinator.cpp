#include "../include/akinator.hpp"
#include "../include/tree_function.hpp"

const char *NAME_GRAPH_FILE = "/mnt/c/Users/User/Desktop/programs/akinator/res/graph.dot";
static int number_png = 0;

void akinator(const char *FILE_INPUT) {
    
    int command = 0;

    Tree tree = {};

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
}

void clear_input_buff() {
    while (getchar() != '\n') {}
}

void create_defin(Node *node, tree_elem_t elem, stack *stk_defin) {
    assert(node != nullptr && "null pointer node");
    
    printf("%s - это ", elem);
  
    for (int i = 0; i < stk_defin->size - 1; i++) {
        Node *node_parent = stk_defin->data[i];
        Node *node_tmp = stk_defin->data[i + 1];

        if (node_parent->left == node_tmp) {
            printf("%s", node_parent->elem_tree);
        } else {
            printf("не %s", node_parent->elem_tree);
        }

        if (i == stk_defin->size - 2) printf(".\n");
        else printf(", ");
        node_tmp = node_parent;
    }
}


void create_comparation(const Node *node_1, const Node *node_2, stack *stk_defin1, stack *stk_defin2) {
    assert(node_1 != nullptr && "null pointer node");
    assert(node_2 != nullptr && "null pointer node");

    printf("я провела очень сложный анализ и выяснила, что %s и %s\n", node_1->elem_tree, node_2->elem_tree);
    printf("похожи тем, что оба: ");

    int i = 0;
    
    for (; i < stk_defin1->size - 1 && i < stk_defin2->size - 1; i++) {
        if (stk_defin1->data[i + 1] == stk_defin2->data[i + 1]) {
            if (stk_defin1->data[i]->left == stk_defin1->data[i + 1]) {
                printf(" %s,", stk_defin1->data[i]->elem_tree);
            } else {
                printf("не %s,", stk_defin1->data[i]->elem_tree);
            }
        } else {
            printf("на этом их сходства усе\n");
            break;
       }
    }

    printf("\nно первый элемент:\n");

    for (int j = i; j < stk_defin1->size - 1; j++) {
        Node *node_parent = stk_defin1->data[j];
        Node *node_tmp = stk_defin1->data[j + 1];

        if (node_parent->left == node_tmp) {
            printf("%s", node_parent->elem_tree);
        } else {
            printf("не %s", node_parent->elem_tree);
        }

        if (j == stk_defin1->size - 2) printf(".\n");
        else printf(", ");
        node_tmp = node_parent;
    }
    

    printf("а второй элемент:\n");

    for (int j = i; j < stk_defin2->size - 1; j++) {
        Node *node_parent = stk_defin2->data[j];
        Node *node_tmp = stk_defin2->data[j + 1];

        if (node_parent->left == node_tmp) {
            printf("%s", node_parent->elem_tree);
        } else {
            printf("не %s", node_parent->elem_tree);
        }

        if (j == stk_defin2->size - 2) printf(".\n");
        else printf(", ");
        node_tmp = node_parent;
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

int find_char(char * text, char symbol) {
    char *point = text;
    int count = 0;
    for (; *point != '\0'; point++) {
        if (*point == symbol) count++;
    }
    return count;
}

int check_answer(char *new_elem) {
    char *point = new_elem;

    if (find_char(point, '\n') || find_char(point, '\"') || find_char(point, '\'') || find_char(point, '\t') || find_char(point, ' ')) {
        return 1;
    } else
        return 0;
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

            new_elem = fgets(new_elem, MAX_SIZE, stdin);
            new_elem = delete_symbol(new_elem, '\n');

            while (check_answer(new_elem)) {
                printf("введите заново(ты использовал запретные символы)\n");
                new_elem = fgets(new_elem, MAX_SIZE, stdin);
                new_elem = delete_symbol(new_elem, '\n');
            }

            printf("и чем же %s отличается от %s?\n", new_elem, node->elem_tree);

            fgets(sign_difference, MAX_SIZE, stdin);
            sign_difference = delete_symbol(sign_difference, '\n');

            
            while (check_answer(new_elem)) {
                printf("введите заново(ты использовал запретные символы)\n");
                new_elem = fgets(new_elem, MAX_SIZE, stdin);
                new_elem = delete_symbol(new_elem, '\n');
            }

            node->right = tree_add_elem(node->right, node, node->elem_tree);
            node->left = tree_add_elem(node->left, node, new_elem);
            node->elem_tree = strcpy(node->elem_tree, sign_difference);

            free(new_elem);
            free(sign_difference);
        } else {
            guessing(node->right);
        }
    }
}

void definition(Node *node) {
    assert(node != nullptr && "null pointer node");

    printf("введите название объекта, которому хотите дать определение:\n");
    char *search_elem = (char *) calloc(MAX_SIZE, sizeof(char));
    scanf("%40s", search_elem);

    stack stk_defin = {};
    stack_ctor(stk_defin, 5);

    Node *node_search = tree_find_elem(node, &stk_defin, search_elem);
    
    if (node_search == NULL) {
        printf("чел, походу ты сам не знаешь, что ищешь!\nв моей базе нет такого объекта\n");
    } else {
        create_defin(node_search, search_elem, &stk_defin);
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

    stack stk_defin1 = {};
    stack_ctor(stk_defin1, 5);
    
    stack stk_defin2 = {};
    stack_ctor(stk_defin2, 5);
    
    Node *node_search_elem_1 = tree_find_elem(node, &stk_defin1, compare_elem_1);
    Node *node_search_elem_2 = tree_find_elem(node, &stk_defin2, compare_elem_2);

    if (!node_search_elem_1 || !node_search_elem_2) {
        printf("чел, походу ты сам не знаешь, что ищешь!\nв моей базе нет такого объекта\n");
    } else {
        printf("%s %s\n", node_search_elem_1->elem_tree, node_search_elem_2->elem_tree);
        create_comparation(node_search_elem_1, node_search_elem_2, &stk_defin1, &stk_defin2);
    }

    clear_input_buff(); 

    stack_dtor(&stk_defin1);
    stack_dtor(&stk_defin2);
    free(compare_elem_1);
    free(compare_elem_2);
}
