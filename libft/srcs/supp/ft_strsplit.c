/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 17:34:07 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 13:58:12 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

static void			compute_words(const char *str, int *nb_words, char c)
{
	int i;

	i = -1;
	*nb_words = 0;
	while (str[++i] != '\0')
	{
		if (str[i] != c && *nb_words == 0)
			*nb_words = 1;
		if (str[i] != c)
			;
		else
		{
			while (str[++i] == c)
				;
			if (str[i] == '\0')
				return ;
			else
			{
				*nb_words = *nb_words + 1;
				i--;
			}
		}
	}
	return ;
}

static int			compute_size(char *s, int word, int i, char c)
{
	int nb_words;
	int size;

	size = 0;
	nb_words = -1;
	while ((s[++i] == c) && s[i] != '\0')
		;
	i--;
	while (s[++i] != '\0')
	{
		if (s[i] != c && nb_words != word)
			size++;
		else
		{
			if (nb_words == word - 1)
				return (size);
			while ((s[++i] == c) && s[i] != '\0')
				;
			nb_words++;
			i--;
			size = 0;
		}
	}
	return (size);
}

static void			parser(char **tab, char *str, int i, char c)
{
	int j;

	j = -1;
	while (*(str) == c && *str != '\0')
		str++;
	str--;
	while (*(++str) != '\0')
	{
		if (*str != c)
			tab[i][++j] = *str;
		else
		{
			while (*(++str) == c)
				;
			tab[i][++j] = '\0';
			if (*str != '\0')
			{
				--str;
				++i;
				j = -1;
			}
			else
				return ;
		}
	}
}

char				**ft_strsplit(char *str, char c)
{
	int		nb_words;
	char	**res;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	compute_words(str, &nb_words, c);
	res = 0;
	res = malloc(sizeof(*res) * (nb_words + 1));
	if (!res)
		return (0);
	while (i < nb_words)
	{
		res[i] = 0;
		res[i] = malloc(sizeof(*res[i]) * compute_size(str, i, -1, c));
		if (!res[i])
			return (0);
		i++;
	}
	res[nb_words] = 0;
	parser(res, str, 0, c);
	return (res);
}
