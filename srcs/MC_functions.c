#include "../include/minishell.h"

int			is_meta(char *str, int i)
{
	return (i == 0 || (str[i - 1] && str[i - 1] != '\\' &&
	between_quotes(str, i) != 1));
}

int			contains_comment(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '#' && is_meta(str, i) && !between_quotes(str, i))
			return (i);
	}
	return (-1);
}

int			count_occur_before(char *str, int i, int c)
{
	int count;

	count = 0;
	while (--i >=0)
	{
		if (str[i] == c && (!i || str[i - 1] != '\\'))
			count++;
	}
	return (count);
}

int			count_occur_after(char *str, int i, int c)
{
	int count;

	count = 0;
	while (str[++i])
	{
		if (str[i] == c && (!i || str[i - 1] != '\\'))
			count++;
	}
	return (count);
}

int			between_quotes(char *str, int i)
{
	int qu_left;
	int qu_right;

	qu_left = count_occur_before(str, i, '\'');
	qu_right = count_occur_after(str, i, '\'');
	if (qu_right % 2 || qu_left % 2)
		return (1);
	qu_left = count_occur_before(str, i, '\"');
	qu_right = count_occur_after(str, i, '\"');
	if (qu_right % 2 || qu_left % 2)
		return (2);
	return (0);
}
