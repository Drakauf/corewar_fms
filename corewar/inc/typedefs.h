/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   typedefs.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 14:35:15 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 14:39:57 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

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
	int				zcycles;
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

#endif
