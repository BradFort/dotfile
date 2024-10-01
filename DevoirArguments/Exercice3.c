#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
 FILE *file;
 char mots;
 
 file = fopen("mon_fichier.txt", "r");

 if(NULL == file)
 {
	 printf("Le fichier ne peux pas s'ouvrir \n");
 }

 while((mots = fgetc(file)) != EOF)
 {
	 fprintf(stdout, "%c", mots);
	 fprintf(stderr,"%c", mots);
 }

 fclose(file);

 return 0;

}
