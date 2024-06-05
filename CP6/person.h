#ifndef __person_h__
#define __person_h__

typedef struct {
    char name[25];
    char sex[3];
    int mark1; // Математика
    int mark2; // Физика
    int mark3; // Химия
    int mark4; // Биология
    int mark5; // История
    int mark6; // География
    int mark7; // Литература
} person;

#endif