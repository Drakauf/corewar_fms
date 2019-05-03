/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_label.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 20:13:39 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/03 19:02:50 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int		strlen_sp(const char *s)
{
	const char	*start = s;

	while (ft_isalnum(*s) || *s == '_')
		s++;
	return (s - start);
}

extern int		is_label(const char *s, t_vector *label, t_data *d)
{
	int		i;
	int		splen;
	t_label	**lab;

	i = 0;
	lab = (t_label**)label->tab;
	if (d->syntax == DFLT)
		s++;
	splen = strlen_sp(s);
	while (i < label->len)
	{
		if (splen == lab[i]->len &&
			ft_strncmp(lab[i]->name, s, splen) == 0)
		{
			return (lab[i]->len + (d->syntax == DFLT));
		}
		i++;
	}
	return (0);
}

extern int		get_label_addr(const char *s, t_vector *label, t_data *d)
{
	int		i;
	int		splen;
	t_label	**lab;

	i = 0;
	lab = (t_label**)label->tab;
	if (d->syntax == DFLT)
		s++;
	splen = strlen_sp(s);
	while (i < label->len)
	{
		if (splen == lab[i]->len &&
			ft_strncmp(lab[i]->name, s, splen) == 0)
		{
			return (lab[i]->addr);
		}
		i++;
	}
	return (-1);
}
