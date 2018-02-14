/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/07 17:17:41 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/07 17:17:41 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/Includes/libft.h"
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>

# define S_IXUGO (S_IXUSR | S_IXGRP | S_IXOTH)

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              cd_minishell.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void	ft_cd_env(char **envp);
int		ft_cd_error(char **cmd);
void	ft_modif_cd(char **cmd, char **envp);
void	ft_cd_minishell(char **cmd, char **envp);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              echo_minishell.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void	ft_echo_env(char **envp, char *str);
int		ft_option_echo(char **cmd, char **option);
void	ft_echo_minishell(char **cmd, char **envp);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              env_minishell.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void	ft_print_env(char **envp);
int		ft_error_setenv(char **cmd);
char	**ft_setenv(char **envp, char **cmd);
void	ft_unsetenv(char **envp, char **cmd);
int		ft_fill_setenv(char **cmd, char **ret, char *env);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              exe_minishell.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char	**ft_find_path(char **environ);
char	*ft_find_path_exe(char **env, char *exe);
int		ft_exe_special_cmd(char **cmd, char ***envp);
void	ft_exec_cmd(char **cmd, char **envp, char *path_exe, int check);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                             tools_minishell.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int		ft_tablen(char **tab);
void	ft_free_tab(char ***tab);
char	**ft_cpy_envp(char **envp);
char	**ft_split_cmd(const char *s, char c);
char	*ft_find_line_env(char **envp, char *path);

#endif
