/*
** bin_node_other.c for 42sh in /home/tran_0/rendu/rendugit/PSU_2013_42sh
** 
** Made by david tran
** Login   <tran_0@epitech.net>
** 
** Started on  Wed May 21 12:47:58 2014 david tran
** Last update Sun May 25 21:53:37 2014 david tran
*/

#include "42sh.h"
#include "my.h"

void		add_nodd_command(t_bin *bin, t_bin *new)
{
  t_bin		*tmp;

  if (!bin->head)
    {
      bin->head = new;
    }
  else
    {
      tmp = bin->head;
      while (tmp->left)
	tmp = tmp->left;
      tmp->left = new;
    }
}

int		create_nodd_command(t_bin *bin, char **command, char *princ)
{
  t_bin		*new;

  if (!(new = malloc(sizeof(t_bin))))
    return (-1);
  new->command = NULL;
  if (command)
    if (!(new->command = wordtabdup(command)))
      return (-1);
  new->princ = princ;
  new->op = NULL;
  if (!(new->redo = malloc(sizeof(t_redirec))) ||
      !(new->pre = malloc(sizeof(t_redirec))))
      return (-1);
  new->pre->head = NULL;
  new->redo->head = NULL;
  new->left = NULL;
  new->right = NULL;
  add_nodd_command(bin, new);
  return (EXIT_SUCCESS);
}

int		update_command(t_bin *bin, char **command, char *princ)
{
  t_bin		*tmp;

  tmp = bin->head;
  while (tmp->left)
    tmp = tmp->left;
  while (tmp->right)
    tmp = tmp->right;
  if (!(tmp->command = wordtabdup(command)) ||
      !(tmp->princ = my_strdup(princ)))
    return (-1);
  return (EXIT_SUCCESS);
}

int		check_feeded_node(t_bin *bin)
{
  t_bin		*tmp;

  tmp = bin->head;
  while (tmp->left)
    tmp = tmp->left;
  while (tmp->right)
    tmp = tmp->right;
  if (tmp->command == NULL)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		check_nodes(t_bin *bin)
{
  t_bin		*tmp;

  tmp = bin->head;
  if (!tmp->left)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
