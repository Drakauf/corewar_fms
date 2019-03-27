/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   general_parser.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 11:01:06 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 17:54:49 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void	set_data(t_data *d)
{
	d->header_stat = 0;
	d->current = NULL;
	d->previous = NULL;
	d->comment = NULL;
	d->name = NULL;
	d->syntax_error = 0;
	d->label = new_vector(VECTOR_PTR, 8);
	d->p.line = 1;
	d->p.col = 1;
	if (d->syntax == ATNT)
	{
		d->inst_set = g_altr_inst_set;
		d->n_inst = TOTAL_INST_NUMBER;
	}
	else if (d->syntax == INTL)
	{
		d->inst_set = g_altr_inst_set;
		d->n_inst = TOTAL_INST_NUMBER;
	}
	else
	{
		d->inst_set = g_dflt_inst_set;
		d->n_inst = TOTAL_INST_NUMBER;
	}
}

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

/*
** get_labels() recupere d'abord tous les labels dans le tableau d->label
** (aucun message d'erreur a cette etape)
**
** parse_code() verifie la syntaxe, recupere les instructions dans
** la liste de type t_synt_tree et calcul l'adresse des labels
** tout en affichant des messages d'erreur si besoin.
** le nombre d'erreurs est contenu dans d->syntax_error
*/

extern void	general_parser(t_data *d, t_synt_tree **tree)
{
	set_data(d);
	get_labels(d);
	d->p.line = 1;
	d->p.col = 1;
	d->cur_addr = 0;
	parse_code(d, tree);
}
