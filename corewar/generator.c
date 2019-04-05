/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   generator.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 10:58:15 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 14:28:06 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define PATH "/Users/mhouppin/Documents/Ongoing_projects/corewar_fms"

char	*add_instruction(FILE *f)
{
	static const char	*appends[3] = {"r", "%", ""};
	static const int	modulos[3] = {16, 16777216, 8192};
	static const int	adds[3] = {1, -8388608, -4096};
	static int			ln = 0;
	int		i;
	int		p1, p2, p3;
	int		t1, t2, t3;
	char	*str;

	i = rand() % 100;
	t1 = rand();
	t2 = rand();
	t3 = rand();
	p1 = rand();
	p2 = rand();
	p3 = rand();
	if (i < 8)
	{
		ln++;
		asprintf(&str, "live_%d:\nlive\t%%%d\n", ln, rand());
	}
	if (i >= 8 && i < 17)
	{
		t1 = t1 % 2 + 1;
		p1 = (p1 % modulos[t1]) + adds[t1];
		p2 = (p2 % 16) + 1;
		asprintf(&str, "ld\t%s%d, r%d\n", appends[t1], p1, p2);
	}
	if (i >= 17 && i < 26)
	{
		t2 = (t2 % 2) * 2;
		p2 = (p2 % modulos[t2]) + adds[t2];
		p1 = (p1 % 16) + 1;
		asprintf(&str, "st\tr%d, %s%d\n", p1, appends[t2], p2);
	}
	if (i >= 26 && i < 35)
	{
		p1 = (p1 % 16) + 1;
		p2 = (p2 % 16) + 1;
		p3 = (p3 % 16) + 1;
		asprintf(&str, "add\tr%d, r%d, r%d\n", p1, p2, p3);
	}
	if (i >= 35 && i < 44)
	{
		p1 = (p1 % 16) + 1;
		p2 = (p2 % 16) + 1;
		p3 = (p3 % 16) + 1;
		asprintf(&str, "sub\tr%d, r%d, r%d\n", p1, p2, p3);
	}
	if (i >= 44 && i < 51)
	{
		t1 %= 3;
		t2 %= 3;
		p1 = (p1 % modulos[t1]) + adds[t1];
		p2 = (p2 % modulos[t2]) + adds[t2];
		p3 = (p3 % 16) + 1;
		asprintf(&str, "and\t%s%d, %s%d, r%d\n", appends[t1], p1, appends[t2], p2, p3);
	}
	if (i >= 51 && i < 58)
	{
		t1 %= 3;
		t2 %= 3;
		p1 = (p1 % modulos[t1]) + adds[t1];
		p2 = (p2 % modulos[t2]) + adds[t2];
		p3 = (p3 % 16) + 1;
		asprintf(&str, "or\t%s%d, %s%d, r%d\n", appends[t1], p1, appends[t2], p2, p3);
	}
	if (i >= 58 && i < 65)
	{
		t1 %= 3;
		t2 %= 3;
		p1 = (p1 % modulos[t1]) + adds[t1];
		p2 = (p2 % modulos[t2]) + adds[t2];
		p3 = (p3 % 16) + 1;
		asprintf(&str, "xor\t%s%d, %s%d, r%d\n", appends[t1], p1, appends[t2], p2, p3);
	}
	if (i >= 65 && i < 72)
	{
		p1 = (p1 % 8192) - 4096;
		asprintf(&str, "zjmp\t%%%d\n", p1);
	}
	if (i >= 72 && i < 78)
	{
		t1 %= 3;
		t2 %= 2;
		p1 = (p1 % modulos[t1]) + adds[t1];
		p2 = (p2 % modulos[t2]) + adds[t2];
		p3 = (p3 % 16) + 1;
		asprintf(&str, "ldi\t%s%d, %s%d, r%d\n", appends[t1], p1, appends[t2], p2, p3);
	}
	if (i >= 78 && i < 84)
	{
		t2 %= 3;
		t3 %= 2;
		p2 = (p2 % modulos[t2]) + adds[t2];
		p3 = (p3 % modulos[t3]) + adds[t3];
		p1 = (p1 % 16) + 1;
		asprintf(&str, "sti\tr%d, %s%d, %s%d\n", p1, appends[t2], p2, appends[t3], p3);
	}
	if (i >= 84 && i < 89)
	{
		p1 = (p1 % 8192) - 4096;
		asprintf(&str, "fork\t%%%d\n", p1);
	}
	if (i >= 89 && i < 96)
	{
		t1 = t1 % 2 + 1;
		p1 = (p1 % modulos[t1]) + adds[t1];
		p2 = (p2 % 16) + 1;
		asprintf(&str, "lld\t%s%d, r%d\n", appends[t1], p1, p2);
	}
	if (i >= 96)
	{
		t1 %= 3;
		t2 %= 2;
		p1 = (p1 % modulos[t1]) + adds[t1];
		p2 = (p2 % modulos[t2]) + adds[t2];
		p3 = (p3 % 16) + 1;
		asprintf(&str, "lldi\t%s%d, %s%d, r%d\n", appends[t1], p1, appends[t2], p2, p3);
	}
	return (str);
}

int		main(void)
{
	char	*line = NULL;
	size_t	size = 0;
	FILE	*f;
	int		i;
	int		l;
	int		j;
	int		k;
	char	*tab[80];

	srand(time(NULL));
	i = 0;
	j = 0;
	do
	{
		fprintf(stdout, "Attempt %d...\n", ++j);
		usleep(10000);
		f = fopen("random.s", "w+");
		fprintf(f, ".name \"Random\"\n");
		fprintf(f, ".comment \"srand(time(NULL))\"\n\n");
		for (i = 0; i < 80; ++i)
			tab[i] = add_instruction(f);
		for (i = 0; i < 80; ++i)
			if (!memcmp(tab[i], "live_", 5))
			{
				sscanf(tab[i], "live_%d", &k);
				fprintf(f, "sti\tr1, %%:live_%d, %%1\n", k);
			}
		for (i = 0; i < 80; ++i)
		{
			fprintf(f, "%s", tab[i]);
			free(tab[i]);
		}
		fclose(f);
		system(PATH "/asm/asm random.s");
		system(PATH "/corewar/corewar " PATH "/cores/jumper.cor random.cor > log");
		f = fopen("log", "r");
		getline(&line, &size, f);
		getline(&line, &size, f);
		getline(&line, &size, f);
		i = 0;
		fscanf(f, "Contestant %d", &i);
		fclose(f);
		system(PATH "/corewar/corewar " PATH "/cores/fluttershy.cor random.cor > log");
		f = fopen("log", "r");
		getline(&line, &size, f);
		getline(&line, &size, f);
		getline(&line, &size, f);
		l = 0;
		fscanf(f, "Contestant %d", &l);
		fclose(f);
	} while (i != 2 || l != 2);
}
