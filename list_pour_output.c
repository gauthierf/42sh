/*
** list_output.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:56:40 2016
** Last update Sun Jun  5 19:44:15 2016 retyt
*/

#include <stdlib.h>
#include "parser.h"
#include "readline.h"
#include "my.h"

static t_output	*create_output(char *file, int append_or_not, int is_pipe)
{
  t_output	*new;

  if ((new = (t_output*)malloc(sizeof(*new))))
    {
      new->file = file;
      new->append_or_not = append_or_not;
      new->is_pipe = is_pipe;
      new->next = NULL;
    }
  else
    if ((my_putstr("error: could not alloc\n", 2)) == -1)
      return (NULL);
  return (new);
}

int		push_output(t_output **output, char *file, int append_or_not,
			    int is_pipe)
{
  t_output	*tmp;

  tmp = *output;
  if (tmp)
    {
      while (tmp->next)
	tmp = tmp->next;
      if ((tmp->next = create_output(file, append_or_not, is_pipe)) == NULL)
	return (-1);
    }
  else
    if ((*output = create_output(file, append_or_not, is_pipe)) == NULL)
      return (-1);
  return (0);
}
