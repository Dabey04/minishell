/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:01:32 by dabey             #+#    #+#             */
/*   Updated: 2022/12/14 19:41:24 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_new_cmd(char *line, char *str_d, int i, int j)
{
	int 	k;
	char	*str_1;
	char	*str_2;

	str_1 = NULL;
	str_2 = NULL;
	k = ft_strlen(line) - (j - i); // ft_strlen(line + j) ??
	str_1 = ft_substr(line, 0, i - 1);//debut de line
	str_2 = ft_strjoin(str_1, str_d);//debut + expand_dollar
	free(str_d);
	free(str_1);
	str_d = ft_substr(line, j, k);//la fin de line
	str_1 = ft_strjoin(str_2, str_d);//debut + expand_dollar + fin de line
	free(str_2);
	free(str_d);
	free(line);
	return (str_1);
}

char	*get_env_line_dollar(t_envlist *envlist, char *str_d)
{
	int			lenline;
	char		*lineresult;

	lineresult = NULL;
	lenline = ft_strlen(str_d); //useless?
	envlist = findline(envlist, str_d);//pas besoin de malloc line
	if (envlist)
	{
		lineresult = cutline(envlist->line);
//		lineresult = removequote(lineresult);
		printf("LINERESULT = %s\n", lineresult);
	}
	free(str_d);
	return (lineresult);
}

char	first_quote(char *line, int i)
{
	int		j;
	char	first_q;
	
	j = 0;
	while(line[j] && j < i)
	{
		if (line[j] == '\'' || line[j] == '\"')
		{
			if (line[j] == '\'')
				first_q = '\'';
			else
				first_q = '\"';
			while (line[j] && j < i && line[j] != first_q)
				j++;
			if (line[j] == first_q)
				first_q = 0;
			else return (first_q);
		}
		j++;
	}
	return (0);
}

char	*find_expand_dollar(t_envlist *envlist, char *line)
{
	int		i;
	int		j;
	int		k;
	char	*str_d;

	i = 0;
	j = 0;
	k = 0;
	str_d = NULL;
	while (line[i])
	{
		// replace = 0;
		if (line[i] == '$')//test "$HOME"
		{
			if (first_quote(line, i) == '\"'
				|| first_quote(line, i) == 0) //faut il mettre '\0'
			{
				j = ++i;// i = 7  
				while (line[j] && line[j] != ' ')// && line[++j] != '\'' && line[++j] != '\"')
					j++;//j = 11;
				str_d = malloc(sizeof(char) * (j - i) + 1);
				j = i;
				while (line[j] && line[j] != ' ')
					str_d[k++] = line[j++];
				str_d[k] = '\0';
				str_d = get_env_line_dollar(envlist ,str_d);
				str_d = ft_new_cmd(line, str_d, i, j);
				return (str_d);
			}
		}
		i++;
	}
	return (str_d);
}

char	**expand_dollar(char **str_cmd, t_envlist *env)
{
	int			i;
	char		*str_d;

	if (!str_cmd)
		return (NULL);
	i = 0;
	str_d = NULL;
	while (str_cmd[i])
	{
		str_cmd[i] = find_expand_dollar(env, str_cmd[i]);
		i++;
	}
	return (str_cmd);
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

