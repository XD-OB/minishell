/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:18:53 by obelouch          #+#    #+#             */
/*   Updated: 2019/05/10 22:27:56 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		msg_error(char *msg, int n)
{
	ft_putstr_fd(msg, 2);
	exit(n);
}

void		free_tabstr(char ***tab)
{
	int		i;

	i = -1;
	while ((*tab)[++i])
		free((*tab)[i]);
	free(*tab);
}

int			len_tab(char **tab)
{
	int		len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

pid_t		create_process(void)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid != -1)
		return (child_pid);
	write(2, "fork: Error\n", 12);
	exit(EXIT_FAILURE);
}

void		triple_free(char **s1, char **s2, char **s3)
{
	free(*s1);
	free(*s2);
	free(*s3);
}

int			well_quoted(char *str)
{
	int		d_quote;
	int		s_quote;
	int		i;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (str[i])
	{
		if (str[i] == 34)
			d_quote++;
		if (str[i] == 39)
			s_quote++;
		i++;
	}
	if (!(s_quote % 2) && !(d_quote % 2))
		return (1);
	return (0);
}
