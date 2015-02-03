#include <string.h>
#include "Chromosome.h"

struct Chromosome* createChromosome(int *features, int num_features)
{
  int i;
  struct Chromosome *chromosome;

  chromosome = (Chromosome *)my_malloc(sizeof(Chromosome));
  chromosome->features    = (Gene **)my_malloc(num_features * sizeof(Gene *));
  chromosome->carcinogens = (bool *) my_malloc(num_features * sizeof(bool));
  memset(chromosome->carcinogens, false, num_features);

  chromosome->numFeatures        = num_features;
  chromosome->fitness            = 0;
  chromosome->normalized_fitness = 0;
  for(i = 0; i < num_features && features != NULL; i++) {
    chromosome->features[i] = createGene(features[i]);
  }

  return chromosome;
}

struct Chromosome* cloneChromosome(struct Chromosome *chromosome)
{
  int *features;
  struct Chromosome *cloneChromosome;

  features        = getFeaturesInt(chromosome);
  cloneChromosome = createChromosome(features, chromosome->numFeatures);
  free(features);

  return cloneChromosome;
}

int* featuresToInt(struct Chromosome* chromosome)
{
  int i, *features;

  features = (int *)my_malloc(chromosome->numFeatures * sizeof(int));
  for(i = 0; i < chromosome->numFeatures; i++) {
	features[i] = chromosome->features[i]->feature;
  }

  return features;
}

/**
* Two-point crossovers
*/
struct Chromosome** crossover(struct Chromosome *parent_1, struct Chromosome *parent_2)
{
  int i, num_children, num_features, point_1, point_2, aux;
  struct Chromosome **children;
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

void mutate(struct Chromosome *chromosome)
{
  int gene, position;

  gene     = rand() % MAX_GEN;
  position = rand() % chromosome->numFeatures;

  freeGene(chromosome->features[position]);
  chromosome->features[position] = createGene(gene);
}

bool activeCarcinogen(struct Chromosome *chromosome, int position)
{
  bool wasActive = chromosome->carcinogens[position];

  if(wasActive == false) {
    chromosome->carcinogens[position] = true;
  }

  return wasActive;
}

/**
* f(x) = A(x)*w1 + w2*(M - R(x))/M --> A(x) ->suma de elementos cancerígenos, M--> total genes, R(X)--> genes seleccionados
*/
float calculateFitness(struct Chromosome *chromosome)
{
  int i, A, R, M;

  A = 0;
  for (i = 0; i < chromosome->numFeatures; ++i) {
    if(isCarcinogen(chromosome->features[i]) == true && activeCarcinogen(chromosome, i) == false) {
      A++;
    }
  }
  M = MAX_GEN;
  R = chromosome->numFeatures - A; //Number of selected features - Carcinogen genes selected
  chromosome->fitness = (A * WEIGHT_1) + (WEIGHT_2 * (M - R))/M;

  return chromosome->fitness;
}

float setNormalizedFitness(struct Chromosome *chromosome, float totalFitness, float aggregatedFitness)
{
  chromosome->normalized_fitness = (chromosome->fitness / totalFitness) + aggregatedFitness;

  return chromosome->normalized_fitness;
}

float getFitness(struct Chromosome *chromosome)
{
  return chromosome->fitness;
}

void freeChromosome(struct Chromosome *chromosome)
{
  int i;

  for(i = 0; i < chromosome->numFeatures; i++) {
    freeGene(chromosome->features[i]);
  }
  free(chromosome->carcinogens);
  free(chromosome->features);
  free(chromosome);
}
