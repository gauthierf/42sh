/*
** list_completition.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:17:31 2016
** Last update Wed Jun  8 10:51:16 2016 
*/

#include <stdlib.h>
#include "readline.h"
#include "tools.h"
#include "my.h"

static t_completion	*create_completition(char *file)
{
  t_completion	*new;
  int			i;

  if ((new = (t_completion*)malloc(sizeof(*new))))
    {
      i = 0;
      new->file = NULL;
      if ((new->file = (char*)malloc(my_strlen(file) + 2)) == NULL)
	return ((void*)(unsigned long)my_putstr("error: malloc\n", 1));
      while (file && file[i])
	{
	  new->file[i] = file[i];
	  i += 1;
	}
      new->file[i] = 0;
      new->file[i + 1] = 0;
      new->prev = NULL;
      new->next = NULL;
    }
  return (new);
}

int			push_completition(t_completion **list, char *file)
{
  t_completion		*tmp;

  tmp = *list;
  if (tmp)
    {
      while (tmp->next)
	tmp = tmp->next;
      if ((tmp->next = create_completition(file)) == NULL)
	return (-1);
      tmp->next->prev = tmp;
    }
  else
    if ((*list = create_completition(file)) == NULL)
      return (-1);
  return (0);
}

int	get_size_completition(t_completion *list)
{
  int	size;

  size = 0;
  while (list)
    {
      size += 1;
      list = list->next;
    }
  return (size);
}

void			free_completition(t_completion *list)
{
  t_completion		*tmp;

  while (list)
    {
      tmp = list;
      list = list->next;
      free(tmp->file);
      free(tmp);
    }
}

int	get_len_max(t_completion *list)
{
  int	max;
  int	tmp;

  max = 0;
  while (list)
    {
      if ((tmp = my_strlen(list->file)) > max)
	max = tmp;
      list = list->next;
    }
  return (max);
}
