/*
** ctrl.c for ctrl in /home/wallet_v/42sh_edition_historique
** 
** Made by valentin wallet
** Login   <wallet_v@epitech.net>
** 
** Started on  Mon May 19 15:07:30 2014 valentin wallet
** Last update Sun May 25 18:34:01 2014 valentin wallet
*/

#include "42sh.h"
#include "my.h"

void			ctrl_l(char *str, t_cmd *data)
{
  tputs(data->clearstr, 1, my_putchar2);
  my_putstr("$42sh> ");
  my_putstr(str);
}

char			*ctrl_y(char *dest, char *src, int *x, t_cmd *data)
{
  char			*end;
  char			*debut;
  char			*final;

  if ((end = malloc(sizeof(char) * (my_strlen(dest) + 1))) == NULL)
    return (NULL);
  if ((debut = malloc(sizeof(char) * (my_strlen(dest) + my_strlen(src) + 2)))
      == NULL)
    return (NULL);
  memset(debut, '\0', (my_strlen(dest) + my_strlen(src) + 2));
  strcpy(end, &dest[(*x) - PROMPT_SIZE]);
  my_putstr(src);
  tputs(data->save, 1, my_putchar2);
  my_putstr(end);
  tputs(data->restor, 1, my_putchar2);
  strncpy(debut, dest, (*x - PROMPT_SIZE));
  strcat(debut, src);
  final = strcat(debut, end);
  *x = *x + my_strlen(src);
  free(dest);
  return (final);
}

char			*ctrl_k(char *str, t_cmd *data, int *x)
{
  char			*buffer;
  int			k;
  int			j;

  k = *x - PROMPT_SIZE;
  j = 0;
  if ((*x - PROMPT_SIZE) == my_strlen(str))
    return (NULL);
  buffer = malloc(sizeof(char) * (my_strlen(str) + 1));
  tputs(data->save, 1, my_putchar2);
  while (str[k] != '\0')
    {
      buffer[j++] = str[k++];
      write(1, " ", 1);
    }
  buffer[j] = '\0';
  tputs(data->restor, 1, my_putchar2);
  str[(*x) - PROMPT_SIZE] = '\0';
  return (buffer);
}
