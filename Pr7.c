#include <stdio.h>
#include <stdlib.h>

typedef struct vertex{
    unsigned id, num_fills;
    struct vertex * fills[4], *pare;
} vertex;

typedef struct{
    vertex * siguiente;
    vertex * mateix;
}ElementPila;

typedef struct pila{
    ElementPila * inici;
}pila;

void apilar(pila * p, vertex * v);

int main(){
    FILE * fitxer;
    char num_vertex=0, i, j, *estat_vertex, caracter;
    vertex ** llista, * anterior, * actual;
    pila pila = {NULL};


    fitxer = fopen("laberint.txt","r");
    if (fitxer == NULL){
        printf("\nNo s'ha accedit al fitxer de dades\n");
        return 1;
    }
    while (caracter = fgetc(fitxer) != EOF){
        if (caracter == '\n'){
            num_vertex++;
        }
    }
    rewind(fitxer);
    // ------------- Reservem memoria --------------------
    if ((estat_vertex = (char *)malloc(sizeof(char)*num_vertex)) == NULL){
        printf("ERROR: No s'ha pogut assignar memoria per falta d'espai");
        return 2;
    }
    if ((llista = (vertex **)malloc(sizeof(vertex *)*num_vertex)) == NULL){
        printf("ERROR: No s'ha pogut assignar memoria per falta d'espai");
        return 2;
    }
    for (i=0;i<num_vertex;i++){
        if ((llista[i] = (vertex *)malloc(sizeof(vertex))) == NULL){
            printf("ERROR: No s'ha pogut assignar memoria per falta d'espai");
            return 2;
        }
    }
    // ------------------- llegim fitxer ----------------

    for (i=0;i<num_vertex;i++){
        fscanf("%u",llista[0]->id);
        j = 0;
        while (caracter = fgetc(fitxer) != '\n'){
            fscanf(", %u",llista[i]->fills[j]);
            j++;
        }
        llista[i]->num_fills = j;
    }
    fclose(fitxer);
    // Creem arbre
    llista[0]->pare = NULL;
    apilar(&pila, llista[0]);
    i = 0;
    while ((i < num_vertex) && (actual->id != num_vertex)){
        actual = llista[i];
        for (j=0;j < (actual->num_fills); j++){
            apilar(&pila, actual);
        }
    }
}

void apilar(pila * p, vertex * v){
    ElementPila * e =(ElementPila *)malloc(sizeof(ElementPila));
    e->mateix = v;
    e->siguiente = p->inici;
    p->inici = e;
}

vertex * desapilar(pila * p){
    if (p->inici == NULL){
        return NULL;
    }
    ElementPila * e = p->inici;
    p->inici = e->siguiente;
    return e->mateix;
}