/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd_minishell.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/08 20:14:42 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/08 20:14:42 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd_error(char **cmd)
{
	if (cmd[1] && cmd[2] && cmd[3])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(cmd[1], 2);
		return (1);
	}
	return (0);
}

void	ft_cd_env(char **envp)
{
	char	buf[1024];
	char	*tmp;
	int		y;

	y = -1;
	getcwd(buf, 1024);
	while (envp[++y])
		if (ft_strncmp(envp[y], "OLDPWD=", 7) == 0)
		{
			tmp = ft_strjoin("OLDPWD=", ft_find_line_env(envp, "PWD=/"));
			ft_strdel(&envp[y]);
			envp[y] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	y = -1;
	while (envp[++y])
		if (ft_strncmp(envp[y], "PWD=", 4) == 0)
		{
			tmp = ft_strjoin("PWD=", (char *)buf);
			ft_strdel(&envp[y]);
			envp[y] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
}

void	ft_modif_cd(char **cmd, char **envp)
{
	char	*home;
	char	*str;
	int		y;

	y = -1;
	home = ft_find_line_env(envp, "HOME=/");
	str = ft_strnew(ft_strlen(cmd[1]) + ft_strlen(home) + 2);
	while (cmd[1][++y])
	{
		if (cmd[1][y] == '~')
		{
			ft_strcat(str, home);
			ft_strcat(str, (ft_strchr(cmd[1], '~') + 1));
			break ;
		}
		str[y] = cmd[1][y];
	}
	free(cmd[1]);
	cmd[1] = ft_strdup(str);
	free(str);
}

void	ft_cd_minishell(char **cmd, char **envp)
{
	if (cmd[1] && ft_strchr(cmd[1], '~'))
		ft_modif_cd(cmd, envp);
	if (!(cmd[1]))
	{
		cmd[1] = ft_strdup(ft_find_line_env(envp, "HOME=/"));
		cmd[2] = NULL;
	}
	if (!(ft_cd_error(cmd)))
	{
		if (ft_strcmp("-", cmd[1]) == 0)
		{
			free(cmd[1]);
			cmd[1] = ft_strdup(ft_find_line_env(envp, "OLDPWD=/"));
			if (cmd[1])
				ft_putendl(cmd[1]);
		}
		if (chdir(cmd[1]) == -1)
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putendl_fd(cmd[1], 2);
		}
		else
			ft_cd_env(envp);
	}
}
