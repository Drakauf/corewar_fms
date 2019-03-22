/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 15:32:35 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 15:37:29 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

void	reverse(unsigned int *a)
{
	unsigned int swap;

	swap = ((*a >> 24) & 255) << 0;
	swap |= ((*a >> 16) & 255) << 8;
	swap |= ((*a >> 8) & 255) << 16;
	swap |= ((*a >> 0) & 255) << 24;
	*a = swap;
}
