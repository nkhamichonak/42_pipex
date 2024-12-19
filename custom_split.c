/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:06:21 by nkhamich          #+#    #+#             */
/*   Updated: 2024/12/19 20:52:47 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	strlen_till_sep_or_quote(const char *s, char c)
{
	size_t	i;
	char	quote;

	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i++];
			while (s[i] && (s[i] != quote
					|| (s[i] == quote && s[i - 1] == '\\')))
				i++;
			if (s[i])
				i++;
		}
		else
			i++;
	}
	return (i);
}

static char	*get_word(const char *s, char c, size_t *i)
{
	size_t	word_len;
	char	*word;
	char	*trimmed_word;

	word_len = strlen_till_sep_or_quote(&s[*i], c);
	word = ft_substr(s, *i, word_len);
	if (word == NULL)
		return (NULL);
	if (word[0] == '"')
		trimmed_word = ft_strtrim(word, "'\"");
	else if (word[0] == '\'')
		trimmed_word = ft_strtrim(word, "'");
	else
		trimmed_word = ft_strdup(word);
	free(word);
	*i += word_len;
	return (trimmed_word);
}

static void	handle_complex_arg(const char *str, int *i)
{
	int		j;
	char	quote;

	j = *i;
	quote = str[j];
	j++;
	while (str[j] && (str[j] != quote
			|| (str[j] == quote && str[j - 1] == '\\')))
		j++;
	if (str[j])
		j++;
	*i = j;
}

static int	count_words(const char *str, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			if (str[i] == '"' || str[i] == '\'')
				handle_complex_arg(str, &i);
			else
				while (str[i] && str[i] != c)
					i++;
		}
	}
	return (count);
}

char	**custom_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**strs;

	i = 0;
	j = 0;
	if (!s || *s == '\0')
		return (NULL);
	strs = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (strs == NULL || count_words(s, c) == 0)
		return (free_double_array(strs), NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			strs[j] = get_word(s, c, &i);
			if (strs[j] == NULL)
				return (free_double_array(strs), NULL);
			j++;
		}
	}
	strs[j] = NULL;
	return (strs);
}
