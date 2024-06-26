#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef struct _node {
    struct _node* left;
    struct _node* right;
    char* value;
} Node;

Node* parseExpression(char** expression);
Node* parseTerm(char** expression);
Node* parseFactor(char** expression);

Node* newNode(char* value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->value = (char*)malloc((strlen(value) + 1) * sizeof(char));
    strcpy(node->value, value);
    return node;
}

char* nextToken(char** expression) {
    while (isspace(**expression)) (*expression)++;
    if (**expression == '\0') return NULL;

    int length = 0;
    if (isdigit(**expression)) {
        while (isdigit((*expression)[length])) length++;
        if (isalpha((*expression)[length])) length++; // Include the variable if it follows a number
    } else if (isalpha(**expression)) {
        length = 1;
        while (isdigit((*expression)[length])) length++; 
    } else {
        length = 1;
    }

    char* token = (char*)malloc((length + 1) * sizeof(char));
    strncpy(token, *expression, length);
    token[length] = '\0';
    (*expression) += length;

    return token;
}

Node* parseFactor(char** expression) {
    char* token = nextToken(expression);
    if (token == NULL) return NULL;
    Node* node;
    if (strcmp(token, "(") == 0) {
        node = parseExpression(expression);
        free(token);
        token = nextToken(expression);
        if (token == NULL || strcmp(token, ")") != 0) {
            exit(1);
        }
    } else if (strcmp(token, "-") == 0) {
        node = newNode(token);
        node->right = parseFactor(expression);
    } else {
        int coefficient = 0;
        sscanf(token, "%d", &coefficient);
        if (coefficient != 0 && isalpha(token[strlen(token) - 1])) {

            node = newNode("*");
            char coef_str[16];
            snprintf(coef_str, sizeof(coef_str), "%d", coefficient);
            node->left = newNode(coef_str);
            char var_str[2] = {token[strlen(token) - 1], '\0'};
            node->right = newNode(var_str);
        } else {
            node = newNode(token);
        }
    }
    free(token);
    return node;
}

Node* parsePower(char** expression) {
    Node* node = parseFactor(expression);
    char* token;
    while ((token = nextToken(expression)) != NULL) {
        if (strcmp(token, "^") == 0) {
            Node* right = parseFactor(expression);
            Node* parent = newNode(token);
            parent->left = node;
            parent->right = right;
            node = parent;
        } else {
            (*expression)--;
            free(token);
            break;
        }
        free(token);
    }
    return node;
}

Node* parseTerm(char** expression) {
    Node* node = parsePower(expression);
    char* token;
    while ((token = nextToken(expression)) != NULL) {
        if (strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
            Node* right = parsePower(expression);
            Node* parent = newNode(token);
            parent->left = node;
            parent->right = right;
            node = parent;
        } else {
            (*expression)--;
            free(token);
            break;
        }
        free(token);
    }
    return node;
}

char* my_strdup(const char* s) {
    char* new_str = malloc(strlen(s) + 1);
    if (new_str) {
        strcpy(new_str, s);
    }
    return new_str;
}

Node* parseExpression(char** expression) {
    Node* node = parseTerm(expression);
    char* token;
    while ((token = nextToken(expression)) != NULL) {
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0) {
            Node* right = parseTerm(expression);
            Node* parent = newNode(token);
            parent->left = node;
            parent->right = right;
            node = parent;
        } else {
            (*expression)--;
            free(token);
            break;
        }
        free(token);
    }
    return node;
}

void freeTree(Node* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node->value);
    free(node);
}

Node* cloneNode(Node* node) {
    if (node == NULL) return NULL;
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = (char*)malloc((strlen(node->value) + 1) * sizeof(char));
    strcpy(newNode->value, node->value);
    newNode->left = cloneNode(node->left);
    newNode->right = cloneNode(node->right);
    return newNode;
}

void expandSquare(Node* node) {
    if (node == NULL) return;
    expandSquare(node->left);
    expandSquare(node->right);
    if (strcmp(node->value, "^") == 0 && strcmp(node->right->value, "2") == 0 &&
        (strcmp(node->left->value, "-") == 0 || strcmp(node->left->value, "+") == 0)) {
        Node* a = cloneNode(node->left->left);
        Node* b = cloneNode(node->left->right);
        Node* two = newNode("2");
        Node* two_a_b = newNode("*");
        two_a_b->left = two;
        two_a_b->right = newNode("*");
        if (strcmp(a->value, "+") == 0 || strcmp(a->value, "-") == 0) {
            Node* a_paren = newNode("(");
            a_paren->right = a;
            a = a_paren;
            Node* a_paren_close = newNode(")");
            a_paren_close->left = a;
            a = a_paren_close;
        }
        if (strcmp(b->value, "+") == 0 || strcmp(b->value, "-") == 0) {
            Node* b_paren = newNode("(");
            b_paren->right = b;
            b = b_paren;
            Node* b_paren_close = newNode(")");
            b_paren_close->left = b;
            b = b_paren_close;
        }
        two_a_b->right->left = a;
        two_a_b->right->right = b;
        Node* a_squared = newNode("^");
        a_squared->left = cloneNode(a);
        a_squared->right = newNode("2");
        Node* b_squared = newNode("^");
        b_squared->left = cloneNode(b);
        b_squared->right = newNode("2");
        free(node->value); 
        node->value = my_strdup(node->left->value); 
        freeTree(node->left); 
        node->left = a_squared;
        freeTree(node->right); 
        node->right = newNode("+");
        node->right->left = two_a_b;
        node->right->right = b_squared;
    }
}

void printTree(Node* node, int space) {
    if (node == NULL) return;

    space += 1;

    printTree(node->right, space);

    printf("\n");
    for (int i = 1; i < space; i++)
        printf(" ");
    printf("%s\n", node->value);

    printTree(node->left, space);
}

void printExpressionHelper(Node* node, int isRoot, char* parentValue, int parentIsEmptyPlus) {
    if (node == NULL) return;
    int isUnaryMinus = (strcmp(node->value, "-") == 0 && node->right != NULL && node->left == NULL);
    int isEmptyPlus = (strcmp(node->value, "+") == 0 && node->left == NULL && node->right != NULL);
    int needParentheses = (!isRoot && !parentIsEmptyPlus && (isUnaryMinus || 
                      ((strcmp(node->value, "*") == 0 || strcmp(node->value, "/") == 0 || strcmp(node->value, "^") == 0) && 
                      (strcmp(parentValue, "+") == 0 || strcmp(parentValue, "-") == 0))));
    int needPowerParentheses = (strcmp(node->value, "^") == 0 && (strcmp(node->left->value, "+") == 0 || strcmp(node->left->value, "-") == 0));
    int needMultiplicationParentheses = (strcmp(node->value, "^") == 0 && strcmp(node->left->value, "*") == 0);

    if (needParentheses) printf("(");
    if (needPowerParentheses || needMultiplicationParentheses) printf("(");
    printExpressionHelper(node->left, 0, node->value, isEmptyPlus);
    if (needPowerParentheses || needMultiplicationParentheses) printf(")");
    if (!isEmptyPlus) printf("%s", node->value);
    printExpressionHelper(node->right, 0, node->value, isEmptyPlus);
    if (needParentheses) printf(")");
}

void printExpression(Node* node) {
    printExpressionHelper(node, 1, NULL, 0);
}

int main() {
    char expression[100];
    printf(">>> ");
    fgets(expression, 100, stdin);
    char* p = expression;
    Node* root = parseExpression(&p);
    printExpression(root);
    expandSquare(root);
    printf("\n");
    printExpression(root);
    printTree(root, 0);
    printf("\n");
    freeTree(root);
    return 0;
}
