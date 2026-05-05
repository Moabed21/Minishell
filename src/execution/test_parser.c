/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 18:30:00 by moabed            #+#    #+#             */
/*   Updated: 2026/04/29 18:30:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executionpart.h"

/*
** TEMPORARY test parser — delete when real parser is ready.
** Supports: simple cmds, pipes, >, >>, <
** Does NOT support: quotes, $vars, heredoc, escaping
*/

static int	count_args(char **tokens, int start)
{
	int	count;

	count = 0;
	while (tokens[start] && ft_strcmp(tokens[start], "|") != 0)
	{
		if (ft_strcmp(tokens[start], ">") == 0
			|| ft_strcmp(tokens[start], ">>") == 0
			|| ft_strcmp(tokens[start], "<") == 0)
		{
			start += 2;
			continue ;
		}
		count++;
		start++;
	}
	return (count);
}

static t_redir	*new_redir(char *filename, t_token_type type)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->filename = ft_strdup(filename);
	r->type = type;
	r->next = NULL;
	return (r);
}

static void	add_redir(t_redir **head, t_redir *new)
{
	t_redir	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static t_token_type	get_redir_type(char *token)
{
	if (ft_strcmp(token, ">") == 0)
		return (TRUNC);
	if (ft_strcmp(token, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(token, "<") == 0)
		return (INPUT);
	return (WORD);
}

static t_cmd	*build_one_cmd(char **tokens, int *pos)
{
	t_cmd	*cmd;
	int		arg_count;
	int		ai;
	int		start;

	start = *pos;
	arg_count = count_args(tokens, start);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	cmd->redir = NULL;
	cmd->next = NULL;
	cmd->fork_id = 0;
	cmd->ret_stat = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->cmd_type = NONE;
	ai = 0;
	while (tokens[*pos] && ft_strcmp(tokens[*pos], "|") != 0)
	{
		if (ft_strcmp(tokens[*pos], ">") == 0
			|| ft_strcmp(tokens[*pos], ">>") == 0
			|| ft_strcmp(tokens[*pos], "<") == 0)
		{
			if (tokens[*pos + 1])
			{
				add_redir(&cmd->redir,
					new_redir(tokens[*pos + 1],
						get_redir_type(tokens[*pos])));
				(*pos) += 2;
			}
			else
				(*pos)++;
			continue ;
		}
		cmd->args[ai++] = ft_strdup(tokens[*pos]);
		(*pos)++;
	}
	cmd->args[ai] = NULL;
	return (cmd);
}

static int	is_separator(char c)
{
	return (c == ' ' || c == '\t');
}

static int	is_special(char *s)
{
	if (s[0] == '>' && s[1] == '>')
		return (2);
	if (s[0] == '>' || s[0] == '<' || s[0] == '|')
		return (1);
	return (0);
}

static int	count_tokens(char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_separator(input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_special(&input[i]))
		{
			i += is_special(&input[i]);
			count++;
		}
		else
		{
			while (input[i] && !is_separator(input[i])
				&& !is_special(&input[i]))
				i++;
			count++;
		}
	}
	return (count);
}

static char	**tokenize(char *input)
{
	char	**tokens;
	int		total;
	int		i;
	int		t;
	int		start;

	total = count_tokens(input);
	tokens = malloc(sizeof(char *) * (total + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	t = 0;
	while (input[i])
	{
		while (input[i] && is_separator(input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_special(&input[i]))
		{
			start = is_special(&input[i]);
			tokens[t++] = ft_substr(input, i, start);
			i += start;
		}
		else
		{
			start = i;
			while (input[i] && !is_separator(input[i])
				&& !is_special(&input[i]))
				i++;
			tokens[t++] = ft_substr(input, start, i - start);
		}
	}
	tokens[t] = NULL;
	return (tokens);
}

t_cmd	*builder(char *input)
{
	char	**tokens;
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*cmd;
	int		pos;

	if (!input || !input[0])
		return (NULL);
	tokens = tokenize(input);
	if (!tokens)
		return (NULL);
	head = NULL;
	tail = NULL;
	pos = 0;
	while (tokens[pos])
	{
		cmd = build_one_cmd(tokens, &pos);
		if (!cmd)
			break ;
		if (!head)
			head = cmd;
		else
			tail->next = cmd;
		tail = cmd;
		if (tokens[pos] && ft_strcmp(tokens[pos], "|") == 0)
			pos++;
	}
	free2d_array(tokens);
	return (head);
}
