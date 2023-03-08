#pragma once


struct Chromosome{
	int numGenes;
	int *Genes;
	int fitnessValue;
};

int * intAlloc (int size)
{
    int *aux;
    aux =(int *) malloc(size*sizeof(int));   
    return aux;
}

Cromossomo * chromossomeAlloc(int size)
{
	Chromossome *auxiliar;
    auxiliar =(Chromossome *) malloc(size*sizeof(Chromosome));
    return auxiliar;
}

