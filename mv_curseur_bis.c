/*
** move_curs_advanced.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:21:29 2016
** Last update Wed Jun  8 10:31:08 2016 
*/

#include <unistd.h>
#include "readline.h"
#include "my.h"

int	go_start(t_rdd *reader)
{
  if ((is_multiline(reader)) == 1)
    return (0);
  if (reader->list_read)
    {
      while (reader->current > 0)
	{
	  if ((my_tputs(tgetstr("le", NULL), reader->fd)) == -1)
	    return (-1);
	  reader->current -= 1;
	}
      if (reader->current == 0)
	reader->is_rm = -1;
    }
  return (0);
}

int	go_end(t_rdd *reader)
{
  char	str[4];
  int	size;

  if (is_multiline(reader) == 1)
    return (0);
  str[0] = 27;
  str[1] = 91;
  str[2] = 67;
  str[3] = 0;
  size = get_size_list(reader->list_read);
  while (reader->current < size)
    {
      if ((write(1, str, 4)) == -1)
	return (-1);
      reader->is_rm = 0;
      reader->current += 1;
    }
  return (0);
}
