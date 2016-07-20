/*
** move_curs.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:13:59 2016
** Last update Wed Jun  8 10:31:52 2016 
*/

#include <sys/ioctl.h>
#include <unistd.h>
#include "readline.h"
#include "my.h"

int	get_char(t_rdd *reader, char *buf)
{
  int	i;

  i = 0;
  while (buf[i] >= 32 && i <= SIZE_BUF)
    {
      reader->current += 1;
      if (reader->is_rm == -1)
	reader->current = 0;
      if ((push_read(&(reader->list_read), buf[i], reader->current)) == -1)
	return (-1);
      if (reader->is_rm == -1)
	reader->current = 1;
      reader->is_rm += 1;
      if ((write(reader->fd, &(buf[i]), 1)) == -1)
	return (-1);
      i += 1;
    }
  return (0);
}

int	go_left(t_rdd *reader)
{
  int	ret;

  ret = 0;
  if (reader->list_read)
    {
      if ((ret = line_up()) == -1)
	return (-1);
      else if (ret == 0)
	{
	  if (reader->current > 0)
	    if ((my_tputs(tgetstr("le", NULL), reader->fd)) == -1)
	      return (-1);
	}
      if (reader->current - 1 >= 0)
	reader->current -= 1;
      if (reader->current == 0)
	reader->is_rm = -1;
    }
  return (0);
}

int	rm_left(t_rdd *reader)
{
  int	ret;

  if (reader->current > 0)
    {
      if ((ret = line_up()) == -1)
	return (-1);
      else if (ret == 0)
	if ((my_tputs(tgetstr("le", NULL), reader->fd)) == -1)
	  return (-1);
      if ((my_tputs(tgetstr("dc", NULL), reader->fd)) == -1)
	return (-1);
      if (reader->current - 1 >= 0)
	reader->current -= 1;
      reader->list_read = rm_in_list(reader, reader->current);
    }
  return (0);
}

int	rm_cur(t_rdd *reader)
{
  if ((my_tputs(tgetstr("dc", NULL), reader->fd)) == -1)
    return (-1);
  reader->list_read = rm_in_list(reader, reader->current);
  return (0);
}

int			go_right(t_rdd *reader)
{
  struct winsize	win;

  if (reader->current < get_size_list(reader->list_read))
    {
      if ((ioctl(1, TIOCGWINSZ, &win)) == -1)
	return (-1);
      if ((line_down(win.ws_col)) == -1)
	return (-1);
      reader->is_rm = 0;
      reader->current += 1;
    }
  return (0);
}
