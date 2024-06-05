#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "tree_data.txt"

typedef struct TreeNode {
    float value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(float value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


TreeNode* insertNode(TreeNode* root, float value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->value) {
        root->left = insertNode(root->left, value);
    } else if (value > root->value) {
        root->right = insertNode(root->right, value);
    } else {
        printf("Значение %.2f уже существует в дереве.\n", value);
    }
    return root;
}

void printTree(TreeNode* root, int depth, char prefix) {
    if (root == NULL) {
        return;
    }
    printTree(root->right, depth + 1, '/');
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%c %.2f\n", prefix, root->value);
    printTree(root->left, depth + 1, '\\');
}


TreeNode* findMin(TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}


TreeNode* deleteNode(TreeNode* root, float value) {
    if (root == NULL) {
        return root;
    }
    if (value < root->value) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->value) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        TreeNode* temp = findMin(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}


int hasNodeWithMatchingDegree(TreeNode* root, float value) {
    if (root == NULL) {
        return 0;
    }
    int degree = 0;
    if (root->left != NULL) degree++;
    if (root->right != NULL) degree++;
    if (root->value == value && root->value == (float)degree) {
        return 1;
    }
    if (hasNodeWithMatchingDegree(root->left, value) || hasNodeWithMatchingDegree(root->right, value)) {
        return 1;
    }
    return 0;
}


void printAllNodesWithMatchingDegree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    int degree = 0;
    if (root->left != NULL) degree++;
    if (root->right != NULL) degree++;
    if (root->value == (float)degree) {
        printf("%.2f ", root->value);
    }
    printAllNodesWithMatchingDegree(root->left);
    printAllNodesWithMatchingDegree(root->right);
}


void saveTreeToFile(TreeNode* root, FILE* file) {
    if (root == NULL) {
        fprintf(file, "#\n");
        return;
    }
    fprintf(file, "%.2f\n", root->value);
    saveTreeToFile(root->left, file);
    saveTreeToFile(root->right, file);
}


TreeNode* loadTreeFromFile(FILE* file) {
    char buffer[256];
    if (!fgets(buffer, sizeof(buffer), file) || buffer[0] == '#') {
        return NULL;
    }
    float value;
    sscanf(buffer, "%f", &value);
    TreeNode* root = createNode(value);
    root->left = loadTreeFromFile(file);
    root->right = loadTreeFromFile(file);
    return root;
}


void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    TreeNode* root = NULL;
    int choice;
    char input[256];
    float value;


    FILE* file = fopen(DATA_FILE, "r");
    if (file != NULL) {
        root = loadTreeFromFile(file);
        fclose(file);
    }

    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить новый узел\n");
        printf("2. Текстовая визуализация дерева\n");
        printf("3. Удалить узел\n");
        printf("4. Определить число вершин, степень которых совпадает со значением элемента\n");
        printf("5. Выйти\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите значение для добавления: ");
                scanf("%f", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Текстовая визуализация дерева:\n");
                printTree(root, 0, '-');
                break;
            case 3:
                printf("Введите значение для удаления: ");
                scanf("%f", &value);
                root = deleteNode(root, value);
                break;
            case 4:
                printf("Введите значение для поиска или 'all' для вывода всех вершин с совпадающей степенью: ");
                scanf("%s", input);
                if (strcmp(input, "all") == 0) {
                    printf("Все вершины, чьи степени совпадают с их значениями: ");
                    printAllNodesWithMatchingDegree(root);
                    printf("\n");
                } else {
                    if (sscanf(input, "%f", &value) == 1) {
                        if (value == (int)value) {  // Проверка, что значение целое
                            int result = hasNodeWithMatchingDegree(root, value);
                            printf("%d\n", result);
                        } else {
                            printf("Значение должно быть целым числом.\n");
                        }
                    } else {
                        printf("Неверный ввод.\n");
                    }
                }
                break;
            case 5:
                file = fopen(DATA_FILE, "w");
                if (file != NULL) {
                    saveTreeToFile(root, file);
                    fclose(file);
                }
                freeTree(root);
                return 0;
            default:
                printf("Неверный выбор. Пожалуйста, попробуйте снова.\n");
        }
    }
    return 0;
}