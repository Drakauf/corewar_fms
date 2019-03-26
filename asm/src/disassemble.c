/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 19:31:22 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 22:21:31 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

#undef lines

void	check_header(char *file, int len)
{
	if ((unsigned long)len < sizeof(t_header)
		|| ((t_header*)file)->prog_name[0] == '\0'
		|| ((t_header*)file)->prog_comment[0] == '\0'
		|| ((t_header*)file)->magic != (t_uint)big_endian_int(COREWAR_EXEC_MAGIC)
		|| big_endian_int(((t_header*)file)->prog_size) < 3
		|| big_endian_int(((t_header*)file)->prog_size) > CHAMP_MAX_SIZE)
	{
		write(2, "invalid header\n", 15);
		exit(-1);
	}
}

int		check_types(t_param *p, int op)
{
	if (op == LD_M)
		return (p->count != 2 || p->type[0] == REG_D || p->type[1] != REG_D);
	else if (op == ST_M)
		return (p->count != 2 || p->type[0] != REG_D || p->type[1] == DIR_D);
	else if (op == ADD_M || op == SUB_M)
		return (p->count != 3 || p->type[0] != REG_D || p->type[1] != REG_D || p->type[2] != REG_D);
	else if (op == AND_M || op == XOR_M || op == OR_M)
		return (p->count != 3 || p->type[0] != REG_D);
	else if (op == LDI_M)
		return (p->count != 3 || p->type[1] == IND_D || p->type[2] != REG_D);
	else if (op == STI_M)
		return (p->count != 3 || p->type[0] != REG_D || p->type[2] == IND_D);
	else if (op == LLD_M)
		return (p->count != 2 || p->type[0] == REG_D || p->type[1] != REG_D);
	else if (op == LLDI_M)
		return (p->count != 3 || p->type[1] == IND_D || p->type[0] != REG_D);
	else if (op == AFF_M)
		return (p->count != 1 || p->type[0] != REG_D);
	return (0);
}

void	set_size(t_param *param, int opcode)
{
	int		i;

	if (check_types(param, opcode) == 1)
	{
		write(2, "invalid parameter\n", 18);
		exit(-1);
	}
	i = 0;
	while (i < param->count)
	{
		if (param->type[i] == REG_D)
			param->size[i] = 1;
		else if (param->type[i] == IND_D)
			param->size[i] = 2;
		else
		{
			param->size[i] = ((opcode > LIVE_M && opcode < ZJMP_M) || opcode == LLD_M) ?
				4 : 2;
		}
		i++;
	}
}

void	count_and_get_params(t_param *param, int byte, int opcode)
{
	int	n;

	n = ((param->type[0] = ((byte & 0xc0) >> 6)) != 0)
		+ ((param->type[1] = ((byte & 0x30) >> 4)) != 0)
		+ ((param->type[2] = ((byte & 0x0c) >> 2)) != 0);
	if (byte & 0x3)
	{
		write(2, "invalid param code byte\n", 24);
		exit(-1);
	}
	param->count = n;
	set_size(param, opcode);
}

int		get_value(char **s, int size)
{
	char	*ptr;
	int		i;
	int		shl;
	int		n;

	ptr = *s;
	i = 0;
	shl = 8 * (size - 1);
	n = 0;
	while (i < size)
	{
		n |= *ptr << shl;
		ptr++;
		shl -= 8;
		i++;
	}
	*s = ptr;
	return (n);
}

char	*add_line(char *file, t_vector *lines, t_param *p, int opcode)
{
	char	buf[100];
	int		i;
	int		value;

	i = 0;
	*buf = '\0';
	ft_strcat(buf, g_dflt_inst_set[opcode]);
	ft_strcat(buf, " ");
	while (i < p->count)
	{
		if (i)
			ft_strcat(buf, ", ");
		if (p->type[i] == DIR_D)
			ft_strcat(buf, "%");
		else if (p->type[i] == REG_D)
			ft_strcat(buf, "r");
		value = get_value(&file, p->size[i]);
		ft_strcat(buf, ft_itoa(value));
		i++;
	}
	ft_strcat(buf, "\n");
	lines->push_back(lines, (t_all)ft_strdup(buf));
	return (file);
}

void	disassemble_file(char *file, t_vector *lines, char *end)
{
	t_param		param;
	int			opcode;

	while (file < end)
	{
		if (*file < 1 || *file > REG_NUMBER)
		{
			write(2, "invalid opcode\n", 15);
			exit(-1);
		}
		opcode = *file;
		if (opcode != LIVE_M && opcode != ZJMP_M && opcode != FORK_M && opcode != LFORK_M)
		{
			count_and_get_params(&param, file[1], opcode);
			file += 2;
		}
		else
		{
			param.count = 1;
			param.type[0] = DIR_D;
			param.size[0] = (opcode == LIVE_M) ? 4 : 2;
			file++;
		}
		file = add_line(file, lines, &param, opcode);
	}
}

void	print_file(t_vector *lines, t_header *header)
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
