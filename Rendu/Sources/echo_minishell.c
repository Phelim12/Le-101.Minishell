/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   echo_minishell.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/09 16:58:49 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/09 16:58:49 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int		ft_option_echo(char **cmd, char **option)
{
	int		y;
	int		x;

	x = 0;
	y = 1;
	(*option) = ft_strnew(5);
	while (cmd[y] &&
		(!(ft_strcmp(cmd[y], "-e")) || !(ft_strcmp(cmd[y], "-n")) ||
		!(ft_strcmp(cmd[y], "-en")) || !(ft_strcmp(cmd[y], "-ne"))))
	{
		if (!(ft_strchr((*option), 'e')) && ft_strchr(cmd[y], 'e'))
			(*option)[x++] = 'e';
		if (!(ft_strchr((*option), 'n')) && ft_strchr(cmd[y], 'n'))
			(*option)[x++] = 'n';
		y++;
	}
	return (y);
}

void	ft_echo_env(char **envp, char *str)
{
	char	*env;
	int		a;
	int		b;

	a = -1;
	env = ft_strnew(ft_strlen(str) + 2);
	while (str[++a])
	{
		if (str[a] == '$' && str[a - 1] != 92)
		{
			b = 0;
			while (ft_isalpha(str[++a]) || str[a] == '_')
				env[b++] = str[a];
			env[b] = 0;
			ft_strcat(env, "=\0");
			ft_putstr(ft_find_line_env(envp, env));
		}
		ft_putchar(str[a]);
	}
	ft_strdel(&env);
}

void	ft_echo_minishell(char **cmd, char **envp)
{
	char	*option;
	int		add;
	int		y;

	y = ft_option_echo(cmd, &option);
	while (cmd[y])
	{
		add = 0;
		if (cmd[y][0] == '~')
		{
			ft_putstr(ft_find_line_env(envp, "HOME="));
			add = 1;
		}
		if (ft_strchr(cmd[y], '$'))
			ft_echo_env(envp, (cmd[y] + add));
		else if (cmd[y + 1] == NULL)
			ft_printf("%s", (cmd[y] + add));
		else
			ft_printf("%s ", (cmd[y] + add));
		y++;
	}
	if (!(ft_strchr(option, 'n')))
		ft_putchar('\n');
	ft_strdel(&option);
}
