
#include "GAHandler.h"

struct GAHandler* createGAHandler(char *config_file)
{

}

void initAlgorithm(struct GAHandler *gaHandler)
{

}

struct Chromosome** getPopulation(struct GAHandler *gaHandler)
{
  return gaHandler->population;
}

struct Chromosome* getBestChromosome(struct GAHandler *gaHandler)
{
  int i;
  struct Chromosome *chromosome;
  float             fitness, bestFitness = 0;

  for (i = 0; i < POPULATION_SIZE && bestFitness < BEST_POSIBLE_FITNESS; ++i) {
    fitness = getFitness(gaHandler->population[i]);
    if(fitness > bestFitness) {
      bestFitness = fitness;
      chromosome = gaHandler->population[i];
    }
  }

  return chromosome;
}

void freeGAHandler(struct GAHandler *gaHandler)
{
  int i;

  for (i = 0; i < POPULATION_SIZE; ++i) {
    freeChromosome(gaHandler->population[i]);
  }

  free(gaHandler);
}