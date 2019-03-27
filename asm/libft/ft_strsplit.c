/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/22 18:25:43 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/24 12:06:08 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int			count_words(const char *s, char c)
{
	int count;

	count = 1;
	while (*s)
	{
		if (*s && *s == c)
		{
			count++;
			while (*s && *s == c)
				s++;
			continue;
		}
		s++;
	}
	return (count);
}

static char			*get_wordcpy(const char *s, char c)
{
	int		length;

	length = 0;
	while (s[length] && s[length] != c)
		length++;
	return (ft_strndup(s, length));
}

static void			copy_words(char **split, const char *trim, char c)
{
	*(split++) = get_wordcpy(trim, c);
	while (*trim)
	{
		if (*trim == c)
		{
			while (*trim == c)
				trim++;
			*(split++) = get_wordcpy(trim, c);
			continue ;
		}
		trim++;
	}
	*split = NULL;
}

char				**ft_strsplit(const char *s, char c)
{
	char	**split;
	char	*trim;
	int		words_count;

	trim = ft_strctrim(s, c);
	if (!s || !trim)
		return (NULL);
	if (*trim == '\0')
	{
		if (!(split = (char**)malloc(sizeof(char*))))
			return (NULL);
		*split = NULL;
		free(trim);
		return (split);
	}
	words_count = count_words(trim, c);
	if ((split = (char**)malloc(sizeof(char*) * (words_count + 1))) == NULL)
	{
		free(trim);
		return (NULL);
	}
	copy_words(split, trim, c);
	free(trim);
	return (split);
}
