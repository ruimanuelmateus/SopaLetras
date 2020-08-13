//
// Created by Rui Mateus on 29/12/2018.
//

#ifndef CROSSWORDS_FINAL_H
#define CROSSWORDS_FINAL_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXSOUP 150
#define MAXPATH 10
#define FILENAME "C:\\Projects\\CrossWords\\sopa.txt"
//#define WORDFILE "C:\\Projects\\CrossWords\\dicionario.txt"

typedef struct cel{
    struct cel* N;
    struct cel* NE;
    struct cel* E;
    struct cel* SE;
    struct cel* S;
    struct cel* SO;
    struct cel* O;
    struct cel* NO;
    char letter;
    int col;
} CEL;

typedef struct table{
    int line;
    CEL* pcel;
}TABLE;

typedef struct soup{
    int nlines;
    int ncol;
    TABLE* ptable;
} SOUP;

struct word{
    char* name;
    struct word* pnext;
};

typedef struct words{
    struct word* pword;
    int nwords;
}WORDS;

struct point{
    int x;
    int y;
};

typedef struct cache{
    char* name;
    struct point inicio;
    int path[MAXPATH];
    struct cache* pnext;
}CACHE;

typedef struct main_cache{
    CACHE* cache;
    int ncache;
}MAIN_CACHE;


int main_fase2();
void line_columns_from_txt(int *col, int* lin);
char** read_file_to_pointer(int lin, int col);
void create_array_table(SOUP* ps, int lines, int cols);
void insert_cel_into_table(SOUP *ps, char** matrix);
void connect(SOUP* ps, CEL* cel_temp, CEL* cel_aux, int i, int j);

void read_words_txt(WORDS* ws);
void print_words(WORDS ws);
void print_single_word(struct word* w);

void print_soup(SOUP* s);

void start_search(SOUP* ps, WORDS* pw, MAIN_CACHE* pcache);
int consistency(struct word* w, CEL* c, int name_col);
void find_word(CEL* cel, struct word* w, MAIN_CACHE* pcache, int aux[], int aux_col, int name_col);


void ver(int aux[]);
void print_cache(MAIN_CACHE* m_c);
void search(SOUP* ps);

void new_words(WORDS* ws);
void free_words(WORDS* ws);
void found_word_in_cache(struct word* w, CACHE* cache);

void main_menu();

void save_cache_txt(MAIN_CACHE main, char fn[]);
void read_cache_txt(MAIN_CACHE* main, char fn[]);

#endif //CROSSWORDS_FINAL_H
