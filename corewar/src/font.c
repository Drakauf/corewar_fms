/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   font.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/19 10:27:24 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 14:22:46 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		**load_font(void)
{
	int		fd;
	char	pixel;
	int		**font;
	int		p;
	int		f;

	font = (int **)malloc(sizeof(int *) * 256);
	fd = open("fonts.txt", O_RDONLY);
	f = 0;
	while (f < 256)
	{
		font[f] = (int *)malloc(sizeof(int) * 80);
		p = 0;
		while (p < 80)
		{
			read(fd, &pixel, 1);
			font[f][p] = (pixel == 'X');
			p++;
			if (p % CHAR_SX == 0)
				read(fd, &pixel, 1);
		}
		read(fd, &pixel, 1);
		f++;
	}
	return (font);
}
