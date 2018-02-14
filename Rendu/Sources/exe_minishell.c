/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exe_minishell.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/14 15:46:30 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/14 15:46:30 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exe_special_cmd(char **cmd, char ***envp)
{
	if (ft_strcmp("cd", cmd[0]) == 0)
		ft_cd_minishell(cmd, *envp);
	else if (ft_strcmp("env", cmd[0]) == 0)
		ft_print_env(*envp);
	else if (ft_strcmp("echo", cmd[0]) == 0)
		ft_echo_minishell(cmd, *envp);
	else if (ft_strcmp("setenv", cmd[0]) == 0)
		(*envp) = ft_setenv(*envp, cmd);
	else if (ft_strcmp("unsetenv", cmd[0]) == 0)
		ft_unsetenv(*envp, cmd);
	else
		return (0);
	return (1);
}

void	ft_modif_env(char **envp)
{
	int	add;
	int	y;

	y = -1;
	add = 0;
	while (envp[++y])
	{
		if (ft_strchr(envp[y], '=')[1] == 0)
			add++;
		if (add > 0)
		{
			free(envp[y]);
			if (envp[y + add])
				envp[y] = ft_strdup(envp[y + add]);
		}
	}
	envp[y - add] = NULL;
}

char	*ft_find_path_exe(char **env, char *exe)
{
	t_stat	statbuf;
	char	*join;
	int		check;
	int		a;

	a = -1;
	check = 0;
	while (env[++a])
	{
		join = ft_strjoin(env[a], exe);
		check = stat(join, &statbuf);
		if (check == 0)
			return (join);
		ft_strdel(&join);
	}
	return (NULL);
}

char	**ft_find_path(char **environ)
{
	char	**ret;
	char	*tmp;
	int		a;

	a = 0;
	while (environ[a] && ft_strncmp("PATH=", environ[a], 5) != 0)
		a++;
	if (environ[a] == NULL)
		return (NULL);
	tmp = ft_strsub(environ[a], 5, (ft_strlen(environ[a]) - 5));
	if (ft_strchr(tmp, ':') == NULL)
		ret = ft_strsplit(tmp, '=');
	else
		ret = ft_strsplit(tmp, ':');
	ft_strdel(&tmp);
	a = -1;
	while (ret[++a])
	{
		tmp = ft_strjoin(ret[a], "/");
		ft_strdel(&ret[a]);
		ret[a] = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	return (ret);
}

void	ft_exec_cmd(char **cmd, char **envp, char *path_exe, int check)
{
	char	**path_env;

	ft_modif_env(envp);
	if (!(path_exe))
	{
		if ((path_env = ft_find_path(envp)))
			path_exe = ft_find_path_exe(path_env, cmd[0]);
		ft_free_tab(&path_env);
	}
	if (path_exe)
	{
		ft_strdel(&cmd[0]);
		cmd[0] = ft_strdup(path_exe);
		if (fork() == 0)
			execve(path_exe, cmd, envp);
		else
			wait(NULL);
	}
	else
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
	}
	if (check == 0)
		ft_strdel(&path_exe);
}
