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
**┃           This structure is a coordinate (ordinate and abscissa)           ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/



/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                             main_minishell.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		ft_free_tab(char ***tab);
char		**ft_find_path(char **environ);
char		*ft_find_path_exe(char **env, char *exe);
char		*ft_find_line_env(char **envp, char *path);
int			ft_exe_special_cmd(char **cmd, char **envp);
void	ft_exec_cmd(char **cmd, char **envp, char *path_exe);


/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              cd_minishell.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			ft_cd_error(char **cmd);
void		ft_cd_env(char **envp, char *path);
void		ft_modif_cd(char **cmd, char **envp);
void		ft_cd_minishell(char **cmd, char **envp);

#endif
