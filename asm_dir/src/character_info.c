/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   character_info.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 14:56:24 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 12:12:57 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern int		is_authorized_char(t_data *d, char c)
{
	if (d->syntax == ATNT)
	{
		return (c == '$' || c == '%' || (c > 39 && c < 44)
				|| (c >= '0' && c <= ':') || (c >= 'A' && c <= 'Z')
				|| c == '_' || (c >= 'a' && c <= 'z') || c == '-');
	}
	if (d->syntax == INTL)
	{
		return (c == '[' || c == ']' || (c > 41 && c < 44)
				|| (c >= '0' && c <= ':') || (c >= 'A' && c <= 'Z')
				|| c == '_' || (c >= 'a' && c <= 'z') || c == '-');
	}
	return (c == '%' || (c >= '0' && c <= ':') || (c >= 'A' && c <= 'Z')
			|| c == '_' || (c >= 'a' && c <= 'z') || c == '-');
}

extern int		is_comment(char c)
{
	return (c == '#' || c == ';');
}

extern int		is_not_space_or_label_end(char c)
{
	return (c != '\0' && c != ' ' && c != '\t' && c != ':'
			&& c != '\n' && !is_comment(c));
}
