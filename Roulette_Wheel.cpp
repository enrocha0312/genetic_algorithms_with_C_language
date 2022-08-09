Cromossomo * Selecao(Cromossomo *populacao, int tamanho){
	
	Cromossomo *pais = alocaCromossomo(2); //dois pais
	//const int tamanhoPopulacao = sizeof(populacao)/sizeof(Cromossomo);

	//CALCULAR APTIDÕES DOS CROMOSSOMOS DA POPULAÇÃO
	for(int i = 0; i<tamanho; i++)
	{
		populacao[i].valorAptidao = Sphere(populacao[i].Genes, tamanho);
	}
	//normalizar aptidões
	
	int *aptidaoNormalizada = alocaInteiro(tamanho);
	int *vetorAptidao = alocaInteiro(tamanho);
	for(int i = 0; i<tamanho; i++)
	{
		vetorAptidao[i] = populacao[i].valorAptidao;	
	}
	
	for(int i = 0; i<tamanho; i++)
	{
		aptidaoNormalizada[i] = populacao[i].valorAptidao /	somatorio(vetorAptidao, tamanho);
	}		
	
	free(vetorAptidao);
	
	int *indices = AssociarIndices(aptidaoNormalizada, tamanho);
	
	
	int *aptidaoNormalizadaOrdenada = OrdemDecrescente(aptidaoNormalizada, tamanho);

	
	struct Cromossomo *populacaoTemporaria = alocaCromossomo(tamanho);
	
	for(int i=0; i<tamanho; i++)
	{
		populacaoTemporaria[i].valorAptidao = aptidaoNormalizada[indices[i]];
		populacaoTemporaria[i].numGenes = populacao[i].numGenes;
	}
	//copiar genes
	
	for(int i =0; i<tamanho; i++)
	{
		for(int j=0; j<populacaoTemporaria[i].numGenes; j++)
		{
			populacaoTemporaria[i].Genes[j] = populacao[i].Genes[indices[j]];
		}
	}
	
	int somaAcumulada [tamanho];
	
	for (int i = 0; i<tamanho; i++){
		for(int j=i; j<tamanho; j++){
			somaAcumulada[i] = somaAcumulada[i] + populacaoTemporaria[j].valorAptidao;
		}		
	} //criar vetor de soma cumulativa
	
	int R1 = rand() % 100; // valores entre 0 e 100
	
	int indicePai1, indicePai2;
	
	indicePai1 = tamanho;
	
	for (int i = 0; i<tamanho ; i++){
		if(R1 > somaAcumulada[i]*100){
			indicePai1 = i-1;
			break;
		}
	}
	
	indicePai2 = indicePai1;
	
	while (indicePai2 == indicePai1){
		int R2 = rand() % 100;
		for(int i =0; i<tamanho; i++){
			if (R2>somaAcumulada[i] * 100)
			{
				indicePai2 = i -1;
				break;
			}

		}
	}
	
	pais[0] = populacaoTemporaria[indicePai1];
	pais[1] = populacaoTemporaria[indicePai2];
	
	return pais;
	

	
	return pais;
}

