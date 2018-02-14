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

void	ft_exit(char **line, char ***environ)
{
	ft_strdel(line);
	ft_putendl("exit");
	ft_free_tab(environ);
}

int		ft_argc_minishell(int argc, char **argv)
{
	char	*line;

	get_next_line(-1, &line);
	if (argc == 1)
		return (0);
	else
	{
		ft_putendl_fd("minishell: don't need option(s)", 2);
		ft_putendl_fd("usage: ", 2);
		ft_putendl_fd(argv[0], 2);
		return (1);
	}
}

int		main(int argc, char **argv, char **envp)
{
	char	**environ;
	t_stat	statbuf;
	char	**cmd;
	char	*line;

	environ = ft_cpy_envp(envp);
	if (ft_argc_minishell(argc, argv))
		return (0);
	while (1)
	{
		ft_printf("$> ");
		get_next_line(0, &line);
		if (ft_strncmp("exit\0", line, 5) == 0)
			break ;
		cmd = ft_split_cmd(line, 32);
		if (cmd[0] && stat(cmd[0], &statbuf) != -1 &&
			S_ISREG(statbuf.st_mode) && (S_IXUGO & statbuf.st_mode))
			ft_exec_cmd(cmd, environ, cmd[0], 1);
		else if (cmd[0] && ft_exe_special_cmd(cmd, &environ) == 0)
			ft_exec_cmd(cmd, environ, NULL, 0);
		ft_free_tab(&cmd);
		ft_strdel(&line);
	}
	ft_exit(&line, &environ);
	return (0);
}
