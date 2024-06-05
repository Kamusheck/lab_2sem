#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <output_file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "w");
    if (!f) {
        perror("Unable to open file");
        return 2;
    }

    fprintf(f, "Имя:Пол:Математика:Физика:Химия:Биология:История:География:Литература\n");

    char girlima[][9] = {"Маша", "Даша", "Лиза"};
    char fam[][13] = {"Кандин", "Иванов", "Боринд"};
    char manima[][11] = {"Макар", "Антип", "Рюрик"};

    srand(time(NULL));

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            fprintf(f, "%sа%s:Ж:%d:%d:%d:%d:%d:%d:%d\n", fam[j], girlima[i], rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1);
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            fprintf(f, "%s%s:М:%d:%d:%d:%d:%d:%d:%d\n", fam[j], manima[i], rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1);
        }
    }

    fclose(f);
    return 0;
}