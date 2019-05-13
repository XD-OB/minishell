/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 23:17:09 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/12 23:38:33 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../../minishell.h"

/*
**		echo functions:
*/

void			print_ee(char *str, t_echo echo);
int				print_var(char **envp, char *var);
void			ft_print_sbslch(char *str);

/*
**		setenv functions:
*/

void		affect_chars(char **s1, char **s2, char *val1, char *val2);
void		triple_free(char **s1, char **s2, char **s3);
void		free_tabstr(char ***tab);
void		show_env(char **envp);
int			len_tab(char **tab);

#endif
