/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_minishell.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/10 16:32:19 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/10 16:32:19 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char ***tab)
{
	int y;

	y = -1;
	if (!(*tab))
		return ;
	while ((*tab)[++y])
		ft_strdel(&(*tab)[y]);
	if ((*tab))
		free(*tab);
}

int		ft_tablen(char **tab)
{
	int	y;

	y = 0;
	while (tab[y])
		y++;
	return (y);
}

char	*ft_find_line_env(char **envp, char *path)
{
	int y;

	y = -1;
	while (envp[++y])
	{
		if (ft_strncmp(envp[y], path, (ft_strlen(path) - 1)) == 0)
			return (ft_strchr(envp[y], '=') + 1);
	}
	return (NULL);
}

char	**ft_cpy_envp(char **envp)
{
	char	**ret;
	int		y;

	y = 0;
	ret = (char **)malloc(sizeof(char *) * (ft_tablen(envp) + 5));
	while (envp[y])
	{
		if (ft_strncmp(envp[y], "SHELL=", 4) == 0)
			ret[y] = ft_strjoin("SHELL=", "minishell");
		else if (ft_strncmp(envp[y], "_=/", 3) == 0)
			ret[y] = ft_strdup("_=./minishell/env");
		else
			ret[y] = ft_strdup(envp[y]);
		y++;
	}
	ret[y] = NULL;
	return (ret);
}
