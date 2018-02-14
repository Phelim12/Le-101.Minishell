/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env_minishell.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/14 15:44:26 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/14 15:44:26 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int		ft_error_setenv(char **cmd)
{
	if (cmd[2] == NULL || cmd[3] != NULL)
	{
		ft_putendl_fd("setenv: needs two arguments", 2);
		ft_putendl_fd("usage: setenv [NAME] [CONTENT]", 2);
		return (1);
	}
	return (0);
}

void	ft_print_env(char **envp)
{
	int y;

	y = -1;
	ft_sort_tab_ascii(&envp);
	while (envp[++y])
	{
		if (ft_strchr(envp[y], '=')[1] != 0)
			ft_putendl(envp[y]);
	}
}

char	**ft_setenv(char **envp, char **cmd)
{
	char	**ret;
	int		check;
	int		y;

	y = -1;
	check = 0;
	if (ft_error_setenv(cmd))
		return (envp);
	ret = (char **)malloc(sizeof(char *) * (ft_tablen(envp) + 3));
	while (envp[++y])
	{
		if (check == 0)
			check = ft_fill_setenv(cmd, &ret[y], envp[y]);
		else
			ft_fill_setenv(cmd, &ret[y], envp[y]);
	}
	if (check == 0)
		ft_fill_setenv(cmd, &ret[y], envp[y]);
	ret[++y] = NULL;
	ft_free_tab(&envp);
	return (ret);
}

int		ft_fill_setenv(char **cmd, char **ret, char *env)
{
	char	*add;
	int		check;

	check = 0;
	add = ft_strjoin(cmd[1], "=");
	if (env == NULL)
		*ret = ft_strjoin(add, cmd[2]);
	else if (ft_strncmp(env, add, ft_strlen(add)) == 0 &&
		ft_strcmp(cmd[1], "PATH") == 0 && env[5])
	{
		check = 1;
		free(add);
		add = ft_strjoin(env, ":");
		*ret = ft_strjoin(add, cmd[2]);
	}
	else if (ft_strncmp(env, add, ft_strlen(add)) == 0)
	{
		check = 1;
		*ret = ft_strjoin(add, cmd[2]);
	}
	else
		*ret = ft_strdup(env);
	free(add);
	return (check);
}

void	ft_unsetenv(char **envp, char **cmd)
{
	char	*join;
	int		y;
	int		x;

	y = 0;
	if (cmd[1] == NULL)
	{
		ft_putendl_fd("setenv: needs two argument minimum", 2);
		ft_putendl_fd("usage: setenv [ENV1] [ENV2] [...]", 2);
	}
	while (cmd[++y])
	{
		x = -1;
		join = ft_strjoin(cmd[y], "=");
		while (envp[++x])
		{
			if (ft_strncmp(envp[x], join, ft_strlen(join)) == 0)
			{
				free(envp[x]);
				envp[x] = ft_strdup(join);
			}
		}
		ft_strdel(&join);
	}
}
