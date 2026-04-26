/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:23:48 by moabed            #+#    #+#             */
/*   Updated: 2026/04/26 13:26:34 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/execution-part.h"

volatile sig_atomic_t	global_sig = 0;

void	shell_protection(void)
{
	if (!isatty(STDIN_FILENO))
		exit(3);
	if (!isatty(STDOUT_FILENO))
		exit(3);
}

int	shell_init(char **env, t_exec *shell)
{
	shell_protection();
	shell->envp = env;
	shell->first_env_node = env_init(env);
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

void	unset_2(t_env **head, char *name)
{
	t_env	**curr;
	t_env	*tmp;
	int		len;

	len = ft_strlen(name);
	curr = head;
	while (*curr)
	{
		if (!ft_strncmp((*curr)->variable, name, len)
			&& (*curr)->variable[len] == '=')
		{
			tmp = *curr;
			*curr = (*curr)->next;
			free(tmp->variable);
			free(tmp);
			return ;
		}
		curr = &((*curr)->next);
	}
}

// char    **list_to_array(t_env *env)
// {
// 	int size;
// 	char **envp;
// 	t_env   *ptr;
// 	int i;

// 	i = 0;
// 	size = 0;
// 	ptr = env;
// 	while(ptr)
// 	{
// 		size++;
// 		ptr = ptr->next;
// 	}
// 	envp = malloc(sizeof(char *) * (size+1));
// 	if(!envp)
// 		return (NULL);
// 	while(env)
// 	{
// 		envp[i] = ft_strdup(env->variable);
// 		env = env->next;
// 		i++;
// 	}
// 	envp[i] = NULL;
// 	return(envp);
// }
