/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_minishell.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/08 14:40:13 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/08 14:40:13 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char ***tab)
{
	int y;

	y = -1;
	while ((*tab)[++y])
		free((*tab)[y]);
	free(*tab);
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

int		ft_exe_special_cmd(char **cmd, char **envp)
{
	if (ft_strcmp("cd", cmd[0]) == 0)
		ft_cd_minishell(cmd, envp);
	else if (ft_strcmp("env", cmd[0]) == 0)
		ft_puttab(envp);
	else if (ft_strcmp("echo", cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("setenv", cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("unsetenv", cmd[0]) == 0)
		return (1);
	else 
		return (0);
	return (1);
}

char	**ft_find_path(char **environ)
{
	char	**ret;
	char	*tmp;
	int		a;
			
	a = 0;
	while (ft_strncmp("PATH=", environ[a], 5) != 0)
		a++;
	ret = ft_strsplit(environ[a], ':');
	tmp = ft_strdup(ret[0]);
	ft_strdel(&ret[0]);
	ret[0] = ft_strsub(tmp, 5, (ft_strlen(tmp) - 5));
	a = -1;
	while (ret[++a])
	{
		tmp = ft_strjoin(ret[a], "/");
		ft_strdel(&ret[a]);
		ret[a] = ft_strdup(tmp);
	}
	return (ret);
}

char		*ft_find_path_exe(char **env, char *exe)
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

void	ft_exec_cmd(char **cmd, char **envp, char *path_exe)
{
	char	**path_env;
	
	if (!(path_exe))
	{
		path_env = ft_find_path(envp);
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
}

int		main(int argc, const char **argv, char **envp)
{
	t_stat	statbuf;
	char	**cmd;
	char	*line;

	ft_printf("$> ");
	get_next_line(0, &line);
	while(ft_strncmp("exit\0", line, 5) != 0)	
	{
		cmd = ft_strsplit(line, 32);
		if (cmd[0] && stat(cmd[0], &statbuf) != -1 && 
			S_ISREG(statbuf.st_mode) && (S_IXUGO & statbuf.st_mode))
			ft_exec_cmd(cmd, envp, cmd[0]);
		else if (cmd[0] && ft_exe_special_cmd(cmd, envp) == 0)
			ft_exec_cmd(cmd, envp, NULL);
		ft_printf("$> ");
		ft_strdel(&line);
		get_next_line(0, &line);
	}
	return 0;
}

