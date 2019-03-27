/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/16 00:41:35 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 19:13:04 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"


/*
** print_total_errors()
**
** affiche le nombre d'erreurs s'il y en a,
** ou la presence de la section .name et .comment et
** d'au moins une instruction (sans compter les labels)
*/

static int		print_total_errors(t_data *d, t_synt_tree *tree)
{
	const char	*buf = ft_itoa(d->syntax_error);
	int			error;

	error = 0;
	if (d->syntax_error)
	{
		write(2, "\e[1;31m", 7);
		write(2, buf, ft_strlen(buf));
		d->syntax_error == 1 ?
			write(2, " error\n\e[0m", 11) : write(2, " errors\n\e[0m", 12);
	}
	else
	{
		if (d->name == NULL)
			error = write(2, "\e[0;31mError:\e[0m missing .name section\n", 40);
		if (d->comment == NULL)
			error = write(2, "\e[0;31mError:\e[0m missing .comment section\n", 43);
		if (d->cur_addr == 0)
			error = write(2, "\e[0;31mError:\e[0m no instructions\n", 34);
	}
	if (!error && !d->syntax_error)
		return (0);
	free_all(d, tree);
	return (1);
}

/*
** general_parser() s'occupe de verifier la syntaxe et de recuperer
** les instructions sous forme de liste chainee.
**
** write_binary() enregistre les instructions contenues
** dans la liste chainee en binaire.
*/

int			main(int ac, char *av[])
{
	t_data		data;
	t_synt_tree	*tree;

	tree = NULL;
	if (ac == 1)
		return (print_help(av[0]));
	ft_assert(ac > 5, TOO_MANY_ARGS);
	get_arguments(av + 1, &data);
	ft_assert(!(data.file = get_contents(data.input, &data.file_len)), OPEN_ERROR);
	if (data.syntax == CSTYLE)
	{
		//convert_c_to_intel_style_assembly();
	}
	else if (data.output == NULL)
		return (disassemble(data.file, data.file_len));
	general_parser(&data, &tree);
	if (print_total_errors(&data, tree))
		return (-1);
	write_binary(&data, tree, data.output);
	free_all(&data, tree);
	return (0);
}
