

#include "ConfigReader.h"

ConfigReader* createConfigReader()
{
  int i, j;
  ConfigReader *configReader = (ConfigReader *)my_malloc(sizeof(ConfigReader));

  //Gene vars
  configReader->maxGeneNumber   = 100;
  configReader->numCarcinogen   = 20;
  configReader->carcinogenGenes = (int *)my_malloc(configReader->numCarcinogen * sizeof(int));
  for (i = 0; i < configReader->numCarcinogen; ++i) {
    configReader->carcinogenGenes[i] = rand() % configReader->maxGeneNumber;
  }

  //Chromosome vars
  configReader->numFeatures = 10;
  configReader->weight1     = 0.65;
  configReader->weight2     = 1 - configReader->weight1;

  //GA vars
  configReader->mutationProb     = 15;
  configReader->maxGenerations   = 100;
  configReader->elitism          = 20;
  configReader->crossoversPerGen = 10;
  configReader->populationSize   = 10;
  configReader->population       = (int **)my_malloc(configReader->populationSize * sizeof(int *));
  for(i = 0; i < configReader->populationSize; ++i)
  {
    configReader->population[i] = (int *)my_malloc(configReader->numFeatures * sizeof(int));
    for (j = 0; j < configReader->numFeatures; ++j)
    {
      configReader->population[i][j] = (10 * i) + j;
    }
  }

  return configReader;
}


int readGeneVarsConfig(ConfigReader* configReader, config_t *cfg)
{
  int i;
  config_setting_t *setting;

  setting = config_lookup(cfg, "GENE_VARS");
  if(setting != NULL)
  {
    if(!(config_setting_lookup_int(setting, "MAX_GENE_NUMBER", &configReader->maxGeneNumber)))
      return CONFIG_ERROR;

    setting = config_setting_get_member(setting, "CARCINOGEN_GENES");
      if(setting != NULL)
      {
        configReader->numCarcinogen = config_setting_length(setting);
        for(i = 0; i < configReader->numCarcinogen; ++i)
        {
          configReader->carcinogenGenes[i] = config_setting_get_int_elem(setting, i);
        }
      }
      else
        return CONFIG_ERROR;
  }
  else
    return CONFIG_ERROR;

  return CONFIG_RIGHT;
}

int readChromosomeVarsConfig(ConfigReader* configReader, config_t *cfg)
{
  config_setting_t *setting;

  setting = config_lookup(cfg, "CHROMOSOME_VARS");
  if(setting != NULL)
  {
    if(!(config_setting_lookup_int(setting, "NUM_FEATURES", &configReader->numFeatures)
         && config_setting_lookup_float(setting, "WEIGHT_1", &configReader->weight1)
         && config_setting_lookup_float(setting, "WEIGHT_2", &configReader->weight2)))
      return CONFIG_ERROR;
  }
  else
    return CONFIG_ERROR;
  return CONFIG_RIGHT;
}

int readGAVarsConfig(ConfigReader* configReader, config_t *cfg)
{
  int i, j, numFeatures;
  config_setting_t *setting, *chromosome;

  setting = config_lookup(cfg, "GA_VARS");
  if(setting != NULL)
  {
    if(!(config_setting_lookup_int(setting, "MUTATION_PROBABILITY", &configReader->mutationProb)
         && config_setting_lookup_int(setting, "MAX_GENERATIONS", &configReader->maxGenerations)
         && config_setting_lookup_int(setting, "ELITISM", &configReader->elitism)
         && config_setting_lookup_int(setting, "CROSSOVERS_PER_GEN", &configReader->crossoversPerGen)))
      return CONFIG_ERROR;

    setting = config_setting_get_member(setting, "POPULATION");
    if(setting != NULL)
    {
      configReader->populationSize = config_setting_length(setting);
      for(i = 0; i < configReader->populationSize; ++i)
      {
        chromosome  = config_setting_get_elem(setting, i);
        numFeatures = config_setting_length(chromosome);
        if(numFeatures != configReader->numFeatures)
          return CONFIG_ERROR;
        for(j = 0; j < numFeatures; ++j)
        {
          configReader->population[i][j] = config_setting_get_int_elem(chromosome, j);
        }
      }
    }
    else
      return CONFIG_ERROR;
  }
  else
    return CONFIG_ERROR;
  return CONFIG_RIGHT;
}

int readConfigFile(ConfigReader* configReader, char* configFile)
{
  config_t cfg;
  const char *str;

  config_init(&cfg);

  /* Read the file. If there is an error, report it and exit. */
  if(! config_read_file(&cfg, configFile))
  {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
            config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
    return CONFIG_ERROR;
  }
  if(readGeneVarsConfig(configReader, &cfg) == CONFIG_ERROR
      || readChromosomeVarsConfig(configReader, &cfg) == CONFIG_ERROR
      || readGAVarsConfig(configReader, &cfg) == CONFIG_ERROR)
  {
   config_destroy(&cfg);
   return CONFIG_ERROR;
  }
  config_destroy(&cfg);
  return CONFIG_RIGHT;
}

int getCRMaxGeneNumber(ConfigReader* configReader)
{
  return configReader->maxGeneNumber;
}

int getCRNumCarcinogenGenes(ConfigReader* configReader)
{
  return configReader->numCarcinogen;
}

int* getCRCarcinogenGenes(ConfigReader* configReader)
{
  return configReader->carcinogenGenes;
}

int getCRFeaturesPerChromosome(ConfigReader* configReader)
{
  return configReader->numFeatures;
}

float getCRWeight1(ConfigReader* configReader)
{
  return (float)configReader->weight1;
}

float getCRWeight2(ConfigReader* configReader)
{
  return (float)configReader->weight2;
}

int getCRPopulationSize(ConfigReader* configReader)
{
  return configReader->populationSize;
}

int** getCRPopulation(ConfigReader* configReader)
{
  return configReader->population;
}

int getCRMutationProbability(ConfigReader* configReader)
{
  return configReader->mutationProb;
}

int getCRMaxGenerations(ConfigReader* configReader)
{
  return configReader->maxGenerations;
}

int getCRElitism(ConfigReader* configReader)
{
  return configReader->elitism;
}

int getCRCrossoversPerGeneration(ConfigReader* configReader)
{
  return configReader->crossoversPerGen;
}

void freeConfigReader(ConfigReader* configReader)
{
  int i;

  free(configReader->carcinogenGenes);
  for (i = 0; i < configReader->populationSize; ++i) {
    free(configReader->population[i]);
  }
  free(configReader->population);

}
