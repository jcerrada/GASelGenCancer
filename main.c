#include "chromosome.h"

int main() {
  int array[] = {1,2,3,4,5,6,7,8,9,0};
  struct Gene gene;
  struct Chromosome *chromosome = createChromosome(array);
  initializeGene(&gene, 5);
  printf("Hello world!\n");
  return 0;
}