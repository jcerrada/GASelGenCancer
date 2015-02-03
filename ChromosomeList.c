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
  chromosomeList->chromosomeList = (Chromosome **)my_malloc(size * sizeof(Chromosome*));
  chromosomeList->minFitness     = 0;
  chromosomeList->occupied       = 0;
  chromosomeList->size           = size;

  return chromosomeList;
}

void addChromosomeToList(ChromosomeList *chromosomeList, struct Chromosome *chromosome)
{
  int i, position;
  struct Chromosome *aux_chromo;

  for(i = 0; i < chromosomeList->occupied && getFitness(chromosomeList->list[i]) < getFitness(chromosome->fitness); ++i);
  position = i;

  if(chromosomeList->occupied < chromosomeList->size) {
	for(i = ++chromosomeList->occupied; i > position;) {
	  chromosomeList->list[i] = chromosomeList->list[--i];
	}
  }
  else {
	for(i = 0; i < position;) {
	  chromosomeList->list[i] = chromosomeList->list[++i];
	}
  }

  chromosomeList->list[position] = chromosome;
  chromosomeList->minFitness               = getFitness(chromosomeList->list[0]);
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

void freeChromosomeList(ChromosomeList *chromosomeList)
{
  int i;

  for(i = 0; i < chromosomeList->occupied; ++i) {
    freeChromosome(chromosomeList->list[i]);
  }

  free(chromosomeList);
}
