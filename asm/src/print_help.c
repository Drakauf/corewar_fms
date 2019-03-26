/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_help.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 10:49:51 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 10:50:16 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

extern int		print_help(const char *prog)
{
	ft_printf("%s [syntax option] file [option]\n\n"
			"syntax options:\n"
			"    --gnu    : gnu style assembly syntax\n"
			"    --intel  : intel style assembly syntax\n"
			"    --clang  : c style high-level syntax\n\n"
			"options:\n"
			"    -o file  : choose output file name\n"
			"    -d       : disassemble file (printed in stdout)\n", prog);
	return (0);
}
