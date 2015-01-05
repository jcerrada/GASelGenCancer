
#ifndef GENE_H
#define GENE_H

#include "commons.h"

#define NUM_CARCINOGEN     20
extern const int CARCINOGEN_GENES[];

typedef struct Gene {
  int    feature; //array containing the features of the chromosome
  bool   carcinogen;
} Gene;

void  initializeGene(struct Gene *gene, int feature);
void  setCarcinogen(struct Gene *gene);
bool  isCarcinogen(struct Gene *gene);

#endif
