// biuaidinaive
// Author: Wagner Meira Jr.
// Version history:
//    1.0 - 21/07/2024
//
// Usage:
// biuaidinaive x y
//    x - geographical x coordinate of current location
//    y - geographical y coordinate of current location
//
// Output:
//    10 closest recharging locations
//
// gcc -g src/biuaidinaive2.c -o bin/biuaidinaive.out -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
// struct that contains the information about the recharging locations
typedef struct
{
  char *idend;
  long id_logrado;
  char *sigla_tipo;
  char *nome_logra;
  int numero_imo;
  char *nome_bairr;
  char *nome_regio;
  int cep;
  double x;
  double y;
  bool active;
} addr_t, *ptr_addr_t;

// struct that contain the distance information between the origin location and
// each recharging location.
typedef struct knn
{
  double dist; // distance between origin location and recharging location
  int id;      // recharging location id
} knn_t, *ptr_knn_t;

// qsort comparison function between distances to recharging locations
int cmpknn(const void *a, const void *b)
{
  ptr_knn_t k1 = (ptr_knn_t)a;
  ptr_knn_t k2 = (ptr_knn_t)b;
  if (k1->dist > k2->dist)
    return 1;
  else if (k1->dist < k2->dist)
    return -1;
  else
    return 0;
}

// calculates Euclidean distance between (x1,y1) and (x2,y2)
double dist(double x1, double y1, double x2, double y2)
{
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

// print illustrative map using gnuplot
void printmap(ptr_knn_t kvet, int kmax, ptr_addr_t rvet, int nrec, double tx, double ty)
{
  FILE *out;

  // gnuplot script. to obtain the actual map, it is necessary to run:
  // gnuplot out.gp
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

  // origin point, just one pair of x, y coordinates
  out = fopen("origin.gpdat", "wt");
  fprintf(out, "%f %f\n", tx, ty);
  fclose(out);

  // all recharging locations
  out = fopen("recharge.gpdat", "wt");
  for (int i = 0; i < nrec; i++)
  {
    fprintf(out, "%f %f\n", rvet[i].x, rvet[i].y);
  }
  fclose(out);

  // the nearest recharging locations
  out = fopen("suggested.gpdat", "wt");
  for (int i = 0; i < kmax; i++)
  {
    fprintf(out, "%f %f\n", rvet[kvet[i].id].x, rvet[kvet[i].id].y);
  }
  fclose(out);
}

// vector containing the information about the recharging locations
addr_t *rechargevet;
int num_addresses;

void load_rechargevet(char path[])
{
  FILE *file = fopen(path, "r");
  if (file == NULL)
  {
    perror("Unable to open file");
    exit(EXIT_FAILURE);
  }

  // Ler o número de endereços
  if (fscanf(file, "%d\n", &num_addresses) != 1)
  {
    perror("Failed to read the number of addresses");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  // Alocar memória para o vetor de endereços
  rechargevet = (addr_t *)malloc(num_addresses * sizeof(addr_t));
  if (rechargevet == NULL)
  {
    perror("Memory allocation failed");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  char line[256];
  int i = 0;
  while (fgets(line, sizeof(line), file) && i < num_addresses)
  {
    char *token = strtok(line, ";");

    // Alocar memória e copiar os dados
    rechargevet[i].idend = strdup(token);
    token = strtok(NULL, ";");
    rechargevet[i].id_logrado = strtol(token, NULL, 10);
    token = strtok(NULL, ";");
    rechargevet[i].sigla_tipo = strdup(token);
    token = strtok(NULL, ";");
    rechargevet[i].nome_logra = strdup(token);
    token = strtok(NULL, ";");
    rechargevet[i].numero_imo = atoi(token);
    token = strtok(NULL, ";");
    rechargevet[i].nome_bairr = strdup(token);
    token = strtok(NULL, ";");
    rechargevet[i].nome_regio = strdup(token);
    token = strtok(NULL, ";");
    rechargevet[i].cep = atoi(token);
    token = strtok(NULL, ";");
    rechargevet[i].x = strtod(token, NULL);
    token = strtok(NULL, ";");
    rechargevet[i].y = strtod(token, NULL);
    rechargevet[i].active = 1;
    i++;
  }

  fclose(file);
}

// print the recharge location information
void printrecharge(int pos)
{
  printf("%s %s, %d, %s, %s, %d", rechargevet[pos].sigla_tipo,
         rechargevet[pos].nome_logra, rechargevet[pos].numero_imo,
         rechargevet[pos].nome_bairr, rechargevet[pos].nome_regio,
         rechargevet[pos].cep);
}

void free_rechargevet()
{
  for (int i = 0; i < num_addresses; i++)
  {
    free(rechargevet[i].idend);
    free(rechargevet[i].sigla_tipo);
    free(rechargevet[i].nome_logra);
    free(rechargevet[i].nome_bairr);
    free(rechargevet[i].nome_regio);
  }
  free(rechargevet);
}

int main(int argc, char *argv[])
{

  load_rechargevet(argv[1]);

  printf("Number of addresses: %d\n", num_addresses);
  FILE *file = fopen(argv[2], "r");
  if (file == NULL)
  {
    perror("Unable to open command file");
    exit(EXIT_FAILURE);
  }

  int num_entries;
  if (fscanf(file, "%d\n", &num_entries) != 1)
  {
    perror("Failed to read the number of entries");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  if (argv[3] != NULL && strcmp(argv[3], "lab-test") == 0)
  {
    printf("INITIALIZED\n");
  }

  char line[256];
  while (fgets(line, sizeof(line), file))
  {
    printf("%s", line);
    line[strcspn(line, "\n")] = '\0'; // Remove newline character
    char *token = strtok(line, " ");
    char command_type = token[0];

    if (command_type == 'C')
    {
      double tx = atof(strtok(NULL, " "));
      double ty = atof(strtok(NULL, " "));
      int kmax = atoi(strtok(NULL, " "));

      // Count the number of recharge locations
      int numrecharge = 0;
      while (numrecharge < num_addresses && rechargevet[numrecharge].id_logrado != -1)
        numrecharge++;

      // Create and populate the vector of distances
      ptr_knn_t kvet = (ptr_knn_t)malloc(numrecharge * sizeof(knn_t));
      if (kvet == NULL)
      {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
      }

      for (int i = 0; i < numrecharge; i++)
      {
        kvet[i].id = i;
        kvet[i].dist = dist(tx, ty, rechargevet[i].x, rechargevet[i].y);
      }

      // Sort the vector of distances
      qsort(kvet, numrecharge, sizeof(knn_t), cmpknn);
      int printed = 0;
      // Print the k nearest recharging locations
      for (int i = 0; printed < kmax && i < numrecharge; i++)
      {
        if (rechargevet[kvet[i].id].active == 1)
        {
          printrecharge(kvet[i].id);
          printf(" (%f)\n", kvet[i].dist);
          printed++;
        }
      }

      // Print the map
      // printmap(kvet, kmax, rechargevet, numrecharge, tx, ty);

      // Free allocated memory for distances
      free(kvet);
    }
    else if (command_type == 'D')
    {
      char *id = strdup(strtok(NULL, " "));
      int i;
      for (i = 0; i < num_addresses; i++)
      {
        if (strcmp(rechargevet[i].idend, id) == 0)
        {
          if (rechargevet[i].active == 1)
          {
            rechargevet[i].active = 0;
            printf("Ponto de recarga %s desativado\n", id);
            break;
          }
          printf("Ponto de recarga %s ja estava desativado\n", id);
          break;
        }
      }
      if (i == num_addresses)
        printf("Ponto de recarga %s nao encontrado\n", id);
    }
    else if (command_type == 'A')
    {
      char *id = strdup(strtok(NULL, " "));
      int i;
      for (i = 0; i < num_addresses; i++)
      {
        if (strcmp(rechargevet[i].idend, id) == 0)
        {
          if (rechargevet[i].active == 0)
          {
            rechargevet[i].active = 1;
            printf("Ponto de recarga %s ativado\n", id);
            break;
          }
          printf("Ponto de recarga %s ja estava ativo\n", id);
          break;
        }
      }
      if (i == num_addresses)
        printf("Ponto de recarga %s nao encontrado\n", id);
    }
    else
    {
      fprintf(stderr, "Unknown command type '%c'\n", command_type);
    }
  }

  if (argv[3] != NULL && strcmp(argv[3], "lab-test") == 0)
  {
    printf("FINISHED\n");
  }

  fclose(file);
  free_rechargevet();

  return 0;
}
