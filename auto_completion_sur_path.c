/*
** path_completition.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:15:35 2016
** Last update Wed Jun  8 10:50:14 2016 
*/

#include <stdlib.h>
#include <sys/stat.h>
#include "readline.h"
#include "tools.h"
#include "my.h"

static int	is_path_in_word(char *word)
{
  int		i;

  i = 0;
  while (word[i])
    {
      if (word[i] == '/')
	return (1);
      i += 1;
    }
  return (0);
}

static char	*get_true_path_abs(char **word_ptr)
{
  char		*to_free;
  char		*true_path;

  to_free = *word_ptr;
  if ((*word_ptr = my_strdup(*word_ptr)) == NULL)
    return (NULL);
  if ((true_path = my_strdup(*word_ptr)) == NULL)
    return (NULL);
  *word_ptr = cut_before_dir(*word_ptr);
  true_path = cut_after_dir(true_path);
  free(to_free);
  return (true_path);
}

char	*get_true_path(char *word, char *dir_cur, char **word_ptr)
{
  char	*true_path;

  if (word[0] == '.' && word[1] == '/')
    {
      true_path = dir_cur;
      word_ptr = cut_executable(word_ptr);
    }
  else if (word[0] != '/')
    {
      while (my_strstr(word, "../") != NULL)
	{
	  dir_cur = cut_dir_cur(dir_cur);
	  word = cut_word(word);
	}
      true_path = dir_cur;
    }
  else
    true_path = get_true_path_abs(word_ptr);
  return (true_path);
}

char	*get_complete_path(char *word, char *path)
{
  char	*new;

  if ((path = check_if_slash(path)) == NULL)
    return (NULL);
  if (is_path_in_word(word) == 1)
    {
      if ((new = str_cat(path, word)) == NULL)
	return (NULL);
      new = cut_after_dir(new);
      word = cut_before_dir(word);
      if (my_strlen(word) == 1 && word[0] == '/')
	word[0] = 0;
      free(path);
      path = new;
    }
  return (path);
}

int		mod_directory(char *path, t_completion *list)
{
  struct stat	buf;
  char		*tmp;

  while (list)
    {
      if ((tmp = str_cat(path, list->file)) == NULL)
	return (-1);
      if (lstat(tmp, &buf) == 0)
	{
	  if (S_ISDIR(buf.st_mode))
	    list->file[my_strlen(list->file)] = '/';
	}
      free(tmp);
    list = list->next;
    }
  return (0);
}
