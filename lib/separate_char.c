/*
** separate_char.c for lib in /home/tran_0/rendu/rendugit/PSU_2013_42sh/src
** 
** Made by david tran
** Login   <tran_0@epitech.net>
** 
** Started on  Tue May  6 16:18:44 2014 david tran
** Last update Thu May 22 01:14:35 2014 david tran
*/

#include "my.h"

int	count_separ(char *str, char *src)
{
  int	i;
  int	j;
  int	count;

  i = my_strlen(src);
  j = 0;
  count = 0;
  while (str[j])
    {
      if (my_strncmp(&str[j], src, i) == 0)
	{
	  while (str[j] && j < i)
	    j++;
	  count += 1;
	}
      j++;
    }
  return (count + 1);
}

void	check_after(char *dest, char *src, int *i, int *j)
{
  if (src[*i] && src[*i] == src[*i - 1])
    {
      dest[(*j)++] = src[*i];
      *i += 1;
    }
  if (src[*i] && src[*i] != ' ')
    dest[(*j)++] = ' ';
}

void	feed_separate(char *src, char *dest, int *i, int *j)
{
  if (*i != 0 && src[*i - 1] && src[*i - 1] != ' ')
    dest[(*j)++] = ' ';
}

char	*separate_char(char *src, char *str)
{
  int	i;
  int	j;
  int	k;
  char	*dest;

  i = 0;
  if (!(dest = my_xmalloc(my_strlen(src) + count_separ(src, str) * 2 + 1)))
    return (NULL);
  j = 0;
  while (src[i])
    {
      if (my_strncmp(&src[i], str, my_strlen(str)) == 0)
	{
	  k = -1;
	  feed_separate(src, dest, &i, &j);
	  while (str[++k])
	    dest[j++] = src[i++];
	  check_after(dest, src, &i, &j);
	}
      else
	dest[j++] = src[i++];
    }
  dest[j] = 0;
  free(src);
  return (dest);
}
