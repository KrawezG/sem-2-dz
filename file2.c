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
};
static struct nlist* hashtab[HASHSIZE];
 int booksmark;
 struct books* prevbooks;
 struct books** rootbooks;
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
//-----------------------------------------------------фнкции books.csv
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
        if (booksmark == 1) {
            str = NULL;
        }
        else {
            str = getstr1(file);
        }
    }
   // printf("vyhod loadbooktree\n");
    fclose(file);
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
void freetree(struct books* p) {
    if (p != NULL) {
        freetree(p->left);
        free(p->left);
        free(p->ISBN);
        free(p->title);
        free(p->author);
        freetree(p->right);
        free(p->right);
    }
}

//-------------------------------------------------MAIN-------------------------------------
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); //руссификатор для записи данных в файл
    setlocale(LC_ALL, "Rus");
    int c;
    booksmark = 0;
    char name[70];
    int value;
    
    struct books* root = NULL;
    rootbooks = &root;
    root = loadbookstree(root);
    printf("Menu\nAdd city - 1\nRemove city - 2\nList all - 3\n");
    c = getchar();
    while (c != 'e') {
        switch (c) {
        case '1':
            
            printbookstree(root);
            break;
        case '2':
            
            bookstreeaddnew(root);
            break;
        case '3':
            bookstreedelete(root);
            break;
        case '4':
            bookstreedelete(root);
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
    returnbookstree(root);
    freetree(root);
    

    return 0;
}

