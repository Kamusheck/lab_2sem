#include <stdio.h>
#include "person.h"

int ReadBase(person *person, FILE *file) {
    return fscanf(file, "%[^:]:%[^:]:%d:%d:%d:%d:%d:%d:%d\n",
                  person->name, person->sex,
                  &person->mark1, &person->mark2, &person->mark3,
                  &person->mark4, &person->mark5, &person->mark6,
                  &person->mark7) == 9;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    person person;
    FILE *base = fopen(argv[1], "r");
    if (!base) {
        perror("Unable to open file");
        return 2;
    }

    FILE *bin = fopen("bin", "wb");
    if (!bin) {
        perror("Unable to create binary file");
        fclose(base);
        return 3;
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), base);

    while (ReadBase(&person, base)) {
        fwrite(&person, sizeof(person), 1, bin);
    }

    fclose(bin);
    fclose(base);
    return 0;
}