#include "../include/tree.hpp"

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
        fprintf(file_tree, "%*s{\"%s\"}\n", " ", count_space, node->elem_tree);
    } else {

        fprintf(file_tree, "%*s{", " ", count_space);
        fprintf(file_tree, "\"%s\"\n", node->elem_tree);

        if (node->left) {
            count_space *= 2;
            printf_tree(node->left);
        }

        if (node->right) {
            count_space /= 2;

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

        node->left = NULL;
        node->right = NULL;
        node->parent = parent;
    }
    return node;
}

Node *find_elem(Node *node, tree_elem_t search_elem) {

    if (!node) return node;

    if (strcmp(node->elem_tree, search_elem) == 0) return node;
    
    Node *tmp = find_elem(node->left, search_elem);

    if (tmp == NULL) tmp = find_elem(node->right, search_elem);

    return tmp;
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

void close_file() {
    fclose(file_tree);
}