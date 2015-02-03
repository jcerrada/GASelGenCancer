#include "Gene.h"

struct Gene* createGene(int feature)
{
	struct Gene *gene = my_malloc(sizeof(struct Gene));

	gene->feature = feature;
	setCarcinogen(gene);

	return gene;
}

int getFeature(struct Gene *gene)
{
	return gene->feature;
}

bool isCarcinogen(struct Gene *gene)
{
  return gene->carcinogen;
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

void freeGene(struct Gene *gene)
{
	free(gene);
}
