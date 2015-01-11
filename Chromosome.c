#include "Chromosome.h"

struct Chromosome* createChromosome(int *features, int num_features)
{
  int i;
  struct Chromosome *chromosome;

  chromosome = (Chromosome *)my_malloc(sizeof(Chromosome));
  chromosome->features    = (Chromosome **)my_malloc(num_features * sizeof(Chromosome *));
  chromosome->numFeatures = num_features;
  chromosome->fitness     = 0;
  for(i = 0; i < NUM_FEATURES && features != NULL; i++) {
    chromosome->features[i] = createGene(features[i]);
  }

  return chromosome;
}

/**
* Two-point crossovers
*/
void crossover(struct Chromosome *parent_1, struct Chromosome *parent_2, struct Chromosome **children)
{
  int i, num_children, point_1, point_2, aux;
  num_children = 2;

  children     = (Chromosome **)my_malloc(num_children * sizeof(Chromosome *));
  for(i = 0; i < num_children; i++) {
    children[i] = createChromosome(NULL);
  }

  point_1 = rand() % NUM_FEATURES;
  do {
    point_2 = rand() % NUM_FEATURES;
  } while(point_1 == point_2);
  if(point_1 > point_2) {
    aux = point_1;
    point_1 = point_2;
    point_2 = aux;
  }

  memcpy(children[0]->features, parent_1->features, point_1 * sizeof(struct Gene));
  memcpy(children[1]->features, parent_2->features, point_1 * sizeof(struct Gene));
  memcpy(children[0]->features + point_1, parent_2->features + point_1, (point_2 - point_1) * sizeof(struct Gene));
  memcpy(children[1]->features + point_1, parent_1->features + point_1, (point_2 - point_1) * sizeof(struct Gene));
  memcpy(children[0]->features + point_2, parent_1->features + point_2, (NUM_FEATURES - point_2) * sizeof(struct Gene));
  memcpy(children[1]->features + point_2, parent_2->features + point_2, (NUM_FEATURES - point_2) * sizeof(struct Gene));
}

void mutate(struct Chromosome *chromosome)
{
  int gene, position;

  gene     = rand() % MAX_GEN;
  position = rand() % NUM_FEATURES;

  freeGene(chromosome->features[position]);
  chromosome->features[position] = createGene(gene);
}

/*
float fitness(Chromosome *chromosome, Chromosome **population) {

}
*/

/**
* f(x) = A(x)*w1 + w2*(M - R(x))/M --> A(x) ->suma de elementos cancerígenos, M--> total genes, R(X)--> genes seleccionados
*/
float calculateFitness(struct Chromosome *chromosome) {
  int i, A, R, M;

  A = 0;
  for (i = 0; i < NUM_FEATURES; ++i) {
    if(isCarcinogen(chromosome->features[i]) == true) {
      A++;
    }
  }
  M = MAX_GEN;
  R = NUM_FEATURES - A; //Number of selected features - Carcinogen genes selected
  chromosome->fitness = (A * WEIGHT_1) + (WEIGHT_2 * (M - R))/M;

  return chromosome->fitness;
}

float getFitness(struct Chromosome *chromosome) {
  return chromosome->fitness;
}

void freeChromosome(struct Chromosome *chromosome)
{
  int i;

  for(i = 0; i < chromosome->numFeatures; i++) {
	freeGene(chromosome->features[i]);
  }
  free(chromosome->features);
  free(chromosome);
}
