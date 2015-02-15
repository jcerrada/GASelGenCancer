#include <string.h>
#include "Chromosome.h"

Chromosome* createChromosome(int *features, int num_features)
{
  int i;
  Chromosome *chromosome;

  chromosome = (Chromosome *)my_malloc(sizeof(Chromosome));
  chromosome->features    = (Gene **)my_malloc(num_features * sizeof(Gene *));

  chromosome->numFeatures        = num_features;
  chromosome->fitness            = 0;
  chromosome->normalized_fitness = 0;
  for(i = 0; i < num_features && features != NULL; i++) {
    chromosome->features[i] = createGene(features[i]);
  }

  return chromosome;
}

Chromosome* cloneChromosome(Chromosome *chromosome)
{
  int *features;
  Chromosome *cloneChromosome;

  features        = featuresToInt(chromosome);
  cloneChromosome = createChromosome(features, chromosome->numFeatures);

  cloneChromosome->fitness = chromosome->fitness;

  free(features);

  return cloneChromosome;
}

bool alreadyInChromosome(Chromosome* chromosome, Gene* gene, int position)
{
  int i;
  bool exists = false;

  for(i = 0; i < position && exists == false; ++i) {
    if(getFeature(gene) == getFeature(chromosome->features[i])) {
      exists = true;
    }
  }

  return exists;
}

int* featuresToInt(Chromosome* chromosome)
{
  int i, *features;

  features = (int *)my_malloc(chromosome->numFeatures * sizeof(int));
  for(i = 0; i < chromosome->numFeatures; i++) {
    features[i] = getFeature(chromosome->features[i]);
  }

  return features;
}

/**
* Two-point crossovers
*/
Chromosome** crossover(Chromosome *parent_1, Chromosome *parent_2)
{
  int i, num_children, num_features, point_1, point_2, aux;
  Chromosome **children;
  num_features = parent_1->numFeatures;
  num_children = 2;

  children     = (Chromosome **)my_malloc(num_children * sizeof(Chromosome *));
  for(i = 0; i < num_children; i++) {
    children[i] = createChromosome(NULL, num_features);
  }

  point_1 = rand() % num_features;
  do {
    point_2 = rand() % num_features;
  } while(point_1 == point_2);
  if(point_1 > point_2) {
    aux = point_1;
    point_1 = point_2;
    point_2 = aux;
  }

  for (i = 0; i < point_1; ++i) {
    children[0]->features[i] = createGene(getFeature(parent_1->features[i]));
    children[1]->features[i] = createGene(getFeature(parent_2->features[i]));
  }
  for (; i < point_2; ++i) {
    children[0]->features[i] = createGene(getFeature(parent_2->features[i]));
    children[1]->features[i] = createGene(getFeature(parent_1->features[i]));
  }
  for (; i < num_features; ++i) {
    children[0]->features[i] = createGene(getFeature(parent_1->features[i]));
    children[1]->features[i] = createGene(getFeature(parent_2->features[i]));
  }

  /* If we use static arrais to store the genes, the code below gives better performance
  memcpy(children[0]->features, parent_1->features, point_1 * sizeof(struct Gene));
  memcpy(children[1]->features, parent_2->features, point_1 * sizeof(struct Gene));
  memcpy(children[0]->features + point_1, parent_2->features + point_1, (point_2 - point_1) * sizeof(struct Gene));
  memcpy(children[1]->features + point_1, parent_1->features + point_1, (point_2 - point_1) * sizeof(struct Gene));
  memcpy(children[0]->features + point_2, parent_1->features + point_2, (num_features - point_2) * sizeof(struct Gene));
  memcpy(children[1]->features + point_2, parent_2->features + point_2, (num_features - point_2) * sizeof(struct Gene));
  */

  return children;
}

void mutate(Chromosome *chromosome)
{
  int gene, position;

  gene     = rand() % MAX_GENES;
  position = rand() % chromosome->numFeatures;

  freeGene(chromosome->features[position]);
  chromosome->features[position] = createGene(gene);
}

/**
* f(x) = A(x)*w1 + w2*(M - R(x))/M --> A(x) ->suma de elementos cancerígenos, M--> total genes, R(X)--> genes seleccionados
*/
float calculateFitness(Chromosome *chromosome)
{
  int i, A, R, M;
  float aux;

  A = 0;

  for (i = 0; i < chromosome->numFeatures; ++i) {
    if(isCarcinogen(chromosome->features[i]) == true && alreadyInChromosome(chromosome, chromosome->features[i], i) == false) {
      A++;;
    }
  }

  M = MAX_GENES;
  R = chromosome->numFeatures - A; //Number of selected features - Carcinogen genes selected

  chromosome->fitness = (A * WEIGHT_1) + (WEIGHT_2 * (M - R))/M;

  return chromosome->fitness;
}

float setNormalizedFitness(Chromosome *chromosome, float totalFitness, float aggregatedFitness)
{
  chromosome->normalized_fitness = (chromosome->fitness / totalFitness) + aggregatedFitness;

  return chromosome->normalized_fitness;
}

float getFitness(Chromosome *chromosome)
{
  return chromosome->fitness;
}

float getNormalizedFitness(Chromosome *chromosome)
{
  return chromosome->normalized_fitness;
}

void printChromosome(Chromosome *chromosome)
{
  int i, numFeatures = chromosome->numFeatures - 1;
  printf("[");
  for(i = 0; i < numFeatures; ++i) {
    printf("%d, ", getFeature(chromosome->features[i]));
  }
  if(chromosome->numFeatures > 0) {
    printf("%d", getFeature(chromosome->features[numFeatures]));
  }
  printf("] -> %f", chromosome->fitness);
}

void freeChromosome(Chromosome *chromosome)
{
  int i;

  for(i = 0; i < chromosome->numFeatures; i++) {
    freeGene(chromosome->features[i]);
  }
  free(chromosome->features);
  free(chromosome);
}
