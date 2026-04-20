/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:23:48 by moabed            #+#    #+#             */
/*   Updated: 2026/04/20 11:48:37 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

void	shell_protection(void)
{
	if (!isatty(STDIN_FILENO))
		exit(3);
	if (!isatty(STDOUT_FILENO))
		exit(3);
}

int	shell_init(char **env,t_exec *shell)
{
	volatile sig_atomic_t global_sig = 0;
	shell_protection();
	interactive_signals();
	shell->first_env_node =  env_init(env);
	if (!shell->first_env_node)
		return (1);
	shell->last_status = 0;
	return (0);
}

void	free2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char    **list_to_array(t_env *env)
{
	int size;
	char **envp;
	t_env   *ptr;
	int i;

	i = 0;
	size = 0;
	ptr = env;
	while(ptr)
	{
		size++;
		ptr = ptr->next;
	}
	envp = malloc(sizeof(char *) * (size+1));
	if(!envp)
		return (NULL);
	while(env)
	{
		envp[i] = ft_strdup(env->variable);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return(envp);
}
void	ruin_everything(t_cmd *cmds_list)
{
	//postponed until i know from partner how its malloc'd
}