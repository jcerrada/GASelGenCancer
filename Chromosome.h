
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
  float   normalized_fitness;
} Chromosome;

struct Chromosome*  createChromosome(int *features, int num_features);
struct Chromosome*  cloneChromosome(struct Chromosome *chromosome);
int*                featuresToInt(struct Chromosome* chromosome);
struct Chromosome** crossover(struct Chromosome *parent_1, struct Chromosome *parent_2);
void                mutate(struct Chromosome *chromosome);
bool                activeCarcinogen(struct Chromosome *chromosome, int position);
float               calculateFitness(struct Chromosome *chromosome);
float               setNormalizedFitness(struct Chromosome *chromosome, float totalFitness, float aggregatedFitness);
float               getFitness(struct Chromosome *chromosome);
void                freeChromosome(struct Chromosome *chromosome);

#endif
