#include "main.h"


//метка конца файла
int treemark;
//указатель на предыдущий элемент дерева книг
struct books* prevbooks;
//указатель на предыдущий элемент дерева студентов
struct students* prevstudents;
//указатель на предыдущий элемент дерева пользователей
struct users* prevusers;
//указатель на корневую €чейку дерева книг
struct books** rootbooks;
//указатель на корневую €чейку дерева студентов
struct students** rootstudents;
//указатель на корневую €чейку дерева пользователей
struct users** rootusers;
//указатель на €чейку текущего пользовател€
struct users* currentuser;
//указатель на корневую €чейку списка вз€тых книг
struct booklease** rootbooklease;



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); //русификатор дл€ записи данных в файл
    setlocale(LC_ALL, "Rus");
    int c;
    int access = 0;
    treemark = 0;
    char name[70];
    int value;
    char* action;
    struct users* usersroot = NULL;
    rootusers = &usersroot;
    usersroot = loaduserstree(usersroot);
    while (access == 0) {
        //printf("vhod auth");
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
                c = getchar();
                while (c != 'e') {
                    printf("Menu\nList all students - 1\nAdd student - 2\nDelete student - 3\nCreate backup - 4\nLoad backup - 5\nSearch student by surname - 6\nLook taken books by ID - 7\nExit - e\n");
                    switch (c) {
                    case '1':
                        printf("   ID   |            Surname             |      Name       |           Patronymic           | Faculty |           Speciality         \n");
                        printstudentstree(studentsroot);
                        action = "print students";
                        addlog(action);
                        break;
                    case '2':

                        studentstreeaddnew(studentsroot);
                        action = "add student";
                        addlog(action);
                        break;
                    case '3':
                        studentstreedelete(studentsroot);
                        action = "delete student";
                        addlog(action);
                        break;
                    case '4':
                        studentstreebackup(studentsroot);
                        action = "create students backup";
                        addlog(action);
                        break;
                    case '5':
                        studentsroot = loadstudentstreebackup(studentsroot);
                        action = "load students backup";
                        addlog(action);
                        break;
                    case '6':
                        searchstudentstreebysurname(studentsroot);
                        action = "search students by name";
                        addlog(action);
                        break;
                    case '7':
                        printstudentbooks(studentsroot);
                        action = "print student books";
                        addlog(action);
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


                c = getchar();
                while (c != 'e') {
                    printf("Menu\nList all books - 1\nAdd book - 2\nDelete book - 3\nSearch book by ISBN - 4\nGive out book - 5\nReturn book - 6\nSee given books - 7\nExit - e\n");
                    switch (c) {
                    case '1':
                        printf("    ISBN    |             Title               |              Author            | Amount | Count \n");
                        printbookstree(booksroot);
                        action = "print books";
                        addlog(action);
                        break;
                    case '2':

                        bookstreeaddnew(booksroot);
                        action = "add book";
                        addlog(action);
                        break;
                    case '3':
                        bookstreedelete(booksroot);
                        action = "delete book";
                        addlog(action);
                        break;
                    case '4':
                        searchbookstreebyISBN(booksroot);
                        action = "search book by ISBN";
                        addlog(action);
                        break;
                    case '5':
                        giveoutbook(booksroot);
                        action = "give out book";
                        addlog(action);
                        break;
                    case '6':
                        returnbook(booksroot);
                        action = "return book";
                        addlog(action);
                        break;
                    case '7':
                        printbookstudents(booksroot);
                        action = "print books";
                        addlog(action);
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

        c = getchar();
        while (c != 'e') {
            printf("Menu\nList all students - 1\nAdd student - 2\nDelete student - 3\nCreate backup - 4\nLoad backup - 5\nSearch student by surname - 6\nLook taken books by ID - 7\nExit - e\n");
            switch (c) {
            case '1':

                printstudentstree(studentsroot);
                action = "print students";
                addlog(action);
                break;
            case '2':

                studentstreeaddnew(studentsroot);
                action = "add student";
                addlog(action);
                break;
            case '3':
                studentstreedelete(studentsroot);
                action = "delete student";
                addlog(action);
                break;
            case '4':
                studentstreebackup(studentsroot);
                action = "create students backup";
                addlog(action);
                break;
            case '5':
                studentsroot = loadstudentstreebackup(studentsroot);
                action = "load students backup";
                addlog(action);
                break;
            case '6':
                searchstudentstreebysurname(studentsroot);
                action = "search students by name";
                addlog(action);
                break;
            case '7':
                printstudentbooks(studentsroot);
                action = "print student books";
                addlog(action);
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
    }
    else {

        c = getchar();
        while (c != 'e') {
            printf("Menu\nList all books - 1\nAdd book - 2\nDelete book - 3\nSearch book by ISBN - 4\nGive out book - 5\nReturn book - 6\nSee given books - 7\nExit - e\n");
            switch (c) {
            case '1':

                printbookstree(booksroot);
                action = "print books";
                addlog(action);
                break;
            case '2':

                bookstreeaddnew(booksroot);
                action = "add book";
                addlog(action);
                break;
            case '3':
                bookstreedelete(booksroot);
                action = "delete book";
                addlog(action);
                break;
            case '4':
                searchbookstreebyISBN(booksroot);
                action = "search book by ISBN";
                addlog(action);
                break;
            case '5':
                giveoutbook(booksroot);
                action = "give out book";
                addlog(action);
                break;
            case '6':
                returnbook(booksroot);
                action = "return book";
                addlog(action);
                break;
            case '7':
                printbookstudents(booksroot);
                action = "print books";
                addlog(action);
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

