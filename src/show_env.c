/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 20:24:57 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 04:07:46 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		show_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_putendl(envp[i]);
		i++;
	}
}

int			adv_show_env(char **envp, t_env *env, int len_t)
{
	int		i;

	if (len_t == 0)
	{
		show_env(envp);
		return (1);
	}
	if (len_t == 1 && env->null && !env->i && !env->u)
	{
		i = 0;
		while (envp[i])
			ft_putstr(envp[i++]);
		ft_putchar('\n');
		return (1);
	}
	if (len_t == 1 && env->i)
		return (1);
	return (0);
}
