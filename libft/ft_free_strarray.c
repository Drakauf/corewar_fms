/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_ptrarray.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 19:35:50 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/01 15:43:01 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_strarray(char **a)
{
	char	**ptr;

	if (a)
	{
		ptr = a;
		while (*a)
		{
			free(*(a++));
		}
		free(ptr);
	}
	return (NULL);
}