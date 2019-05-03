/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   param_get.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/24 15:05:05 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 11:37:47 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "op.h"

unsigned char	fparam(unsigned char op)
{
	return ((op & 192U) >> 6);
}

unsigned char	sparam(unsigned char op)
{
	return ((op & 48U) >> 4);
}

unsigned char	tparam(unsigned char op)
{
	return ((op & 12U) >> 2);
}

unsigned char	uparam(unsigned char op)
{
	return (op & 3U);
}
