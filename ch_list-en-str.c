/*
** list_to_str.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:16:04 2016
** Last update Wed Jun  8 10:37:05 2016 
*/

#include <stdlib.h>
#include "readline.h"
#include "tools.h"
#include "my.h"

static void	rm_empty(t_histo **historic)
{
  t_histo	*tmp;

  tmp = *historic;
  while (tmp)
    {
      if (tmp->list_read
	  && tmp->list_read->c == '\0')
	{
	  if (tmp == *historic)
	    {
	      *historic = tmp->next;
	      if (*historic)
		(*historic)->prev = NULL;
	      free(tmp);
	    }
	  else
	    {
	      tmp->prev->next = tmp->next;
	      if (tmp->next)
		tmp->next->prev = tmp->prev;
	      free(tmp);
	    }
	}
      tmp = tmp->next;
    }
}

static void	clean_is_cur(t_histo **historic)
{
  t_histo	*tmp;

  tmp = *historic;
  if (tmp == NULL)
    return ;
  while (tmp)
    {
      tmp->is_cur = 0;
      tmp = tmp->next;
    }
}

char	*replace_cmd(char *str, int i, t_histo *historic)
{
  int	j;
  char	*last_cmd;

  if ((last_cmd = search_last_cmd(str + i + 1, historic)) == NULL)
    return (NULL);
  if (my_strcmp(str + 1, last_cmd))
    {
      j = 0;
      while (last_cmd[j] && last_cmd[j] != '|' && last_cmd[j] != ';'
	     && last_cmd[j] != '&')
	j += 1;
      last_cmd[j] = 0;
      if ((str = replace_it(str, i, last_cmd)) == NULL)
	return (NULL);
    }
  return (str);
}

char	*get_historic(char *str, t_histo *historic)
{
  int	i;
  char	*found_alias;

  i = 0;
  if (str == NULL)
    return (NULL);
  while (str[i])
    {
      if (str[i] == '!')
	{
	  if ((is_cmd(str, i)) == 1)
	    if ((str = replace_cmd(str, i, historic)) == NULL)
	      return (NULL);
	}
      else if (is_cmd(str, i) == 1)
	{
	  if ((found_alias = alias(str + i, 0)))
	    if ((str = replace_alias(str, i, found_alias)) == NULL)
	      return (NULL);
	}
      i += 1;
    }
  return (str);
}

char		*list_to_str(t_rd *list_read,t_histo **historic)
{
  t_rd		*tmp;
  char		*str;
  int		i;

  i = 0;
  tmp = list_read;
  if ((str = (char*)malloc(get_size_list(list_read) + 1)) == NULL)
    return ((void*)(unsigned long)my_putstr("error: could not alloc\n", 1));
  while (tmp)
    {
      str[i] = tmp->c;
      i += 1;
      tmp = tmp->next;
    }
  str[i] = 0;
  if (my_strlen(str) != 0)
    {
      if ((push_historic(historic, list_read)) == -1)
	return (NULL);
    }
  else
    rm_empty(historic);
  clean_is_cur(historic);
  return (str = get_historic(str, *historic));
}
