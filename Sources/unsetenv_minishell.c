/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unsetenv_minishell.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/10 16:42:09 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/10 16:42:09 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

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