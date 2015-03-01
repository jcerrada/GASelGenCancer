
#include "GAHandler.h"

extern int   MAX_GENES;
extern int   NUM_FEATURES;
extern float WEIGHT_1;
extern float WEIGHT_2;
extern int   NUM_CARCINOGEN;
extern int   *CARCINOGEN_GENES;

GAHandler* createGAHandler()
{
  int i, *carGenes, numGenes, **population;
  ConfigReader *config = createConfigReader();
  GAHandler *gaHandler = (GAHandler *)my_malloc(sizeof(GAHandler));

  //Reading Config file
  if(readConfigFile(config, CONFIG_FILE) == CONFIG_ERROR) {
    fprintf(stderr, "Error trying to read the configuration file: %s\n", CONFIG_FILE);
    freeConfigReader(config);
    free(gaHandler);
    return NULL;
  }

  // Initializing seed
  srand(time(NULL));

  MAX_GENES      = getCRMaxGeneNumber(config);
  NUM_FEATURES   = getCRFeaturesPerChromosome(config);
  WEIGHT_1       = getCRWeight1(config);
  WEIGHT_2       = getCRWeight2(config);
  NUM_CARCINOGEN = getCRNumCarcinogenGenes(config);
  carGenes       = getCRCarcinogenGenes(config);
  CARCINOGEN_GENES = (int *)my_malloc(NUM_CARCINOGEN * sizeof(int));
  for(i = 0; i < NUM_CARCINOGEN; ++i) {
    CARCINOGEN_GENES[i] = carGenes[i];
  }

  BEST_POSIBLE_FITNESS = (WEIGHT_1 * NUM_FEATURES) + WEIGHT_2;

  gaHandler->populationSize   = getCRPopulationSize(config);
  gaHandler->mutationProb     = getCRMutationProbability(config);
  gaHandler->maxGenerations   = getCRMaxGenerations(config);
  gaHandler->elitism          = getCRElitism(config);
  gaHandler->crossoversPerGen = getCRCrossoversPerGeneration(config);
  gaHandler->population       = (Chromosome **)my_malloc(gaHandler->populationSize * sizeof(Chromosome *));

  // Generating initial population with all the genes
  numGenes   = MAX_GENES / gaHandler->populationSize;
  population = getCRPopulation(config);
  for (i = 0; i < gaHandler->populationSize; ++i) {
    gaHandler->population[i] = createChromosome(population[i], numGenes);
    calculateFitness(gaHandler->population[i]);
  }

  freeConfigReader(config);

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
    printf("\n==================================================\n");
    printf("Generation: %d\n", k + 1);
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
      free(children);
      free(parents);
    }
    restoreElite(gaHandler, elite);
    printPopulation(gaHandler);

    freeChromosomeList(elite);
  }
}

void printPopulation(GAHandler *gaHangler)
{
  int i;

  printf("\n############# Population #############\n");
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
  free(gaHandler->population);
  free(CARCINOGEN_GENES);

  free(gaHandler);
}
