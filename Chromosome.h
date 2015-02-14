
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

Chromosome*  createChromosome(int *features, int num_features);
Chromosome*  cloneChromosome(Chromosome *chromosome);
int*         featuresToInt(Chromosome* chromosome);
Chromosome** crossover(Chromosome *parent_1, Chromosome *parent_2);
void         mutate(Chromosome *chromosome);
bool         activeCarcinogen(Chromosome *chromosome, int position);
float        calculateFitness(Chromosome *chromosome);
float        setNormalizedFitness(Chromosome *chromosome, float totalFitness, float aggregatedFitness);
float        getFitness(Chromosome *chromosome);
float        getNormalizedFitness(Chromosome *chromosome);
void         printChromosome(Chromosome *chromosome);
void         freeChromosome(Chromosome *chromosome);

#endif
