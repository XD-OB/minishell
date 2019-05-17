/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:14:17 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/17 07:50:21 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			init_minishell(t_minishell *ms, char **envp)
{
	ms->envp = copy_2_char(envp);
	ms->status = 0;
	ms->last_ret = 0;
	ms->sig_int = 0;
	ms->old = signal(SIGINT, handler_sigint);
}

void				free_ms(t_minishell *ms)
{
	if (ms->cmd)
		free_tabstr(&(ms->cmd));
	free_tabstr(&(ms->envp));
}

int					main(int ac, char **av, char **envp)
{
	t_minishell		ms;
	char			*line;

	init_minishell(&ms, envp);
	while (ac)
	{
		if (!ms.sig_int)
			display_prompt(ms.envp);
		ms.sig_int = 0;
		get_next_line(0, &line);
		ft_trimstr(&line);
		ms.cmd = cmdsplit(line);
		free(line);
		ms.i = -1;
		while (ms.cmd[++(ms.i)])
			if (cmd_lancher(ac, av, &ms, &(ms.envp)))
			{
				free_ms(&ms);
				return (1);
			}
		free_tabstr(&(ms.cmd));
	}
	free_ms(&ms);
	return (EXIT_SUCCESS);
}
