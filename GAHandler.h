
#ifndef GAHANDLER_H
#define GAHANDLER_H

#include "Chromosome.h"

#define POPULATION_SIZE 10
#define MAX_GENERATIONS 100
#define BEST_POSIBLE_FITNESS NUM_FEATURES    
#define CONFIG_FILE "gaselcancer.cfg"

typedef struct GAHandler {
  struct Chromosome *population[POPULATION_SIZE];
} GAHandler;

struct GAHandler*   createGAHandler(char *config_file);
void                initAlgorithm(struct GAHandler *gaHandler);
struct Chromosome** getPopulation(struct GAHandler *gaHandler);
struct Chromosome*  getBestChromosome(struct GAHandler *gaHandler);
void                freeGAHandler(struct GAHandler *gaHandler);