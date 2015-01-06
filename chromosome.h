
#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "Gene.h"

#define MAX_GEN       100
#define NUM_FEATURES  10
#define MUTATION_PROB 15 //percentaje
#define WEIGHT_1      0.65
#define WEIGHT_2      0.35

typedef struct Chromosome {
  Gene    features[NUM_FEATURES]; //array containing the features of the chromosome
  float   fitness;
} Chromosome;

struct Chromosome*  createChromosome(int *features);
void                crossover(struct Chromosome *parent_1, struct Chromosome *parent_2, struct Chromosome **children);
void                mutate(struct Chromosome *chromosome);
//float              fitness(Chromosome *chromosome, Chromosome **population);
float               calculateFitness(struct Chromosome *chromosome);
float               getFitness(struct Chromosome *chromosome)
void                freeChromosome(struct Chromosome *chromosome);

#endif
