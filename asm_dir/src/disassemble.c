/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 19:31:22 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 14:56:00 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

static void	exit_error_msg(const char *msg, int len)
{
	write(2, msg, len);
	exit(1);
}

static void	check_header(char *file, int len)
{
	if ((unsigned long)len < HEADERSIZ)
		exit_error_msg(ERR "en-tete trop petit\n", 39);
	if (((t_header*)file)->prog_name[0] == '\0')
		exit_error_msg(ERR "section .name vide\n", 39);
	if (((t_header*)file)->magic != (t_uint)big_endian_int(MAGIC))
		exit_error_msg(ERR "nombre 'magic' invalid\n", 43);
	if (little_endian(((t_header*)file)->prog_size) < 3)
		exit_error_msg(ERR "aucune instruction\n", 39);
	if (little_endian(((t_header*)file)->prog_size) != (len - HEADERSIZ))
		exit_error_msg(ERR "prog_size different de la taille du corps\n", 62);
}

static void	disassemble_file(char *file, t_vector *lines, char *end)
{
	t_param		param;
	int			opc;

	while (file < end)
	{
		if (*file < 1 || *file > AFF)
			exit_error_msg(ERR "opcode invalide\n", 36);
		opc = *(file++);
		if (opc != LIVE && opc != ZJMP && opc != FORK && opc != LFORK)
		{
			count_and_get_params(&param, *file, opc);
			file++;
		}
		else
		{
			param.count = 1;
			param.type[0] = DIR_D;
			param.size[0] = (opc == LIVE) ? 4 : 2;
		}
		file = add_line(file, lines, &param, opc);
	}
}

static void	print_file(t_vector *lines, t_header *header)
{
	int			i;
	const char	**l = (const char**)lines->tab;

	ft_printf("%s \"%s\"\n%s \"%s\"\n\n",
				NAME_CMD_STRING, header->prog_name,
				COMMENT_CMD_STRING, header->prog_comment);
	i = 0;
	while (i < lines->len)
		ft_puts(l[i++]);
}

extern int	disassemble(char *file, int len)
{
	t_vector	*lines;

	check_header(file, len);
	lines = new_vector(VECTOR_PTR, 16);
	disassemble_file(file + sizeof(t_header), lines, file + len);
	print_file(lines, (t_header*)file);
	free(file);
	lines->free(lines);
	return (0);
}
