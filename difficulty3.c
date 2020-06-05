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
#define ADD_DAYS 14
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
struct booklease {
    char* ISBN;
    char* ID;
    char* returndate;
    struct booklease* next;
    struct booklease* parent;
};


 int treemark;
 struct books* prevbooks;
 struct students* prevstudents;
 struct users* prevusers;
 struct books** rootbooks;
 struct students** rootstudents;
 struct users** rootusers;
 struct users* currentuser;
 struct booklease** rootbooklease;


//---------------------------------------------------указатели




FILE* openfile(char name[], char rights[]);
char* getstr(FILE* file);
char* getstr1(FILE* file);
char* getword(FILE* file);
char* readstr();
char* readstr1();
char* extractstr(char* str, int num);
int extractint(char* str, int num);

struct books* loadbookstree(struct books* p);
struct books* tallocbooks(void);
struct books* addbookstree(struct books* p, char* str, char* s, struct books* prev);
void bookstreeadd(struct books* p, char* str);
void bookstreeaddnew(struct books* p);
void bookstreedelete(struct books* p);
void deletebookstree(struct books*);
struct books* searchbookstree(struct books* p, char* str);
void searchbookstreebyISBN(struct books* p);
void printbookstree(struct books* p);
void returnbookstree(struct books* p);
void writebookstree(struct books* p, FILE* file);
void freebookstree(struct books* p);
void giveoutbook(struct books* p);
void returnbook(struct books* p);
void printbookstudents(struct books* p);

struct students* loadstudentstree(struct students* p);
struct students* tallocstudents(void);
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
void printstudentbooks(struct students* p);

struct users* loaduserstree(struct users* p);
struct users* adduserstree(struct users* p, char* str, char* s, struct users* prev);
void userstreeadd(struct users* p, char* str);
struct users* tallocusers(void);
int authorization(struct users* p);
struct users* searchuserstree(struct users* p, char* str);
void freeuserstree(struct users* p);

struct booklease* loadbookleasenode();
struct booklease* addbookleasenode(struct booklease* p, struct booklease* prev, char* str);
void addbookleasenode1(char* ID, char* ISBN, char* time);
void bookleasenodeadd(struct booklease* p, char* str);
struct booklease* tallocbooklease(void);
struct booklease* bookleasenodesearch(struct booklease* p, char* s1, char* s2);
void bookleasenodedelete(struct booklease* p);
int  bookleasenodesearchISBN(struct booklease* p, char* s1);
struct booklease* bookleasenodesearchISBN1(struct booklease* p, char* s1);
void  bookleasenodeprintbyISBN(struct booklease* p, char* s1);
int  bookleasenodesearchID(struct booklease* p, char* s1);
void  bookleasenodeprintbyID(struct booklease* p, char* s1);
void returnbookleasenode(struct booklease* p);
void writebookleasenode(struct booklease* p, FILE* file);
void freebookleasenode(struct booklease* p);
void printbookleasenode(struct booklease* p);

//---------------------------------------------------общие функции

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
        string = (char*)realloc(string, i * sizeof(char));
        string[i - 1] = 0; '\0';
        printf("symbol = EOF && i !=1 %s, %i, %i, %d\n", string, i*sizeof(char), i, (int)string);
//        if (i == 65) {
//            string = (char*)realloc(string, i * sizeof(char));
//            putchar('4');
//            free(string); putchar('5'); return NULL; }
        return string;
    }
    else {
        free(string);
        printf("else NULL\n");
        return NULL;
    }
}
/*char* getstr(FILE* file) {
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
}*/
char* readstr()
{
    //printf("vhod readstr\n");
    int c;
    char* str = NULL;
    int i = 0;
    c = getchar();
    c = getchar();
    //printf("schityvanie c = %c\n", c);
    while (c != '\n')
    {
        i++;
        str = (char*)realloc(str, (i + 1) * sizeof(char));
        str[i - 1] = c;
        c = getchar();
    }
    str[i] = '\0';
    printf("\n str - |%s|", str);
    return str;
}
char* readstr1()
{
    //printf("vhod readstr\n");
    int c;
    char* str = NULL;
    int i = 0;
    c = getchar();
    //printf("schityvanie c = %c\n", c);
    while (c != '\n')
    {
        i++;
        str = (char*)realloc(str, (i + 1) * sizeof(char));
        str[i - 1] = c;
        c = getchar();
    }
    str[i] = '\0';
    printf("\n str - |%s|", str);
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
        free(string);
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
        free(string);
        return number;
    }
    else {
        number = -1;
        free(string);
        return number;
    }
}
//-----------------------------------------------------функции books.csv
struct books* tallocbooks(void) {
    return (struct books*) malloc(sizeof(struct books));
}
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
    int i = 0;
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
    char * time1 = malloc(15 * sizeof(char));
    memset(time1, 0, 15);
    const time_t timer = time(NULL);
    u = localtime(&timer);
    u->tm_mday += ADD_DAYS;
    time_t next = mktime(u);
    u = localtime(&next);
    strftime(time1, 13, "\"%d.%m.%Y\"", u);
    printf("time1  = %s\n", time1);
    addbookleasenode1( strID, strISBN, time1);
    printf("marker 1, %d\n", (int)*rootbooklease);
    //free(strID);
    //free(strISBN);
    //free(u);

}
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
    if ((chanp == NULL )|| (test == NULL)) {
        printf("wrong data\n");
        return;
    }
    struct booklease* delel = bookleasenodesearch(*rootbooklease, strISBN, strID);
    if (delel == NULL) {
        printf("student doesn't have this book\n");
        return;
    }
    chanp->count++;
    printf("before del, %d\n", (int)delel);
    bookleasenodedelete(delel);

}
void printbookstudents(struct books* p) {
    printf("\nVvedite ISBN:");
    char* strISBN;
    struct books* delp;
    strISBN = readstr();
    bookleasenodeprintbyISBN(*rootbooklease, strISBN);
    free(strISBN);
}

//-------------------------------------------------функции students.csv---------------------------
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

        printf("vhod v while loadstudentstree\n");
        s = extractstr(str, 1);
        p = addstudentstree(p, str, s, NULL);
        //printf("before free loadstudentstree, %d\n", (int)s);
       putchar('9');
        //if (s != NULL)
        free(s); putchar('0');
        //printf("first free loadstudentstree, %d\n", (int)str);
        free(str); putchar('1');
        printf("second free loadstudentstree\n");
        //str = getstr1(file);
        if (treemark == 1) {
            str = NULL;
        }
        else {
            str = getstr1(file);
        }
        printf("vyhod v while loadstudentstree\n");
    }
     printf("vyhod loadstudentstree\n");
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
     printf("vyhod addstudenttree\n");
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
    printf("studentadd\n");
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
void printstudentbooks(struct students* p) {
    printf("\nVvedite ID:");
    char* strID;
    struct students* delp;
    strID = readstr();
    bookleasenodeprintbyID(*rootbooklease, strID);
    free(strID);
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
    printf("Enter backup name:");
    char *backupname = readstr();
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
//------------------------------------------------функции users.csv----------------------------
struct users* tallocusers(void) {
    return (struct users*) malloc(sizeof(struct users));
}
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
     printf("vyhod loadbooktree\n");
    return p;

}
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
void userstreeadd(struct users* p, char* str) {
    // printf("vhod bookadd\n");
    p->login = extractstr(str, 1);
    //printf("ID - %s, p = %d \n", p->ID, (int)p);
    p->password = extractstr(str, 2);
    p->rightsstudents = extractint(str, 3);
    p->rightsbooks = extractint(str, 4);
    //printf("bookadd\n");
}
int authorization(struct users *p) {
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
//-------------------------------------------------bookslease
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
struct booklease* addbookleasenode(struct booklease* p, struct booklease* prev, char *str) {
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
void addbookleasenode1(  char* ID, char* ISBN, char* time ) {
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
    printf("vhod deletenode\n");
    if (p->parent == NULL) {
        *rootbooklease = p->next;   
    }
    else {
        (p->parent)->next = p->next;  
    }
    if (p->next != NULL) {
        (p->next)->parent = p->parent;
    }
    printf("before free\n");
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
void  bookleasenodeprintbyISBN (struct booklease* p, char* s1) {
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
    return ;
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
    return ;
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
void printbookleasenode(struct booklease* p ) {
    if (p != NULL) {
        printbookleasenode(p->next);
        printf( "%s;%s;%s\n", p->ISBN, p->ID, p->returndate);
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



//-------------------------------------------------MAIN-------------------------------------
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); //русификатор для записи данных в файл
    setlocale(LC_ALL, "Rus");
    int c;
    int access = 0;
    treemark = 0;
    char name[70];
    int value;
    struct users* usersroot = NULL;
    rootusers = &usersroot;
    usersroot = loaduserstree(usersroot);
    while (access == 0) {
        printf("vhod auth");
        access = authorization(usersroot);
    }
    treemark = 0;
    struct books* booksroot = NULL;
    rootbooks = &booksroot;
    booksroot = loadbookstree(booksroot);
    treemark = 0;
    struct students* studentsroot = NULL;
    rootstudents = &studentsroot;
    studentsroot = loadstudentstree(studentsroot);
    treemark = 0;
    struct booklease* bookleaseroot = NULL;
    rootbooklease = &bookleaseroot;
    bookleaseroot = loadbookleasenode();
    if (((currentuser->rightsstudents) == 1) && ((currentuser->rightsbooks) == 1)) {
    
        printf("Menu\nWork with students.csv - 1\nWork with books.csv - 2\nExit - e\n");
        c = getchar();
        while (c != 'e') {
            switch (c) {
            case '1':

                printf("Menu\nList all students - 1\nAdd student - 2\nDelete student - 3\nCreate backup - 4\nLoad backup - 5\nSearch student by surname - 6\nLook taken books by ID - 7\nExit - e\n");
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
                        searchstudentstreebysurname(studentsroot);
                        break;
                    case '7':
                        printstudentbooks(studentsroot);
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
                break;
            case '2':

                printf("Menu\nList all books - 1\nAdd book - 2\nDelete book - 3\nSearch book by ISBN - 4\nGive out book - 5\nReturn book - 6\nSee given books - 7\nExit - e\n");
                c = getchar();
                while (c != 'e') {
                    switch (c) {
                    case '1':

                        printbookstree(booksroot);
                        break;
                    case '2':

                        bookstreeaddnew(booksroot);
                        break;
                    case '3':
                        bookstreedelete(booksroot);
                        break;
                    case '4':
                        searchbookstreebyISBN(booksroot);
                        break;
                    case '5':
                        giveoutbook(booksroot);
                        break;
                    case '6':
                        returnbook(booksroot);
                        break;
                    case '7':
                        printbookstudents(booksroot);
                        break;
                    case '8':
                        printbookleasenode(*rootbooklease);
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
            printf("Menu\nWork with students.csv - 1\nWork with books.csv - 2\nExit - e\n");
            //printf("sym %d \n", c);
        }
    }
    else if ((currentuser->rightsstudents) == 1) {
    printf("Menu\nList all students - 1\nAdd student - 2\nDelete student - 3\nCreate backup - 4\nLoad backup - 5\nSearch student by surname - 6\nLook taken books by ID - 7\nExit - e\n");
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
            searchstudentstreebysurname(studentsroot);
            break;
        case '7':
            printstudentbooks(studentsroot);
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
    } else {
    printf("Menu\nList all books - 1\nAdd book - 2\nDelete book - 3\nSearch book by ISBN - 4\nGive out book - 5\nReturn book - 6\nSee given books - 7\nExit - e\n");
    c = getchar();
    while (c != 'e') {
        switch (c) {
        case '1':

            printbookstree(booksroot);
            break;
        case '2':

            bookstreeaddnew(booksroot);
            break;
        case '3':
            bookstreedelete(booksroot);
            break;
        case '4':
            searchbookstreebyISBN(booksroot);
            break;
        case '5':
            giveoutbook(booksroot);
            break;
        case '6':
            returnbook(booksroot);
            break;
        case '7':
            printbookstudents(booksroot);
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
    


    }
    returnbookstree(booksroot);
    freebookstree(booksroot);
    returnstudentstree(studentsroot);
    freestudentstree(studentsroot);
    freeuserstree(usersroot);
    returnbookleasenode(bookleaseroot);
    freebookleasenode(bookleaseroot);

    return 0;
}

