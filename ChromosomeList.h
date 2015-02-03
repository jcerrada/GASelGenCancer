
#ifndef CHROMOSOMELIST_H
#define CHROMOSOMELIST_H

#include "Chromosome.h"

typedef struct ChromosomeList {
  struct Chromosome **list;
  float               minFitness;
  int                 size;
  int                 occupied;
} ChromosomeList;

ChromosomeList* createChromosomeList(int size);
void            addChromosomeToList(struct Chromosome *chromosome);
float           getMinFitness(ChromosomeList *chromosomeList);
int             getListSize(ChromosomeList *chromosomeList);
int             getListOccupied(ChromosomeList *chromosomeList);
void            freeChromosomeList(ChromosomeList *chromosomeList);

#endif
