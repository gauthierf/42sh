/*
** list_read.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:16:41 2016
** Last update Wed Jun  8 10:33:06 2016 
*/

#include <stdlib.h>
#include <unistd.h>
#include "readline.h"
#include "my.h"

t_rd		*create_read(char c)
{
  t_rd		*new;

  new = NULL;
  if ((new = (t_rd*)malloc(sizeof(*new))))
    {
      new->c = c;
      new->is_current = 0;
      new->prev = NULL;
      new->next = NULL;
    }
  else
    if ((my_putstr("error: could not alloc\n", 2)) == -1)
      return (NULL);
  return (new);
}

t_rd		*rm_in_list(t_rdd *reader, int nb)
{
  t_rd		*tmp;
  int		i;

  i = 0;
  tmp = reader->list_read;
  if (tmp == NULL)
    return (NULL);
  if (nb == 0)
    {
      reader->list_read = tmp->next;
      if (reader->list_read)
	reader->list_read->prev = NULL;
      return (reader->list_read);
    }
  while (i++ < nb && tmp)
    tmp = tmp->next;
  if (tmp == NULL)
    return (reader->list_read);
  if (tmp && tmp->prev)
    tmp->prev->next = tmp->next;
  if (tmp->next)
    tmp->next->prev = tmp->prev;
  free(tmp);
  return (reader->list_read);
}

int		get_size_list(t_rd *list)
{
  t_rd		*tmp;
  int		size;

  size = 0;
  tmp = list;
  while (tmp)
    {
      tmp = tmp->next;
      size += 1;
    }
  return (size);
}

int	disp_list_read(t_rd *list, int fd)
{
  while (list)
    {
      if ((write(fd, &(list->c), 1)) == -1)
	return (-1);
      list = list->next;
    }
  return (0);
}
