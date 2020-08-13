//
// Created by Rui Mateus on 29/12/2018.
//

#include "final.h"

int main_fase2(){
/*
    SOUP sopa={0, 0, NULL};
    int col=0;
    int lin=0;
    line_columns_from_txt(&col, &lin);
    char** matriz_sopa=read_file_to_pointer(lin, col);
    create_array_table(&sopa, lin, col);
    insert_cel_into_table(&sopa, matriz_sopa);
    print_soup(&sopa);

*/
/*
    WORDS ws={NULL, 0};

    //read_words_txt(&ws);
    new_words(&ws);
    print_words(ws);
*/
/*
    MAIN_CACHE cache={NULL, 0};
    start_search(&sopa, &ws, &cache);

    print_cache(&cache);
*/

main_menu();

return 0;
}

void line_columns_from_txt(int *col, int* lin){
    FILE* fp;
    fp=fopen(FILENAME, "r");
    if(fp==NULL){
        puts("Ficheiro nao encontrado");
        return;
    }
    char str[MAXSOUP];
    fgets(str, MAXSOUP, fp);
    for(int i=0; str[i]!='\n'; i++){
        *col+=1;
    }
    *lin=1;
    while(!feof(fp)){
        fgets(str, MAXSOUP, fp);
        *lin+=1;
    }
    fclose(fp);
}

char** read_file_to_pointer(int lin, int col){
    FILE* fp;
    char* paux=NULL;
    char** ppaux=(char**) calloc((lin), sizeof(char*));
    for(int i=0; i<lin; i++){
        paux=(char*) calloc((col), sizeof(char));
        *(ppaux+i)=paux;
    }
    fp=fopen("C:\\Projects\\CrossWords\\sopa.txt", "r");
    char str[MAXSOUP];
    int k=0;
    while(!feof(fp)){
        fgets(str, MAXSOUP, fp);
        strcpy(*(ppaux+k), str);
        k++;
    }
    fclose(fp);
    return ppaux;
}

void create_array_table(SOUP* ps, int lines, int cols){
    ps->ptable=malloc(sizeof(TABLE)*lines);
    ps->nlines=lines;
    ps->ncol=cols;
    for(int i=0; i<lines; i++){
        (ps->ptable+i)->pcel=NULL;
        (ps->ptable+i)->line=i;
    }
}

void insert_cel_into_table(SOUP *ps, char** matrix){
    for(int i=0; i<ps->nlines; i++){
        TABLE* table_aux=(ps->ptable+i);
        for(int j=0; j<ps->ncol; j++){
            CEL* cel_aux=table_aux->pcel;
            CEL* cel_temp=malloc(sizeof(CEL));
            cel_temp->N=NULL;
            cel_temp->NE=NULL;
            cel_temp->E=NULL;
            cel_temp->SE=NULL;
            cel_temp->S=NULL;
            cel_temp->SO=NULL;
            cel_temp->O=NULL;
            cel_temp->NO=NULL;
            cel_temp->col=j;
            cel_temp->letter=*(*(matrix+i)+j);
            connect(ps, cel_temp, cel_aux, i, j);
        }
    }
}

void connect(SOUP* ps, CEL* cel_temp, CEL* cel_aux, int i, int j){
    if(i==0){
        if(ps->ptable->pcel==NULL){
            ps->ptable->pcel=cel_temp;
            return;
        }
        while(cel_aux->E!=NULL){
            cel_aux=cel_aux->E;
        }
        cel_aux->E=cel_temp;
        cel_temp->O=cel_aux;
        return;
    }
    if(j==(ps->ncol)-1){
        while(cel_aux->E!=NULL){
            cel_aux=cel_aux->E;
        }
        cel_aux->E=cel_temp;
        cel_temp->O=cel_aux;
        cel_aux=cel_aux->N;
        cel_temp->NO=cel_aux;
        cel_aux->SE=cel_temp;
        cel_aux=cel_aux->E;
        cel_temp->N=cel_aux;
        cel_aux->S=cel_temp;
        return;
    }
    if((ps->ptable+i)->pcel==NULL){
        (ps->ptable+i)->pcel=cel_temp;
        cel_temp->N=(ps->ptable+(i-1))->pcel;
        return;
    }
    while(cel_aux->E!=NULL){
        cel_aux=cel_aux->E;
    }
    cel_aux->E=cel_temp;
    cel_temp->O=cel_aux;
    cel_aux=cel_aux->N;
    cel_temp->NO=cel_aux;
    cel_aux->SE=cel_temp;
    cel_aux=cel_aux->E;
    cel_temp->N=cel_aux;
    cel_aux->S=cel_temp;
    cel_aux=cel_aux->E;
    cel_temp->NE=cel_aux;
    cel_aux->SO=cel_temp;
}

void read_words_txt(WORDS* ws){
    int linhas=0;
    FILE* fp1;
    fp1=fopen("C:\\Projects\\CrossWords\\dicionario.txt", "r");
    char str1[MAXSOUP];
    while(!feof(fp1)){
        fgets(str1, MAXSOUP, fp1);
        linhas+=1;
    }
    fclose(fp1);
    ws->nwords=linhas;
    FILE* fp2;
    fp2=fopen("C:\\Projects\\CrossWords\\dicionario.txt", "r");
    if(fp2==NULL){
        puts("Ficheiro nao encontrado");
        return;
    }
    char str2[MAXSOUP];
    char** ppdic=(char**)calloc((size_t)linhas, sizeof(char*));
    int k=0;
    while(!feof(fp2)){
        fgets(str2, MAXSOUP, fp2);
        *(ppdic+k)=(char*)calloc(strlen(str2), sizeof(char));
        int i=0;
        for(i=0; i<strlen(str2)-1; i++){
            *(*(ppdic+k)+i)=str2[i];
        }
        *(*(ppdic+k)+i)='\0';
        struct word* w=ws->pword;
        struct word* temp=malloc(sizeof(struct word));
        temp->name= *(ppdic+k);
        temp->pnext=NULL;
        if(ws->pword==NULL){
            ws->pword=temp;
        } else{
            while(w->pnext!=NULL){
                w=w->pnext;
            }
            w->pnext=temp;
        }
        k++;
    }
    fclose(fp2);

}

void print_words(WORDS ws){
    if(ws.pword==NULL && ws.nwords==0){
        puts("Nao ha palavras no dicionario");
        return;
    }
    struct word* temp= ws.pword;
    for(int i=0; i<ws.nwords; i++){
        printf("Word[%d]\t", i);
        print_single_word(temp);
        temp=temp->pnext;
    }
}

void print_single_word(struct word* w){
    printf("%s\n",w->name);
}

void print_soup(SOUP* s){
    for(int i=0; i<s->nlines; i++){
        CEL* c=(s->ptable+i)->pcel;
        for(int j=0; j<s->ncol; j++){
            printf("%c", c->letter);
            c=c->E;
        }
        puts("");
    }
}

void start_search(SOUP* ps, WORDS* pw, MAIN_CACHE* pcache){
    struct word* w=pw->pword;
    while(w!=NULL){
        CACHE* cch=pcache->cache;
        while(cch!=NULL){
            if(*cch->name==*w->name){
                //puts("1");
                found_word_in_cache(w, cch);
                //puts("2");
                goto NEXT;
            }
            cch=cch->pnext;
        }
        for (int i = 0; i < ps->nlines; i++) {
            CEL* cel=(ps->ptable+i)->pcel;
            while(cel!=NULL) {
                if ((w->name[0])==cel->letter) {
                    int aux_col=0;
                    int name_col=0;
                    int aux[MAXPATH];
                    aux[aux_col]=i;
                    ++aux_col;
                    aux[aux_col]= cel->col;
                    find_word(cel, w, pcache, aux, aux_col, name_col);
                }
                cel=cel->E;
            }
        }
        NEXT:
        w=w->pnext;
    }
}

void find_word(CEL* cel, struct word* w, MAIN_CACHE* pcache, int aux[], int aux_col, int name_col) {
    ++name_col;
    ++aux_col;
    if(w->name[name_col]=='\0')
    {
        aux[aux_col]=-1;
        CACHE* cache_aux=malloc(sizeof(CACHE));
        //cache_aux->name=w->name;
        cache_aux->name=malloc((sizeof(char)*strlen(w->name)));
        strcpy(cache_aux->name, w->name);
        cache_aux->name[strlen(w->name)]='\0';
        cache_aux->inicio.x=aux[0];
        cache_aux->inicio.y=aux[1];
        cache_aux->pnext=NULL;
        pcache->ncache++;
        for(int i=2; i<=aux_col; i++){
            cache_aux->path[i]=aux[i];
        }
        if(pcache->cache==NULL || strcmp(pcache->cache->name, cache_aux->name)>0){
            cache_aux->pnext=pcache->cache;
            pcache->cache=cache_aux;
        }else {
            CACHE* current=pcache->cache;
            while (current->pnext != NULL && strcmp(current->pnext->name, cache_aux->name)<=0) {
                current = current->pnext;
            }
            cache_aux->pnext = current->pnext;
            current->pnext=cache_aux;
        }
        printf("%s\t", cache_aux->name);
        printf("(%d, %d)\t", cache_aux->inicio.x, cache_aux->inicio.y);
        ver(cache_aux->path);
        puts("");
        return;
    }
    //N
    if(consistency(w, cel->N, name_col)==1) {
        aux[aux_col]=1;
        find_word(cel->N, w, pcache, aux, aux_col, name_col);
    }
    //NE
    if(consistency(w, cel->NE, name_col)==1) {
        aux[aux_col]=2;
        find_word(cel->NE, w, pcache, aux, aux_col, name_col);
    }
    //E
    if(consistency(w, cel->E, name_col)==1){
        aux[aux_col]=3;
        find_word(cel->E, w, pcache, aux, aux_col, name_col);
    }
    if(consistency(w, cel->SE, name_col)==1){
        aux[aux_col]=4;
        find_word(cel->SE, w, pcache, aux, aux_col, name_col);
    }
    if(consistency(w, cel->S, name_col)==1) {
        aux[aux_col]=5;
        find_word(cel->S, w, pcache, aux, aux_col, name_col);
    }
    if(consistency(w, cel->SO, name_col)==1){
        aux[aux_col]=6;
        find_word(cel->SO, w, pcache, aux, aux_col, name_col);
    }
    if(consistency(w, cel->O, name_col)==1) {
        aux[aux_col]=7;
        find_word(cel->O, w, pcache, aux, aux_col, name_col);
    }
    if(consistency(w, cel->NO, name_col)==1){
        aux[aux_col]=8;
        find_word(cel->NO, w, pcache, aux, aux_col, name_col);
    }
}

int consistency(struct word* w, CEL* c, int name_col) {
    if(c!=NULL)
    {
        if(c->letter==w->name[name_col])
            return 1;
    }
    return 0;
}

void ver(int aux[]){
    for(int i=0; aux[i]!=-1; i++){
        if(aux[i]==1){
            printf("N ");
        }else if(aux[i]==2){
            printf("NE ");
        }else if(aux[i]==3){
            printf("E ");
        }else if(aux[i]==4){
            printf("SE ");
        }else if(aux[i]==5){
            printf("S ");
        }else if(aux[i]==6){
            printf("SO ");
        }else if(aux[i]==7){
            printf("O ");
        }else if(aux[i]==8){
            printf("NO ");
        }
    }
}

void print_cache(MAIN_CACHE* m_c){
    CACHE* c=m_c->cache;
    for(int i=0; i<m_c->ncache; i++){
        while(c!=NULL){
            printf("%s\t", c->name);
            printf("[%d, %d]", c->inicio.x, c->inicio.y);
            ver(c->path);
            c=c->pnext;
            puts("");
        }
    }
}

void search(SOUP* ps){
    if(ps->ptable==NULL){
        puts("Sopa nao encontrada");
        return;
    }
    char aux[MAXPATH];
    int x=0, y=0;
    puts("Insira coordenada x");
    scanf("%d", &x);
    CEL* cel=(ps->ptable+x)->pcel;
    puts("Insira coordenada y");
    scanf("%d", &y);
    while(cel->col!=y){
        cel=cel->E;
    }
    int i=0;
    aux[i]=cel->letter;
    i++;
    int w=-1;
    printf("(NO->7)\t(N->8)\t(NE->9)\n(O->4)\t\t(E->6)\n(SO->1)\t(S->2)\t(SE->3)\n");
    while(w!=0){
        scanf("%d", &w);
        if(w==0){
            printf("\n");
        }else if(w==8){
            if(cel->N==NULL){
                puts("Direcao invalida");
            }else {
                cel = cel->N;
                aux[i] = cel->letter;
                i++;
            }
        } else if(w==9){
            if(cel->NE==NULL){
                puts("Direcao invalida");
            }else {
                cel = cel->NE;
                aux[i] = cel->letter;
                i++;
            }
        } else if(w==6){
            if(cel->E==NULL){
                puts("Direcao invalida");
            }else {
                cel = cel->E;
                aux[i] = cel->letter;
                i++;
            }
        } else if(w==3){
            if(cel->SE==NULL){
                puts("Direcao invalida");
            }else {
                cel = cel->SE;
                aux[i] = cel->letter;
                i++;
            }
        }else if(w==2){
            if(cel->S==NULL){
                puts("Direcao invalida");
            }else {
                cel = cel->S;
                aux[i] = cel->letter;
                i++;
            }
        }else if(w==1){
            if(cel->SO==NULL){
                puts("Direcao invalida");
            }else {
                cel = cel->SO;
                aux[i] = cel->letter;
                i++;
            }
        }else if(w==4){
            if(cel->O==NULL){
                puts("Direcao invalida");
            }else {
                cel = cel->O;
                aux[i] = cel->letter;
                i++;
            }
        }else if(w==7){
            if(cel->NO==NULL){
                puts("Direcao invalida");
            }else {
                cel = cel->NO;
                aux[i] = cel->letter;
                i++;
            }
        }
    }
    printf("%s", aux);
}

void main_menu(){
    char op;
    MAIN_CACHE cache={NULL, 0};
    SOUP sopa={0, 0, NULL};
    WORDS ws={NULL, 0};
    do {
        printf("Escolha uma opcao entre as possiveis:\n");
        printf(" [1]Carregar sopa do ficheiro\n");
        printf(" [2]Imprimir sopa\n");
        printf(" [3]Carregar palavras do dicionario\n");
        printf(" [4]Imprimir palavras\n");
        printf(" [5]Procurar palavras na sopa\n");
        printf(" [6]Imprimir cache\n");
        printf(" [7]Inserir palavras\n");
        printf(" [8]Limpar palavras\n");
        printf(" [9]Introduzir coordenadas\n");
        printf(" [G]Guardar cache\n");
        printf(" [I]Importar cache\n");
        printf(" [S]Terminar\n");
        fflush(stdin);
        scanf(" %c", &op);
        switch (op) {
            case '1':
                printf("\nmenu 1\n\n");
                int col=0;
                int lin=0;
                line_columns_from_txt(&col, &lin);
                char** matriz_sopa=read_file_to_pointer(lin, col);
                create_array_table(&sopa, lin, col);
                insert_cel_into_table(&sopa, matriz_sopa);
                break;
            case '2':
                printf("\nmenu 2\n\n");
                print_soup(&sopa);
                break;
            case '3':
                printf("\nmenu 3\n\n");
                read_words_txt(&ws);
                break;
            case '4':
                printf("\nmenu 4\n\n");
                print_words(ws);
                break;
            case '5':
                printf("\nmenu 5\n\n");
                start_search(&sopa, &ws, &cache);
                break;
            case '6':
                printf("\nmenu6\n\n");
                print_cache(&cache);
                break;
            case '7':
                printf("\nmenu7\n\n");
                new_words(&ws);
                break;
            case '8':
                printf("\nmenu8\n\n");
                free_words(&ws);
                break;
            case '9':
                printf("\nmenu9\n\n");
                search(&sopa);
                break;
            case 'G':
            case 'g':
                printf("\nGuardar\n\n");
                save_cache_txt(cache, "C:\\Projects\\CrossWords\\caches.txt");
                break;
            case 'I':
            case 'i':
                printf("\nImportar cache\n\n");
                read_cache_txt(&cache, "C:\\Projects\\CrossWords\\caches.txt");
                break;
            case 's':
            case 'S':
                break;
            default:
                printf("Opcao invalida!!!\n");
        }
        if (op!='s' && op!='S') {
            printf("\n\nPrima qualquer tecla para voltar ao menu...");
            getchar();
        }
    }  while (op!='s' && op!='S');
}

void new_words(WORDS* ws){
    puts("N de palavras a inserir");
    int x;
    scanf("%d", &x);
    for(int i=0; i<x; i++){
        char aux[10];
        puts("insira nome");
        scanf("%s", aux);
        struct word* temp=malloc(sizeof(struct word));
        temp->pnext=NULL;
        temp->name=malloc(sizeof(char)*strlen(aux)+1);
        strcpy(temp->name, aux);
        temp->name[strlen(aux)+1]='\0';
        ws->nwords++;
        if(ws->pword==NULL){
            ws->pword=temp;
        }else{
            struct word* current=ws->pword;
            while(current->pnext!=NULL){
                current=current->pnext;
            }
            current->pnext=temp;
        }
    }
}

void free_words(WORDS* ws){
    struct word* aux=ws->pword;
    struct word* next=aux->pnext;
    while(aux->pnext!=NULL){
        free(aux);
        aux=next;
        next=aux->pnext;
    }
    free(aux);
    ws->nwords=0;
    ws->pword=NULL;
}

void save_cache_txt(MAIN_CACHE main, char fn[]){
    CACHE* cache=NULL;
    FILE* fp=NULL;
    fp=fopen(fn,"w");
    if(fp==NULL){
        fprintf(stdout, "ERRO ABRIR FICH %s PARA ESCRITA\n", fn);
        return;
    }
    fprintf(fp,"MAIN_CACHE: %d\n", main.ncache);
    cache=main.cache;
    for(int i=0; i<main.ncache; i++){
        fprintf(fp,"cache %d: %s %d %d\n", i, cache->name, cache->inicio.x, cache->inicio.y);
        int j;
        for(j=0; cache->path[j]!=-1; j++){
            fprintf(fp, "%d ", cache->path[j]);
        }
        fprintf(fp, "%d\n", -1);
        cache=cache->pnext;
    }
    fclose(fp);
}

void read_cache_txt(MAIN_CACHE* main, char fn[]){
    FILE*fp=NULL;
    CACHE* cache=NULL;
    char auxStr[200]="";
    int size=0;
    if((fp=fopen(fn,"r"))==NULL){
        fprintf(stdout, "ERRO ABRIR FICH%s PARA LEITUTA\n", fn);
    }
    fscanf(fp,"%*s%d\n", &size);
    main->ncache=size;
    main->cache=malloc(sizeof(CACHE));
    cache=main->cache;
    for(int i=0; i<size; i++){
        if(i!=0) {
            CACHE* aux=malloc(sizeof(CACHE));
            cache->pnext=aux;
            cache=aux;
        }
        fscanf(fp, "%[^:] %*[:] %s %d %d\n", auxStr, cache->name, &cache->inicio.x, &cache->inicio.y);
        int j;
        for(j=0; cache->path[j-1]!=-1; j++){
            fscanf(fp,"%d ", &cache->path[j]);
        }
        fscanf(fp, "\n");
    }
    fclose(fp);
}

void found_word_in_cache(struct word* w, CACHE* cache){
    while(cache!=NULL){
        if(*cache->name==*w->name) {
            printf("%s\t", cache->name);
            printf("[%d, %d]", cache->inicio.x, cache->inicio.y);
            ver(cache->path);
            puts("");
        }else{
            return;
        }
        cache=cache->pnext;
    }
}
