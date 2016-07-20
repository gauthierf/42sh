/*
** move_curs_others.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:14:33 2016
** Last update Wed Jun  8 10:32:16 2016 
*/

#include <sys/ioctl.h>
#include <unistd.h>
#include "readline.h"
#include "tools.h"
#include "my.h"

int	rm_or_quit(t_rdd *reader)
{
  if (reader->list_read)
    {
      rm_cur(reader);
      return (0);
    }
  else
    {
      if ((write(1, "\n", 1)) == -1)
	return (-1);
      if ((my_tputs(tgetstr("ei", (void*)0), 1)) == -1)
	return (-1);
      if ((tcsetattr(1, TCSANOW, &(reader->term_attr_save))) == -1)
	return (my_putstr("error: tcsetattr\n", 2));
      return (-1);
    }
}

int			is_multiline(t_rdd *reader)
{
  struct winsize	win;
  int			size_prompt;
  int			size_cmd;

  size_prompt = 20;
  size_cmd = get_size_list(reader->list_read);
  if ((ioctl(1, TIOCGWINSZ, &win)) == -1)
    return (-1);
  if (size_cmd + size_prompt > win.ws_col)
    return (1);
  return (0);
}

int	rm_left_without_change_line(t_rdd *reader)
{
  if (reader->current > 0)
    {
      if (((my_tputs(tgetstr("le", NULL), reader->fd)) == -1)
	  || (my_tputs(tgetstr("dc", NULL), reader->fd)) == -1)
	return (-1);
      if (reader->current - 1 >= 0)
	reader->current -= 1;
      reader->list_read = rm_in_list(reader, reader->current);
    }
  return (0);
}
