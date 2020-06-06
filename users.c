#include "main.h"



//файл с функциями для работы с users.csv

//функция создания нового элемента дерева
struct users* tallocusers(void) {
    return (struct users*) malloc(sizeof(struct users));
}

//функция загрузки дерева из файла
struct users* loaduserstree(struct users* p) {
    int cond;
    FILE* file;
    file = openfile("users.csv", "r+");
    char* str;
    char* s;
    prevusers = NULL;
    //  printf("vhod loadbooktree\n");
    str = getstr1(file);

    while ((str != NULL)) {

        //printf("vhod v while loadbooktree\n");
        s = extractstr(str, 1);
        p = adduserstree(p, str, s, NULL);
        free(s);
        //str = getstr1(file);
        free(str);
        if (treemark == 1) {

            str = NULL;
        }
        else {
            str = getstr1(file);
        }
    }

    fclose(file);
    treemark = 0;
    //free(s);
     //printf("vyhod loadbooktree\n");
    return p;

}

//функция добавления элемента в дерево
struct users* adduserstree(struct users* p, char* str, char* s, struct users* prev) {
    // printf("vhod addbooktree\n");
    // char* s;
    int cond;
    //  s = extractstr(str, 1);

    if (p == NULL) {
        //    printf("p null\n");
        p = tallocusers();
        userstreeadd(p, str);
        p->left = p->right = NULL;
        p->parent = prev;
        //   printf("zapis knigi\n");
    }
    else if ((cond = strcmp(s, p->login)) == 0)
        printf("user already exist\n");
    else if (cond < 0) {
        //    printf("left addbooktree\n");
        p->left = adduserstree(p->left, str, s, p);
    }

    else {
        //   printf("right addbooktree\n");
        p->right = adduserstree(p->right, str, s, p);

    }
    // printf("vyhod addbooktree\n");
    return p;
}

// функция записи элемента в ячейку дерева
void userstreeadd(struct users* p, char* str) {
    // printf("vhod bookadd\n");
    p->login = extractstr(str, 1);
    //printf("ID - %s, p = %d \n", p->ID, (int)p);
    p->password = extractstr(str, 2);
    p->rightsstudents = extractint(str, 3);
    p->rightsbooks = extractint(str, 4);
    //printf("bookadd\n");
}

// функция авторизации
int authorization(struct users* p) {
    char* strlogin;
    char* strpassword;
    int cond;
    struct users* find;
    printf("\nEnter your login:");
    strlogin = readstr1();
    find = searchuserstree(p, strlogin);
    if (find == NULL) {
        printf("\nWrong login");
        return 0;
    }
    printf("\nEnter your password:");
    strpassword = readstr1();
    if ((cond = strcmp(strpassword, find->password)) == 0) {
        currentuser = find;
        return 1;
    }
    else {
        printf("\nWrong password");
        return 0;
    }
}

//функция поиска в дерева пользователя по логину
struct users* searchuserstree(struct users* p, char* str) {
    if (p == NULL) {
        return NULL;
    }
    int cond = strcmp(str, p->login);
    //printf("condition %d\n", cond);
    if ((cond) > 0) {
        return searchuserstree(p->right, str);
    }
    else if ((cond) < 0) {
        return searchuserstree(p->left, str);
    }

    return p;
}

//функция очистки дерева
void freeuserstree(struct users* p) {
    if (p != NULL) {
        freeuserstree(p->left);
        free(p->left);
        free(p->login);
        free(p->password);
        freeuserstree(p->right);
        free(p->right);

    }
}