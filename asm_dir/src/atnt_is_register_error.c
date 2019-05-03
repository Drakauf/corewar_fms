/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   atnt_is_register_error.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 16:36:22 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 16:45:34 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern int		perror_undefined_label(t_data *d, t_child *c)
{
	ft_perror(NULL, "undefined label", &c->p, d);
	return (-1);
}

extern int		perror_inexistant_register(t_data *d, t_child *c)
{
	ft_perror(NULL, "inexistant register", &c->p, d);
	return (-1);
}
