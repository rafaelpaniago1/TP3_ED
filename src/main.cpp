#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Inclua o arquivo da implementação da quadtree
#include "quad_tree.hpp"

// struct that contains the information about the recharging locations
typedef struct {
    char * idend;
    long id_logrado;
    char * sigla_tipo;
    char * nome_logra;
    int numero_imo;
    char * nome_bairr;
    char * nome_regio;
    int cep;
    double x;
    double y;
} addr_t, *ptr_addr_t;

// struct that contain the distance information between the origin location and
// each recharging location.
typedef struct knn {
    double dist; // distance between origin location and recharging location
    int id;      // recharging location id
} knn_t, *ptr_knn_t;

// vector containing the information about the recharging locations
addr_t rechargevet[] = {
    // Suponha que você tenha uma lista de locais de recarga aqui
};


void printrecharge(int pos) {
    printf("%s %s, %d, %s, %s, %d", rechargevet[pos].sigla_tipo,
           rechargevet[pos].nome_logra, rechargevet[pos].numero_imo,
           rechargevet[pos].nome_bairr, rechargevet[pos].nome_regio,
           rechargevet[pos].cep);
}

void printmap(ptr_knn_t kvet, int kmax, ptr_addr_t rvet, int nrec, double tx, double ty) {
    FILE *out;

    out = fopen("out.gp", "wt");
    fprintf(out, "set term postscript eps\n");
    fprintf(out, "set output \"out.eps\"\n");
    fprintf(out, "set size square\n");
    fprintf(out, "set key bottom right\n");
    fprintf(out, "set title \"BiUaiDi Recharging Stations\"\n");
    fprintf(out, "set xlabel \"\"\n");
    fprintf(out, "set ylabel \"\"\n");
    fprintf(out, "unset xtics \n");
    fprintf(out, "unset ytics \n");
    fprintf(out, "plot \"origin.gpdat\" t \"Your location\" pt 4 ps 2, \"recharge.gpdat\" t \"\", \"suggested.gpdat\" t \"Nearest stations\" pt 7 ps 2\n");
    fclose(out);

    out = fopen("origin.gpdat", "wt");
    fprintf(out, "%f %f\n", tx, ty);
    fclose(out);

    out = fopen("recharge.gpdat", "wt");
    for (int i = 0; i < nrec; i++) {
        fprintf(out, "%f %f\n", rvet[i].x, rvet[i].y);
    }
    fclose(out);

    out = fopen("suggested.gpdat", "wt");
    for (int i = 0; i < kmax; i++) {
        fprintf(out, "%f %f\n", rvet[kvet[i].id].x, rvet[kvet[i].id].y);
    }
    fclose(out);
}

int main(int argc, char **argv) {
    // count the number of recharge locations we have in rechargevet
    int numrecharge = 0;
    while (rechargevet[numrecharge].id_logrado != -1) numrecharge++;

    // read the coordinates of the current point that needs recharging
    double tx = atof(argv[1]);
    double ty = atof(argv[2]);

    // Create and populate the quadtree
    QuadTree *qt;  // Supondo que a função para criar uma quadtree se chame `quadtree_create`
    for (int i = 0; i < numrecharge; i++) {
        Ponto* ponto = new Ponto(rechargevet[i].x, rechargevet[i].y);
        qt->insert(*ponto);
    }

    // Create the vector of distances to store nearest neighbors
    ptr_knn_t kvet = (ptr_knn_t)malloc(10 * sizeof(knn_t));
    
    // Find the 10 nearest recharging locations
    findNearestNeighbors(qt, tx, ty, 10, kvet);

    // Print the 10 nearest recharging locations
    int kmax = 10;
    for (int i = 0; i < kmax; i++) {
        printrecharge(kvet[i].id);
        printf(" (%f)\n", kvet[i].dist);
    }

    printmap(kvet, kmax, rechargevet, numrecharge, tx, ty);

    free(kvet);
    quadtree_destroy(qt);  // Supondo que a função para destruir a quadtree se chame `quadtree_destroy`

    return 0;
}
