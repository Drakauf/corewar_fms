/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/16 00:41:35 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/26 14:32:19 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

static void	set_data(t_data *d)
{
	d->header_stat = 0;
	d->current = NULL;
	d->previous = NULL;
	d->comment = NULL;
	d->name = NULL;
	d->syntax_error = 0;
	d->label = new_vector(VECTOR_PTR, 8);
	d->p.line = 1;
	d->p.col = 1;
	if (d->syntax == ATNT)
	{
		d->inst_set = g_altr_inst_set;
		d->n_inst = TOTAL_INST_NUMBER;
	}
	else if (d->syntax == INTL)
	{
		d->inst_set = g_altr_inst_set;
		d->n_inst = TOTAL_INST_NUMBER;
	}
	else
	{
		d->inst_set = g_dflt_inst_set;
		d->n_inst = TOTAL_INST_NUMBER;
	}
}

static void		free_all(t_data *d, t_synt_tree *tree)
{
	d->label->free(d->label);
	free_tree(tree);
	free(d->file);
}

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

int			main(int ac, char *av[])
{
	t_data		data;
	t_synt_tree	*tree;

	tree = NULL;
	if (ac == 1)
		return (print_help(av[0]));
	ft_assert(ac > 5, TOO_MANY_ARGS);
	get_argument(av + 1, &data);
	ft_assert(!(data.file = get_contents(data.input, &data.file_len)), OPEN_ERROR);
	if (data.syntax == CSTYLE)
	{
		//convert_c_to_intel_style_assembly();
	}
	else if (data.output == NULL)
		return (disassemble(data.file, data.file_len));
	set_data(&data);
	general_parser(&data, &tree);
	if (print_total_errors(&data, tree))
		return (-1);
	write_binary(&data, tree, data.output);
	free_all(&data, tree);
	return (0);
}
