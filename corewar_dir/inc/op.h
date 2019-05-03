/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mhouppin <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 11:17:29 by mhouppin     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 09:49:19 by mhouppin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include <stdint.h>
# include <errno.h>
# include "SDL.h"
# include "libft.h"
# include <fcntl.h>
# include "defines.h"
# include "typedefs.h"

extern const int g_color[2 * MAX_PLAYERS + 2];

void				cw_init_window(struct s_vdata *data);
void				cw_update_window(struct s_vm *vm, struct s_vdata *data,
		int last_frame);
struct s_vm			**get_vmp(void);

/*
** champ_intro.c
*/

void				champ_intro(struct s_vm *vm, int p, int fd);

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

unsigned char		fparam(unsigned char op);
unsigned char		sparam(unsigned char op);
unsigned char		tparam(unsigned char op);
unsigned char		uparam(unsigned char op);

/*
** param_tool.c
*/

int					param_size(unsigned char op, struct s_proc *p);
int					get_param1(struct s_proc *p, struct s_vm *vm,
		unsigned char op, int pc);
int					get_param2(struct s_proc *p, struct s_vm *vm,
		unsigned char op, int pc);
int					get_param3(struct s_proc *p, struct s_vm *vm,
		unsigned char op, int pc);
void				get_params(struct s_proc *p, struct s_vm *vm,
		unsigned char op);

/*
** exec_*.c
*/

int					live(struct s_vm *vm, struct s_proc *p);
int					ld(struct s_vm *vm, struct s_proc *p);
int					st(struct s_vm *vm, struct s_proc *p);
int					add(struct s_vm *vm, struct s_proc *p);
int					sub(struct s_vm *vm, struct s_proc *p);
int					and(struct s_vm *vm, struct s_proc *p);
int					or(struct s_vm *vm, struct s_proc *p);
int					xor(struct s_vm *vm, struct s_proc *p);
int					zjmp(struct s_vm *vm, struct s_proc *p);
int					ldi(struct s_vm *vm, struct s_proc *p);
int					sti(struct s_vm *vm, struct s_proc *p);
int					cfork(struct s_vm *vm, struct s_proc *p);
int					lld(struct s_vm *vm, struct s_proc *p);
int					lldi(struct s_vm *vm, struct s_proc *p);
int					lfork(struct s_vm *vm, struct s_proc *p);
int					aff(struct s_vm *vm, struct s_proc *p);

/*
** exec_misc.c
*/

void				disp_sti(struct s_proc *p, int index, int idxsum);
void				disp_ldi(struct s_proc *p, int index, int idxsum);
void				disp_lldi(struct s_proc *p, int index, int idxsum);

/*
** exec_tools.c
*/

void				set_pc(struct s_proc *p, struct s_vm *vm, int x);
int					invalid_reg(int regnum);
int					i_inst(int c);

/*
** load_tools.c
*/

int					get_int(void *arena, int pc, int offset);
void				set_int(struct s_vm *vm, int pc, int player,
		unsigned int value);

/*
** exec_cooldowns.c
*/

int					do_aff(unsigned char c, struct s_proc *p);
int					do_live_or_pc(unsigned char c, struct s_proc *p);
int					do_operation(unsigned char c, struct s_proc *p);
int					do_load(unsigned char c, struct s_proc *p);

/*
** exec_checks.c
*/

int					bitset_fail(struct s_proc *p);
int					sti_fail(struct s_proc *p);
int					ldi_fail(struct s_proc *p);

/*
** execute.c
*/

int					execute(struct s_proc *p, struct s_vm *vm);

/*
** font.c
*/

int					**load_font(void);

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
void				destroy(struct s_vm *vm);

/*
** tools.c
*/

void				reverse(unsigned int *a);
void				load_vm(void) __attribute__((constructor));

/*
** process.c
*/

void				create_processes(struct s_vm *vm);
void				kill_process(struct s_proc **proc, struct s_vm *vm,
		struct s_proc *last);
void				fork_process(struct s_vm *vm, struct s_proc *proc,
		int param);
struct s_proc		*fresh_process(int pn, int pc, struct s_vm *vm);

void				draw_line(struct s_pos s, struct s_pos e, int col,
		struct s_vdata *data);
int					draw_char(unsigned char c, struct s_pos p, int co,
		struct s_vdata *data);
int					draw_str(char *str, struct s_pos p, int color,
		struct s_vdata *data);
int					draw_score(struct s_pos p, int value, int color,
		struct s_vdata *data);

void				generate_borders(struct s_vdata *data);
void				generate_arena(struct s_vdata *data, struct s_vm *vm);
void				generate_processes(struct s_vdata *data,
		struct s_proc *proc, int x, int y);
void				generate_toolbar(struct s_vdata *data, struct s_vm *vm,
		int last_frame);
int					draw_process_count(struct s_vdata *data, struct s_vm *vm,
		int y);

#endif
