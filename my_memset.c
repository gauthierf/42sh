/*
** my_memset.c for  in /home/fernan_w/Téléchargements/backup/gnl
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:55:48 2016
** Last update Sun Jun  5 19:45:49 2016 retyt
*/

#include "my.h"

char	*my_memset(char *str, int len)
{
  int	i;

  i = 0;
  while (i < len)
    str[i++] = '\0';
  return (str);
}
