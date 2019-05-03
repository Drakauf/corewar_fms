/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 15:32:35 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 09:48:41 by mhouppin    ###    #+. /#+    ###.fr     */
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

void	load_vm(void)
{
	uint64_t		hashval;
	const uint64_t	bitset_1 = 0xf0e1d2c3b4a59687;
	const uint64_t	bitset_2 = 0x08192a3b4c5d6e7f;
	const uint64_t	bitset_3 = 0xefcdab8967452301;

	hashval = (bitset_1 ^ MAX_PLAYERS) + (bitset_2 * MEM_SIZE);
	reverse((unsigned int *)&hashval);
	hashval += (bitset_3 ^ ((uint64_t)IDX_MOD << 27)) -
		(bitset_1 * CHAMP_MAX_SIZE);
	hashval += (bitset_2 ^ ((uint64_t)REG_NUMBER << 19)) +
		(bitset_3 * sizeof(t_reg));
	reverse((unsigned int *)&hashval);
	hashval += (~bitset_1 ^ ((uint64_t)CYCLE_TO_DIE << 42)) -
		(~bitset_2 * CYCLE_DELTA);
	hashval += (~bitset_3 ^ ((uint64_t)NBR_LIVE << 55)) +
		(~bitset_1 * MAX_CHECKS);
	reverse((unsigned int *)&hashval);
	hashval += (~bitset_2 ^ ((uint64_t)PROG_NAME_LEN << 34)) -
		(~bitset_3 * COMMENT_LEN);
	if (hashval != 0x3c1b36c6964f25a9)
	{
		ft_printf("%con't %couch %cy %cacros!%c", 0x44, 0x74, 0x6d, 0x6d, 0x0a);
		get_vmp()[0] = NULL;
		exit(0);
	}
}
