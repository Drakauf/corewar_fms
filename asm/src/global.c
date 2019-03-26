/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/16 00:41:35 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 17:04:17 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/asm.h"
/*
const t_inst_info	g_inst_info[TOTAL_INST] = {
	{0, {0}, {{0}, {0}, {0}}},
	{1, {T_DIR, 0, 0}, {{0, 0, M_4}, {0}, {0}}},							// live
	{2, {T_DI, T_REG}, {{0, M_2, M_4}, {M_1}, {0}}},						// ld (mov)
	{2, {T_REG, T_RI}, {{M_1}, {M_1, M_2}, {0}}},							// st (mov)
	{3, {T_REG, T_REG, T_REG}, {{M_1}, {M_1}, {M_1}}},						// add
	{3, {T_REG, T_REG, T_REG}, {{M_1}, {M_1}, {M_1}}},						// sub
	{3, {T_RDI, T_RDI, T_REG}, {{M_1, M_2, M_4}, {M_1, M_2, M_4}, {M_1}}},	// and
	{3, {T_RDI, T_RDI, T_REG}, {{M_1, M_2, M_4}, {M_1, M_2, M_4}, {M_1}}},	// or
	{3, {T_RDI, T_RDI, T_REG}, {{M_1, M_2, M_4}, {M_1, M_2, M_4}, {M_1}}},	// xor
	{1, {T_DIR}, {{0, 0, M_2}, {0}, {0}}},									// zjmp (jz)
	{3, {T_RDI, T_RD, T_REG}, {{M_1, M_2, M_2}, {M_1, 0, M_2}, {M_1}}},		// ldi (mov)
	{3, {T_REG, T_RDI, T_RD}, {{M_1}, {M_1, M_2, M_2}, {M_1, 0, M_2}}},		// sti (mov)
	{1, {T_DIR}, {{0, 0, M_2}, {0}, {0}}},									// fork
	{2, {T_DI, T_REG}, {{0, M_2, M_4}, {M_1}, {0}}},						// lld (lmov)
	{3, {T_RDI, T_RD, T_REG}, {{M_1, M_2, M_2}, {M_1, 0, M_2}, {M_1}}},		// lldi (lmov)
	{1, {T_DIR}, {{0, 0, M_2}, {0}, {0}}},									// lfork
	{1, {T_REG}, {{M_1}, {0}, {0}}},										// aff (nop)
};
*/
const t_inst_info	g_inst_info[TOTAL_INST_NUMBER] = {
	{0, {0}},
	{1, {T_DIR, 0, 0}},			// live
	{2, {T_DI, T_REG}},			// ld (mov)
	{2, {T_REG, T_RI}},			// st (mov)
	{3, {T_REG, T_REG, T_REG}},	// add
	{3, {T_REG, T_REG, T_REG}},	// sub
	{3, {T_RDI, T_RDI, T_REG}},	// and
	{3, {T_RDI, T_RDI, T_REG}},	// or
	{3, {T_RDI, T_RDI, T_REG}},	// xor
	{1, {T_DIR}},				// zjmp (jz)
	{3, {T_RDI, T_RD, T_REG}},	// ldi (mov)
	{3, {T_REG, T_RDI, T_RD}},	// sti (mov)
	{1, {T_DIR}},				// fork
	{2, {T_DI, T_REG}},			// lld (lmov)
	{3, {T_RDI, T_RD, T_REG}},	// lldi (lmov)
	{1, {T_DIR}},				// lfork
	{1, {T_REG}}				// aff (nop)
};

const t_inst_size	g_binsize[TOTAL_INST_NUMBER] = {
	{0, {{0}, {0}, {0}}},
	{0, {{0, 0, 4}, {0}, {0}}},			// live
	{1, {{0, 2, 4}, {1}, {0}}},			// ld
	{1, {{1}, {1, 2}, {0}}},			// st
	{1, {{1}, {1}, {1}}},				// add
	{1, {{1}, {1}, {1}}},				// sub
	{1, {{1, 2, 4}, {1, 2, 4}, {1}}},	// and
	{1, {{1, 2, 4}, {1, 2, 4}, {1}}},	// or
	{1, {{1, 2, 4}, {1, 2, 4}, {1}}},	// xor
	{0, {{0, 0, 2}, {0}, {0}}},			// zjmp
	{1, {{1, 2, 2}, {1, 0, 2}, {1}}},	// ldi
	{1, {{1}, {1, 2, 2}, {1, 0, 2}}},	// sti
	{0, {{0, 0, 2}, {0}, {0}}},			// fork
	{1, {{0, 2, 4}, {1}, {0}}},			// lld
	{1, {{1, 2, 2}, {1, 0, 2}, {1}}} ,	// lldi
	{0, {{0, 0, 2}, {0}, {0}}},			// lfork
	{1, {{1}, {0}, {0}}}				// aff
};

const char	*g_altr_inst_set[TOTAL_INST_NUMBER] = {
	"", "live", "mov", "mov", "add", "sub", "and", "or", "xor",
	"jz", "mov", "mov", "fork", "lmov", "lmov", "lfork", "aff"
};

const char	*g_dflt_inst_set[TOTAL_INST_NUMBER] = {
	"", "live", "ld", "st", "add", "sub", "and", "or", "xor",
	"zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"
};
