#include "Gene.h"

Gene* createGene(int feature)
{
	Gene *gene = my_malloc(sizeof(Gene));

	gene->feature = feature;
	setCarcinogen(gene);

	return gene;
}

int getFeature(Gene *gene)
{
	return gene->feature;
}

bool isCarcinogen(Gene *gene)
{
  return gene->carcinogen;
}

void setCarcinogen(Gene *gene)
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

void freeGene(Gene *gene)
{
	free(gene);
}
