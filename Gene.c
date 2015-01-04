#include "Gene.h"

void initializeGene(struct Gene *gene, int feature)
{
  gene->feature = feature;
  setCarcinogen(gene);
}

void setCarcinogen(struct Gene *gene)
{
  int i;

  gene->carcinogen = false;
  for(i = 0; i < NUM_CARCINOGEN; i++) {
    if(CARCINOGEN_GENES[i] == gene->feature) {
      gene->carcinogen = true;
      break;
    }
  }
}

bool isCarcinogen(Gene *gene)
{
  return gene->carcinogen;
}