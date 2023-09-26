#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LGMAX 500
#define NRSEP 30

int main()
{
	FILE *fin = fopen("text.in", "r");

	if (!fin)
	{
		printf("Eroare fisier text.in\n");
		return 1;
	}

	size_t lgmax;
	char *prop, *tmp, *propmax, *sep;
	
	lgmax = LGMAX + 1;

	prop = (char*)malloc(lgmax);
	tmp = (char*)malloc(lgmax);
	propmax = (char*)malloc(lgmax);
	sep = (char*)malloc(NRSEP+1);

	if (!prop)
	{
		printf("Eroare alocare memorie *prop\n");
		return 2;
	}

	if (!propmax)
	{
		printf("Eroare alocare memorie *propmax\n");
		return 3;
	}

	if (!tmp)
	{
		printf("Eroare alocare memorie *tmp\n");
		return 4;
	}


	if (!sep)
	{
		printf("Eroare alocare memorie *sep\n");
		return 5;
	}

	strcpy(sep, " ,!@#$%^&*()-=+_`~/\\'\"");

	char *ptr;
	unsigned nrcuv, nrmax = 0;
	ssize_t lgp, lgpmax;

	do
	{
		lgp = getdelim(&prop, &lgmax, '.', fin);

		if (lgp > 1)		
		{
			strcpy(tmp, prop);

			for (nrcuv = 0, ptr = strtok(tmp, sep);
					ptr;
					nrcuv++, ptr = strtok(NULL, sep));

			if (nrcuv > nrmax)
			{
				nrmax = nrcuv, lgpmax = lgp;

				strcpy(propmax, prop);
			}
			else if (nrcuv == nrmax)
			{
				if (strcmp(prop, propmax) < 0)
				{
					lgpmax = lgp;

					strcpy(propmax, prop);
				}
			}
		}
	}
	while (lgp > 0);	

	FILE *fout = fopen("text.out", "w");
	
	fprintf(fout, "%s", propmax);	

	fclose(fin);
	fclose(fout);

	free(prop);
	free(sep);
	free(propmax);
	free(tmp);

	return 0;
}
