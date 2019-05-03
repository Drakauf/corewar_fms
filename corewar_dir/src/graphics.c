/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   graphics.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 13:45:44 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 11:58:56 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"
#include <math.h>

const int	g_color[2 * MAX_PLAYERS + 2] = {
	COLOR_NONE, COLOR_ORANGE, COLOR_GREEN, COLOR_CYAN, COLOR_RED,
	COLOR_LNONE, COLOR_LORANGE, COLOR_LGREEN, COLOR_LCYAN, COLOR_LRED
};

void		cw_init_window(struct s_vdata *data)
{
	int		t;

	data->tbx = 1810;
	data->sx = 2456;
	data->sy = 1164;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		exit((ft_printf("SDL_Init Error: %s\n", SDL_GetError()) | 1) & 1);
	if (!(data->win = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, data->sx, data->sy, 0)))
		exit((ft_printf("SDL_Window Error: %s\n", SDL_GetError()) | 1) & 1);
	if (!(data->rd = SDL_CreateRenderer(data->win, -1, 0)))
		exit((ft_printf("SDL_Renderer Error: %s\n", SDL_GetError()) | 1) & 1);
	if (!(data->tx = SDL_CreateTexture(data->rd, SDL_PIXELFORMAT_ARGB32,
		SDL_TEXTUREACCESS_STREAMING, data->sx, data->sy)))
		exit((ft_printf("SDL_Texture Error: %s\n", SDL_GetError()) | 1) & 1);
	t = SDL_SetRenderTarget(data->rd, data->tx);
	if (SDL_LockTexture(data->tx, NULL, (void **)&data->px, &data->pitch) != 0)
		exit((ft_printf("SDL_Lock Error: %s\n", SDL_GetError()) | 1) & 1);
	ft_memset(data->px, '\0', data->sy * data->pitch);
	data->font = load_font();
	SDL_UnlockTexture(data->tx);
	SDL_RenderCopy(data->rd, data->tx, NULL, NULL);
	SDL_RenderPresent(data->rd);
}

static int	living_count(struct s_proc *p, int pnum, struct s_vm *vm)
{
	int		i;

	i = 0;
	while (p)
	{
		i += (p->number == pnum && (vm->zcycles - p->lives < vm->kcycles));
		p = p->next;
	}
	return (i);
}

static int	process_count(struct s_proc *p, int pnum)
{
	int		i;

	i = 0;
	while (p)
	{
		i += (p->number == pnum);
		p = p->next;
	}
	return (i);
}

int			draw_process_count(struct s_vdata *data, struct s_vm *vm, int y)
{
	int				pl;
	int				c;
	int				d;
	int				x;

	pl = 0;
	while (pl < vm->players)
	{
		x = data->tbx + draw_str("Processes: ", (struct s_pos){data->tbx, y},
			g_color[pl + MAX_PLAYERS + 2], data);
		c = process_count(vm->processes, pl + 1);
		d = living_count(vm->processes, pl + 1, vm);
		x += draw_score((struct s_pos){x, y}, c,
			g_color[pl + MAX_PLAYERS + 2], data);
		x += draw_str(" (", (struct s_pos){x, y},
			g_color[pl + MAX_PLAYERS + 2], data);
		x += draw_score((struct s_pos){x, y}, d,
			g_color[pl + MAX_PLAYERS + 2], data);
		draw_str(" alive)", (struct s_pos){x, y},
			g_color[pl + MAX_PLAYERS + 2], data);
		y += 18;
		pl++;
	}
	y += 8;
	return (y);
}

void		cw_update_window(struct s_vm *vm, struct s_vdata *data,
		int last_frame)
{
	SDL_PollEvent(&(data->ev));
	if ((data->ev.type == SDL_KEYDOWN && data->ev.key.keysym.sym == SDLK_ESCAPE)
		|| data->ev.type == SDL_QUIT)
		exit(0);
	if (data->ev.type == SDL_KEYDOWN && data->ev.key.keysym.sym == SDLK_SPACE)
	{
		SDL_WaitEvent(&(data->ev));
		while (data->ev.type != SDL_KEYDOWN ||
				data->ev.key.keysym.sym != SDLK_SPACE)
		{
			if ((data->ev.type == SDL_KEYDOWN && data->ev.key.keysym.sym
				== SDLK_ESCAPE) || data->ev.type == SDL_QUIT)
				exit(0);
			SDL_WaitEvent(&(data->ev));
		}
	}
	if (SDL_LockTexture(data->tx, NULL, (void **)&data->px, &data->pitch) != 0)
		exit((ft_printf("SDL_Lock Error: %s\n", SDL_GetError()) | 1) & 1);
	generate_borders(data);
	generate_arena(data, vm);
	generate_processes(data, vm->processes, 0, 0);
	generate_toolbar(data, vm, last_frame);
	SDL_UnlockTexture(data->tx);
	SDL_RenderCopy(data->rd, data->tx, NULL, NULL);
	SDL_RenderPresent(data->rd);
}
