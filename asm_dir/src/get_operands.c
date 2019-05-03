/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_operands.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 19:11:46 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 12:14:20 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static char		*goto_operand_end(char *s, t_data *d)
{
	while (1)
	{
		if (*s == ' ')
		{
			if (s[1] == '+')
				s++;
			else if (s[-1] != '+')
				break ;
		}
		else if (is_comment(*s) || *s == ',' || *s == '\t'
				|| !is_authorized_char(d, *s))
			break ;
		else if (*s == ':')
		{
			if (d->syntax != DFLT
					|| ((s == d->start + 1 && s[-1] != '%')
						|| s > d->start + 1))
				break ;
		}
		s++;
	}
	return (s);
}

static int		skip_spaces_after_operand(char **s, t_data *d)
{
	t_pos	p;

	while (**s == ' ' || **s == '\t')
		(*s)++;
	if (**s != ',' && **s != '\n' && !is_comment(**s))
	{
		p.col = d->p.col + (*s - d->start);
		p.line = d->p.line;
		d->cur_inst_error = 1;
		ft_perror(NULL, "unexpected token", &p, d);
		return (BREAK);
	}
	return (0);
}

/*
** skip_spaces()
**     - Passe les espaces avant l'operande
**
** goto_opernd_end()
**     - Incremente s jusqu'au premier
**       ' ' '\n' ',' '\0' ou caractere invalide
**
** write_operand_into_tree()
**     - Si l'operande est valide (lexicalement),
**       l'ajoute a tree.
**     - Si l'erreur est 'fatale',
**       saute tout le reste de la ligne.
**	   - Si l'erreur n'est pas 'fatale', saute l'operande.
**
** skip_spaces_after_operand()
**     -
**
** check_operands_syntax_and_type()
**     - verifie la syntaxe des operandes ainsi que leurs types.
**
** update_current_addr()
**     - calcul la taille de la nouvelle instruction,
**       et l'ajoute a la position actuelle.
*/

extern char		*get_operands(char *s, t_data *d)
{
	d->cur_inst_error = 0;
	while (1)
	{
		s = skip_spaces(s, &d->p);
		d->start = s;
		s = goto_operand_end(s, d);
		if (write_operand_into_tree(&s, d) == FATAL_ERROR)
			return (s);
		if ((*s == ' ' || *s == '\t')
				&& skip_spaces_after_operand(&s, d) == BREAK)
			break ;
		if (*s != ',')
			break ;
		d->p.col += (s - d->start) + 1;
		s++;
	}
	d->p.col += (s - d->start);
	if (d->current->remainder > 0 && !d->cur_inst_error)
		ft_perror(d->current->s, "too few operands", &d->p, d);
	else if (d->current->total_operands > 0 && !d->cur_inst_error)
	{
		check_operands_syntax_and_type(d->current, d);
		update_current_addr(d);
	}
	return (skip_all_but('\n', s));
}
