/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:26:15 by shathaamarn       #+#    #+#             */
/*   Updated: 2026/05/05 16:44:38 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/parsingpart.h"

int	arg_count(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

int	add_arg(t_cmd *cmd, char *value)
{
	char	**new_args;
	int		i;
	int		count;

	count = arg_count(cmd->args);
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (0);
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(value);
	if (!new_args[i])
		return (0);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (1);
}

static int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != PIPE && tokens->type != END)
	{
		if (is_redir(tokens->type))
		{
			if (tokens->next)
				tokens = tokens->next->next;
			else
				tokens = NULL;
		}
		else
		{
			count++;
			tokens = tokens->next;
		}
	}
	return (count);
}

static char	**free_args_return(char **args)
{
	free_args(args);
	return (NULL);
}

char	**fill_args(t_token *tokens)
{
	char	**args;
	int		count;
	int		i;

	count = count_args(tokens);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens && tokens->type != PIPE && tokens->type != END)
	{
		if (is_redir(tokens->type))
		{
			if (tokens->next)
				tokens = tokens->next->next;
			else
				tokens = NULL;
		}
		else
		{
			args[i] = ft_strdup(tokens->value);
			if (!args[i])
	            return (free_args_return(args));
			i++;
			tokens = tokens->next;
		}
	}
	args[i] = NULL;
	return (args);
}

