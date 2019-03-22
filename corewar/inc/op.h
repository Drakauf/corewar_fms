/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 11:17:29 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 11:13:50 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include <stdint.h>
# include <errno.h>
# include "SDL2/SDL.h"
# include "libft.h"
# include <fcntl.h>

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

# define MEM_LINES		64
# define MEM_COLS		64
# define CHAR_SX		8
# define CHAR_SY		10
# define CHAR_HSP		2
# define CHAR_VSP		8
# define CHAR_BSP		10
# define CHAR_SP		(CHAR_HSP + CHAR_BSP)
# define TB_MAX_CHARS	80
# define BORDER_SIZE	6
# define BORDER_COLOR	0x007F7F7F

/*
** Little endian: BGRA color
*/

enum	e_colors
{
	COLOR_BORDER = 0x7F7F7F00,
	COLOR_NONE = 0x3F3F3F00,
	COLOR_CYAN = 0xFFFF0000,
	COLOR_ORANGE = 0x009FFF00,
	COLOR_GREEN = 0x1FFF1F00,
	COLOR_RED = 0x0F0FFF00,
	COLOR_LNONE = 0x9F9F9F00,
	COLOR_LCYAN = 0xFFFF7F00,
	COLOR_LORANGE = 0x7FCFFF00,
	COLOR_LGREEN = 0x8FFF8F00,
	COLOR_LRED = 0x8888FF00,
	COLOR_WHITE = 0xFFFFFF00
};

typedef int		t_reg;

struct	s_pos
{
	int		x;
	int		y;
};

struct	s_proc
{
	t_reg			regs[REG_NUMBER];
	char			carry;
	int				pcount;
	int				lives;
	int				number;
	int				cooldown;
	int				last_it;
	int				last_op;
	int				last_p1;
	int				last_p2;
	int				last_p3;
	struct s_proc	*next;
};

struct	s_vdata
{
	SDL_Window		*win;
	SDL_Renderer	*rd;
	SDL_Texture		*tx;
	int				*px;
	int				pitch;
	int				sx;
	int				sy;
	int				**font;
	int				tbx;
	int				frate;
	int				gcycles;
};

struct	s_header
{
	unsigned int	magic;
	char			*prog_name;
	unsigned int	prog_size;
	char			*comment;
};

struct	s_vm
{
	char			*champs[MAX_PLAYERS];
	void			*arena;
	void			*ainfo;
	int				asize;
	int				aspace;
	struct s_vdata	*data;
	struct s_proc	*processes;
	int				cycles;
	int				dcycles;
	int				kcycles;
	int				tcycles;
	int				lives;
	int				llives[MAX_PLAYERS];
	int				checks;
	int				mchecks;
	int				players;
	int				flags;
	struct s_header	headers[MAX_PLAYERS];
	FILE			*f;
};

typedef int		(*t_exec)(struct s_vm *, struct s_proc *);

int		get_champ_num(struct s_vm *vm);

void	launch_corewar(struct s_vm *vm);

void	load_champs(struct s_vm *vm);

struct s_proc	*fresh_process(struct s_vm *vm, int pn, int pc);

void	cw_init_window(struct s_vdata *data);
void	cw_update_window(struct s_vm *vm);
int		**load_font(void);

#endif
