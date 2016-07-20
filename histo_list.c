/*
** list_historic.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:18:13 2016
** Last update Wed Jun  8 10:40:03 2016 
*/

#include <stdlib.h>
#include "readline.h"
#include "my.h"

static t_histo		*create_hist(t_rd *list_read)
{
  t_histo		*new;

  if ((new = (t_histo*)malloc(sizeof(*new))) != NULL)
    {
      new->list_read = list_read;
      new->is_cur = 0;
      new->prev = NULL;
      new->next = NULL;
    }
  else
    if ((my_putstr("error: could not alloc\n", 1)) == -1)
      return (NULL);
  return (new);
}

static void	rm_same_cmd_in_list(t_histo **historic)
{
  t_histo	*last_add;
  t_histo	*tmp;
  t_histo	*next;

  tmp = NULL;
  last_add = *historic;
  if (last_add)
    tmp = last_add->next;
  while (tmp)
    {
      while (tmp->list_read && tmp->list_read->prev)
	tmp->list_read = tmp->list_read->prev;
      if (is_same_list(tmp->list_read, last_add->list_read) == 0)
	{
	  tmp->prev->next = tmp->next;
	  if (tmp->next)
	    tmp->next->prev = tmp->prev;
	  next = tmp->prev;
	  free(tmp);
	  tmp = next;
	}
      if (tmp)
	tmp = tmp->next;
    }
}

static unsigned int	get_size_historic(t_histo **historic)
{
  t_histo		*tmp;
  unsigned int		size;

  size = 0;
  tmp = *historic;
  while (tmp)
    {
      size += 1;
      tmp = tmp->next;
    }
  return (size);
}

static void	rm_last_historic(t_histo **historic)
{
  t_histo	*tmp;
  t_histo	*tmp_save;

  tmp = *historic;
  while (tmp->next)
    tmp = tmp->next;
  tmp_save = tmp->prev;
  tmp_save->next = NULL;
  free(tmp);
}

int		push_historic(t_histo **historic, t_rd *list_read)
{
  t_histo	*tmp;

  tmp = *historic;
  if (tmp)
    {
      if (is_same_list(list_read, tmp->list_read) == 0)
	return (0);
      if ((tmp->prev = create_hist(list_read)) == NULL)
	return (-1);
      *historic = tmp->prev;
      tmp->prev->next = tmp;
      rm_same_cmd_in_list(historic);
      if (get_size_historic(historic) == HISTORIC_SIZE + 1)
	rm_last_historic(historic);
    }
  else
    if ((*historic = create_hist(list_read)) == NULL)
      return (-1);
  return (0);
}
