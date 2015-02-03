
#ifndef GAHANDLER_H
#define GAHANDLER_H

#include "ChromosomeList.h"

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
struct Chromosome** elitism(struct GAHandler *gaHandler);
struct Chromosome** selection(struct GAHandler *gaHandler);
struct Chromosome** crossover(struct Chromosome *parent_1, struct Chromosome *parent_2);
void                mutation(struct Chromosome *chromosome);
void                applyGA(struct GAHandler *gaHandler);
struct Chromosome** getPopulation(struct GAHandler *gaHandler);
struct Chromosome*  getBestChromosome(struct GAHandler *gaHandler);
void                freeGAHandler(struct GAHandler *gaHandler);

#endif
