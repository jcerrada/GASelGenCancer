
#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include "Commons.h"
#include "libconfig/libconfig.h"

#define CONFIG_ERROR -1
#define CONFIG_RIGHT  1

typedef struct ConfigReader {
  //Gene vars
  int maxGeneNumber;
  int numCarcinogen;
  int *carcinogenGenes;

  //Chromosome vars
  int   numFeatures;
  float weight1;
  float weight2;

  //GA vars
  int   populationSize;
  int** population;
  int   mutationProb;
  int   maxGenerations;
  int   elitism;
  int   crossoversPerGen;

} ConfigReader;

ConfigReader* createConfigReader();
int           readGeneVarsConfig(ConfigReader* configReader, config_t *cfg);
int           readChromosomeVarsConfig(ConfigReader* configReader, config_t *cfg);
int           readGAVarsConfig(ConfigReader* configReader, config_t *cfg);
int           readConfigFile(ConfigReader* configReader, char* configFile);
int           getMaxGeneNumber(ConfigReader* configReader);
int           getNumCarcinogenGenes(ConfigReader* configReader);
int*          getCarcinogenGenes(ConfigReader* configReader);
int           getFeaturesPerChromosome(ConfigReader* configReader);
float         getWeight1(ConfigReader* configReader);
float         getWeight2(ConfigReader* configReader);
int           getPopulationSize(ConfigReader* configReader);
int**         getPopulation(ConfigReader* configReader);
int           getMutationProbability(ConfigReader* configReader);
int           getMaxGenerations(ConfigReader* configReader);
int           getElitism(ConfigReader* configReader);
int           getCrossoversPerGeneration(ConfigReader* configReader);
void          freeConfigReader(ConfigReader* configReader);

#endif
