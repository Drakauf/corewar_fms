/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   general_parser.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 11:01:06 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 18:53:02 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static char		*get_label(char *s, t_data *d)
{
	char		*start;
	t_label		*new;

	start = s;
	while (is_not_space_or_label_end(*s, d))
		s++;
	if (*s == ':' && s - start > 0)
	{
		new = malloc(sizeof(t_label));
		new->len = s - start;
		new->name = ft_strndup(start, new->len);
		new->addr = 0;
		if (!is_valid_label(new->name, d))
		{
			free(new->name);
			free(new);
		}
		else
			d->label->push_back(d->label, (t_all)new);
	}
	return (skip_all_but('\n', s));
}

static void		get_labels(t_data *d)
{
	char	*s;

	s = d->file;
	while (*s)
	{
		if (is_comment(d, *s))
			s = skip_all_but('\n', s);
		else if (*s == '\t' || *s == ' ')
			s = skip_spaces(s, &d->p);
		else if (*s == '\n')
			s = skip_new_lines(s, d);
		else
			s = get_label(s, d);
	}
}

static void		parse_code(t_data *d, t_synt_tree **tree)
{
	char	*s;
	char	*end;

	s = d->file;
	end = s + d->file_len;
	while (s < end)
	{
		if (is_comment(d, *s))
			s = skip_all_but('\n', s);
		else if (*s == '\t' || *s == ' ')
			s = skip_spaces(s, &d->p);
		else if (*s == '\n')
			s = skip_new_lines(s, d);
		else
			s = get_instruction(s, d, tree);
	}
}

extern void	general_parser(t_data *d, t_synt_tree **tree)
{
	get_labels(d);
	d->p.line = 1;
	d->p.col = 1;
	d->cur_addr = 0;
	parse_code(d, tree);
}
