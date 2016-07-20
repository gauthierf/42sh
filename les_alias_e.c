/*
** go_other_word.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:14:21 2016
** Last update Wed Jun  8 10:27:15 2016 
*/

#include "readline.h"
#include "my.h"

static int	is_alphanum(char c)
{
  if (c >= 'a' && c <= 'z')
    return (1);
  if (c >= 'A' && c <= 'Z')
    return (1);
  if (c >= '0' && c <= '9')
    return (1);
  return (0);
}

static int	loop_next_word(t_rdd *reader, char *str, int to_move)
{
  int		i;

  i = 0;
  while (is_multiline(reader) != 1 && i++ < to_move && ++(reader->current))
    {
      if ((my_tputs(str, reader->fd)) == -1)
	return (-1);
      reader->is_rm = 0;
    }
  return (0);
}

static int	loop_prev_word(t_rdd *reader, int to_move)
{
  int		i;

  i = 0;
  while (i < to_move)
    {
      if ((my_tputs(tgetstr("le", (void*)0), reader->fd)) == -1)
	return (-1);
      i += 1;
    }
  reader->current -= to_move;
  if (reader->current < 0)
    if ((go_right(reader)) == -1)
      return (-1);
  return (0);
}

int		go_next_word(t_rdd *reader)
{
  t_rd		*tmp_list;
  char		str[4];
  int		to_move;
  int		i;

  i = 0;
  to_move = 0;
  str[0] = 27;
  str[1] = 91;
  str[2] = 67;
  str[3] = 0;
  tmp_list = reader->list_read;
  while (tmp_list && i++ < reader->current)
    tmp_list = tmp_list->next;
  while (tmp_list && is_alphanum(tmp_list->c) == 0 && ++to_move)
    tmp_list = tmp_list->next;
  while (tmp_list && is_alphanum(tmp_list->c) == 1 && ++to_move)
    tmp_list = tmp_list->next;
  if ((loop_next_word(reader, str, to_move)) == -1)
    return (-1);
  return (0);
}

int		go_prev_word(t_rdd *reader)
{
  t_rd		*tmp_list;
  int		to_move;
  int		i;

  i = 0;
  tmp_list = reader->list_read;
  if (tmp_list && reader->current != 0 && is_multiline(reader) != 1)
    {
      while (tmp_list && tmp_list->next && i++ < reader->current)
	tmp_list = tmp_list->next;
      to_move = (tmp_list->next == (void*)0) ? (1) : (0);
      while (tmp_list && is_alphanum(tmp_list->c) == 0 && --i && ++to_move)
	tmp_list = tmp_list->prev;
      while (tmp_list && is_alphanum(tmp_list->c) == 1 && ++to_move)
	tmp_list = tmp_list->prev;
      if ((loop_prev_word(reader, to_move)) == -1)
	return (-1);
      reader->current = (reader->current < 0) ? (0) : (reader->current);
      reader->is_rm = (reader->current == 0) ? (-1) : (reader->is_rm);
    }
  return (0);
}
