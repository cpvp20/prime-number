#include <stdio.h>
#include <stdlib.h>

unsigned int * initializePrimes();
unsigned int getPrime(int k, unsigned int ** primes, int * n);

int main(){
	setbuf(stdout, 0);
	unsigned int * primes = initializePrimes();
	int k, n=1;
	scanf("%d", &k);
	while (k != -1)
	{
		unsigned int primoK= getPrime(k, &primes, &n);
		if (primoK==0) return -1;
		else printf("%d\n", getPrime(k, &primes, &n));
		scanf("%d", &k);
	}
	free(primes);
	return 0;
}

unsigned int * initializePrimes(){//devolver la dirección de un arreglo de tamaño 1 cuyo único elemento debe valer 2
	unsigned int* primes = (unsigned int*) malloc(sizeof(int));
	if(primes == NULL)
	{
		printf("Error");
		free(primes);
		return 0;
	}
	*primes=2;//primes[0]=2;
	return primes;//puntero que apunta al arreglo
}

unsigned int getPrime(int k, unsigned int ** primes, int * n)
{
	if (k < (*n)) return (*primes)[k];

	unsigned int * tempPointer = (unsigned int *) realloc(*primes, (1+k) * sizeof(int));//puntero auxiliar que apunta a algun bloque nuevo del tamano de primes pero crecido en uno

	if(tempPointer == NULL)//check
	{
		printf("Error");
		free (*primes);
		return 0;
	}
	else *primes = tempPointer;//hacer que primes tambien apunte a este nuevo bloque crecido

	unsigned int candidate;
	int isPrime = 1;//bandera
	for (int j = (*n); j <= k; j++)//calcular todos los primos que no esten ya en la lista hasta el kaeano
	{
		candidate = (*primes)[j-1] + 1;
		do//test para asegurar que el candidato sea primo
		{
			for (int i = 0; ((*primes)[i]) * ((*primes)[i]) <= candidate; i++)//recorre sólo los primos cuyo cuadrado NO sea mayor que el candidato
			{
				isPrime = 1;
				if (candidate % ((*primes)[i]) == 0)
				{
					isPrime = 0;
					candidate += 1;
					break;
				}
			}
		}while (!isPrime);

		(*primes)[j] = candidate;//agregarle el candidato (ya primo for sure) al ultimo elemento de la lista
		(*n)++;//reflejar este crecimiento en la varibale que almacena el tamano del arreglo

	}//ya calculo el k-aeano primo asi como los anteriores

	return (*primes)[k];
}
