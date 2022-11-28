#include <stdio.h>
#include <stdlib.h>
typedef struct s_list{
char *buffer;
char **cmd;
int buf_size;
struct s_list *next;
int nb_quote;
int nb_db_quote;
}t_list;
int lenght_of_word(char *s, char sep){
  int len_w;
  char quote_tp;
  len_w = 0;
  while (*s && *s != sep)
    if (*s && (*s == '\"' || *s == '\'')){
    len_w++;
    quote_tp = *s;
    s++;
    while (*s && *s != quote_tp){
      s++;
      len_w++;}
    s++;
    len_w++;}
    else if (*s && *s != sep){
      while (*s && *s != '\'' && *s != '\"' && *s != ' '){
        len_w++;
        s++;}}
  return (len_w);}
int ft_count_word(char *s, char sep){
  int quote_tp;
  int count_w;
  quote_tp = 0;
  count_w = 0;
  while (*s){
    if (*s && (*s == '\"' || *s == '\'')){
      quote_tp = *s;
      s++;
      while (*s && *s != quote_tp)
        s++;}
    if (*s == sep)
      ++count_w;
    s++;}
  return (++count_w);}
char **ft_split_quote(char *buffer, char c){
  int i;
  int j;
  char **tab;
  char quote_tp; 
  int count_w;
  i = 0;
  if (!buffer)
    return (0);
  count_w = ft_count_word(buffer, '|');
  tab = (char **)malloc((count_w + 1) * sizeof(char *));
  if (!(tab))
    return (0);
  while (i < count_w){
    j = 0;
    while (*buffer == ' ' || *buffer == c)
      buffer++;
    tab[i] = (char *)malloc(sizeof(char) * (lenght_of_word(buffer, ' ') + 1));
    if (!tab[i])
      return (0);
    while (*buffer != c && *buffer != '\0'){
      // while (*buffer && *buffer == ' ' && *(buffer - 1) == ' ')
      //   buffer++;
      if (*buffer && (*buffer == '\"' || *buffer == '\'')){
        quote_tp = *buffer;
        tab[i][j++] = *buffer++;
        while (*buffer && *buffer != quote_tp)
         tab[i][j++] = *buffer++;}
      tab[i][j++] = *buffer++;
      while (*buffer && *buffer == ' ')
        buffer++;}
    tab[i++][j] = '\0';}
  tab[i] = 0;
  return (tab);}
t_list *ft_new_node(char *cmd_i, char *buffer){
  t_list *new;
  new = (t_list *)malloc(sizeof(t_list));
  if (!new)
    return (NULL);
  new->buffer = buffer;
  new->cmd = ft_split_quote(cmd_i,' ');
  new->next = NULL;
  return (new);}
t_list *ft_add_node(t_list *list, char *cmd_i, char *buffer){
  t_list *head;
  t_list *new; 
  head = NULL;
  new = ft_new_node(cmd_i, buffer);
  if (!(list))
      list = new;
  else{
    head = list;
    while (head->next != NULL)
        head = head->next;
    head->next = new;}
  return (list);}
int main(){
  t_list *list = NULL;
  char **str_cmd;
  char *buffer = malloc(sizeof(char) * 40);
  buffer = "\"te|st\" | \'he|y\' | haha";
  str_cmd = ft_split_quote(buffer, '|');
  int k = 0;
  while (str_cmd[k]){
    printf("pipe ==== %s\n", str_cmd[k]);
    k++;}
  int i = 0;
  while(str_cmd[i] != 0){
    list = ft_add_node(list, str_cmd[i], buffer);
    i++;}}

    //ctutor test qui ne marche pas 
    #include <stdio.h>
#include <stdlib.h>
typedef struct s_list{
char *buffer;
char **cmd;
int buf_size;
struct s_list *next;
int nb_quote;
int nb_db_quote;
}t_list;
int lenght_of_word(char *s, char sep){
  int len_w;
  char quote_tp;
  len_w = 0;
  while (*s && *s != sep)
    if (*s && (*s == '\"' || *s == '\'')){
    len_w++;
    quote_tp = *s;
    s++;
    while (*s && *s != quote_tp){
      s++;
      len_w++;}
    s++;
    len_w++;}
    else if (*s && *s != sep){
      while (*s && *s != '\'' && *s != '\"' && *s != ' '){
        len_w++;
        s++;}}
  return (len_w);}
int ft_count_word(char *s, char sep){
  int quote_tp;
  int count_w;
  quote_tp = 0;
  count_w = 0;
  while (*s){
    if (*s && (*s == '\"' || *s == '\'')){
      quote_tp = *s;
      s++;
      while (*s && *s != quote_tp)
        s++;}
    if (*s == sep)
      ++count_w;
    s++;}
  return (++count_w);}
char **ft_s_q(char *buffer, char c){
  int i;
  int j;
  char **tab;
  char quote_tp; 
  int count_w;
  i = 0;
  if (!buffer)
    return (0);
  count_w = ft_count_word(buffer, c);
  tab = (char **)malloc((count_w + 1) * sizeof(char *));
  if (!(tab))
    return (0);
  while (i < count_w){
    j = 0;
    while (*buffer == ' ' || *buffer == c)
      buffer++;
    tab[i] = (char *)malloc(sizeof(char) * (lenght_of_word(buffer, ' ') + 1));
    if (!tab[i])
      return (0);
    while (*buffer != c && *buffer != '\0'){
      while (*buffer && *buffer == ' ' && *(buffer - 1) == ' ')
        buffer++;
      if (*buffer && (*buffer == '\"' || *buffer == '\'')){
        quote_tp = *buffer;
        tab[i][j++] = *buffer++;
        while (*buffer && *buffer != quote_tp)
         tab[i][j++] = *buffer++;}
      tab[i][j++] = *buffer++;
      while (*buffer && *buffer == ' ')
        buffer++;}
    tab[i++][j] = '\0';}
  tab[i] = 0;
  return (tab);}
t_list *ft_new_node(char *cmd_i, char *buffer){
  t_list *new;
  new = (t_list *)malloc(sizeof(t_list));
  if (!new)
    return (NULL);
  new->buffer = buffer;
  new->cmd = ft_s_q(cmd_i,' ');
  new->next = NULL;
  return (new);}
t_list *ft_add_node(t_list *list, char *cmd_i, char *buffer){
  t_list *head;
  t_list *new; 
  head = NULL;
  new = ft_new_node(cmd_i, buffer);
if (!(list))
list = new;
else{
head = list;
while (head->next != NULL)
head = head->next;
head->next = new;}
return (list);}
int main(){ 
t_list *list = NULL,*tmp;
char **str_cmd;
char *buffer = malloc(sizeof(char) * 40);
buffer = "\"te|st\" | \'he|y\' | haha";
str_cmd = ft_s_q(buffer, '|');
int k = 0;
while (str_cmd[k]){
printf("pipe ==== %s\n", str_cmd[k]);
k++;}
int i = 0;
while(str_cmd[i] != 0){
list = ft_add_node(list, str_cmd[i], buffer);
i++;}
tmp = list;
int j;
while (tmp != 0)
{
printf("\nnode :\t");
j = 0;
while (tmp->cmd[j] != 0)
{
printf("cmd = %s\t",tmp->cmd[j]);
j++;
}
printf("\n");
tmp = tmp->next;
} }