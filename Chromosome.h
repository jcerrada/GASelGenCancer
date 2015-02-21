
#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "Gene.h"

float WEIGHT_1;
float WEIGHT_2;

typedef struct Chromosome {
  Gene    **features; //array containing the features of the chromosome
  int     numFeatures;
  float   fitness;
  float   normalized_fitness;
} Chromosome;

Chromosome*  createChromosome(int *features, int num_features);
Chromosome*  cloneChromosome(Chromosome *chromosome);
bool         alreadyInChromosome(Chromosome* chromosome, Gene* gene, int position);
int*         featuresToInt(Chromosome* chromosome);
Chromosome** crossover(Chromosome *parent_1, Chromosome *parent_2);
void         mutate(Chromosome *chromosome);
float        calculateFitness(Chromosome *chromosome);
float        setNormalizedFitness(Chromosome *chromosome, float totalFitness, float aggregatedFitness);
float        getFitness(Chromosome *chromosome);
float        getNormalizedFitness(Chromosome *chromosome);
void         printChromosome(Chromosome *chromosome);
void         freeChromosome(Chromosome *chromosome);

#endif
