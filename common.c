#include "main.h"


// файл с общими функциями

// функция для открытия файла
FILE* openfile(char name[], char rights[]) {
    FILE* file;
    file = fopen(name, rights);
    if ((file) == NULL) {
        printf("%s\n", "cannot open file");
        exit(EXIT_FAILURE);
    }
    return file;
}

//функция извлечения из файла строки
char* getstr1(FILE* file) {
    treemark = 0;
    int symbol;
    int i = 1;
    char* string;
    string = (char*)malloc(sizeof(char));
    symbol = getc(file);
    while ((symbol != '\n') && (symbol != EOF)) {
        string = (char*)realloc(string, i * sizeof(char));
        string[i - 1] = symbol & 255;
        symbol = getc(file);
        i++;
    }
    if (symbol == EOF)
        treemark = 1;
    if (i != 1) {
        string = (char*)realloc(string, i * sizeof(char));
        string[i - 1] = 0; '\0';
        return string;
    }
    else {
        free(string);
        //printf("else NULL\n");
        return NULL;
    }
}

//функция чтения строки, 1 вариант
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
    //printf("\n str - |%s|", str);
    return str;
}

//функция чтения строки, 2 вариант
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
    //printf("\n str - |%s|", str);
    return str;
}

//функция для чтения слова из файла
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

//функция извлечения из строки аргумента в виде строки
char* extractstr(char* str, int num) {
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
    string = (char*)malloc((j + 1) * sizeof(char));
    while ((str[i] != ';') && (str[i] != '\0')) {
        //     printf("schityvanie %d simvola %c\n", j, str[i]);
        string = (char*)realloc(string, (j + 1) * sizeof(char));
        string[j] = str[i];
        j++;
        i++;
        //       strlen++;
    }

    // printf("vyhod extractstr\n");
    if (j > 0) {
        string = (char*)realloc(string, (j + 1) * sizeof(char));
        string[j] = '\0';
        return string;
    }
    else {
        free(string);
        return NULL;
    }
}

// функция извлечения из строки аргумента в виде числа
int extractint(char* str, int num) {
    //printf("vhod extractstr\n");
    char symbol;
    int count = 1;
    int i = 0;
    int j = 0;
    char* string;
    int number;
    while (count < num) {
        while (str[i] != ';') {
            i++;
        }
        count++;
        i++;
    }
    //printf("doxod do neobh polya %d\n", i);
    int strlen = 2;
    string = (char*)malloc(strlen * sizeof(char));
    while ((str[i] != ';') && (str[i] != '\0') && (str[i] != EOF)) {
        //    printf("schityvanie %d simvola %c\n", j, str[i]);
        string = (char*)realloc(string, strlen * sizeof(char));
        string[j] = str[i];
        j++;
        i++;
        strlen++;
    }
    // printf("vyhod extractstr\n");
    if (j > 0) {
        string[j] = '\0';
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

//функция добавления записи в лог
void addlog(char* str) {
    FILE* file;
    file = openfile("library.log", "a");
    char time1[50] = { 0 };
    struct tm* t;
    time_t timer = time(NULL);
    t = localtime(&timer);
    strftime(time1, 40, "\"%d.%m.%Y %H:%M:%S\"", t);
    fprintf(file, "%s;\"%s\";\"%s\"\n", time1, currentuser->login, str);


    fclose(file);
}