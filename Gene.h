
#ifndef GENE
#define GENE

#include "commons.h"

#define NUM_CARCINOGEN     20
const int CARCINOGEN_GENES[] = {3, 4 , 7, 9, 12, 15, 19, 22, 28, 36, 41, 49, 53, 57, 64, 65, 70, 73, 81, 97};

typedef struct Gene {
  int    feature; //array containing the features of the chromosome
  bool   carcinogen;
} Gene;

void  initializeGene(struct Gene *gene, int feature);
void  setCarcinogen(struct Gene *gene);
bool  isCarcinogen(struct Gene *gene);

#endif