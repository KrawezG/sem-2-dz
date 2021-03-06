#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <locale.h>
#include <Windows.h>
#include <time.h>
#define HASHSIZE 300
struct nlist {
    struct nlist* next;
    char* name;
    int defn;
};
struct books {
    char* ISBN;
    char* author;
    char* title;
    int amount;
    int count;
    struct books* left;
    struct books* right;
    struct books* parent;
};
struct students {
    char* ID;
    char* name;
    char* surname;
    char* patronymic;
    char* faculty;
    char* speciality;
    struct students* left;
    struct students* right;
    struct students* parent;
};
struct users {
    char* login;
    char* password;
    int rightsbooks;
    int rightsstudents;
    struct users* left;
    struct users* right;
    struct users* parent;
};
static struct nlist* hashtab[HASHSIZE];
 int treemark;
 struct books* prevbooks;
 struct students* prevstudents;
 struct users* prevusers;
 struct books** rootbooks;
 struct students** rootstudents;
 struct users** rootusers;
const char ordermod[] = "-o";
const char descstr[] = "DESC";
const char ascstr[] = "ASC";



//---------------------------------------------------���������

unsigned int hash(char* s);
struct nlist* delete1(char* name);
struct nlist* lookup(char* s);
struct books* tallocbooks(void);
struct students* tallocstudents(void);
void print();
FILE* openfile(char name[], char rights[]);
char* getstr1(FILE* file);
char* getword(FILE* file);
char* readstr();
char* extractstr(char* str, int num);
int extractint(char* str, int num);
struct books* loadbookstree(struct books* p);
struct books* addbookstree(struct books* p, char* str, char* s, struct books* prev);
void bookstreeadd(struct books* p, char* str);
void bookstreeaddnew(struct books* p);
void bookstreedelete(struct books* p);
struct books* searchbookstree(struct books* p, char* str);
void deletebookstree(struct books* );
void bookstreedelete(struct books* p);
void writebookstree(struct books* p, FILE* file);
void returnbookstree(struct books* p);

struct students* loadstudentstree(struct students* p);
struct students* addstudentstree(struct students* p, char* str, char* s, struct students* prev);
void studentstreeadd(struct students* p, char* str);
void studentstreeaddnew(struct students* p);
void studentstreedelete(struct students* p);
void deletestudentstree(struct students* delel1);
struct students* searchstudentstree(struct students* p, char* str);
void printstudentstree(struct students* p);
void returnstudentstree(struct students* p);
void writestudentstree(struct students* p, FILE* file);
void freestudentstree(struct students* p);
void studentstreebackup(struct students* p);
struct students* loadstudentstreebackup(struct students* p);
int  printstudentstreebysurname(struct students* p, char* s);
void searchstudentstreebysurname(struct students* p);

//---------------------------------------------------�������
unsigned int hash(char* s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 29 * hashval;
    return hashval % HASHSIZE;
}
struct nlist* delete1(char* name) {
    struct nlist* np;
    unsigned int hashval;
    if ((np = lookup(name)) == NULL) {
        printf(" nothing found\n");
    }
    else {
        free((void*)np->defn);
    }
    return np;
}
struct nlist* lookup(char* s) {
    struct nlist* np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}
struct books* tallocbooks(void) {
    return (struct books*) malloc(sizeof(struct books));
}

void print() {
    struct nlist* np;
    for (int i = 0; i < HASHSIZE; i++) {
        printf("Nodes for hash: %d\n", i);
        for (np = hashtab[i]; np != NULL; np = np->next) {
            printf("%d %s %d\n", i, np->name, np->defn);
        }
    }
}
FILE* openfile(char name[], char rights[]) {
    FILE* file;
    file = fopen(name, rights);
    if ((file) == NULL) {
        printf("%s\n", "cannot open file");
        exit(EXIT_FAILURE);
    }
    return file;
}
char* getstr1(FILE* file) {
    
        treemark = 0;
        
    
    int symbol;
    int i=1;
    char* string;
    string = (char*)malloc(sizeof(char));
    symbol = getc(file);
    while ((symbol  != '\n') && (symbol != EOF)) {
        string = (char*)realloc(string, i * sizeof(char));
        string[i - 1] = symbol&255;
        symbol = getc(file);
        i++;
    }
    if (symbol == EOF)
        treemark = 1;

    //printf(" %d, %i\n", (int)symbol,i);
    //printf("pered if");
  /*  if ((symbol == EOF) &&(i == 1)) {
               printf("symbol == EOF && i==1 EOF, exit");
 //              booksmark = 0;   
               return NULL;
        } else*/
        if ( i !=1){
        string[i-1] = '\0';
        printf("symbol = EOF && i !=1 %s, %i, %i\n", string, string[0], i);
        return string;
    }
    else {
        
        printf("else NULL\n");
        return NULL;
    }
}
char* getstr(FILE* file) {
    char symbol;
    int i=1;
    char* string;
    string = (char*)malloc(sizeof(char));
    for (i = 1; (symbol = getc(file)) != '\n' && (symbol != EOF); i++) {
        string = (char*)realloc(string, i * sizeof(char));
        string[i - 1] = symbol;
    }
    if (symbol == EOF ) {
        return NULL;
    }
    
    else {
        string[i - 1] = '\0';
        return string;
    }
}
char* readstr()
{
    printf("vhod readstr\n");
    int c;
    char* str = NULL;
    int i = 0;
    c = getchar();
    c = getchar();
    printf("schityvanie c = %c\n", c);
    while (c != '\n')
    {
        i++;
        str = (char*)realloc(str, (i + 1) * sizeof(char));
        str[i - 1] = c;
        c = getchar();
    }
    str[i] = '\0';
    return str;
}
char* getword(FILE* file) {
    char symbol;
    int i = 2;
    char* string;
    string = (char*)malloc(i * sizeof(char));
    while (isspace(symbol = getc(file))) {
        ;
    }
    if (symbol == EOF) {
        return NULL;
    }
    if (symbol == '\n') {
        ;
    }
    if (!isalpha(symbol)) {
        string = (char*)realloc(string, i * sizeof(char));
        string[i - 2] = symbol;
    }
    else {
        string[i - 2] = symbol;
        for (i = 2; (isalpha(symbol = getc(file))) != 0; i++) {
            string = (char*)realloc(string, i * sizeof(char));
            string[i - 1] = symbol;
        }
    }
    string[i - 1] = '\0';
    return string;
}
char* extractstr(char *str, int num) {
  //  printf("vhod extractstr\n");
    int symbol;
    int count = 1;
    int i = 0;
    int j = 0;
    char* string;
    while (count < num) {
        while (str[i] != ';') {
            i++;
        }
        count++;
        i++;
    }
 //   printf("doxod do neobh polya %d\n", i);
  //  int strlen = 1;
    string = (char*)malloc((j+1) * sizeof(char));
    while ((str[i] != ';')&& (str[i] != '\0')) {
   //     printf("schityvanie %d simvola %c\n", j, str[i]);
        string = (char*)realloc(string, (j+1) * sizeof(char));
        string[j] = str[i];
        j++;
        i++;
 //       strlen++;
    }
   // printf("vyhod extractstr\n");
    if (j > 0) {
        string = (char*)realloc(string, (j+1) * sizeof(char));
        string[j] = '\0';
        return string;
    }
    else {
        free(string);
        return NULL;
    }
}
int extractint(char* str, int num) {
    //printf("vhod extractstr\n");
    char symbol;
    int count = 1;
    int i = 0;
    int j = 0;
    char* string;
    int number;
    while (count < num) {
        while (str[i] != ';' ) {
            i++;
        }
        count++;
        i++;
    }
    //printf("doxod do neobh polya %d\n", i);
    int strlen = 2;
    string = (char*)malloc(strlen * sizeof(char));
    while ((str[i] != ';') && (str[i] != '\0') &&( str[i] != EOF)) {
    //    printf("schityvanie %d simvola %c\n", j, str[i]);
        string = (char*)realloc(string, strlen * sizeof(char));
        string[j] = str[i];
        j++;
        i++;
        strlen++;
    }
   // printf("vyhod extractstr\n");
    if (j > 0) {
        string[j ] = '\0';
        number = atoi(string);
        return number;
    }
    else {
        number = -1;
        return number;
    }
}
//-----------------------------------------------------������ books.csv
struct books* loadbookstree(struct books* p) {
    int cond;
    FILE* file;
    file = openfile("books.csv", "r+");
    char* str;
    char* s;
    prevbooks = NULL;
  //  printf("vhod loadbooktree\n");
    str = getstr1(file);

    while ((str != NULL) ) {
        
        printf("vhod v while loadbooktree\n");
        s = extractstr(str, 1);
        p = addbookstree(p, str, s, NULL);
        free(s);
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
struct books* addbookstree(struct books* p, char *str, char* s, struct books* prev) {
   // printf("vhod addbooktree\n");
   // char* s;
    int cond;
  //  s = extractstr(str, 1);
    printf("ISBN - %s \n", s);
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
void bookstreeadd(struct books* p, char* str) {
   // printf("vhod bookadd\n");
    p->ISBN = extractstr(str, 1);
    printf("ISBN - %s, p = %d \n", p->ISBN, (int)p);
    p->author = extractstr(str, 2);
    p->title = extractstr(str, 3);
    p->amount = extractint(str, 4);
    p->count = extractint(str, 5);
    //printf("bookadd\n");
}
void bookstreeaddnew(struct books* p) {
    printf("\nVvedite str:");
    char* str;
    str = readstr();
//    scanf("%s", str);
    char* s = extractstr(str, 1);
    if ((strlen(str) < 20)|| (strlen(s) != 10)) {
        printf("wrong data\n");
        return ;
    }
    
    p = addbookstree(p, str, s, NULL);
    free(s);
    free(str);
    return ;
}
void bookstreedelete(struct books* p) {
    printf("\nVvedite ISBN:");
    char* str;
    struct books* delp;
    str = readstr();
    if (strlen(str) != 10) {
        printf("wrong IBSN\n");
        return;
    }
    printf("str - %s\n", str);
    delp = searchbookstree(p, str);
    printf("vozvrats delp = %d\n", (int)delp);
    printf(" |%d| |%s| %d \n", (int)delp, delp->ISBN, (int)(delp->parent));
    if (delp == NULL) {
        printf("nothing found\n");
        return;
    }
    deletebookstree( delp);
    free(str);
    return;
}
void deletebookstree(  struct books* delel1) {
    printf("vhod deletebookstree\n");
    struct books* prev1;
    printf(" %d \n", (int)delel1);
    struct books* delel;
    delel = delel1;
    prev1 = (delel->parent);
    printf("pered if\n");
    struct books* nextright;
    printf("pered if\n");
    if ((delel->left == NULL) && (delel->right == NULL)) {
        printf("net zavisimyh\n");
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
        printf("1 zavisimy\n");

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
        printf("2 zavisimyh\n");
        nextright = delel->right;
        while (nextright->left != NULL) {
            nextright = nextright->left;
        }
        nextright->left = delel->left;
        delel->left->parent = nextright;
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
    free(delel->ISBN);
    free(delel->title);
    free(delel->author);
    free(delel);
    // printf("vyhod addbooktree\n");
    printf("vyhod deletebookstree\n");
    return ;
}

struct books* searchbookstree(struct books* p, char* str) {
    if (p == NULL) {
        return NULL;
    }
    int cond = strcmp(str, p->ISBN);
    printf("condition %d\n", cond);
         if ((cond) > 0) {
            return searchbookstree(p->right, str);
        }
        else if ((cond) < 0) {
            return searchbookstree(p->left, str);
        }
    
    return p;
}
void printbookstree(struct books* p) {
    //printf("vhod printbook");
    if (p != NULL) {
        printbookstree(p->left);
        printf("ISBN %s |Title %s  | Author  %s |  Amount %d | Count %d\n", p->ISBN, p->title, p->author, p->amount, p->count);
        printbookstree(p->right);
    }
}
void returnbookstree(struct books* p) {
    FILE* fileclose;
    fileclose = openfile("books1.csv", "w");
    writebookstree(p, fileclose);
    fclose(fileclose);
}
void writebookstree(struct books* p, FILE* file) {
    if (p != NULL) {
        writebookstree(p->left, file);
        fprintf(file, "%s;%s;%s;%d;%d\n", p->ISBN,p->author,p->title,p->amount,p->count);
        //fprintf(file, "%s;%s;%s;%d;%d\n", p->ISBN, p->author, p->title, p->amount, p->count);
        writebookstree(p->right, file);
    }
}
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
//-------------------------------------------------students.csv---------------------------
struct students* tallocstudents(void) {
    return (struct students*) malloc(sizeof(struct students));
}
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

        printf("vhod v while loadbooktree\n");
        s = extractstr(str, 1);
        p = addstudentstree(p, str, s, NULL);
        free(s);
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
struct students* addstudentstree(struct students* p, char* str, char* s, struct students* prev) {
    // printf("vhod addbooktree\n");
    // char* s;
    int cond;
    //  s = extractstr(str, 1);
    printf("ID - %s \n", s);
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
    // printf("vyhod addbooktree\n");
    return p;
}
void studentstreeadd(struct students* p, char* str) {
    // printf("vhod bookadd\n");
    p->ID = extractstr(str, 1);
    printf("ID - %s, p = %d \n", p->ID, (int)p);
    p->surname = extractstr(str, 2);
    p->name = extractstr(str, 3);
    p->patronymic = extractstr(str, 4);
    p->faculty = extractstr(str, 5);
    p->speciality = extractstr(str, 6);
    //printf("bookadd\n");
}
void studentstreeaddnew(struct students* p) {
    printf("\nVvedite str:");
    char* str;
    str = readstr();
    //    scanf("%s", str);
    char* s = extractstr(str, 1);
    if ((strlen(str) < 20) || (strlen(s) != 6)) {
        printf("wrong data\n");
        return;
    }
    s = extractstr(str, 2);
    p = addstudentstree(p, str, s, NULL);
    free(s);
    free(str);
    return;
}
void studentstreedelete(struct students* p) {
    printf("\nVvedite ID:");
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
        return;
    }
    deletestudentstree(delp);
    free(str);
    return;
}
void deletestudentstree(struct students* delel1) {
    //printf("vhod deletebookstree\n");
    struct students* prev1;
    //printf(" %d \n", (int)delel1);
    struct students* delel;
    delel = delel1;
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
        }
        nextright->left = delel->left;
        delel->left->parent = nextright;
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
struct students* searchstudentstree(struct students* p, char* str) {
    if (p == NULL) {
        return NULL;
    }
    int cond = strcmp(str, p->ID);
    printf("condition %d\n", cond);
    if ((cond) > 0) {
        return searchstudentstree(p->right, str);
    }
    else if ((cond) < 0) {
        return searchstudentstree(p->left, str);
    }

    return p;
}
void printstudentstree(struct students* p) {
    //printf("vhod printbook");
    if (p != NULL) {
        printstudentstree(p->left);
        printf("ID %s |Surname %s  | Name  %s |  Patronymic %s | Faculty %s | Speciality %s\n", p->ID, p->surname, p->name, p->patronymic, p->faculty, p->speciality);
        printstudentstree(p->right);
    }
}
void returnstudentstree(struct students* p) {
    FILE* fileclose;
    fileclose = openfile("students1.csv", "w");
    writestudentstree(p, fileclose);
    fclose(fileclose);
}
void writestudentstree(struct students* p, FILE* file) {
    if (p != NULL) {
        writestudentstree(p->left, file);
        fprintf(file, "%s;%s;%s;%s;%s;%s\n", p->ID, p->surname, p->name, p->patronymic, p->faculty, p->speciality);
        //fprintf(file, "%s;%s;%s;%d;%d\n", p->ISBN, p->author, p->title, p->amount, p->count);
        writestudentstree(p->right, file);
    }
}
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
struct students* loadstudentstreebackup(struct students* p) {
    printf("vvedite imya backupa:");
    char *backupname = readstr();
    char* str;
    char* s;
    FILE* backup = openfile(backupname, "r");

    if (backup == NULL) {
        printf("wronf backup filename");
        return p;
    }
    struct students* pbackup = NULL;
    freestudentstree(p);
    str = getstr1(backup);

    while ((str != NULL)) {

        printf("vhod v while loadbooktree\n");
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
void searchstudentstreebysurname(struct students* p) {
    printf("\nPrint surname:");
    char* str;
    int i;
    str = readstr();
    i = printstudentstreebysurname(p, str);
    if (i == 0)
        printf("nothing found");
    
}
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
//------------------------------------------------������� users.csv----------------------------
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

        printf("vhod v while loadbooktree\n");
        s = extractstr(str, 1);
        p = addstudentstree(p, str, s, NULL);
        free(s);
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
struct students* adduserstree(struct students* p, char* str, char* s, struct students* prev) {
    // printf("vhod addbooktree\n");
    // char* s;
    int cond;
    //  s = extractstr(str, 1);
    printf("ID - %s \n", s);
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
        p->left = adduserstree(p->left, str, s, p);
    }

    else {
        //   printf("right addbooktree\n");
        p->right = adduserstree(p->right, str, s, p);

    }
    // printf("vyhod addbooktree\n");
    return p;
}
void userstreeadd(struct students* p, char* str) {
    // printf("vhod bookadd\n");
    p->ID = extractstr(str, 1);
    printf("ID - %s, p = %d \n", p->ID, (int)p);
    p->surname = extractstr(str, 2);
    p->name = extractstr(str, 3);
    p->patronymic = extractstr(str, 4);
    p->faculty = extractstr(str, 5);
    p->speciality = extractstr(str, 6);
    //printf("bookadd\n");
}
//-------------------------------------------------MAIN-------------------------------------
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); //������������ ��� ������ ������ � ����
    setlocale(LC_ALL, "Rus");
    int c;
    treemark = 0;
    char name[70];
    int value;
    
    struct books* booksroot = NULL;
    rootbooks = &booksroot;
    booksroot = loadbookstree(booksroot);
    struct students* studentsroot = NULL;
    rootstudents = &studentsroot;
    treemark = 0;
    studentsroot = loadstudentstree(studentsroot);
    printf("Menu\nList all students - 1\nAdd student - 2\nDelete student - 3\nCreate backup - 4\nLoad backup - 5\nSearch student by surname - 6\nExit - e\n");
    c = getchar();
    while (c != 'e') {
        switch (c) {
        case '1':
            
            printstudentstree(studentsroot);
            break;
        case '2':
            
            studentstreeaddnew(studentsroot);
            break;
        case '3':
            studentstreedelete(studentsroot);
            break;
        case '4':
            studentstreebackup(studentsroot);
            break;
        case '5':
            studentsroot = loadstudentstreebackup(studentsroot);
            break;
        case '6':
            searchstudentstreebysurname( studentsroot);
            break;
        case '\n':

            break;
        case ' ':

            break;
        default:
            printf("error: unknown command \n");
            break;
        }
        c = getchar();
        //printf("sym %d \n", c);
    }
    returnbookstree(booksroot);
    freebookstree(booksroot);
    returnstudentstree(studentsroot);
    freestudentstree(studentsroot);
    

    return 0;
}

