#include "main.h"


//файл с функциями  для работы с файлом students.csv

//функция создание нового элемента дерева
struct students* tallocstudents(void) {
    return (struct students*) malloc(sizeof(struct students));
}

//функция загрузки дерева из файла
struct students* loadstudentstree(struct students* p) {
    int cond;
    FILE* file;
    file = openfile("students.csv", "r+");
    char* str;
    char* s;
    prevstudents = NULL;
    //  printf("vhod loadbooktree\n");
    str = getstr1(file);

    while ((str != NULL)) {

        //printf("vhod v while loadstudentstree\n");
        s = extractstr(str, 1);
        p = addstudentstree(p, str, s, NULL);
        //printf("before free loadstudentstree, %d\n", (int)s);
        putchar('9');
        //if (s != NULL)
        free(s); putchar('0');
        //printf("first free loadstudentstree, %d\n", (int)str);
        free(str); putchar('1');
        //printf("second free loadstudentstree\n");
        //str = getstr1(file);
        if (treemark == 1) {
            str = NULL;
        }
        else {
            str = getstr1(file);
        }
        //printf("vyhod v while loadstudentstree\n");
    }
    //printf("vyhod loadstudentstree\n");
    fclose(file);
    treemark = 0;
    return p;

}

//функция добавления элемента в дерево
struct students* addstudentstree(struct students* p, char* str, char* s, struct students* prev) {
    // printf("vhod addbooktree\n");
    int cond;
    //printf("ID - %s \n", s);
    if (p == NULL) {
        //    printf("p null\n");
        p = tallocstudents();
        studentstreeadd(p, str);
        p->left = p->right = NULL;
        p->parent = prev;
        //   printf("zapis knigi\n");
    }
    else if ((cond = strcmp(s, p->ID)) == 0)
        printf("student already exist\n");
    else if (cond < 0) {
        //    printf("left addbooktree\n");
        p->left = addstudentstree(p->left, str, s, p);
    }

    else {
        //   printf("right addbooktree\n");
        p->right = addstudentstree(p->right, str, s, p);

    }
    //printf("vyhod addstudenttree\n");
    return p;
}

//функция добавления элемента в дерево
struct students* addstudentstree1(struct students* p, char* strID , char* strsurname, char* strname, char* strpatronymic, char* strfaculty, char* strspeciality, struct students* prev) {
    // printf("vhod addbooktree\n");
    int cond;
    if (p == NULL) {
        //    printf("p null\n");
        p = tallocstudents();
        p->ID = strID;
        //printf("ID - %s, p = %d \n", p->ID, (int)p);
        p->surname = strsurname;
        p->name = strname;
        p->patronymic = strpatronymic;
        p->faculty = strfaculty;
        p->speciality = strspeciality;
        p->left = p->right = NULL;
        p->parent = prev;
    }
    else if ((cond = strcmp(strID, p->ID)) == 0)
        printf("student already exist\n");
    else if (cond < 0) {
        //    printf("left addbooktree\n");
        p->left = addstudentstree1(p->left, strID, strsurname, strname, strpatronymic, strfaculty, strspeciality, p);
    }

    else {
        //   printf("right addbooktree\n");
        p->right = addstudentstree1(p->right, strID, strsurname, strname, strpatronymic, strfaculty, strspeciality, p);

    }
    //printf("vyhod addstudenttree\n");
    return p;
}

//функция добавления данных в ячейку дерева
void studentstreeadd(struct students* p, char* str) {
    // printf("vhod bookadd\n");
    p->ID = extractstr(str, 1);
    //printf("ID - %s, p = %d \n", p->ID, (int)p);
    p->surname = extractstr(str, 2);
    p->name = extractstr(str, 3);
    p->patronymic = extractstr(str, 4);
    p->faculty = extractstr(str, 5);
    p->speciality = extractstr(str, 6);
    //printf("studentadd\n");
}

// фуекция добавления в дерево нового студента
void studentstreeaddnew(struct students* p) {
    char* strID;
    char* strsurname;
    char* strname;
    char* strpatronymic;
    char* strfaculty;
    char* strspeciality;
    printf("\nEbter ID:");
    strID = readstr();
    if (strlen(strID) != 6) {
        printf("wrong data\n");
        return;
    }
    printf("\nEbter surname:");
    strsurname = readstr1();
    printf("\nEbter name:");
    strname = readstr1();
    printf("\nEbter patronymic:");
    strpatronymic = readstr1();
    printf("\nEbter faculty:");
    strfaculty = readstr1();
    printf("\nEbter speciality:");
    strspeciality = readstr1();
    /*
    printf("\nEnter str:");
    char* str;
    str = readstr();
    //    scanf("%s", str);
    char* s = extractstr(str, 1);
    if ((strlen(str) < 20) || (strlen(s) != 6)) {
        printf("wrong data\n");
        return;
    }
    s = extractstr(str, 2);
    */
    p = addstudentstree1(p, strID, strsurname, strname, strpatronymic, strfaculty, strspeciality, NULL);
    return;
}

//функция удаления студента
void studentstreedelete(struct students* p) {
    printf("\nEnter ID:");
    char* str;
    struct students* delp;
    str = readstr();
    if (strlen(str) != 6) {
        printf("wrong ID\n");
        return;
    }
    //printf("str - %s\n", str);
    delp = searchstudentstree(p, str);
    //printf("vozvrats delp = %d\n", (int)delp);
    //printf(" |%d| |%s| %d \n", (int)delp, delp->ISBN, (int)(delp->parent));
    if (delp == NULL) {
        printf("nothing found\n");
        free(str);
        return;
    }
    int i = bookleasenodesearchID(*rootbooklease, str);
    if (i > 0) {
        printf("Student have library books, he cannot be deleted\n");
        free(str);
        return;
    }
    deletestudentstree(delp);
    free(str);
    return;
}

//функция удаления ячейки дерева
void deletestudentstree(struct students* delel1) {
    //printf("vhod deletebookstree\n");
    struct students* prev1;
    //printf(" %d \n", (int)delel1);
    struct students* delel;
    delel = delel1;
    int i = 0;
    prev1 = (delel->parent);
    //printf("pered if\n");
    struct students* nextright;
    //printf("pered if\n");
    if ((delel->left == NULL) && (delel->right == NULL)) {
        //printf("net zavisimyh\n");
        if (delel->parent == NULL) {
            *rootstudents = NULL;
        }
        else {
            if (prev1->left == delel)
                prev1->left = NULL;
            if (prev1->right == delel)
                prev1->right = NULL;
        }

    }
    else if ((delel->left == NULL) || (delel->right == NULL)) {
        //printf("1 zavisimy\n");

        if (delel->left == NULL) {
            if (delel->parent == NULL) {
                *rootstudents = delel->right;
            }
            else {
                if (prev1->left == delel)
                    prev1->left = delel->right;
                if (prev1->right == delel)
                    prev1->right = delel->right;
            }
        }
        else {
            if (delel->parent == NULL) {
                *rootstudents = delel->left;
            }
            else {
                if (prev1->left == delel)
                    prev1->left = delel->left;
                if (prev1->right == delel)
                    prev1->right = delel->left;
            }
        }
    }
    else {
        //printf("2 zavisimyh\n");
        nextright = delel->right;
        while (nextright->left != NULL) {
            nextright = nextright->left;
            i++;
        }
        if (i > 0) {
            nextright->parent->left = NULL;
        }
        nextright->left = delel->left;
        if (i > 0) {
            nextright->right = delel->right;
        }
        delel->left->parent = nextright;
        if (delel->parent == NULL) {
            *rootstudents = nextright;
        }
        else {
            if (prev1->left == delel)
                prev1->left = nextright;
            if (prev1->right == delel)
                prev1->right = nextright;
        }
    }
    free(delel->ID);
    free(delel->surname);
    free(delel->name);
    free(delel->patronymic);
    free(delel->faculty);
    free(delel->speciality);
    free(delel);
    // printf("vyhod addbooktree\n");
    //printf("vyhod deletestudentstree\n");
    return;
}

//функция поиска по номеру зачетной книжки студента
struct students* searchstudentstree(struct students* p, char* str) {
    if (p == NULL) {
        return NULL;
    }
    int cond = strcmp(str, p->ID);
    //printf("condition %d\n", cond);
    if ((cond) > 0) {
        return searchstudentstree(p->right, str);
    }
    else if ((cond) < 0) {
        return searchstudentstree(p->left, str);
    }

    return p;
}

//функция печати всех студентов
void printstudentstree(struct students* p) {
    //printf("vhod printbook");
    if (p != NULL) {
        printstudentstree(p->left);

        printf(" %-6s | %-30s | %-15s | %-30s | %-7s | %-30s\n", p->ID, p->surname, p->name, p->patronymic, p->faculty, p->speciality);
        printstudentstree(p->right);
    }
}

//функция печати книг, имеющихся у студента
void printstudentbooks(struct students* p) {
    printf("\nEnter ID:");
    char* strID;
    struct students* delp;
    strID = readstr();
    bookleasenodeprintbyID(*rootbooklease, strID);
    free(strID);
}

//функция возвращения данных в файл
void returnstudentstree(struct students* p) {
    FILE* fileclose;
    fileclose = openfile("students.csv", "w");
    writestudentstree(p, fileclose);
    fclose(fileclose);
}

//функция ззаписи данных в файл
void writestudentstree(struct students* p, FILE* file) {
    if (p != NULL) {
        writestudentstree(p->left, file);
        fprintf(file, "%s;%s;%s;%s;%s;%s\n", p->ID, p->surname, p->name, p->patronymic, p->faculty, p->speciality);
        //fprintf(file, "%s;%s;%s;%d;%d\n", p->ISBN, p->author, p->title, p->amount, p->count);
        writestudentstree(p->right, file);
    }
}

//функция очистки дерева
void freestudentstree(struct students* p) {
    if (p != NULL) {
        freestudentstree(p->left);
        free(p->left);
        free(p->ID);
        free(p->surname);
        free(p->name);
        free(p->patronymic);
        free(p->faculty);
        free(p->speciality);
        freestudentstree(p->right);
        free(p->right);

    }
}

//функция создания бэкапа
void studentstreebackup(struct students* p) {

    char backupname[50] = { 0 };
    struct tm* t;
    time_t timer = time(NULL);
    t = localtime(&timer);
    strftime(backupname, 50, "students_%d-%m-%Y_%H-%M-%S.csv", t);
    FILE* filebackup = openfile(backupname, "w");
    writestudentstree(p, filebackup);
    fclose(filebackup);
    return;
}

//функция загрузки дерева из бэкапа
struct students* loadstudentstreebackup(struct students* p) {
    printf("Enter backup name:");
    char* backupname = readstr();
    char* str;
    char* s;
    FILE* backup = openfile(backupname, "r");

    if (backup == NULL) {
        printf("\nwrong backup filename");
        return p;
    }
    struct students* pbackup = NULL;
    freestudentstree(p);
    str = getstr1(backup);

    while ((str != NULL)) {

        //printf("vhod v while loadbooktree\n");
        s = extractstr(str, 1);
        pbackup = addstudentstree(pbackup, str, s, NULL);
        free(s);
        //str = getstr1(file);
        if (treemark == 1) {
            str = NULL;
        }
        else {
            str = getstr1(backup);
        }
    }
    // printf("vyhod loadbooktree\n");
    fclose(backup);
    treemark = 0;
    return pbackup;
}

//функция поиска студента по имени
void searchstudentstreebysurname(struct students* p) {
    printf("\nPrint surname:");
    char* str;
    int i;
    str = readstr();
    i = printstudentstreebysurname(p, str);
    if (i == 0)
        printf("nothing found");

}

//функция печати студентов по имени
int  printstudentstreebysurname(struct students* p, char* s) {
    int i = 0;
    int cond;
    if (p != NULL) {
        printstudentstreebysurname(p->left, s);
        if ((cond = strcmp(s, p->surname)) == 0) {
            printf("ID %s |Surname %s  | Name  %s |  Patronymic %s | Faculty %s | Speciality %s\n", p->ID, p->surname, p->name, p->patronymic, p->faculty, p->speciality);
            i++;
        }

        //fprintf(file, "%s;%s;%s;%d;%d\n", p->ISBN, p->author, p->title, p->amount, p->count);
        printstudentstreebysurname(p->right, s);
    }
    return i;
}