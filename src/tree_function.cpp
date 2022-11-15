#include "../include/tree_function.hpp"


const char *NAME_FILE = "/mnt/c/Users/User/Desktop/programs/akinator/res/test.txt";
FILE *file_tree = fopen(NAME_FILE, "w");

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

static int count_space = 0;

void printf_tree(Node *node) {

    if (!node) return;

    if (!node->left && !node->right) {
        for (int i = 0; i < count_space; i++) fprintf(file_tree, " ");

        fprintf(file_tree, "{\"%s\"}\n", node->elem_tree);

    } else {

        for (int i = 0; i < count_space; i++) fprintf(file_tree, " ");

        fprintf(file_tree, "{");
        fprintf(file_tree, "\"%s\"\n", node->elem_tree);

        if (node->left) {
            count_space += 4;
            printf_tree(node->left);
        }

        if (node->right) {
            printf_tree(node->right);
            count_space -= 4;

            for (int i = 0; i < count_space; i++) fprintf(file_tree, " ");
            fprintf(file_tree, "}\n");
        }
    }
}

Node *tree_add_elem(Node *node, Node *parent, tree_elem_t elem) {

    node = (Node *) calloc(1, sizeof(Node));
    node->elem_tree = (tree_elem_t) calloc(MAX_SIZE, sizeof(char));
    node->elem_tree = strcpy(node->elem_tree, elem);

    node->left = NULL;
    node->right = NULL;
    node->parent = parent;

    return node;
}

Node *tree_find_elem(Node *node, stack *stk_search, tree_elem_t search_elem) {

    if (!node) return node;

    stack_push(stk_search, node);

    if (strcmp(node->elem_tree, search_elem) == 0) return node;
    
    if (node->left) {
        if (tree_find_elem(node->left, stk_search, search_elem)) {
            return stk_search->data[stk_search->size - 1];
        } 
    }

    if (node->right) {
        if (tree_find_elem(node->right, stk_search, search_elem)) {
            return stk_search->data[stk_search->size - 1];
        }
    }

    stack_pop(stk_search);

    return NULL;

}

void dtor(Node *node) {
    if (!node) return;

    free(node->elem_tree);
    node->parent = NULL;

    dtor(node->left);
    node->left = NULL;

    dtor(node->right);
    node->right = NULL;
    free(node);
}

void close_file() {
    fclose(file_tree);
}