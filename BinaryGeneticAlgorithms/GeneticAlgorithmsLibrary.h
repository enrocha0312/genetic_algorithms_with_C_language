#pragma once


struct Chromosome{
	int numGenes;
	int *Genes;
	int fitnessValue;
};

int * intAlloc (int size)
{
    int *aux = NULL;
    aux =(int *) malloc(size*sizeof(int));   
    return aux;
}

Chromosome * chromosomeAlloc(int size)
{
	Chromossome *auxiliar = NULL;
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
				temp = copy[i];
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
	for (int m = 0; m<size; m++ )
	{
		for(int n=0; n<size; n++)
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

Chromosome initializePopulation(int m, int n){
	// m = number of Chromosomes
	// n = number of Genes
	struct Chromosome *population = chromosomeAlloc(m);
	srand(time(NULL));
			
	for (int i =0; i<m; i++){
		population[i].Genes =  intAlloc(n);
		population[i].numGenes = n;
		for (int j=0; j<n; j++){
		population[i].Genes[j] = randomRange(0,2);
		}
	}
	return population;
}

//Just a Fitness Function for example
int Sphere(int v[], int size){
	// the user can use/create another
	for(int i = 0; i<size; i++){
		v[i] = v[i] * v[i];
	}
	int sum = 0;
	for(int i = 0; i<size; i++){
		sum += vetor[i];
	}
	return sum;
}

//ROULETTE WHEEL METHOD
Chromosome * Selection(Chromosome *population, int size){
	
	Chromosome *parents = chromosomeAlloc(2); //two parents
	//CALCULATE THE FITNESS OF THE CHROMOSOMES OF THE POPULATION
	for(int i = 0; i<size; i++)
	{
		population[i].fitnessValue = Sphere(population[i].Genes, size);
	}
	//NORMALIZE THE FITNESS VALUES
	
	int *normalizedFitness = intAlloc(size);
	int *fitnessVector = intAlloc(size);
	for(int i = 0; i<size; i++)
	{
		fitnessVector[i] = population[i].fitnessValue;	
	}
	
	for(int i = 0; i<size; i++)
	{
		normalizedFitness[i] = population[i].fitnessValue /	sumOfVector(fitnessVector, size);
	}		
	
	free(fitnesVector);
	
	int *indexes = indexAssociate(normalizedFitness);
	
	
	int *orderedNormalizedFitness = descendingOrder(normalizedFitness, size);

	
	struct Chromosome *tempPopulation = chromosomeAlloc(size);//TEMPORARY POPULATION
	//FOR OPERATIONS
	
	for(int i=0; i<size; i++)
	{
		tempPopulation[i].fitnessValue = normalizedFitness[indexes[i]];
		tempPopulation[i].numGenes = population[i].numGenes;
	}
	
	//COPY GENES
	
	for(int i =0; i<size; i++)
	{
		for(int j=0; j<tempPopulation[i].numGenes; j++)
		{
			tempPopulation[i].Genes[j] = population[i].Genes[indexes[j]];
		}
	}
	// NOTE THAT THE TEMPPOPULATION IS DESCENDING ORDERED
	
	int cumSum [size];
	
	for (int i = 0; i<size; i++){
		for(int j=i; j<size; j++){
			cumSum[i] = cumSum[i] + tempPopulation[j].fitnessValue;
		}		
	} //LOOP WHICH CREATES A VECTOR OF CUMULATIVE SUM
	
	int R1 = rand() % 100; // values between 0 and 100
	
	int indexParent1, indexParent2;
	
	indexParent1 = size;//just setting a value
	
	for (int i = 0; i<size ; i++){
		if(R1 > cumSum[i]*100){
			indexParent1 = i-1;//the position lower than the position of cumulative sum
			break;
		}
	}
	
	indexParent2 = indexParent1; //by fixing that, we will never have the same value for both
	
	while (indexParent2 == indexParent1){
		int R2 = rand() % 100;
		for(int i =0; i<size; i++){
			if (R2>cumSum[i] * 100)
			{
				indexParent2 = i -1;
				break;
			}

		}
	}
	
	parents[0] = tempPopulation[indexParent1];
	parents[1] = tempPopulation[indexParent2];
	
	return parents;
}

Chromosome Mutation (Chromosome x, int Pm){
	//PM = Mutation Rate(between 0 and 100)
	srand(time(NULL));	
	for(int i =0; i<x.numGenes; i++){
		int R = rand() % 100; // values between 0 and 100
		if (R<Pm){
			x.Genes[i] = ~x.Genes[i]; // changes bit;
		}
	}
	return x;
}



Chromosome * Crossover(Chromosome *parents, int Pc, char crossoverType[]){
	
	struct Chromosome *children = NULL;
	//initialize the children
	for(int i = 0; i<2 ; i++){
		children[i].Genes = alocaInteiro(parents[i].numGenes);
		children[i].numGenes = parents[i].numGenes;		
	}
	
		
	if(crossoverType == "single")
	{
			int upperLimit = parents[0].numGenes -1;
			int lowerLimit = 0;
			srand(time(NULL));
			int Cross_P = randomRange(lowerLimit, upperLimit);
			
			//copy the part 1 to the child vector (the parent until the crossover point)
			for(int i = 0; i < Cross_P; i++){
				children[0].Genes[i] = parents[0].Genes[i];
			}
			//copy the part 2 to the child vector (the second parent until the end)
			for(int j = 0; j<parents[0].numGenes - Cross_P; j++){
				children[0].Genes[Cross_P + j] = parents[1].Genes[Cross_P +j];
			}
			// Agora o mesmo processo com o filho 2, porém obviamente trocando os parents
			for(int i = 0; i < Cross_P; i++){
				children[1].Genes[i] = parents[1].Genes[i];
			}
			// copia parte 2 para o vetor filho (o segundo pai do crossover até o fim)
			for(int j = 0; j<parents[1].numGenes - Cross_P; j++){
				children[1].Genes[Cross_P + j] = parents[0].Genes[Cross_P +j];
			}
	}
		
	if(crossoverType == "double")
	{
			int upperLimit = parents[0].numGenes -1;
			int lowerLimit = 1;
			srand(time(NULL));
			int Cross_P1 = randomRange(lowerLimit, upperLimit);
			int Cross_P2 = Cross_P1;
			while(Cross_P2 == Cross_P1)
			{
				Cross_P2 = randomRange(lowerLimit, upperLimit); // garantir que o ponto de crossover nao seja igual
			}
			// usar if para garantir que cross_p1<cross_p2
			if(Cross_P2 < Cross_P1)
			{
				int temp = Cross_P1;
				Cross_P1 = Cross_P2;
				Cross_P2 = temp;
			}
			//copia o pai 1 até Cross_P1 ao filho 1
			for(int i = 0; i < Cross_P1; i++){
				children[0].Genes[i] = parents[0].Genes[i];
			}
			// copia o pai 2 entre Cross_P1 e Cross_P2
			for(int j = 0; j<(Cross_P2 - Cross_P1); j++){
				children[0].Genes[Cross_P1 + j] = parents[1].Genes[Cross_P1 +j];
			}
			// copia o pa1 a partir de Cross_p2
			for(int k = 0; k<parents[0].numGenes -  Cross_P2; k++){
				children[0].Genes[Cross_P2 + k] = parents[0].Genes[Cross_P2 +k];
			}
			//Filho 2
			for(int i = 0; i < Cross_P1; i++){
				children[1].Genes[i] = parents[1].Genes[i];
			}
			// copia o pai 2 entre Cross_P1 e Cross_P2
			for(int j = 0; j<(Cross_P2 - Cross_P1); j++){
				children[1].Genes[Cross_P1 + j] = parents[0].Genes[Cross_P1 +j];
			}
			// copia o pa1 a partir de Cross_p2
			for(int k = 0; k<parents[1].numGenes -  Cross_P2; k++){
				children[1].Genes[Cross_P2 + k] = parents[1].Genes[Cross_P2 +k];
			}
	}
	
	return children;
}
