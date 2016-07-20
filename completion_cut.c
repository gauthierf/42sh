/*
** cut_completition.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:19:16 2016
** Last update Sun Jun  5 19:15:14 2016 retyt
*/

#include "my.h"

char	*cut_dir_cur(char *dir)
{
  int  	i;

  i = 0;
  while (dir[i])
    i += 1;
  i = (dir[i - 1] == '/') ? (i - 2) : (i - 1);
  while (i > 0 && dir[i] != '/')
    {
      dir[i] = 0;
      i -= 1;
    }
  if (i <= 0)
    {
      dir[0] = '/';
      dir[1] = 0;
    }
  else
    {
      dir[i] = '/';
      dir[i + 1] = 0;
    }
  return (dir);
}

char	*cut_word(char *word)
{
  int	i;

  i = 0;
  while (word[i] && word[i] != '/')
    {
      word[i] = 1;
      i += 1;
    }
  word[i] = 1;
  while (word[0] == 1)
    {
      i = 0;
      while (word[i])
	{
	  word[i] = word[i + 1];
	  i += 1;
	}
    }
  return (word);
}

char	**cut_executable(char **word_ptr)
{
  char	*tmp;
  int	i;
  int	j;

  i = 0;
  tmp = *word_ptr;
  while (tmp[i] && i < 2)
    {
      j = 0;
      while (tmp[j])
	{
	  tmp[j] = tmp[j + 1];
	  j += 1;
	}
      i += 1;
    }
  *word_ptr = tmp;
  return (word_ptr);
}

char	*cut_after_dir(char *s)
{
  int	i;

  i = 0;
  while (s[i])
    i += 1;
  while (i > 0 && s[i] != '/')
    {
      s[i] = 0;
      i -= 1;
    }
  return (s);
}

char	*cut_before_dir(char *s)
{
  int	i;

  i = 0;
  while (s[i])
    i += 1;
  while (i > 0 && s[i] != '/')
    i -= 1;
  i -= 1;
  while (i >= 0)
    {
      s[i] = 1;
      i -= 1;
    }
  while (s[0] == 1 || s[0] == '/')
    {
      i = 0;
      while (s[i])
	{
	  s[i] = s[i + 1];
	  i += 1;
	}
    }
  return (s);
}
