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

int * descendingOrder(int v [], int n)
{
	int copy[n];
	for (int i=0; i<n; i++)
	{
		copy[i]=v[i];
	}	
	int i, j, temp;
	for (i=0; i<n; ++i){
		for(j=  i+1; j<n; ++j){
			if(copy[i]<copy[j]){
				temp = copia[i];
				copy[i]= copy[j];
				copy[j]= temp;
					
			}
		}
	}
	int *ret;
	ret = copy;
	return ret;
}

int sumOfVector(int v[]){
	int sum = 0;
	int size = sizeof(v)/sizeof(int)
	for(int i = 0; i<size; i++){
		sum += vetor[i];
	}
	return sum;
}

int randomRange(int min, int max)
{
    return ( rand() % ( max - min ) ) + min;
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

