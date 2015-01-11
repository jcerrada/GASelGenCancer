#include "Gene.h"

const int CARCINOGEN_GENES[] = {3, 4 , 7, 9, 12, 15, 19, 22, 28, 36, 41, 49, 53, 57, 64, 65, 70, 73, 81, 97};

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
