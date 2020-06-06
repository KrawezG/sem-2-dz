#include "main.h"

//файл с функциями для работы с books.csv


//функция для создания нового элемента дерева
struct books* tallocbooks(void) {
    return (struct books*) malloc(sizeof(struct books));
}

//функция для загрузки дерева из файла
struct books* loadbookstree(struct books* p) {
    int cond;
    FILE* file;
    file = openfile("books.csv", "r+");
    char* str;
    char* s;
    prevbooks = NULL;
    //  printf("vhod loadbooktree\n");
    str = getstr1(file);

    while ((str != NULL)) {

        //printf("vhod v while loadbooktree\n");
        s = extractstr(str, 1);
        p = addbookstree(p, str, s, NULL);
        if (s != NULL)
            free(s);
        free(str);
        //str = getstr1(file);
        if (treemark == 1) {
            str = NULL;
        }
        else {
            str = getstr1(file);
        }
    }
    // printf("vyhod loadbooktree\n");
    fclose(file);
    treemark = 0;
    return p;

}

//функция для добавления элемента в дерево
struct books* addbookstree(struct books* p, char* str, char* s, struct books* prev) {
    // printf("vhod addbooktree\n");
    // char* s;
    int cond;
    //  s = extractstr(str, 1);
      //printf("ISBN - %s \n", s);
    if (p == NULL) {
        //    printf("p null\n");
        p = tallocbooks();
        bookstreeadd(p, str);
        p->left = p->right = NULL;
        p->parent = prev;
        //   printf("zapis knigi\n");
    }
    else if ((cond = strcmp(s, p->ISBN)) == 0)
        printf("book already exist\n");
    else if (cond < 0) {
        //    printf("left addbooktree\n");
        p->left = addbookstree(p->left, str, s, p);
    }

    else {
        //   printf("right addbooktree\n");
        p->right = addbookstree(p->right, str, s, p);

    }
    // printf("vyhod addbooktree\n");
    return p;
}

//функция для записи данных в ячейку
void bookstreeadd(struct books* p, char* str) {
    // printf("vhod bookadd\n");
    p->ISBN = extractstr(str, 1);
    //printf("ISBN - %s, p = %d \n", p->ISBN, (int)p);
    p->author = extractstr(str, 2);
    p->title = extractstr(str, 3);
    p->amount = extractint(str, 4);
    p->count = extractint(str, 5);
    //printf("bookadd\n");
}

//функция для записи новой книги в дерево
void bookstreeaddnew(struct books* p) {
    printf("\nVvedite str:");
    char* str;
    str = readstr();
    //    scanf("%s", str);
    char* s = extractstr(str, 1);
    if ((strlen(str) < 20) || (strlen(s) != 10)) {
        printf("wrong data\n");
        return;
    }

    p = addbookstree(p, str, s, NULL);
    free(s);
    free(str);
    return;
}

//функция для удаления студента
void bookstreedelete(struct books* p) {
    printf("\nEnter ISBN:");
    char* str;
    struct books* delp;
    str = readstr();
    if (strlen(str) != 10) {
        printf("wrong IBSN\n");
        return;
    }
    printf("str - %s\n", str);
    delp = searchbookstree(p, str);
    if (delp->amount > delp->count) {
        printf("Some books now in use \n");
        struct booklease* el = bookleasenodesearchISBN1(*rootbooklease, str);
        printf("nearest return date %s\n", el->returndate);
        return;
    }
    //printf("vozvrats delp = %d\n", (int)delp);
    //printf(" |%d| |%s| %d \n", (int)delp, delp->ISBN, (int)(delp->parent));
    if (delp == NULL) {
        printf("nothing found\n");
        return;
    }
    deletebookstree(delp);
    free(str);
    return;
}

//функция для удаления ячейки дерева
void deletebookstree(struct books* delel1) {
    //printf("vhod deletebookstree\n");
    struct books* prev1;
    //printf(" %d \n", (int)delel1);
    struct books* delel;
    delel = delel1;
    int i = 0;
    prev1 = (delel->parent);
    //printf("pered if\n");
    struct books* nextright;
    //printf("pered if\n");
    if ((delel->left == NULL) && (delel->right == NULL)) {
        //printf("net zavisimyh\n");
        if (delel->parent == NULL) {
            *rootbooks = NULL;
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
                *rootbooks = delel->right;
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
                *rootbooks = delel->left;
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
            *rootbooks = nextright;
        }
        else {
            if (prev1->left == delel)
                prev1->left = nextright;
            if (prev1->right == delel)
                prev1->right = nextright;
        }
    }
    free(delel->ISBN);
    free(delel->title);
    free(delel->author);
    free(delel);
    // printf("vyhod addbooktree\n");
    //printf("vyhod deletebookstree\n");
    return;
}

//функция для поиска студента по номеру зачетной книжки
struct books* searchbookstree(struct books* p, char* str) {
    if (p == NULL) {
        return NULL;
    }
    int cond = strcmp(str, p->ISBN);
    //printf("condition %d\n", cond);
    if ((cond) > 0) {
        return searchbookstree(p->right, str);
    }
    else if ((cond) < 0) {
        return searchbookstree(p->left, str);
    }

    return p;
}

//функция для печати всех элементов дерева
void printbookstree(struct books* p) {
    //printf("vhod printbook");
    if (p != NULL) {
        printbookstree(p->left);

        printf(" %-10s | %-30s  | %-30s | %-3d    |%-3d\n", p->ISBN, p->title, p->author, p->amount, p->count);
        printbookstree(p->right);
    }
}

//функция для возврата данных в файл
void returnbookstree(struct books* p) {
    FILE* fileclose;
    fileclose = openfile("books.csv", "w");
    writebookstree(p, fileclose);
    fclose(fileclose);
}

//функция для печати ячеек дерева в файл
void writebookstree(struct books* p, FILE* file) {
    if (p != NULL) {
        writebookstree(p->left, file);
        fprintf(file, "%s;%s;%s;%d;%d\n", p->ISBN, p->author, p->title, p->amount, p->count);
        //fprintf(file, "%s;%s;%s;%d;%d\n", p->ISBN, p->author, p->title, p->amount, p->count);
        writebookstree(p->right, file);
    }
}

//функция для освобождения дерева
void freebookstree(struct books* p) {
    if (p != NULL) {
        freebookstree(p->left);
        free(p->left);
        free(p->ISBN);
        free(p->title);
        free(p->author);
        freebookstree(p->right);
        free(p->right);
    }
}

//функция для поиска книги по ISBN и печати
void searchbookstreebyISBN(struct books* p) {
    char* str;
    printf("\nEnter book ISBN:");
    str = readstr();
    if ((strlen(str)) != 10) {
        printf("Wrong ISBN");
        return;
    }
    struct books* find;
    find = searchbookstree(p, str);
    if (find == NULL) {
        printf("Nothing found");
        return;
    }
    printf("ISBN %s |Title %s  | Author  %s |  Amount %d | Count %d\n", find->ISBN, find->title, find->author, find->amount, find->count);
}

//функция для выдачи книги студенту
void giveoutbook(struct books* p) {
    printf("\nEnter ISBN:");
    char* strISBN;
    char* strID;

    strISBN = readstr();
    if (strlen(strISBN) != 10) {
        printf("wrong IBSN\n");
        return;
    }
    printf("\nEnter students ID:");

    struct books* chanp;
    struct students* test;
    strID = readstr1();
    if (strlen(strID) != 6) {
        printf("wrong IBSN\n");
        return;
    }
    chanp = searchbookstree(p, strISBN);
    test = searchstudentstree(*rootstudents, strID);
    if (chanp == NULL || test == NULL) {
        printf("wrong data\n");
        return;
    }
    if (chanp->count == 0) {
        printf("Not enough books\n");

        return;
    }
    //int c = (chanp->count);
    (chanp->count)--;
    struct tm* u;
    char* time1 = malloc(15 * sizeof(char));
    memset(time1, 0, 15);
    const time_t timer = time(NULL);
    u = localtime(&timer);
    u->tm_mday += ADD_DAYS;
    time_t next = mktime(u);
    u = localtime(&next);
    strftime(time1, 13, "\"%d.%m.%Y\"", u);
    //printf("time1  = %s\n", time1);
    addbookleasenode1(strID, strISBN, time1);
    //printf("marker 1, %d\n", (int)*rootbooklease);
    //free(strID);
    //free(strISBN);
    //free(u);

}

//функция для возврата книги студентом
void returnbook(struct books* p) {
    printf("\nEnter ISBN:");
    char* strISBN;
    char* strID;

    strISBN = readstr();
    if (strlen(strISBN) != 10) {
        printf("wrong IBSN\n");
        return;
    }
    printf("\nEnter students ID:");

    struct books* chanp;
    struct students* test;
    strID = readstr1();
    if (strlen(strID) != 6) {
        printf("wrong ID\n");

        return;
    }
    chanp = searchbookstree(p, strISBN);
    test = searchstudentstree(*rootstudents, strID);
    if ((chanp == NULL) || (test == NULL)) {
        printf("wrong data\n");
        return;
    }
    struct booklease* delel = bookleasenodesearch(*rootbooklease, strISBN, strID);
    if (delel == NULL) {
        printf("student doesn't have this book\n");
        return;
    }
    chanp->count++;
    //printf("before del, %d\n", (int)delel);
    bookleasenodedelete(delel);

}

// функция для печати взятых книг
void printbookstudents(struct books* p) {
    printf("\nVvedite ISBN:");
    char* strISBN;
    struct books* delp;
    strISBN = readstr();
    bookleasenodeprintbyISBN(*rootbooklease, strISBN);
    free(strISBN);
}