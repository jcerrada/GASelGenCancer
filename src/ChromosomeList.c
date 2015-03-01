/*
 * ChromosomeList.c
 *
 *  Created on: 02/02/2015
 *      Author: jose
 */

#include "ChromosomeList.h"

ChromosomeList* createChromosomeList(int size)
{
  ChromosomeList *chromosomeList = (ChromosomeList *)my_malloc(sizeof(ChromosomeList));
  chromosomeList->list           = (Chromosome **)my_malloc(size * sizeof(Chromosome*));
  chromosomeList->minFitness     = 0;
  chromosomeList->occupied       = 0;
  chromosomeList->size           = size;

  return chromosomeList;
}

void addChromosomeToList(ChromosomeList *chromosomeList, Chromosome *chromosome)
{
  int i, position;

  for(i = 0; i < chromosomeList->occupied && getFitness(chromosomeList->list[i]) < getFitness(chromosome); ++i);
  position = (i == chromosomeList->size ? (i - 1) : i);

  if(chromosomeList->occupied < chromosomeList->size) {
    for(i = chromosomeList->occupied; i > position; --i) {
      chromosomeList->list[i] = chromosomeList->list[i - 1];
    }
    chromosomeList->occupied++;
  }
  else {
    freeChromosome(chromosomeList->list[0]);
    for(i = 0; i < position; ++i) {
      chromosomeList->list[i] = chromosomeList->list[i + 1];
    }
  }

  chromosomeList->list[position] = chromosome;
  chromosomeList->minFitness     = getFitness(chromosomeList->list[0]);
}

Chromosome* chromosomeAt(ChromosomeList *chromosomeList, int index)
{
	return chromosomeList->list[index];
}

float getMinFitness(ChromosomeList *chromosomeList)
{
  return chromosomeList->minFitness;
}

int getListSize(ChromosomeList *chromosomeList)
{
  return chromosomeList->size;
}

int getListOccupied(ChromosomeList *chromosomeList)
{
  return chromosomeList->occupied;
}

void printChromosomeList(ChromosomeList *chromosomeList)
{
  int i;
  
  for(i = 0; i < chromosomeList->occupied; ++i) {
    printf("\n");
    printChromosome(chromosomeList->list[i]);
  }
  printf("\n");
}

void freeChromosomeList(ChromosomeList *chromosomeList)
{
  int i;

  for(i = 0; i < chromosomeList->occupied; ++i) {
    freeChromosome(chromosomeList->list[i]);
  }
  free(chromosomeList->list);

  free(chromosomeList);
}
