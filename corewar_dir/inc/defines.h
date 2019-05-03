/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   defines.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 14:33:55 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 09:50:05 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define REG_SIZE		4
# define DIR_SIZE		4
# define IND_SIZE		2

# define REG_CODE		1
# define DIR_CODE		2
# define IND_CODE		3

# define MAX_PLAYERS	4
# define MEM_SIZE		4096
# define IDX_MOD		512
# define CHAMP_MAX_SIZE	682U

# define REG_NUMBER		16
# define CYCLE_TO_DIE	1536
# define CYCLE_DELTA	50
# define NBR_LIVE		21
# define MAX_CHECKS		10

# define PROG_NAME_LEN	128
# define COMMENT_LEN	2048
# define COREWAR_MAGIC	0xea83f3

# define F_DUMP			0x1
# define F_GRAPH		0x2
# define F_VERB			0x4

# define MEM_LINES		64
# define MEM_COLS		64
# define CHAR_SX		8
# define CHAR_SY		10
# define CHAR_HSP		2
# define CHAR_VSP		8
# define CHAR_BSP		10
# define CHAR_SP		12
# define TB_MAX_CHARS	80
# define BORDER_SIZE	6

# define VLIVES			0x01
# define VCYCLES		0x02
# define VOPERS			0x04
# define VDEATHS		0x08
# define VPCMOV			0x10

# define CLIVE			0x01
# define CLD			0x02
# define CST			0x03
# define CADD			0x04
# define CSUB			0x05
# define CAND			0x06
# define COR			0x07
# define CXOR			0x08
# define CZJMP			0x09
# define CLDI			0x0a
# define CSTI			0x0b
# define CFORK			0x0c
# define CLLD			0x0d
# define CLLDI			0x0e
# define CLFORK			0x0f
# define CAFF			0x10

#endif
