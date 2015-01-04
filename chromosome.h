
#ifndef CHROMOSOME
#define CHROMOSOME

#include "Gene.h"

#define MAX_GEN       100
#define NUM_FEATURES  10
#define MUTATION_PROB 15 //percentaje

typedef struct Chromosome {
  Gene    features[NUM_FEATURES]; //array containing the features of the chromosome
  float   fitness;
} Chromosome;

struct Chromosome*  createChromosome(int *features);
struct Chromosome** crossover(struct Chromosome *parent_1, struct Chromosome *parent_2);
void         mutate(struct Chromosome *chromosome);
//float        fitness(Chromosome *chromosome, Chromosome **population);
float        fitness(struct Chromosome *chromosome);
void         freeChromosome(struct Chromosome *chromosome);

#endif