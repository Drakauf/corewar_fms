/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   character_info.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 14:56:24 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 18:53:23 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern int		is_authorized_char(t_data *d, char c)
{
	static char	*authorized = NULL;
	char		*i;

	if (authorized == NULL)
	{
		if (d->syntax == ATNT)
			authorized = ATNT_AUTHORIZED_CHAR;
		else if (d->syntax == INTL)
			authorized = INTL_AUTHORIZED_CHAR;
		else
			authorized = DFLT_AUTHORIZED_CHAR;
	}
	i = authorized;
	while (*i)
	{
		if (*i == c)
			return (1);
		++i;
	}
	return (0);
}

extern int		is_comment(t_data *d, char c)
{
	return (c == '#' || (d->syntax != DFLT && c == ';'));
}

extern int		is_not_space_or_label_end(char c, t_data *d)
{
	return (c != '\0' && c != ' ' && c != '\t' && c != ':'
			&& c != '\n' && !is_comment(d, c));
}
