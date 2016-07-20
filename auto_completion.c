/*
** completition.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:15:44 2016
** Last update Wed Jun  8 10:49:32 2016 
*/

#include <stdlib.h>
#include "readline.h"
#include "tools.h"
#include "my.h"

static int	is_exist(char **path, char *word, t_completion **list)
{
  int		found;
  int		i;

  i = 0;
  found = 0;
  while (path && path[i])
    {
      if (my_strncmp(path[i], word, my_strlen(word)) == 0)
	{
	  if ((push_completition(list, path[i])) == -1)
	    return (-1);
	  found += 1;
	}
      i += 1;
    }
  return (found);
}

static int	found_word(t_rdd *reader, t_completion *list, char *word)
{
  int		to_add;
  int		is_good;
  char		buf[2];

  is_good = 0;
  buf[1] = 0;
  to_add = my_strlen(word);
  while (is_good_with_list(list, to_add))
    {
      buf[0] = list->file[to_add];
      if ((get_char(reader, buf)) == -1)
	return (-1);
      is_good = 1;
      to_add += 1;
    }
  if (is_good == 0 && ++(reader->is_completition) == 2)
    if ((disp_possible_comp(reader, list)) == -1)
      return (-1);
  return (0);
}

static int	try_search_file(t_rdd *reader, t_completion **list,
				char **word,int is_first)
{
  char		**tab_tmp;
  char		*dir_tmp;
  int		unused;

  unused = 0;
  if ((tab_tmp = (char**)malloc(sizeof(char*) * 2)) == NULL)
    return (my_putstr("error: could not alloc\n", 2));
  tab_tmp[1] = NULL;
  if (((dir_tmp = my_strdup(reader->dir_cur)) == NULL)
      || ((tab_tmp[0] = get_true_path(*word, dir_tmp, word)) == NULL)
      || ((tab_tmp[0] = get_complete_path(*word, tab_tmp[0])) == NULL)
      || ((get_files(tab_tmp, list, &unused)) == -1))
    return (-1);
  rm_bad_name(list, *word);
  if ((mod_directory(tab_tmp[0], *list)) == -1)
    return (-1);
  if (is_first == 0)
    list = rm_not_executable(tab_tmp[0], NULL, list);
  free(tab_tmp);
  return (0);
}

static int	select_what(t_rdd *reader,  t_completion **list,
			    char **word, int is_first)
{
  if ((*word)[0] == '$')
    {
      if ((search_var_env(reader->env, list, *word)) == -1)
	return (-1);
    }
  else if (is_first == 1 || (*word)[0] == '.' || (*word)[0] == '/')
    {
      if ((try_search_file(reader, list, word, is_first)) == -1)
	return (-1);
    }
  else
    {
      if ((is_exist(reader->path, *word, list)) == -1)
	return (-1);
    }
  return (0);
}

int			completition(t_rdd *reader)
{
  t_completion		*list;
  char			*word;
  int			is_first;

  list = NULL;
  if ((word = get_word_current(reader)) == NULL)
    return (-1);
  if (my_strlen(word) > 0)
    {
      if (((is_first = is_not_first_word(reader)) == 0
	   && my_strncmp(word, "history", my_strlen(word) - 1) == 0)
	  && my_strlen(word) > 1)
	complete_history(reader, word, "history");
      else
	{
	  if ((select_what(reader, &list, &word, is_first)) == -1)
	    return (-1);
	  if (list)
	    if ((found_word(reader, list, word)) == -1)
	      return (-1);
	}
    }
  free_completition(list);
  free(word);
  return (0);
}
