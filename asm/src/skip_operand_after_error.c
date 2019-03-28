/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   skip_operand_after_error.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 11:38:16 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 11:38:33 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern int		skip_operand_after_error(char **s)
{
	char	*nl;
	char	*comma;

	if ((nl = ft_strchr(*s, '\n')) > (comma = ft_strchr(*s, ',')))
	{
		if (comma == NULL)
		{
			*s = nl;
			return (0);
		}
		*s = comma;
		return (0);
	}
	if (nl)
	{
		*s = nl;
		return (0);
	}
	*s = ft_strchr(*s, '\0');
	return (-1);
}
