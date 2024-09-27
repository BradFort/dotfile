#include <stdio.h>
#include <stdlib.h>

int* Espace(int valeur);

int main()
{
  int valeur = 5;
  int *tab = Espace(valeur);

   printf("Reponse", (void*)tab);

  return 0;  
}

int* Espace(int valeur)
{
        int* tab = (int*)malloc(valeur * sizeof(int));

	return tab;
}

