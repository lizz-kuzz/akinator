#include "akinator.hpp"
const char *NAME_FILE = "/mnt/c/Users/User/Desktop/programs/akinator/test.txt";
const char *NAME_GRAPH_FILE = "/mnt/c/Users/User/Desktop/programs/akinator/graph.dot";
static int number_png = 0;

FILE *file_tree = fopen(NAME_FILE, "w");


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

        node->left = NULL;
        node->right = NULL;
        node->parent = parent;
    }
    return node;
}

void create_defin(Node *node, tree_elem_t elem) {
    assert(node != nullptr && "null pointer node");
    stack defin = {};
    stack_ctor(defin, 5);

    while (node->parent != NULL) {

    path_search_elem path = {};
        path.node = node->parent;

        if (node == path.node->left) path.answer = true;
        else path.answer = false;

        stack_push(&defin, path);

        node = node->parent;

    }


    int size = defin.size;

    printf("%s - это ", elem);
    
    // for (int i = 0; i < size; i++)
    while (defin.size) {
        path_search_elem path = stack_pop(&defin);

        if (path.answer ==  true) {
            printf("%s", path.node->elem_tree);
        } else {
            printf("не %s", path.node->elem_tree);
        }

        // if (i == size - 1) printf(".\n");
        if (defin.size == 0) printf(".\n");
        else printf(", ");
        
    }
    
}




Node *find_elem(Node *node, tree_elem_t search_elem) {
    if (!node) return node;

    if (strcmp(node->elem_tree, search_elem) == 0) {
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