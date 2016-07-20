/*
** historic.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:14:55 2016
** Last update Wed Jun  8 10:42:46 2016 
*/

#include <curses.h>
#include "readline.h"
#include "my.h"

static t_rd	*find_up_hist(t_histo **historic)
{
  t_histo	*tmp;

  tmp = *historic;
  while (tmp)
    {
      if (tmp->is_cur == 1)
	{
	  if (tmp->next)
	    {
	      tmp->is_cur = 0;
	      tmp->next->is_cur = 1;
	      return (tmp->next->list_read);
	    }
	  else
	    return (tmp->list_read);
	}
      tmp = tmp->next;
    }
  (*historic)->is_cur = 1;
  return ((*historic)->list_read);
}

static t_rd	*find_down_hist(t_histo **historic)
{
  t_histo	*tmp;

  tmp = *historic;
  while (tmp)
    {
      if (tmp->is_cur == 1)
	{
	  tmp->is_cur = 0;
	  if (tmp->prev)
	    {
	      tmp->prev->is_cur = 1;
	      return (tmp->prev->list_read);
	    }
	  else
	    return (tmp->list_read);
	}
      tmp = tmp->next;
    }
  (*historic)->is_cur = 0;
  return (NULL);
}

static int	clean_line(t_rdd *reader)
{
  int		i;
  int		nb;

  nb = 1;
  i = 0;
  while (reader->prompt && reader->prompt[i])
    if (reader->prompt[i++] == '\n')
      nb += 1;
  i = 0;
  while (i < nb)
    {
      if (nb > 1 && i > 0)
	if (my_putstr("\033[1A", 1) == -1)
	  return (-1);
      if ((my_tputs(tgetstr("dl", NULL), 1)) == -1
	  || my_tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1) == -1)
	return (-1);
      i += 1;
    }
  if (reader->prompt)
    if ((my_putstr(reader->prompt, reader->fd)) == -1)
      return (-1);
  return (0);
}

int		move_up_hist(t_rdd *reader)
{
  t_rd		*to_return;

  if (reader->historic == NULL)
    return (0);
  if ((clean_line(reader)) == -1)
    return (-1);
  to_return = find_up_hist(&(reader->historic));
  if (to_return)
    {
      if ((disp_list_read(to_return, 1)) == -1)
	return (-1);
      reader->current = get_size_list(to_return);
      reader->list_read = to_return;
    }
  return (0);
}

int		move_down_hist(t_rdd *reader)
{
  t_rd		*to_return;

  if (reader->historic == NULL)
    return (0);
  if ((clean_line(reader)) == -1)
    return (-1);
  if ((to_return = find_down_hist(&(reader->historic))) == reader->list_read)
    {
      reader->current = 0;
      reader->list_read = NULL;
      return (0);
    }
  if (to_return)
    {
      if ((disp_list_read(to_return, 1)) == -1)
	return (-1);
      reader->current = get_size_list(to_return);
      reader->list_read = to_return;
    }
  return (0);
}
