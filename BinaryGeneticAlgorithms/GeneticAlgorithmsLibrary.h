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

int * indexAssociate(int binaryVector[])
{
	int size = sizeof(binaryVector)/sizeof(int);
	int *indexes = intAlloc(size);
	int auxVector [size];
	
	for(int k=0; k<size; k++)
	{
		auxVector[k] = binaryVector[k];	
	}
	int temp;
	for (int i =0; i<size; ++i){
		for(int j=  i+1; j<size; ++j){
			if(auxVector[i]<auxVector[j]){
				temp = auxVector[i];
				auxVector[i]= auxVector[j];
				auxVector[j]= temp;
			}
		}
	}	
	for (int m = 0; m<tam; m++ )
	{
		for(int n=0; n<tam; n++)
		{
			if (auxVector[m] == binaryVector[n])
			{
				indexes[m] = n;
				break;
			}
		}
	}
	return indexes;
}

