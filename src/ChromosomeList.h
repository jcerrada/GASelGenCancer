
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
void            addChromosomeToList(ChromosomeList *chromosomeList, Chromosome *chromosome);
Chromosome*     chromosomeAt(ChromosomeList *chromosomeList, int index);
float           getMinFitness(ChromosomeList *chromosomeList);
int             getListSize(ChromosomeList *chromosomeList);
int             getListOccupied(ChromosomeList *chromosomeList);
void            printChromosomeList(ChromosomeList *chromosomeList);
void            freeChromosomeList(ChromosomeList *chromosomeList);

#endif
