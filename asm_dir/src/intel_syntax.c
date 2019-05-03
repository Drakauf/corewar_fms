/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   intel_syntax.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/20 14:59:37 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 12:02:52 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

static t_child	*rotate_operands_left(t_synt_tree *t)
{
	t_child	*tmp;
	t_child	*i;

	if (t->total_operands == 1)
		return (t->child);
	tmp = t->child;
	t->child = tmp->next;
	tmp->next = NULL;
	i = t->child;
	while (i->next)
		i = i->next;
	i->next = tmp;
	return (t->child);
}

static int		set_lldi(t_child *c, t_data *d, t_synt_tree *t, int i)
{
	t->type = LLDI;
	if (*c->s != '[')
	{
		ft_perror(t->s, "unexpected token", &c->p, d);
		t->fmt[i] = -1;
		return (i);
	}
	return (set_mov_addr_syntax(c, d, t, i));
}

static void		print_addr_syntax_forbidden(t_synt_tree *t, t_child *c,
											t_data *d, int i)
{
	t->fmt[i] = -1;
	ft_perror(t->s, "two arguments address forbidden", &c->p, d);
}

/*
** intel_is_direct()
**     - Verifie si l'operande est de type direct.
**	   Valeur de retour:  0 si la syntaxe est potentiellement celle de mov
**                          (32+r3), (r3+r4), ...
**                       -1 s'il y a une erreur
**                        1 si le type est direct
**
** intel_is_indirect()
**     - Verifie si l'operande est de type indirect.
**     Valeur de retour:  0 si la syntaxe est potentiellement celle de mov
**                       -1 s'il y a une erreur
**                        1 si le type est direct
**
** intel_is_register()
**     - Verifie si l'operande est de type registre.
**     Valeur de retour:  0 si la syntaxe est potentiellement celle de mov
**                       -1 s'il y a une erreur
**                        1 si le type est direct
**
** set_mov_addr_syntax()
**     - si l'instruction est mov, verifie s'il y a un calcul d'addresse.
**       s'il n'y en a pas, set t->fmt[i] a -1 ou 0.
**       (-1 = erreur affichee, 0 = erreur non definie: "syntax error")
**     Valeur de retour: i   en cas d'erreur sur le premier sous-argument
**                       i+1 en cas d'erreur sur le deuxieme sous-argument
**                           ou si la syntaxe est valide
**
** set_lldi()
**     - change l'instruction (type) lld en lldi et
**       appelle set_atnt_intel_addr_calc_syntax()
**
** print_addr_syntax_forbidden()
**     - affiche une erreur si l'instruction n'est pas mov ni lmov.
**       (la syntaxe de calcul d'adresse est interdite
**		  pour les autres instructions)
**
** check_operand_type()
**     - verifie si le type enregistre dans t->fmt[i] correspond
**       a celui de l'operand i de l'instruction.
**     - affiche une erreur si le type ne correspond pas et n'est pas egal a -1
*/

extern void		check_intel_syntax(t_child *c, t_data *d, t_synt_tree *t)
{
	int		i;

	c = rotate_operands_left(t);
	i = 0;
	while (c)
	{
		if ((t->fmt[i] = intel_is_direct(c->s, d, c)) == 0
				&& (t->fmt[i] = intel_is_indirect(c->s, d, c)) == 0
				&& (t->fmt[i] = intel_is_register(c->s, d, c)) == 0)
		{
			if (t->type == LD || t->type == ST)
				i = set_mov_addr_syntax(c, d, t, i);
			else if (t->type == LLD)
				i = set_lldi(c, d, t, i);
			else
				print_addr_syntax_forbidden(t, c, d, i);
		}
		if (i == 0 && t->type == LD && t->fmt[0] == REG_O)
			t->type = ST;
		check_operand_type(c, d, t, i++);
		c = c->next;
	}
	if (t->type == STI)
		check_operand_type(t->child, d, t, 0);
}
