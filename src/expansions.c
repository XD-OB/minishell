/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 22:58:26 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/22 23:08:16 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	i:		0: i		1: j
*/

void			replace_tilda(t_minishell *ms)
{
	char		*a_cmd;
	int			len_cmd;
	int			len_home;
	int			i[2];
	int			k;

	len_cmd = ft_strlen(ms->cmd);
	len_home = ft_strlen(ms->home);
	a_cmd = ft_strnew(len_home + len_cmd - 1);
	i[0] = 0;
	k = 0;
	while (i[0] < len_cmd)
	{
		if (ms->cmd[i[0]] == '~')
		{
			i[0]++;
			i[1] = 0;
			while (i[1] < len_home)
				a_cmd[k++] = ms->home[i[1]++];
		}
		a_cmd[k++] = ms->cmd[i[0]++];
	}
	(ms->cmd_freable) ? free(ms->cmd) : (ms->cmd_freable = 1);
	ms->cmd = a_cmd;
}

int				found_expans(t_minishell *ms)
{
	if (!ft_strcmp(ms->cmd, "cd"))
	{
		ms->cmd = ft_strdup("cd ~");
		ms->cmd_freable = 1;
	}
	if (ft_strchr(ms->cmd, '~'))
		replace_tilda(ms);
	if (ft_strchr(ms->cmd, '='))
		if (!affect_vars(ms))
			return(1);
	if (ft_strchr(ms->cmd, '$'))
		replace_dollar(ms);
	if (wildcard(ms))
		return(1);
	return (0);
}
