/*
** list_input.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:58:52 2016
** Last update Sun Jun  5 19:41:58 2016 retyt
*/

#include <stdlib.h>
#include "parser.h"
#include "readline.h"
#include "my.h"

static t_input	*create_input(char *file, char *heredoc, int is_pipe)
{
  t_input	*new;

  if ((new = (t_input*)malloc(sizeof(*new))))
    {
      new->file = file;
      new->heredoc = heredoc;
      new->is_pipe = is_pipe;
      new->next = NULL;
    }
  else
    if ((my_putstr("error: could not alloc\n", 2)) == -1)
      return (NULL);
  return (new);
}

int		push_input(t_input **input, char *file, char *heredoc, int pipe)
{
  t_input	*tmp;

  tmp = *input;
  if (tmp)
    {
      while (tmp->next)
	tmp = tmp->next;
      if ((tmp->next = create_input(file, heredoc, pipe)) == NULL)
	return (-1);
    }
  else
    if ((*input = create_input(file, heredoc, pipe)) == NULL)
      return (-1);
  return (0);
}
