/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 11:17:29 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 15:18:34 by mhouppin    ###    #+. /#+    ###.fr     */
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
# define F_VERB			0x4

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
	int				pnum;
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
	SDL_Event		ev;
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
	struct s_proc	*forks;
	int				cycles;
	int				dcycles;
	int				kcycles;
	int				tcycles;
	int				lives;
	int				llives[MAX_PLAYERS];
	int				next_pnum;
	int				checks;
	int				mchecks;
	int				players;
	int				flags;
	struct s_header	headers[MAX_PLAYERS];
	int				verbose;
};

typedef int		(*t_exec)(struct s_vm *, struct s_proc *);
/*
int		get_champ_num(struct s_vm *vm);

void	launch_corewar(struct s_vm *vm);

void	load_champs(struct s_vm *vm);

struct s_proc	*fresh_process(struct s_vm *vm, int pn, int pc);

void	cw_init_window(struct s_vdata *data);
void	cw_update_window(struct s_vm *vm);
struct s_vm **get_vmp(void);
*/


/*
** champ_intro.c
*/

void	champ_intro(struct s_vm *vm, int p, int fd);

/*
** corewar.c
*/

int					p_size(struct s_proc *p);
void				check_lives(struct s_vm *vm);
void				dump_memory(struct s_vm *vm);
void				update_info(struct s_vm *vm);
void				go_corewar(struct s_vm *vm);

/*
** launch_corewar.c 
*/

void				launch_corewar(struct s_vm *vm);
void				init_params(struct s_vm *vm);

/*
** load_champs.c
*/

void				load_champs(struct s_vm *vm);
void				read_champs(struct s_vm *vm, int p, int fd);
int					get_champ_num(struct s_vm *vm);
void				next_player(struct s_vm *vm, char *player);
void				add_champ(struct s_vm *vm, char **argv, int i);

/*
** param_get.c
*/

unsigned char 		fparam(unsigned char op);
unsigned char 		sparam(unsigned char op);
unsigned char 		tparam(unsigned char op);
unsigned char 		uparam(unsigned char op);

/*
** param_tool.c
*/

int					param_size(unsigned char op, struct s_proc *p);
int					get_param1(struct s_proc *p, struct s_vm *vm, unsigned char op, int pc);
int					get_param2(struct s_proc *p, struct s_vm *vm, unsigned char op, int pc);
int					get_param3(struct s_proc *p, struct s_vm *vm, unsigned char op, int pc);
void				get_params(struct s_proc *p, struct s_vm *vm, unsigned char op);


int		**load_font(void);

/*
** parsing.c
*/

void				parse_argument(struct s_vm *vm, char **argv, int *ip);
void				exit_usage(char *progname);

/*
** struct.c
*/

struct s_vm			**get_vmp(void);
void				destroy_vm(void) __attribute__((destructor));
void				destroy_vdata(struct s_vdata *data);

/*
** tools.c
*/

void				reverse(unsigned int *a);

/*
** process.c
*/

void				create_processes(struct s_vm *vm);
void				kill_process(struct s_proc **proc, struct s_vm *vm,\
					struct s_proc *last);
void				fork_process(struct s_vm *vm, struct s_proc *proc, int param);
struct s_proc		*fresh_process(int pn, int pc, struct s_vm *vm);

#endif
