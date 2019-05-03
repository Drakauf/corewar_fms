/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   graph_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 16:26:39 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 17:05:06 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void	draw_line(struct s_pos s, struct s_pos e, int col, struct s_vdata *data)
{
	double	dx;
	double	dy;
	int		size;
	int		i;

	size = (int)hypot(e.x - s.x, e.y - s.y) + 1;
	dx = (e.x - s.x) / (double)size;
	dy = (e.y - s.y) / (double)size;
	i = 0;
	while (i <= size)
	{
		e.x = s.x + (dx * (double)i + 0.5);
		e.y = s.y + (dy * (double)i + 0.5);
		data->px[e.x + e.y * data->sx] = col;
		i++;
	}
}

int		draw_char(unsigned char c, struct s_pos p, int co, struct s_vdata *data)
{
	int		ix;
	int		iy;

	ix = 0;
	while (ix < 8 && ix + p.x < data->sx - 7)
	{
		iy = 0;
		while (iy < 10)
		{
			data->px[p.x + ix + (p.y + iy) * data->sx] =
				data->font[c][ix + iy * 8] * co;
			iy++;
		}
		ix++;
	}
	return (ix + 2);
}

int		draw_str(char *str, struct s_pos p, int color, struct s_vdata *data)
{
	int		i;
	int		x;

	i = 0;
	x = p.x;
	while (str[i])
	{
		p.x += draw_char(str[i], p, color, data);
		i++;
	}
	return (p.x - x);
}

int		draw_score(struct s_pos p, int value, int color, struct s_vdata *data)
{
	return (draw_str(ft_itoa(value), p, color, data));
}
