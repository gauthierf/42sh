/*
** buf_zero.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:14:43 2016
** Last update Sun Jun  5 19:11:57 2016 retyt
*/

#include "my.h"

void	buf_zero(char *buf, int size)
{
  int	i;

  i = 0;
  while (i < size)
    {
      buf[i] = 0;
      i += 1;
    }
}
