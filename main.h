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
FILE* openfile(char name[], char rights[]);
char* getstr(FILE* file);
char* getstr1(FILE* file);
char* getword(FILE* file);
char* readstr();
char* readstr1();
char* extractstr(char* str, int num);
int extractint(char* str, int num);
void addlog(char* str);

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