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
#define HASHSIZE 101
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
};
static struct nlist* hashtab[HASHSIZE];
 int booksmark;
const char ordermod[] = "-o";
const char descstr[] = "DESC";
const char ascstr[] = "ASC";



//---------------------------------------------------указатели

unsigned int hash(char* s);
struct nlist* delete1(char* name);
struct nlist* lookup(char* s);
struct books* tallocbooks(void);
struct students* tallocstudents(void);
void print();
FILE* openfile(char name[], char rights[]);
char* getstr(FILE* file);
char* getword(FILE* file);
char* extractstr(char* str, int num);
int extractint(char* str, int num);
struct books* loadbookstree(struct books* p, FILE* file);
struct books* addbookstree(struct books* p, char* str);
void bookstreeadd(struct books* p, char* str);

//---------------------------------------------------функции
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
struct students* tallocstudents(void) {
    return (struct students*) malloc(sizeof(struct students));
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
    
        booksmark = 0;
    
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
        booksmark = 1;

    printf(" %d, %i\n", (int)symbol,i);
    printf("pered if");
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
    printf("vhod extractstr\n");
    char symbol;
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
    printf("doxod do neobh polya %d\n", i);
    int strlen = 2;
    string = (char*)malloc(strlen * sizeof(char));
    while ((str[i] != ';')&& (str[i] != '\0')) {
        printf("schityvanie %d simvola %c\n", j, str[i]);
        string = (char*)realloc(string, strlen * sizeof(char));
        string[j] = str[i];
        j++;
        i++;
        strlen++;
    }
    printf("vyhod extractstr\n");
    if (j > 0) {
        string[j + 1] = '\0';
        return string;
    }
    else {
        return NULL;
    }
}
int extractint(char* str, int num) {
    printf("vhod extractstr\n");
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
    printf("doxod do neobh polya %d\n", i);
    int strlen = 2;
    string = (char*)malloc(strlen * sizeof(char));
    while ((str[i] != ';') && (str[i] != '\0') &&( str[i] != EOF)) {
        printf("schityvanie %d simvola %c\n", j, str[i]);
        string = (char*)realloc(string, strlen * sizeof(char));
        string[j] = str[i];
        j++;
        i++;
        strlen++;
    }
    printf("vyhod extractstr\n");
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
//-----------------------------------------------------фнкции books.csv
struct books* loadbookstree(struct books* p, FILE* file) {
    int cond;
    
    char* str;
    printf("vhod loadbooktree\n");
    str = getstr1(file);
    while ((str != NULL)&&(booksmark != 1)) {
        printf("vhod v while loadbooktree\n");
        p = addbookstree(p, str);
        str = getstr1(file);
    }
    printf("vyhod loadbooktree\n");
    return p;
}
struct books* addbookstree(struct books* p, char *str) {
    printf("vhod addbooktree\n");
    char* s;
    int cond;
    s = extractstr(str, 1);
    printf("ISBN - %s\n", s);
    if (p == NULL) {
        printf("p null\n");
        p = tallocbooks();
        bookstreeadd(p, str);
        p->left = p->right = NULL;
        printf("zapis knigi\n");
    }
    else if ((cond = strcmp(s, p->ISBN)) == 0)
        printf("book already exist\n");
    else if (cond < 0) {
        printf("left addbooktree\n");
        p->left = addbookstree(p->left, str);
    }
        
    else {
        printf("right addbooktree\n");
        p->right = addbookstree(p->right, str);

    }
    printf("vyhod addbooktree\n");
    return p;
}
void bookstreeadd(struct books* p, char* str) {
    printf("vhod bookadd\n");
    p->ISBN = extractstr(str, 1);
    p->author = extractstr(str, 2);
    p->title = extractstr(str, 3);
    p->amount = extractint(str, 4);
    p->count = extractint(str, 5);
    printf("bookadd\n");
}
void printbookstree(struct books* p) {
    printf("vhod printbook");
    if (p != NULL) {
        printbookstree(p->left);
        printf("ISBN %s |Title %s  | Author  %s |  Amount %d | Count %d\n", p->ISBN, p->title, p->author, p->amount, p->count);
        printbookstree(p->right);
    }
}
void freetree(struct books* p) {
    if (p != NULL) {
        freetree(p->left);
        free(p->ISBN);
        free(p->title);
        free(p->author);


        freetree(p->right);
    }
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); //руссификатор для записи данных в файл
    setlocale(LC_ALL, "Rus");
    int c;
    booksmark = 0;
    char name[70];
    int value;
    FILE* filebooks;
    struct books* root = NULL;
    filebooks = openfile("books.csv", "r+");
    root = loadbookstree(root, filebooks);
    printf("Menu\nAdd city - 1\nRemove city - 2\nList all - 3\n");
    c = getchar();
    while (c != EOF) {
        switch (c) {
        case '1':
            
            printbookstree(root);
            break;
        case '2':
            scanf("%s", name);
            break;
        case '3':
            print();
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
    }
    freetree(root);
    fclose(filebooks);

    return 0;
}

