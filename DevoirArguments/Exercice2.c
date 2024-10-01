#include <stdio.h>
#include <stdlib.h>

int main()
{
   char variable[50];
   printf("Veuillez entrer une variable d'environnement:");
   scanf("%s",variable);
   char *path = getenv(variable);

  if(path != NULL)
  {
	  printf("Voici la valeur : %s/n", path);
  } 
  
  else
  {
   printf("Ceci n'est pas une variable d'environnement");
  }

  return 0;  
}
