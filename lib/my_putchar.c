/*
** my_putchar.c for lib in /home/tran_0/rendu/rendugit/PSU_2013_42sh/lib
** 
** Made by david tran
** Login   <tran_0@epitech.net>
** 
** Started on  Tue May  6 06:08:34 2014 david tran
** Last update Tue May  6 06:09:04 2014 david tran
*/

#include "my.h"

void	my_putchar(char c)
{
  write(1, &c, 1);
}
