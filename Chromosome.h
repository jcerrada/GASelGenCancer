
#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "Gene.h"

int   MAX_GEN;
float WEIGHT_1;
float WEIGHT_2;

typedef struct Chromosome {
  Gene    **features; //array containing the features of the chromosome
  bool    *carcinogens; //array of bools telling whether a gene is carcinogenic or not
  int     numFeatures;
  float   fitness;
} Chromosome;

struct Chromosome* createChromosome(int *features, int num_features);
void               crossover(struct Chromosome *parent_1, struct Chromosome *parent_2, struct Chromosome **children);
void               mutate(struct Chromosome *chromosome);
bool               activeCarcinogen(struct Chromosome *chromosome, int position);
float              calculateFitness(struct Chromosome *chromosome);
float              getFitness(struct Chromosome *chromosome);
void               freeChromosome(struct Chromosome *chromosome);

#endif
