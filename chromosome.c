#include <OSAKit/OSAKit.h>
#include "chromosome.h"

struct Chromosome* createChromosome(int *features)
{
  int i;
  struct Chromosome *chromosome;

  chromosome = (Chromosome *)my_malloc(sizeof(Chromosome));
  chromosome->fitness  = 0;
  for(i = 0; i < NUM_FEATURES && features != NULL; i++) {
    initializeGene(&Chromosome->features[i], features[i]);
  }

  return chromosome;
}

struct Chromosome** crossover(struct Chromosome *parent_1, struct Chromosome *parent_2)
{
  int i, num_children, point_1, point_2, aux;
  num_children = 2;
  struct Chromosome *children[num_children];

  //children     = (Chromosome **)my_malloc(num_children * sizeof(Chromosome *));
  for(i = 0; i < num_children; i++) {
    children[i] = createChromosome(NULL);
  }

  srand(NULL);
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

  return children;
}

void mutate(struct Chromosome *chromosome)
{
  int gene, position;

  srand(NULL);
  if((rand() % 100) < MUTATION_PROB) {
    gene     = rand() % MAX_GEN;
    position = rand() % NUM_FEATURES;
    chromosome->features[position] = gene;
  }
}

/*
float fitness(Chromosome *chromosome, Chromosome **population) {

}
*/

float fitness(struct Chromosome *chromosome) {
  int i;

  for (i = 0; i < NUM_FEATURES; ++i) {
    if(isCarcinogen(chromosome->features[i]) == true) {
      chromosome->fitness++;
    }
  }

  return chromosome->fitness;
}

void freeChromosome(struct Chromosome *chromosome)
{
  free(chromosome);
}