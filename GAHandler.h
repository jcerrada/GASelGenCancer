
#ifndef GAHANDLER_H
#define GAHANDLER_H

#include "Chromosome.h"

#define BEST_POSIBLE_FITNESS NUM_FEATURES    
#define CONFIG_FILE "gaselcancer.cfg"

int POPULATION_SIZE;
int MUTATION_PROB;
int MAX_GENERATIONS;
int ELITISM;
int CROSSOVERS_PER_GEN;

typedef struct GAHandler {
  struct Chromosome **population;
} GAHandler;

struct GAHandler*   createGAHandler(char *config_file);
void                initAlgorithm(struct GAHandler *gaHandler);
struct Chromosome** getPopulation(struct GAHandler *gaHandler);
struct Chromosome*  getBestChromosome(struct GAHandler *gaHandler);
void                freeGAHandler(struct GAHandler *gaHandler);

#endif