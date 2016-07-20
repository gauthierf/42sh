/*
** clean_screen.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:18:00 2016
** Last update Wed Jun  8 10:23:40 2016 
*/

#include <curses.h>
#include "readline.h"
#include "my.h"

int	clean_screen(t_rdd *reader)
{
  if ((my_tputs(tgetstr("cl", NULL), reader->fd)) == -1)
    return (-1);
  if (reader->prompt)
    if ((my_putstr(reader->prompt, reader->fd)) == -1)
      return (-1);
  if ((disp_list_read(reader->list_read, reader->fd)) == -1)
    return (-1);
  reader->current = get_size_list(reader->list_read);
  return (0);
}
