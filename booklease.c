include "main.h"

struct booklease* loadbookleasenode() {
    FILE* file;
    file = openfile("students_books.csv", "r+");
    char* str;
    struct booklease* p = NULL;


    str = getstr1(file);

    while ((str != NULL)) {
        p = addbookleasenode(p, NULL, str);
        if (treemark == 1) {
            str = NULL;
        }
        else {
            str = getstr1(file);
        }
    }
    fclose(file);
    treemark = 0;
    return p;
}
struct booklease* addbookleasenode(struct booklease* p, struct booklease* prev, char* str) {
    struct booklease* currenttope = tallocbooklease();
    bookleasenodeadd(currenttope, str);
    currenttope->next = p;
    currenttope->parent = NULL;
    if (p != NULL) {

        p->parent = currenttope;
    }
    p = currenttope;
    return p;
}
void addbookleasenode1(char* ID, char* ISBN, char* time) {
    struct booklease* currenttope = tallocbooklease();
    struct booklease* p = *rootbooklease;
    currenttope->ISBN = ISBN;
    currenttope->ID = ID;
    currenttope->returndate = time;
    currenttope->next = p;
    currenttope->parent = NULL;
    if (p != NULL) {

        p->parent = currenttope;
    }
    *rootbooklease = currenttope;

}
struct booklease* tallocbooklease(void) {
    return (struct booklease*) malloc(sizeof(struct booklease));
}
void bookleasenodeadd(struct booklease* p, char* str) {
    // printf("vhod bookadd\n");
    p->ISBN = extractstr(str, 1);
    p->ID = extractstr(str, 2);
    p->returndate = extractstr(str, 3);
}
struct booklease* bookleasenodesearch(struct booklease* p, char* s1, char* s2) {
    while (p != NULL) {
        if ((strcmp(s1, p->ISBN) == 0) && (strcmp(s2, p->ID) == 0))
            return p;
        p = p->next;

    }
    return NULL;
}
void bookleasenodedelete(struct booklease* p) {
    //printf("vhod deletenode\n");
    if (p->parent == NULL) {
        *rootbooklease = p->next;
    }
    else {
        (p->parent)->next = p->next;
    }
    if (p->next != NULL) {
        (p->next)->parent = p->parent;
    }
    //printf("before free\n");
    free(p->ID);
    free(p->ISBN);
    free(p->returndate);

}
int  bookleasenodesearchISBN(struct booklease* p, char* s1) {
    int i = 0;
    while (p->next != NULL) {
        if ((strcmp(s1, p->ISBN) == 0))
            i++;
        p = p->next;

    }
    return i;
}
struct booklease* bookleasenodesearchISBN1(struct booklease* p, char* s1) {
    struct booklease* el;
    while (p->next != NULL) {
        if ((strcmp(s1, p->ISBN) == 0))
            el = p;
        p = p->next;

    }
    return el;
}
void  bookleasenodeprintbyISBN(struct booklease* p, char* s1) {
    struct booklease* el;
    while (p->next != NULL) {
        struct students* find;
        find = searchstudentstree(*rootstudents, p->ID);
        if (find == NULL) {
            printf("Nothing found");
            return;
        }
        printf("ID %s |Surname %s  | Name  %s |  Patronymic %s | Faculty %s| Speciality %s| return date %s\n", find->ID, find->surname, find->name, find->patronymic, find->faculty, find->speciality, p->returndate);
        p = p->next;

    }
    return;
}
int  bookleasenodesearchID(struct booklease* p, char* s1) {
    int i = 0;
    while (p->next != NULL) {
        if ((strcmp(s1, p->ID) == 0))
            i++;
        p = p->next;

    }
    return i;
}
void  bookleasenodeprintbyID(struct booklease* p, char* s1) {
    int i = 0;
    while (p->next != NULL) {
        if ((strcmp(s1, p->ID) == 0)) {
            struct books* find;
            find = searchbookstree(*rootbooks, p->ISBN);
            if (find == NULL) {
                printf("Nothing found");
                return;
            }
            printf("ISBN %s |Title %s  | Author  %s |  Amount %d | Count %d| return date %s\n", find->ISBN, find->title, find->author, find->amount, find->count, p->returndate);
        }
        p = p->next;

    }
    return;
}
void returnbookleasenode(struct booklease* p) {
    FILE* fileclose;
    fileclose = openfile("students_books.csv", "w");
    writebookleasenode(p, fileclose);
    fclose(fileclose);

}
void writebookleasenode(struct booklease* p, FILE* file) {
    if (p != NULL) {
        writebookleasenode(p->next, file);
        fprintf(file, "%s;%s;%s\n", p->ISBN, p->ID, p->returndate);
        //fprintf(file, "%s;%s;%s;%d;%d\n", p->ISBN, p->author, p->title, p->amount, p->count);

    }
}
void printbookleasenode(struct booklease* p) {
    if (p != NULL) {
        printbookleasenode(p->next);
        printf("%s;%s;%s\n", p->ISBN, p->ID, p->returndate);
        //fprintf(file, "%s;%s;%s;%d;%d\n", p->ISBN, p->author, p->title, p->amount, p->count);

    }
}
void freebookleasenode(struct booklease* p) {
    if (p != NULL) {
        freebookleasenode(p->next);
        free(p->next);
        free(p->ISBN);
        free(p->ID);
        free(p->returndate);
    }
}
