
#ifndef GAHANDLER_H
#define GAHANDLER_H

#include "ChromosomeList.h"

#define BEST_POSIBLE_FITNESS NUM_FEATURES    
#define CONFIG_FILE "gaselcancer.cfg"

typedef struct GAHandler {
  struct Chromosome **population;
  int populationSize;
  int mutationProb;
  int maxGenerations;
  int elitism;
  int crossoversPerGen;

} GAHandler;

GAHandler*      createGAHandler(char *config_file);
Chromosome**    getPopulation(GAHandler *gaHandler);
Chromosome*     getBestChromosome(GAHandler *gaHandler);
int             getWeakestChromosomeIndex(GAHandler *gaHandler);
ChromosomeList* elitism(GAHandler *gaHandler);
int*            selection(GAHandler *gaHandler, int numParents);
Chromosome**    crossoverPhase(GAHandler *gaHandler, Chromosome *parent_1, Chromosome *parent_2);
void            mutation(GAHandler *gaHandler, Chromosome *chromosome);
void            restoreElite(GAHandler *gaHandler, ChromosomeList *elite);
void            applyGA(GAHandler *gaHandler);
void            printPopulation(GAHandler *gaHangler);
void            freeGAHandler(GAHandler *gaHandler);

#endif
