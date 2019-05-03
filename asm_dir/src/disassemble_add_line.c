/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   disassemble_add_line.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 17:04:25 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 16:50:50 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static int		check_types(t_param *p, int op)
{
	if (op == LD)
		return (p->count != 2 || p->type[0] == REG_D || p->type[1] != REG_D);
	else if (op == ST)
		return (p->count != 2 || p->type[0] != REG_D || p->type[1] == DIR_D);
	else if (op == ADD || op == SUB)
		return (p->count != 3 || p->type[0] != REG_D || p->type[1] != REG_D
				|| p->type[2] != REG_D);
	else if (op == AND || op == XOR || op == OR)
		return (p->count != 3 || p->type[0] != REG_D);
	else if (op == LDI)
		return (p->count != 3 || p->type[1] == IND_D || p->type[2] != REG_D);
	else if (op == STI)
		return (p->count != 3 || p->type[0] != REG_D || p->type[2] == IND_D);
	else if (op == LLD)
		return (p->count != 2 || p->type[0] == REG_D || p->type[1] != REG_D);
	else if (op == LLDI)
		return (p->count != 3 || p->type[1] == IND_D || p->type[0] != REG_D);
	else if (op == AFF)
		return (p->count != 1 || p->type[0] != REG_D);
	return (0);
}

static void		set_size(t_param *param, int opc)
{
	int		i;

	if (check_types(param, opc) == 1)
	{
		write(2, ERR "octet de codage incompatible\n", 29);
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
			param->size[i] = ((opc > LIVE && opc < ZJMP) || opc == LLD) ?
				4 : 2;
		}
		i++;
	}
}

extern void		count_and_get_params(t_param *param, int byte, int opcode)
{
	int	rem;

	if (!(param->type[0] = ((byte & 0xc0) >> 6)))
	{
		write(2, ERR "octet de codage invalide\n", 44);
		exit(-1);
	}
	param->type[1] = ((byte & 0x30) >> 4);
	param->type[2] = ((byte & 0x0c) >> 2);
	if (param->type[2])
		rem = (byte & 0x03);
	else if (param->type[1])
		rem = (byte & 0xf);
	else
		rem = (byte & 0x3f);
	if (rem)
	{
		write(2, ERR "octet de codage invalide\n", 44);
		exit(-1);
	}
	param->count = (param->type[0] != 0)
		+ (param->type[1] != 0) + (param->type[2] != 0);
	set_size(param, opcode);
}

static int		get_value(char **s, int size)
{
	char	*end;
	int		n;

	end = *s + size;
	n = *((*s)++);
	while (*s < end)
	{
		n = (n << 8) | (unsigned char)**s;
		(*s)++;
	}
	return (n);
}

extern char		*add_line(char *file, t_vector *lines, t_param *p, int opcode)
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
