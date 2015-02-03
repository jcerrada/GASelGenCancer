
#include "GAHandler.h"

extern int   MAX_GEN            = 100;
extern int   NUM_FEATURES       = 10;
extern float WEIGHT_1           = 0.65;
extern float WEIGHT_2           = 0.35;
extern int   NUM_CARCINOGEN     = 20;
extern int   *CARCINOGEN_GENES = {3, 4, 7, 9, 12, 15, 19, 22, 28, 36, 41, 49, 53, 57, 64, 65, 70, 73, 81, 97};

POPULATION_SIZE    = 10;
MUTATION_PROB      = 15;
MAX_GENERATIONS    = 100;
ELITISM            = 15;
CROSSOVERS_PER_GEN = 10;

struct GAHandler* createGAHandler(char *config_file)
{
	struct GAHandler *gaHandler = my_malloc(sizeof(GAHandler));

}

void applyGA(struct GAHandler *gaHandler)
{
  int i;

  do {
    for (i = 0; i < POPULATION_SIZE; ++i)
    {
      calculateFitness(gaHandler->population[i]);
    }
  } while(true);
}

struct Chromosome** getPopulation(struct GAHandler *gaHandler)
{
  return gaHandler->population;
}

struct Chromosome* getBestChromosome(struct GAHandler *gaHandler)
{
  int i;
  struct Chromosome *chromosome;
  float             fitness, bestFitness = -1;

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
