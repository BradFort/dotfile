#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *tab;
	int loop;

	tab = (int*)malloc(5 * sizeof(int));

        tab[0] = 0;
	tab[1] = 1;
	tab[2] = 2;
	tab[3] = 3;
	tab[4] = 4;

	for(loop = 0; loop < 5; loop++)
	    printf("%d", tab[loop]);


	if (tab == NULL)
	{
		printf("Echec de l'allocation de memoire.\n");
		exit(1);
	}
	

	free(tab);
	return 0;
}
