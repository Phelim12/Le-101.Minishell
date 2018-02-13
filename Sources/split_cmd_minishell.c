/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split_cmd_minishell.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/09 16:03:45 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/09 16:03:45 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_words(const char *s, char c)
{
	int nb_words;

	nb_words = 0;
	while (*s)
		if (*s++ == c)
			nb_words++;
	return (nb_words + 2);
}

static int	ft_lenchr(const char *s, char c, int *x)
{
	int s_x;

	s_x = (*x);
	while (s[(*x)] != c && s[(*x)] != '\0')
		(*x)++;
	return ((*x) - s_x);
}

char		**ft_split_cmd(const char *s, char c)
{
	char	**tab;
	int		x;
	int		a;

	a = 0;
	x = 0;
	if (!s)
		return (NULL);
	if (!(tab = malloc(sizeof(char *) * (ft_count_words(s, c) + 5))))
		return (NULL);
	while (s[x])
	{
		while (s[x] == c)
			x++;
		if (s[x] == 34 && ++x)
			tab[a++] = ft_strsub(s, x, ft_lenchr(s, 34, &x));
		else if (s[x] != '\0')
			tab[a++] = ft_strsub(s, x, ft_lenchr(s, c, &x));
		if (s[x] == 34)
			x++;
	}
	tab[a] = NULL;
	return (tab);
}
