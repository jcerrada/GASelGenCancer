/*
 ============================================================================
 Name        : GASelGenCancer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

 //READ ALL CONSTANTS AND POPULATION FROM CONFIG FILE

#include "GAHandler.h"

int main(void) {
  /*int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  struct Gene *gene;
  struct Chromosome *chromosome = createChromosome(array, 10);
  gene = createGene(5);
  printf("Hello world!\n");
  freeChromosome(chromosome);
  freeGene(gene);
  */

  GAHandler *gaHandler = createGAHandler("");
  applyGA(gaHandler);
  printPopulation(gaHandler);

  freeGAHandler(gaHandler);

  return EXIT_SUCCESS;
}
