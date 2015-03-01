
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
  double weight1;
  double weight2;

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
int           getCRMaxGeneNumber(ConfigReader* configReader);
int           getCRNumCarcinogenGenes(ConfigReader* configReader);
int*          getCRCarcinogenGenes(ConfigReader* configReader);
int           getCRFeaturesPerChromosome(ConfigReader* configReader);
float         getCRWeight1(ConfigReader* configReader);
float         getCRWeight2(ConfigReader* configReader);
int           getCRPopulationSize(ConfigReader* configReader);
int**         getCRPopulation(ConfigReader* configReader);
int           getCRMutationProbability(ConfigReader* configReader);
int           getCRMaxGenerations(ConfigReader* configReader);
int           getCRElitism(ConfigReader* configReader);
int           getCRCrossoversPerGeneration(ConfigReader* configReader);
void          freeConfigReader(ConfigReader* configReader);

#endif
