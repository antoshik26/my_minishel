#include"function.h"

void test(t_command_and_flag *all,int *pipe_1,int *pipe_2,int fd, char **env)
{
	
	if(pipe_2!=0)
		pipe(pipe_2);
	if(!fork())
	{
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
		if(fd)
		{	
			dup2(fd,1);
			close(fd);
		}
		execve(all->command,all->array_flags,env);
	}
	if(pipe_1!=0)
	{
		close(pipe_1[1]);
		close(pipe_1[0]);
	}
}
t_command_and_flag *number_of_pipes(t_minishell *all,int *size,t_command_and_flag *head)
{
	*size=0;
	if(head->pape==2||head->pape==4)
		*size=-1;
	if(head->f_error)
	{	*size==-1;
		return(head->next);
	}
	head=head->next;
	while(head && head->next)
	{
		if(!head->f_error)
			*size++;
		if(head->pape==2 || head->pape==5 ||head->pape==6 || head->f_error)
			break;
		head = head->next;
	}
	return head;
}
int **make_pipe(int size)
{
	int **pipe;
	int i;

	i = 0;
	if(size == 0)
		return(0);
	pipe = malloc(sizeof(int*) * (size + 1));
	pipe[i++] = NULL;
	while(i < size)
		pipe[i++] = malloc(sizeof(int) * 2);
	pipe[size]=NULL;
	return(pipe);
	
}
void find_function(int size,t_minishell *all,t_command_and_flag *head)
{
	int **pipe;
	int i;
	int fd;

	i = -1;
	fd = 0;
	pipe = make_pipe(size);
	while(++i<size)
	{
		if(head->pape==2)//add function check pipe to chosw correct options for open
		{
			fd=open(head->array_flags[1],"O_WRONLY");
			head=head->next;
		}
		test(head,pipe[i],pipe[i+1],fd,all->env);
		fd = 0;
		head=head->next;
	}
	while(size--)
		wait(0);//free pipe;
}
int functions_launch(t_minishell *all)
{
	t_command_and_flag *current_head;
	t_command_and_flag *tmp;
	int size;

	current_head=all->head;
	while(current_head->next)
	{
		tmp = number_of_pipes(all,&size,current_head);
		if(size==-1)
			printf("zsh: command not found:%s",current_head->command);
		else
			find_function(size,all,current_head);
		current_head=tmp;
		check_env(all);//check all values
	}
	//free list
}


