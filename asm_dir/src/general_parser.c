/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   general_parser.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 11:01:06 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 11:29:23 by fcordon     ###    #+. /#+    ###.fr     */
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
		d->inst_set = g_altr_inst_set;
	else if (d->syntax == INTL)
		d->inst_set = g_altr_inst_set;
	else
		d->inst_set = g_dflt_inst_set;
}

static char	*get_label(char *s, t_data *d)
{
	char		*start;
	t_label		*new;

	start = s;
	while (is_not_space_or_label_end(*s))
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

static void	get_labels(t_data *d)
{
	char	*s;

	s = d->file;
	while (*s)
	{
		if (is_comment(*s) || *s == '.')
			s = skip_all_but('\n', s);
		else if (*s == '\t' || *s == ' ')
			s = skip_spaces(s, &d->p);
		else if (*s == '\n')
			s = skip_new_lines(s, d);
		else
			s = get_label(s, d);
	}
}

static void	parse_code(t_data *d, t_synt_tree **tree)
{
	char	*s;

	s = d->file;
	while (*s)
	{
		if (is_comment(*s))
			s = skip_all_but('\n', s);
		else if (*s == '\t' || *s == ' ')
			s = skip_spaces(s, &d->p);
		else if (*s == '\n')
			s = skip_new_lines(s, d);
		else if (!is_authorized_char(d, *s) && *s != '.')
		{
			ft_perror(NULL, "bad character", &d->p, d);
			s = skip_all_but('\n', s);
		}
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
