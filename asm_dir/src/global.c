/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   global.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/03 14:06:35 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/03 14:07:47 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"

const t_inst_info	g_inst_info[TOTAL_INST_NUMBER] = {
	{0, {0}},
	{1, {T_DIR, 0, 0}},
	{2, {T_DI, T_REG}},
	{2, {T_REG, T_RI}},
	{3, {T_REG, T_REG, T_REG}},
	{3, {T_REG, T_REG, T_REG}},
	{3, {T_RDI, T_RDI, T_REG}},
	{3, {T_RDI, T_RDI, T_REG}},
	{3, {T_RDI, T_RDI, T_REG}},
	{1, {T_DIR}},
	{3, {T_RDI, T_RD, T_REG}},
	{3, {T_REG, T_RDI, T_RD}},
	{1, {T_DIR}},
	{2, {T_DI, T_REG}},
	{3, {T_RDI, T_RD, T_REG}},
	{1, {T_DIR}},
	{1, {T_REG}}
};

const t_inst_size	g_binsize[TOTAL_INST_NUMBER] = {
	{0, {{0}, {0}, {0}}},
	{0, {{0, 0, 4}, {0}, {0}}},
	{1, {{0, 2, 4}, {1}, {0}}},
	{1, {{1}, {1, 2}, {0}}},
	{1, {{1}, {1}, {1}}},
	{1, {{1}, {1}, {1}}},
	{1, {{1, 2, 4}, {1, 2, 4}, {1}}},
	{1, {{1, 2, 4}, {1, 2, 4}, {1}}},
	{1, {{1, 2, 4}, {1, 2, 4}, {1}}},
	{0, {{0, 0, 2}, {0}, {0}}},
	{1, {{1, 2, 2}, {1, 0, 2}, {1}}},
	{1, {{1}, {1, 2, 2}, {1, 0, 2}}},
	{0, {{0, 0, 2}, {0}, {0}}},
	{1, {{0, 2, 4}, {1}, {0}}},
	{1, {{1, 2, 2}, {1, 0, 2}, {1}}},
	{0, {{0, 0, 2}, {0}, {0}}},
	{1, {{1}, {0}, {0}}}
};

const char	*g_altr_inst_set[TOTAL_INST_NUMBER] = {
	"", "live", "mov", "mov", "add", "sub", "and", "or", "xor",
	"jz", "mov", "mov", "fork", "lmov", "lmov", "lfork", "aff"
};

const char	*g_dflt_inst_set[TOTAL_INST_NUMBER] = {
	"", "live", "ld", "st", "add", "sub", "and", "or", "xor",
	"zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"
};
