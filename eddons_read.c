/*
** push_read.c for g in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:17:46 2016
** Last update Wed Jun  8 10:38:15 2016 
*/

#include <stdlib.h>
#include "readline.h"
#include "my.h"

int		push_at_place(t_rd *tmp, char c, int place)
{
  t_rd	*tmp2;
  int		i;

  i = 0;
  while (tmp->next && i++ < place - 2)
    tmp = tmp->next;
  tmp2 = tmp->next;
  if ((tmp->next = create_read(c)))
    {
      tmp->next->prev = tmp;
      if (tmp2)
	{
	  tmp->next->next = tmp2;
	  tmp2->prev = tmp->next;
	}
      return (0);
    }
  else
    return (-1);
}

int		push_read(t_rd **list, char c, int place)
{
  t_rd	*tmp;

  tmp = *list;
  if (*list)
    {
      if (place > 0)
	return (push_at_place(tmp, c, place));
      else
	{
	  if ((tmp = create_read(c)))
	    {
	      tmp->next = *list;
	      (*list)->prev = tmp;
	      *list = tmp;
	      return (0);
	    }
	}
    }
  else
    if ((*list = create_read(c)))
      return (0);
  return (-1);
}

int	is_same_list(t_rd *l1, t_rd *l2)
{
  while (l1 && l2)
    {
      if (l1->c != l2->c)
	return (1);
      l1 = l1->next;
      l2 = l2->next;
    }
  if (l1 == NULL && l2 == NULL)
    return (0);
  if ((l1 == NULL && l2) || (l1 && l2 == NULL))
    return (1);
  return (0);
}

char		*list_to_word(t_rd *list_read)
{
  t_rd	*tmp_to_rm;
  char		*str;
  int		i;

  i = 0;
  if ((str = (char*)malloc(get_size_list(list_read) + 1)) == NULL)
    return ((void*)(unsigned long)my_putstr("error: could not alloc\n", 1));
  while (list_read)
    {
      str[i] = list_read->c;
      i += 1;
      tmp_to_rm = list_read;
      list_read = list_read->next;
      free(tmp_to_rm);
    }
  str[i] = '\0';
  return (str);
}
