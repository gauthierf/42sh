/*
** filter_completition.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:21:39 2016
** Last update Wed Jun  8 10:52:09 2016 
*/

#include <stdlib.h>
#include <unistd.h>
#include "readline.h"
#include "tools.h"
#include "my.h"

int	is_good_with_list(t_completion *list, int to_add)
{
  if (to_add >= get_len_max(list))
    return (0);
  if (list->next == NULL)
    return (1);
  while (list->next)
    {
      if (my_strncmp(list->file, list->next->file, to_add + 1) != 0)
	return (0);
      list = list->next;
    }
  return (1);
}

void			rm_bad_name(t_completion **list, char *word)
{
  t_completion		*tmp;
  t_completion		*tmp_to_rm;

  tmp = *list;
  while (tmp)
    {
      if (my_strncmp(tmp->file, word, my_strlen(word)) != 0
	  || my_strcmp(tmp->file, "..") == 0)
	{
	  if (tmp->next)
	    tmp->next->prev = tmp->prev;
	  if (tmp->prev)
	    tmp->prev->next = tmp->next;
	  if (tmp == *list)
	    *list = tmp->next;
	  tmp_to_rm = tmp;
	  tmp = tmp->next;
	  free(tmp_to_rm->file);
	  free(tmp_to_rm);
	}
      else
	tmp = tmp->next;
    }
}

t_completion		**rm_not_executable(char *path, char *tmp_path,
					    t_completion **list)
{
  t_completion		*tmp;
  t_completion		*tmp_to_rm;

  tmp = *list;
  while (tmp)
    {
      if ((tmp_path = str_cat(path, tmp->file)) == NULL)
	return (NULL);
      if (access(tmp_path, F_OK | X_OK) != 0)
	{
	  if (tmp->next)
	    tmp->next->prev = tmp->prev;
	  if (tmp->prev)
	    tmp->prev->next = tmp->next;
	  if (tmp == *list)
	    *list = tmp->next;
	  tmp_to_rm = tmp;
	  tmp = tmp->next;
	  free(tmp_to_rm->file);
	  free(tmp_to_rm);
	}
      else
	tmp = tmp->next;
    }
  return (list);
}

char	*check_if_slash(char *path)
{
  int	i;
  char	*new;

  i = 0;
  while (path && path[i])
    i += 1;
  if (i > 0)
    i -= 1;
  if (path[i] != '/')
    {
      if ((new = my_strdup(path)) == NULL)
	return (NULL);
      new[i + 1] = '/';
      new[i + 2] = 0;
      free(path);
      path = new;
    }
  return (path);
}
