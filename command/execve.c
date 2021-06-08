#include "ft_minishell.h"
void check_build_in(t_command_and_flag *all,int *pipe_1,int fd1,char **env)
{
	//pwd
	if(!ft_strncmp(all->command,"/bin/pwd",9) && fd1)
		ft_pwd(env,fd1);
	if(!ft_strncmp(all->command,"/bin/pwd",9) && pipe_1!=0)
		ft_pwd(env,pipe_1[1]);
	if(!ft_strncmp(all->command,"/bin/pwd",9))
		ft_pwd(env,0);
	//env
	if(!ft_strncmp(all->command,"/usr/bin/env",13) && fd1)
		ft_env(env,fd1);
	if(!ft_strncmp(all->command,"/usr/bin/env",13) && pipe_1!=0)
		ft_env(env,pipe_1[1]);
	if(!ft_strncmp(all->command,"/usr/bin/env",13))
		ft_env(env,0);
	//echo
	if(!ft_strncmp(all->command,"/bin/echo",10)&& fd1)
		ft_echo(all,fd1);
	if(!ft_strncmp(all->command,"/bin/echo",10)&& pipe_1!=0)
		ft_echo(all,pipe_1[1]);
	if(!ft_strncmp(all->command,"/bin/echo",10))
		ft_echo(all,0);
	//cd
	if(!ft_strncmp(all->command,"/usr/bin/cd",13))
	{	
		ft_cd(all,env);
		exit(0);
	}
}
pid_t test(t_command_and_flag *all,int *pipe_1,int *pipe_2,int fd1,int fd2, char **env)
{
	
	if(pipe_2!=0)
		pipe(pipe_2);
	pid_t pid=fork();
	 g_global_pid = pid; /// add global pid
	if(!pid)
	{
		check_build_in(all,pipe_1,fd1,env);
		if(pipe_1!=0)
		{
			dup2(pipe_1[1],1);
			close(pipe_1[1]);
			close(pipe_1[0]);//add function close_fd -5 lines
		}
		if(pipe_2!=0)
		{
			dup2(pipe_2[0],0);
			close(pipe_2[1]);
			close(pipe_2[0]);
		}
		if(fd1)
		{	
			dup2(fd1,1);
			close(fd1);
		}
		if(fd2)
		{	
			dup2(fd2,0);
			close(fd2);
		}
		execve(all->command,all->array_flags,env);
	}
	if(pipe_1!=0)
	{
		close(pipe_1[1]);
		close(pipe_1[0]);
	}
	return(pid);
}
t_command_and_flag *number_of_pipes(int *size,t_command_and_flag **head1,t_command_and_flag **new_head)
{
	//1 | 2 > 3 >> 4 < 5; 6 eof
	t_command_and_flag *head;

	head=*head1;
	*size=0;
	if(head->pape==MORE || head->pape==DOUBLE_MORE)
		*size=-1;
	ft_list_push_front(new_head,head);
	if(!head->f_error || !ft_strncmp(head->command,"export",7)||!ft_strncmp(head->command,"unset",6))
		head=head->next;
	else
	{
		*size=-1;
		return head->next;
	}
	while(head)
	{
		if(head->f_error)
			return(head);
		if(head->pape==MORE || head->pape==DOUBLE_MORE ||head->pape==LESS)
		{	
			ft_list_push_front(new_head,head);
			return head->next;
		}
		if(head->pape==SEMICOLON)
			return head;
		ft_list_push_front(new_head,head);
		*size+=1;
		head = head->next;
	}
	return head;
}
int **make_pipe(int size)
{
	int **pipe;
	int i;

	i = 0;
	if(size < 0)
		return(0);
	pipe = malloc(sizeof(int*) * (size + 2));
	pipe[i++] = NULL;
	while(i <= size)
		pipe[i++] = malloc(sizeof(int) * 2);
	pipe[size+1]=NULL;
	return(pipe);
	
}
void find_function(int size,char **env,t_command_and_flag *head)
{
	int **pipe;
	int i;
	int fd1;
	int fd2;
	pid_t *pid;

	i = -1;
	fd1 = 0;
	fd2 = 0;
	pipe = make_pipe(size);
	pid=malloc(sizeof(pid)*(size+1));
	while(++i<=size)
	{
		if(head->pape==MORE)
		{
			fd1=open(head->command,O_WRONLY|O_TRUNC);
			head=head->next;
		}
		if(head->pape==DOUBLE_MORE)
		{
			fd1=open(head->command,O_WRONLY|O_APPEND);
			head=head->next;
		}
		if(head->pape==LESS)
		{
			fd2=open(head->command,O_RDONLY);
			head=head->next;
		}
		pid[i]=test(head,pipe[i],pipe[i+1],fd1,fd2,env);
		fd1 = 0;
		fd2=0;
		head=head->next;
	}
	i=0;
	while(size>=i)
		waitpid(pid[i++],&fd1,0);
	if(i>0)
	{
		i = 0;
		free(pipe[i++]);
		while(pipe[i])
			free(pipe[i++]);
		free(pipe[i]);
		free(pipe);
	}
}
void functions_launch(t_command_and_flag **head,char **env)
{
	t_command_and_flag *current_head;
	t_command_and_flag *tmp;
	int size;
	pid_t pid;
	tmp=0;
	current_head=*head;
	size=0;
	while(current_head)
	{
		tmp=0;
		current_head=number_of_pipes(&size,&current_head,&tmp);
		printf("%d\n",size);
		if(!ft_strncmp(tmp->command,"export",7))
			ft_export(tmp,env,0);
		if(!ft_strncmp(tmp->command,"unset",6))
			ft_unset(tmp,env);
		else if(size==-1 && tmp->f_error)
			printf("zsh: command not found:%s\n",tmp->command);//waiting for wrong command name abort with wrong command
		else if(size>0 || (size==0 && tmp->pape==MORE) || (size==0 && tmp->pape==DOUBLE_MORE)||(size==0 && tmp->pape==LESS))
			find_function(size,env,tmp);
		else if(size==0 &&!ft_strncmp(tmp->command,"/usr/bin/cd",13))
			ft_cd(tmp,env);
		else if(size==0)
		{	
			pid = test(tmp,0,0,0,0,env);
			waitpid(pid,&size,0);
		}
		ft_list_clear(tmp);
	}
}
