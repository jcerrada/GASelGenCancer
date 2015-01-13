
#ifndef GENE_H
#define GENE_H

#include "Commons.h"

int NUM_CARCINOGEN;
int CARCINOGEN_GENES[];

typedef struct Gene {
  int    feature; //array containing the features of the chromosome
  bool   carcinogen;
} Gene;

struct Gene* createGene(int feature);
int          getFeature(struct Gene *gene);
bool         isCarcinogen(struct Gene *gene);
void         setCarcinogen(struct Gene *gene);
void         freeGene(struct Gene *gene);

#endif
