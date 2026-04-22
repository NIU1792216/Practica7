/*
 Marco Rondón Torres, 1794984
 Mario Roda Sevilla, 1792216
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex{
    unsigned id, num_fills, fills[4]; // encara que digem fills, ens referim a la valencia i a quins nodes esta conectat cada vertex
    struct vertex *pare;
} vertex;

typedef struct Element{
    struct Element * siguiente;
    vertex * mateix;
}ElementPila;

typedef struct pila{
    ElementPila * inici;
}pila;

void apilar(pila * p, vertex * v);
vertex * desapilar(pila * p);

int main(){
    FILE * fitxer;
    unsigned i, j, vertex_cami=0, num_vertex=0;
    char * estat_vertex, caracter;
    vertex ** llista, * actual, * fill, **cami_trobat=NULL;
    pila pila = {NULL};

    fitxer = fopen("./laberint.txt","r");
    if (fitxer == NULL){
        printf("\nNo s'ha accedit al fitxer de dades\n");
        return 1;
    }
    while ((caracter = fgetc(fitxer)) != EOF){
        if (caracter == '\n'){
            num_vertex++;
        }
    }
    rewind(fitxer);
    printf("Hi ha %u vertex al graf\n", num_vertex);
    // ------------- Reservem memoria --------------------
    if ((estat_vertex = (char *)calloc(num_vertex, sizeof(char))) == NULL){
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
    printf("Memoria reservada correctament\n");
    // ------------------- llegim fitxer ----------------
    for (i=0;i<num_vertex;i++){
        llista[i] -> id = i;
        j = 0; // j representa el nombre de conexions
        fscanf(fitxer, "%u",&(llista[i]->fills[j]));
        j++;
        while ((caracter = fgetc(fitxer)) != '\n'){
            fscanf(fitxer," %u",&(llista[i]->fills[j]));
            j++;
        }
        llista[i]->num_fills = j;
    }
    fclose(fitxer);
    printf("Informacio del fitxer guardada en estructures de dades\n");
    // ------------- DFS -----------------------
    // Posem el pare del primer node com a NULL per quan trobem un cami, poder recorre'l
    // a la inversa i saber quan ha acabat.
    llista[0]->pare = NULL;
    apilar(&pila, llista[0]);
    // Recorrem els nodes fins que els hem recorregut tots (la pila es queda buida) o
    // fins que arribem al node de sortida, que en el nostre cas es l'ultim node (55)
    while ((pila.inici != NULL) && (actual->id != 55)){
        actual = desapilar(&pila);
        estat_vertex[actual->id] = 1;
        for (j=0;j < (actual->num_fills); j++){
            // L'us de la variable fill es unicament per fer mes entendible el codi
            fill = llista[(actual->fills[j])];
            if (estat_vertex[fill->id] == 0){
                fill->pare = actual;
                apilar(&pila, fill);
            }
        }
    }
    // Aqui o em trobat la sortida (seguint un cami que podem recorrer a la inversa)
    // o em recorregut tots els vertex.
    if (pila.inici == NULL){
        printf("No s'ha trobat cap cami per sortir del laberint\n");
        return 0;
    }
    // Guardem el cami seguit en una llista (d'apuntadors de vertexs)
    while (actual != NULL){
        if ((cami_trobat = (vertex **)realloc(cami_trobat, sizeof(vertex *)*(vertex_cami+1)))==NULL){
            printf("ERROR: No s'ha pogut assignar memoria per falta d'espai");
            return 2;
        }
        cami_trobat[vertex_cami] = actual;
        actual = actual->pare;
        vertex_cami++;
    }
    // Mostrem el camí seguit per pantalla
    printf("El cami trobat es:\n");
    for (i=(vertex_cami-1);i>0;i--){
        printf("%u -> ", cami_trobat[i]->id);
    }
    printf("%u", cami_trobat[0]->id);
    return 0;
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
    vertex * v = e->mateix;
    e = NULL;
    return v;
}