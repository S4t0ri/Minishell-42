/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satori <satori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:51:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/04/11 19:44:26 by satori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("Error: pwd");
		g_exit_status = 2;
	}
	else
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_exit_status = 0;
	}
	free(cwd);
}
