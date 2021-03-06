/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:52:28 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/05/03 18:43:12 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_first_node(t_env *first, t_env **env)
{
	*env = first->next;
	free(first->varname);
	free(first->varvalue);
	free(first);
}

static void	unset_variable(t_arg *varname)
{
	t_env	**env;
	t_env	*iter;
	t_env	*free_node;

	env = get_env(NULL);
	if (fetch_env_var_value(varname->value) == NULL)
		return ;
	iter = *env;
	if (ft_strcmp(iter->varname, varname->value) == 0)
		return (unset_first_node(iter, env));
	while (iter->next != NULL)
	{
		if (ft_strcmp(iter->next->varname, varname->value) == 0)
		{
			free_node = iter->next;
			iter->next = free_node->next;
			free(free_node->varvalue);
			free(free_node->varname);
			free(free_node);
			return ;
		}
		iter = iter->next;
	}
}

bool	cmd_unset(t_exec_block *cmd_unset)
{
	t_arg	*iter;
	int		exit_status;

	exit_status = 0;
	iter = cmd_unset->arg;
	while (iter != NULL)
	{
		if (ft_strchr(iter->value, '=') != NULL)
		{
			handle_error("\e[46m\e[1;91mMi[shell]in: unset: your unsetting \
is unsettling 👹\e[0m\n", 0);
			exit_status = EXIT_STD_ERROR;
		}
		else
			unset_variable(iter);
		iter = iter->next;
	}
	g_exit_status = exit_status;
	if (exit_status == 0)
		return (false);
	else
		return (true);
}
