/*
** reverse_str.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:19:00 2016
** Last update Sun Jun  5 19:53:11 2016 retyt
*/

#include "readline.h"
#include "tools.h"
#include "my.h"

void	reverse_str(char *str)
{
  char	tmp;
  int	begin;
  int	end;

  begin = 0;
  end = my_strlen(str) - 1;
  while (begin <= end)
    {
      tmp = str[begin];
      str[begin] = str[end];
      str[end] = tmp;
      begin += 1;
      end -= 1;
    }
}
