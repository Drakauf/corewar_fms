/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   graph_toolbar.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 12:42:14 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 17:08:50 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

static void	draw_ply_name(struct s_vdata *data, struct s_vm *vm, int ply, int y)
{
	register int	color;
	struct s_pos	p;

	color = g_color[ply + 1];
	p.x = data->tbx;
	p.y = y;
	p.x += draw_str(vm->headers[ply].prog_name, p, color, data);
	p.x += 4;
	p.x += draw_char('(', p, color, data);
	p.x += draw_str(vm->headers[ply].comment, p, color, data);
	p.x += draw_char(')', p, color, data);
}

static int	draw_ply_scores(struct s_vdata *data, struct s_vm *vm, int y)
{
	int		player;
	int		x;

	player = 0;
	while (player < vm->players)
	{
		draw_ply_name(data, vm, player, y);
		y += 18;
		x = 0;
		while (x < 300)
		{
			draw_line((struct s_pos){x + data->tbx, y},
					(struct s_pos){x + data->tbx, y + 10 - 1},
					(vm->llives[player] > vm->tcycles * x / 300) ?
					g_color[player + 1] : COLOR_NONE, data);
			x++;
		}
		draw_score((struct s_pos){data->tbx + 312, y}, vm->llives[player],
				g_color[player + 2 + MAX_PLAYERS], data);
		y += 18;
		player++;
	}
	return (y + 20);
}

static int	draw_kill_time(struct s_vdata *data, struct s_vm *vm, int y)
{
	struct s_pos	p;
	struct s_pos	q;

	p.x = data->tbx;
	p.y = y;
	p.x += draw_str("Next kill operation: ", p, COLOR_WHITE, data);
	p.x += draw_str("(Cycle To Die ", p, COLOR_LNONE, data);
	p.x += draw_score(p, vm->kcycles, COLOR_LNONE, data);
	draw_char(')', p, COLOR_LNONE, data);
	p.x = data->tbx;
	q.x = data->tbx;
	p.y += 18;
	q.y = p.y + 9;
	while (p.x < data->tbx + 256)
	{
		draw_line(p, q, (vm->cycles * 256 / vm->kcycles > p.x - data->tbx) ?
				(16776960 - (p.x - data->tbx) * 65536) : COLOR_NONE, data);
		p.x++;
		q.x++;
	}
	p.x = data->tbx + 268;
	p.x += draw_score(p, vm->kcycles - vm->cycles, COLOR_WHITE, data);
	draw_str(" cycles", p, COLOR_WHITE, data);
	return (p.y + 26);
}

static void	display_winner(struct s_vdata *data, struct s_vm *vm, int y,
		int winner)
{
	register int	x;

	x = draw_str("Winner: ", (struct s_pos){data->tbx, y}, COLOR_WHITE, data);
	draw_str(vm->headers[winner - 1].prog_name,
		(struct s_pos){x + data->tbx, y}, g_color[winner], data);
	y += 36;
	draw_str("Press any touch to continue...", (struct s_pos){data->tbx, y},
		COLOR_LNONE, data);
}

void		generate_toolbar(struct s_vdata *data, struct s_vm *vm,
		int last_frame)
{
	int		y;
	int		x;

	draw_str("Corewar - version 2.10", (struct s_pos){data->tbx, 10},
			COLOR_WHITE, data);
	y = draw_ply_scores(data, vm, 46);
	y = draw_kill_time(data, vm, y);
	y = draw_process_count(data, vm, y);
	if (last_frame)
		display_winner(data, vm, y, last_frame);
	else
	{
		x = data->tbx;
		x += draw_score((struct s_pos){x, y}, vm->lives, COLOR_WHITE, data);
		draw_str(" lives executed", (struct s_pos){x, y}, COLOR_WHITE, data);
	}
}
