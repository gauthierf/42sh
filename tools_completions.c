/*
** tools_completition.c for  in /home/fernan_w/Téléchargements/backup/readline
** 
** Made by 
** Login   <fernan_w@epitech.net>
** 
** Started on  Thu Jun  2 23:20:26 2016 
** Last update Wed Jun  8 10:45:10 2016 
*/

#include <stdlib.h>
#include <unistd.h>
#include "readline.h"

int	is_char_completition(char c)
{
  if (c != ' ' && c != '"' && c != '|' && c != '`'
      && c != '\'' && c != ';')
    return (1);
  return (0);
}

char		*get_word_current(t_rdd *reader)
{
  char		*word;
  t_rd		*tmp;
  t_rd		*tmp_word;
  int		i;

  i = 1;
  tmp_word = NULL;
  tmp = reader->list_read;
  while (i < reader->current && tmp && tmp->next)
    {
      tmp = tmp->next;
      i += 1;
    }
  i = 1;
  while (tmp && is_char_completition(tmp->c))
    {
      if (push_read(&tmp_word, tmp->c, i) == -1)
	return (NULL);
      tmp = tmp->prev;
      i += 1;
    }
  if ((word = list_to_word(tmp_word)))
    reverse_str(word);
  return (word);
}

int		is_not_first_word(t_rdd *reader)
{
  t_rd		*tmp;
  int		i;

  i = 1;
  tmp = reader->list_read;
  while (tmp && tmp->next && i < reader->current)
    {
      i += 1;
      tmp = tmp->next;
    }
  while (tmp->prev && is_char_completition(tmp->c))
    tmp = tmp->prev;
  while (tmp->prev && tmp->c == ' ')
    tmp = tmp->prev;
  if (is_char_completition(tmp->c) == 0 || tmp->prev == NULL)
    return (0);
  return (1);
}
