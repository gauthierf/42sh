/*
** edit_curs.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:21:13 2016
** Last update Wed Jun  8 10:24:51 2016 
*/

#include <stdlib.h>
#include "readline.h"
#include "my.h"

static void	clean_clipboard(t_rdd *reader)
{
  t_rd		*tmp;
  t_rd		*tmp_to_rm;

  tmp = reader->clipboard;
  while (tmp)
    {
      tmp_to_rm = tmp;
      tmp = tmp->next;
      free(tmp_to_rm);
    }
  reader->clipboard = NULL;
}

static char	get_char_cur(t_rdd *reader)
{
  t_rd		*tmp;
  int		i;

  i = 0;
  tmp = reader->list_read;
  while (tmp && i < reader->current)
    {
      tmp = tmp->next;
      i += 1;
    }
  if (tmp)
    return (tmp->c);
  return (reader->list_read->c);
}

int		rm_after(t_rdd *reader)
{
  t_rd		*tmp;
  int		i;

  i = 0;
  if (is_multiline(reader) == 1)
    return (0);
  tmp = reader->list_read;
  clean_clipboard(reader);
  while (tmp && i < reader->current)
    {
      tmp = tmp->next;
      i += 1;
    }
  i = 1;
  while (tmp)
    {
      if ((push_read(&(reader->clipboard), get_char_cur(reader), i)) == -1)
	return (-1);
      rm_cur(reader);
      i += 1;
      tmp = tmp->next;
    }
  return (0);
}

int		rm_before(t_rdd *reader)
{
  t_rd		*tmp;
  int		i;

  i = 0;
  if (is_multiline(reader) == 1)
    return (0);
  tmp = reader->list_read;
  clean_clipboard(reader);
  while (tmp && tmp->next && i < reader->current)
    {
      if ((push_read(&(reader->clipboard), tmp->c, i + 1)) == -1)
	return (-1);
      tmp = tmp->next;
      i += 1;
    }
  while (tmp)
    {
      if ((rm_left_without_change_line(reader)) == -1)
	return (-1);
      tmp = tmp->prev;
    }
  return (0);
}

int		past_clipboard(t_rdd *reader)
{
  t_rd		*tmp;
  char		buf[2];

  buf[1] = 0;
  tmp = reader->clipboard;
  while (tmp)
    {
      buf[0] = tmp->c;
      if ((get_char(reader, buf)) == -1)
	return (-1);
      tmp = tmp->next;
    }
  return (0);
}
