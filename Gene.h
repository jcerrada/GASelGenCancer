
#ifndef GENE_H
#define GENE_H

#include "Commons.h"

int MAX_GENES;
int NUM_CARCINOGEN;
int *CARCINOGEN_GENES;

typedef struct Gene {
  int    feature; //array containing the features of the chromosome
  bool   carcinogen;
} Gene;

Gene* createGene(int feature);
int   getFeature(Gene *gene);
bool  isCarcinogen(Gene *gene);
void  setCarcinogen(Gene *gene);
void  freeGene(Gene *gene);

#endif
