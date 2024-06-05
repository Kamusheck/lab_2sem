# Отчет по лабораторной работе № 23

## по курсу "Алгоритмы и структуры данных"

Студент группы M80-108Б-23 Исмаилова Камила

Работа выполнена

Преподаватель: каф. 806 Севастьянов Виктор Сергеевич

1. **Тема**: Динамические структуры данных. Обработка деревьев
2. **Цель работы**: Разработать программу на языке C для построения и обработки дерева общего вида или упорядоченного двоичного дерева, содержащего узлы типа float, int, char или enum. Основные функции работы с деревьями реализовать в виде универсальных процедур или функций. Реализовать добавление, удаление узла, текстовую визуализацию дерева и вычисление значения некоторой функции от дерева.
3. **Задание (вариант №9)**: Определить степень вершин двоичного дерева, которые совпадают со значением элемента.
4. **Идея, метод, алгоритм решения задачи**:. прописать логику упорядоченного дерева,чтобы слева значения были меньше корня, а справа больше. С помощью этого алгоритм основной задачи будет идти быстрее. Соавниванием значение , после смотрим на дочерние узлы.
5. **Сценарий выполнения работы**:
   прописать основную функцию. При введении 0, 1 ,2 поиск вершин с тем же количеством ветвей. 1, если найдено , 0 - не найдено. all для всех значений- выводится количество совпавших и значения вершин.

6. **Протокол**:

```
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

```

7. **Замечания автора** не совсем однозначна задана задача, но по итогу искались вершины со значением 0, 1, 2 , из которых исходили ветви в количестве 0, 1, 2 соответсвенно
8. **Выводы**: В процессе выполнения лабораторной работы были изучены основы работы с динамическими структурами данных и обработкой деревьев. Разработанная программа позволяет строить и обрабатывать деревья общего вида или упорядоченные двоичные деревья. Полученные знания о деревьях и их обработке могут быть полезны в дальнейшем при решении различных задач, связанных с хранением и обработкой иерархических данных. В ходе выполнения работы было интересно разбираться с алгоритмами обхода деревьев и реализацией различных операций над ними.
