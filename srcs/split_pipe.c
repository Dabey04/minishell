/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:01:32 by dabey             #+#    #+#             */
/*   Updated: 2022/12/13 18:03:45 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			is_quote_replace(char *line, int i)
{
	int		k;
	char	quote;
	char	db_quote;

	k = i;
	printf("line + i = %s\n", line);
	while (line[k] && line[k] != '$' && k < i)
	{
		while (line[k] && line[k] != '$' && line[k] != '\'' && line[k] != '\"')
			k++;
		if (line[k] && (line[k] == '\'' || line[k] == '\"'))
		{
			if (line[k] == '\'')
				quote = '\'';
			else db_quote = '\"';
			k++;
		}
		// if (line[k] && line[k] == '$' && quote)

	}
	return (0);// a revoir
}

t_envlist	*find_dollar(t_envlist *envlist, char *line)
{
	int			i;
	int			j;
	int			k;
	int			replace;
	char		*str_d;
	t_envlist	*envline;

	i = 0;
	j = 0;
	k = 0;
	str_d = NULL;
	envline = NULL;
	while (line[i])
	{
		replace = 0;
		if (line[i] == '$')//test "$HOME"
		{
			if (is_quote_replace(line, i))
			{
				// replace = 1;
				j = ++i;// i = 7  
				while (line[j] && line[j] != ' ')// && line[++j] != '\'' && line[++j] != '\"')
					j++;//j = 11;
				str_d = malloc(sizeof(char) * (j - i) + 1);
				j = i;
				while (line[j] && line[j] != ' ')
					str_d[k++] = line[j++];
				str_d[k] = '\0';	
				envline = findline(envlist ,str_d);
			}
		}
		i++;
	}
	return (envline);
}

t_list	*expand_dollar(t_list *list)
{
	int			i;
	char		*str_d;
	t_list		*tmp;
	t_envlist	*envl;

	if (list)
		return (NULL);
	tmp = list;
	str_d = NULL;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			envl = find_dollar(list->envlist, tmp->cmd[i]);
			i++;
		}
		tmp = tmp->next;
	}
	return (list);
}

int	ft_count_word(char *s, char sep)
{
	char	c;
	int		count_w;

	count_w = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			c = *s;
			s++;
			while (*s && *s != c)
				s++;
			if (*s == c)
				s++;
		}
		if (*s == sep)
		{
			s++;
			++count_w;
		}
		while (*s && *s != sep && *s != '\'' && *s != '\"')
			s++;
	}
	// printf("count_w = %d\n", count_w + 1);
	return (++count_w);
}

int	lenght_of_word(char *s, char sep)
{
	int		len_w;
	char	quote_tp;
	
	len_w = 0;
	while (*s && *s != sep)
	{
		if (*s && (*s == '\"' || *s == '\''))
		{
			len_w++;
			quote_tp = *s;
			s++;
			while (*s && *s != quote_tp)
			{
				s++;
				len_w++;
			}
			s++;
			len_w++;
		}
		else if (*s && *s != sep)
		{
			while (*s && *s != '\'' && *s != '\"' && *s != sep)
			{
				len_w++;
				s++;
			}
		}
	}
	return (len_w);
}

char	**ft_split_pipe(char *buff, char c)
{
	int		i;
	int		j;
	int		count_w;
	char	**tab;
	char	quote_tp;

	i = 0;
	if (!buff)
		return (0);
	count_w = ft_count_word(buff, c);
	tab = (char **)malloc((count_w + 1) * sizeof(char *));
	if (!(tab))
		return (0);
	while (i < count_w)
	{
		j = 0;
		tab[i] = (char *)malloc(sizeof(char) * (lenght_of_word(buff, c) + 1));
		if (!tab[i])
			return (0);
		while (*buff && *buff != c)
		{
			if (*buff && (*buff == '\"' || *buff == '\''))
			{
				quote_tp = *buff;
				tab[i][j++] = *buff++;
				while (*buff && *buff != quote_tp)
					tab[i][j++] = *buff++;
				tab[i][j++] = *buff++;
			}
			while (*buff && *buff != '\"' && *buff != '\'' && *buff != c)
				tab[i][j++] = *buff++;
		}
		tab[i++][j] = '\0';
		if (*buff == c)
			buff++;
	}
	tab[i] = 0;
	return (tab);
}

