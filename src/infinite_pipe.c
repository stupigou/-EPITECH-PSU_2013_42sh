/*
** infinite_pipe.c for infinite_pipe in /home/wallet_v/PSU_2013_42sh/src/tree
** 
** Made by valentin wallet
** Login   <wallet_v@epitech.net>
** 
** Started on  Wed May 21 19:45:51 2014 valentin wallet
** Last update Sun May 25 21:51:42 2014 david tran
*/

#include "42sh.h"
#include "my.h"

void		built_dad(t_bin *bin, t_env **env)
{
  int		i;

  i = 0;
  while (built[i].name && bin->command && bin->command[0] &&
	 my_strcmp(built[i].name, bin->command[0]) != 0)
    i++;
  if (i < 5 && !bin->right)
    built[i].func(*env, bin->command);
}

int		feed_son(t_bin *bin, char **list)
{
  int		i;

  i = 0;
  while (built[i].name && bin->command && bin->command[0] &&
	 my_strcmp(built[i].name, bin->command[0]) != 0)
    i++;
  if (i >= 5)
    {
      if (!bin->princ || access(bin->princ, X_OK) == -1)
	return (-1);
      if (check_globbing(bin) == -1)
	return (-1);
      execve(bin->princ, bin->command, list);
    }
  return (EXIT_SUCCESS);
}

int		go_son(t_bin *bin, char **list, t_exec *execa)
{
  if (bin->pre->head && bin->pre->head->dinv && bin->right)
    return (-1);
  if (bin->pre->head && bin->pre->head->dinv)
    dup2(execa->pipefd[0], 0);
  else
    (bin->pre->head && bin->pre->head->fd != -1) ?
      dup2(bin->pre->head->fd, 0) : dup2(execa->save_pipeout, 0);
  if (bin->pre->head && bin->pre->head->fd != -1)
    close(bin->pre->head->fd);
  if (bin->right != NULL)
    dup2(execa->pipefd[1], 1);
  close(execa->pipefd[0]);
  close(execa->pipefd[1]);
  if (!bin->right && execa->ffd != -1)
    dup2(execa->ffd, 1);
  if (!bin->right && execa->ffd != -1)
    close(execa->ffd);
  return (feed_son(bin, list));
}

int		go_dad(t_exec *execa, t_env **env, t_bin *bin)
{
  if (bin->pre->head && bin->pre->head->dinv && !bin->right)
    {
      close(execa->pipefd[0]);
      write(execa->pipefd[1], bin->pre->head->dinv,
	    my_strlen(bin->pre->head->dinv));
    }
  else
    built_dad(bin, env);
  close(execa->pipefd[1]);
  wait(&execa->status);
  if (WIFSIGNALED(execa->status) == true)
    aff_signalcaught(WTERMSIG(execa->status));
  execa->save_pipeout = execa->pipefd[0];
  return (WEXITSTATUS(execa->status));
}

int		loop_pipe(t_bin *tmp, char **list, t_env **env)
{
  t_exec	execa;
  t_bin		*bin;

  bin = tmp;
  execa.save_pipeout = 0;
  if (tmp->redo && tmp->redo->head)
    execa.ffd = tmp->redo->head->fd;
  else
    execa.ffd = -1;
  while (bin != NULL)
    {
      pipe(execa.pipefd);
      if ((execa.pid = fork()) == -1)
	return (EXIT_FAILURE);
      else if (execa.pid == 0)
	return (son_error(bin, list, &execa));
      else
	{
	  if (go_dad(&execa, env, bin) == EXIT_FAILURE)
	      return (EXIT_FAILURE);
	  bin = bin->right;
	}
    }
  return (EXIT_SUCCESS);
}
