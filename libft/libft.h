/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 17:46:19 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/04/11 16:25:34 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/ioctl.h>
# include "vector/vector.h"

# ifdef LEAK_DEBUG

#  include "leakfinder.h"

# endif

typedef	unsigned long int	t_longword;
typedef	unsigned char		t_byte;
typedef	int					t_bool;
typedef unsigned short		t_ushort;
typedef unsigned short		t_ush;
typedef	unsigned long		t_ulong;
typedef	unsigned long long	t_ullong;
typedef	unsigned int		t_uint;
typedef long double			t_ld;
typedef long long			t_llong;

# define FT_LWSIZ		8
# define FT_TRUE		1
# define FT_FALSE		0
# define FT_INFINITE	!0
# define FT_IN			0
# define FT_OUT			1
# define FT_ERR			2
# define FT_BUFSIZ		64

# define REPEAT_ONE		0x0101010101010101UL
# define BLACK_HOLE		0x8080808080808080UL

# define BOLD			0x1
# define UNDERLINE		0x2
# define BLINK			0x4
# define REVERSE		0x8

# define K_UP			0x415b1b
# define K_DOWN			0x425b1b
# define K_LEFT			0x445b1b
# define K_RIGHT		0x435b1b
# define K_ENTER		10
# define K_DEL			0x7e335b1b
# define K_BACKSP		127
# define K_ESC			27
# define K_TAB			9
# define K_TILD			126
# define K_SPACE		32
# define K_F1			0x504f1bL
# define K_F2			0x514f1bL
# define K_F3			0x524f1bL
# define K_F4			0x534f1bL
# define K_F5			0x7e35315b1bL
# define K_F6			0x7e37315b1bL
# define K_F7			0x7e38315b1bL
# define K_F8			0x7e39315b1bL
# define K_F9			0x7e30325b1bL
# define K_F10			0x7e31325b1bL
# define K_F12			0x7e34325b1bL

# define CTRL_A			1
# define CTRL_B			2
# define CTRL_C			3
# define CTRL_D			4
# define CTRL_E			5
# define CTRL_F			6
# define CTRL_G			7
# define CTRL_H			8
# define CTRL_I			9
# define CTRL_J			10
# define CTRL_K			11
# define CTRL_L			12
# define CTRL_M			13
# define CTRL_N			14
# define CTRL_O			15
# define CTRL_P			16
# define CTRL_Q			17
# define CTRL_R			18
# define CTRL_S			19
# define CTRL_T			20
# define CTRL_U			21
# define CTRL_V			22
# define CTRL_W			23
# define CTRL_X			24
# define CTRL_Y			25
# define CTRL_Z			26

/*
** pour la fonction ft_sort_array
*/

typedef	struct		s_sortdata
{
	size_t	l1;
	size_t	l2;
	int		(*cmp)(void *a, void *b);
}					t_sortdata;

/*
** Pour ft_getline_mfd
*/

typedef struct		s_file
{
	char			pline[FT_BUFSIZ + 1];
	int				fd;
	struct s_file	*next;
}					t_file;

/*
** Pour ft_get_options
*/

typedef struct		s_ft_options
{
	char				*name;
	char				*value;
	struct s_ft_options	*next;
	int					sname;
}					t_ft_options;

/*
** Partie 1
*/

void				*ft_realloc(void *ptr, int plen, int nlen);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *dst, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memrcpy(void *dst, const void *src, size_t n);
void				*ft_mempcpy(void *dst, const void *src, size_t n);
void				*ft_memrchr(const void *dst, int c, size_t n);
void				*ft_memdup(void *srcaddr, size_t size);
int					ft_memcrrepall(char *s, int c, int replace, int size);

size_t				ft_strlen(const char *s);
size_t				ft_strnlen(const char *s, size_t max);
char				*ft_strdup(const char *s);
char				*ft_strndup(const char *s, size_t len);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t len);
size_t				ft_strlcat(char *s1, const char *s2, size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
								size_t len);
void				ft_strclr(char *s);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strjpath(const char *s1, const char *s2);
char				*ft_strtrim(const char *s);
char				*ft_ltrim(const char *s);
char				*ft_strctrim(const char *s, char c);
char				*ft_strtolower(char *s);
char				*ft_strtoupper(char *s);
char				**ft_strsplit(const char *s, char c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t len);
char				*ft_strnfcat(char **s1, const char *s2, size_t size);
char				*ft_strfcat(char **s1, const char *s2);

t_uint				ft_atoi_hexa(const char *s);
t_uint				ft_atoi_octal(const char *s);
int					ft_atoi(const char *s);
long				ft_atol(const char *s);
char				*ft_itoa(int n);
char				*ft_ltoa(long n);

void				ft_swap(void *a, void *b, size_t size);
void				ft_swap_ptr(char **ptr1, char **ptr2);

int					ft_isspace(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isnumeric(const char *s);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_ishexa(int c, int maj);
int					ft_isoctal(int c);

void				ft_putbin(long n, size_t size, t_uint lf);
void				ft_putc(char c);
void				ft_puts(const char *s);
void				ft_putendl(const char *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(const char *s, int fd);

char				*ft_crep(char *s, int c, int replace);
size_t				ft_crepall(char *s, int c, int replace);
char				*ft_crrep(char *s, int c, int replace);
char				*ft_strrep(const char *s, const char *search,
						const char *replace);
char				*get_fd_contents(int fd, int *len);
char				*get_file_contents(const char *file);
int					ft_getline_mfd(const int fd, char **line);
int					ft_getline(const int fd, char *line, size_t size);
void				ft_sort(void *a1, size_t elemsiz, size_t len,
						int (*cmp)(void *a, void *b));

int					ft_isset_option(const char *s, t_ft_options *o);
char				*ft_get_opt_value(const char *s, t_ft_options *o);
t_ft_options		*ft_get_options(int ac, char **av);
void				ft_print_options(t_ft_options *opt);
void				ft_free_options(t_ft_options **opt);

char				*ft_free_strarray(char **a);

void				*free_arg1_arg2_and_return_arg3(void *a, void *b, void *c);
void				assign_null_2a(void **a1, void **a2);
int					get_next_line(const int fd, char **line);

int					ft_printf(const char *fmt, ...);

/*
** =======================================================
**  : : : : : : : : : : : libterm/ : : : : : : : : : : : :
** =======================================================
*/

/*
** libterm.c
*/

int					term_noecho_2(void);
int					term_noecho(int	stat);
int					term_putc(int c);
int					term_init(void);
void				term_get_size(int *col, int *row);

/*
** color.c
*/

void				term_color_reset(void);
void				term_set_color(int color);

/*
** video_mode.c
*/

void				term_set_bold(void);
void				term_set_underline(void);
void				term_set_blink(void);
void				term_set_reverse(void);

/*
** cursor.c
*/

void				term_move_to_line_start(void);
void				term_save_cursor(void);
void				term_restore_cursor(void);
void				term_move_cursor_right_n(int n);
void				term_move_cursor_right(void);
void				term_move_cursor_left(void);
void				term_move_cursor_up_n(int n);
void				term_move_cursor_up(void);
void				term_move_cursor_down_n(int n);
void				term_move_cursor_down(void);
void				term_move_cursor(int col, int row);
void				term_hide_cursor(void);
void				term_display_cursor(void);
void				term_get_cursor(int *col, int *raw);

/*
** screen.c
*/

void				term_clear(void);
void				term_clear_after(void);
void				term_clear_before(void);

/*
** keys.c
*/

int					get_key(int c);
int					get_key2(long c);

#endif
