/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_cooldowns.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 13:52:12 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 14:13:05 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

int		do_aff(unsigned char c, struct s_proc *p)
{
	(void)c;
	p->cooldown = 2;
	return (1);
}

int		do_live_or_pc(unsigned char c, struct s_proc *p)
{
	if (c == 1)
		p->cooldown = 10;
	else if (c == 9)
		p->cooldown = 20;
	else if (c == 12)
		p->cooldown = 800;
	else
		p->cooldown = 1000;
	return (1);
}

int		do_operation(unsigned char c, struct s_proc *p)
{
	if (c == 4 || c == 5)
		p->cooldown = 10;
	else
		p->cooldown = 6;
	return (1);
}

int		do_load(unsigned char c, struct s_proc *p)
{
	if (c == 2 || c == 3)
		p->cooldown = 5;
	else if (c == 10 || c == 11)
		p->cooldown = 25;
	else if (c == 13)
		p->cooldown = 10;
	else
		p->cooldown = 50;
	return (1);
}
