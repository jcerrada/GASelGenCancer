
#include "GAHandler.h"

extern int   MAX_GENES         = 100;
extern int   NUM_FEATURES      = 10;
extern float WEIGHT_1          = 0.65;
extern float WEIGHT_2          = 0.35;
extern int   NUM_CARCINOGEN    = 20;
extern int   *CARCINOGEN_GENES;
int   AUX_CARCINOGEN_GENES[]   = {3, 4, 7, 9, 12, 15, 19, 22, 28, 36, 41, 49, 53, 57, 64, 65, 70, 73, 81, 97};

GAHandler* createGAHandler(char *config_file)
{
  int i, j, *genes, numGenes;
  GAHandler *gaHandler = (GAHandler *)my_malloc(sizeof(GAHandler));

  // Initializing seed
  srand(time(NULL));

  gaHandler->populationSize   = 10;
  gaHandler->mutationProb     = 15;
  gaHandler->maxGenerations   = 100;
  gaHandler->elitism          = 15;
  gaHandler->crossoversPerGen = 10;
  gaHandler->population       = (Chromosome **)my_malloc(gaHandler->populationSize * sizeof(Chromosome *));

  //Copying the carcinogen genes to the extern variable
  CARCINOGEN_GENES = (int *)my_malloc(NUM_CARCINOGEN * sizeof(int));
  for(i = 0; i < NUM_CARCINOGEN; ++i) {
    CARCINOGEN_GENES[i] = AUX_CARCINOGEN_GENES[i];
  }

  // Generating initial population with all the genes
  numGenes = MAX_GENES / gaHandler->populationSize;
  genes    = (int *)my_malloc(numGenes * sizeof(int));
  for (i = 0; i < gaHandler->populationSize; ++i) {
    for(j = 0; j < numGenes; ++j) {
      genes[j] = (i * 10) + j;
    }
    gaHandler->population[i] = createChromosome(genes, numGenes);
    calculateFitness(gaHandler->population[i]);
  }
  free(genes);

  return gaHandler;
}

Chromosome** getPopulation(GAHandler *gaHandler)
{
  return gaHandler->population;
}

Chromosome* getBestChromosome(GAHandler *gaHandler)
{
  int i;
  struct Chromosome *chromosome;
  float             fitness, bestFitness = -1;

  for (i = 0; i < gaHandler->populationSize && bestFitness < BEST_POSIBLE_FITNESS; ++i) {
    fitness = getFitness(gaHandler->population[i]);
    if(fitness > bestFitness) {
      bestFitness = fitness;
      chromosome = gaHandler->population[i];
    }
  }

  return chromosome;
}

int getWeakestChromosomeIndex(GAHandler *gaHandler)
{
  int   i, position = 0;
  float fitness     = getFitness(gaHandler->population[position]);

  for(i = 1; i < gaHandler->populationSize; i++) {
    if(getFitness(gaHandler->population[i]) < fitness) {
      position = i;
      fitness  = getFitness(gaHandler->population[i]);
    }
  }

  return position;
}

ChromosomeList* elitism(GAHandler *gaHandler)
{
  int i, elite_size = (gaHandler->elitism * gaHandler->populationSize) / 100;
  Chromosome*     chromosome;
  ChromosomeList* elite = createChromosomeList(elite_size);

  if(elite->size > 0) {
    for(i = 0; i < gaHandler->populationSize; ++i) {
      if(getMinFitness(elite) < getFitness(gaHandler->population[i]) || getListOccupied(elite) < getListSize(elite)) {
        chromosome = cloneChromosome(gaHandler->population[i]);
        addChromosomeToList(elite, chromosome);
      }
    }
  }

  return elite;
}

/**
 * Roulette Wheel Selection
 */
int* selection(GAHandler *gaHandler, int numParents)
{
  int i, j, *parents = (int *)my_malloc(numParents * sizeof(int));
  float normalizedFitness,
  	  	totalFitness      = 0,
		aggregatedFitness = 0;

  for(i = 0; i < gaHandler->populationSize; ++i) {
    totalFitness += getFitness(gaHandler->population[i]);
  }

  //Normalizing fitness
  for(i = 0; i < gaHandler->populationSize; ++i) {
    aggregatedFitness += setNormalizedFitness(gaHandler->population[i], totalFitness, aggregatedFitness);
  }

  //Roulette wheel selection
  for(i = 0; i < numParents; ++i) {
    do {
      normalizedFitness = (rand() % 1000 ) / 1000.0; // We generate a random number between 0.000 and 0.999
      for(j = 0; getNormalizedFitness(gaHandler->population[j]) < normalizedFitness; ++j);
      parents[i] = j;
    } while(i != 0 && parents[0] == j);
  }

  return parents;
}

Chromosome** crossoverPhase(GAHandler *gaHandler, Chromosome *parent_1, Chromosome *parent_2)
{
  Chromosome **children = crossover(parent_1, parent_2);

  return children;
}

void mutation(GAHandler *gaHandler, Chromosome *chromosome)
{
  int mutateRate = rand() % 100;

  if(mutateRate < gaHandler->mutationProb) {
	  mutate(chromosome);
  }
}

void restoreElite(GAHandler *gaHandler, ChromosomeList *elite)
{
  int   i, position, size = getListOccupied(elite);
  float fitness;
  Chromosome *chromosome;

  for(i = 0; i < size; ++i) {
    position = getWeakestChromosomeIndex(gaHandler);
    fitness  = getFitness(gaHandler->population[position]);
    for(; i < size && (getFitness(chromosomeAt(elite, i)) <= fitness); ++i);
    if(i < size) {
      freeChromosome(gaHandler->population[position]);
      chromosome = cloneChromosome(chromosomeAt(elite, i));
      gaHandler->population[position] = chromosome;
    }
  }
}

void applyGA(GAHandler *gaHandler)
{
  int i, j, k, *parents,
      numParents  = 2,
      numChildren = 2;
  Chromosome     **children;
  ChromosomeList  *elite;

  printPopulation(gaHandler);
  for(k = 0; k < gaHandler->maxGenerations; ++k) {
    printf("\nGeneration: %d\n", k);
    elite = elitism(gaHandler);
    for(i = 0; i < gaHandler->crossoversPerGen; ++i) {
      parents  = selection(gaHandler, numParents);
      children = crossoverPhase(gaHandler,gaHandler->population[parents[0]], gaHandler->population[parents[1]]);
      for(j = 0; j < numChildren; ++j) {
        mutation(gaHandler, children[j]);
        calculateFitness(children[j]);
        freeChromosome(gaHandler->population[parents[j]]);
        gaHandler->population[parents[j]] = children[j]; // Children always replace their parents
      }
      free(parents);
    }
    restoreElite(gaHandler, elite);
    freeChromosomeList(elite);
    printPopulation(gaHandler);
  }
}

void printPopulation(GAHandler *gaHangler)
{
  int i;

  printf("\n#### Population ###\n");
  printf("Population size: %d\n", gaHangler->populationSize);
  for(i = 0; i < gaHangler->populationSize; ++i) {
    printf("Chromosome %d: ", i);
    printChromosome(gaHangler->population[i]);
    printf("\n");
  }
}

void freeGAHandler(GAHandler *gaHandler)
{
  int i;

  for (i = 0; i < gaHandler->populationSize; ++i) {
    freeChromosome(gaHandler->population[i]);
  }

  free(CARCINOGEN_GENES);
  free(gaHandler);
}
