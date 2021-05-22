#include "ft_minishell.h"

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
t_command_and_flag *number_of_pipes(int *size,t_command_and_flag *head)
{
	//1 | 2 > 3 >> 4 < 5; 6 eof
	*size=0;
	if(!head->f_error)
		head=head->next;
	else
	{
		*size=-1;
		return head->next;
	}
	while(head)
	{
		if(!head->f_error)
			*size+=1;
		else
			return(head);
		if(head->pape==2 || head->pape==3 ||head->pape==4 || head->pape==5 )
			return head->next;
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
			fd=open(head->array_flags[1],O_WRONLY);
			head=head->next;
		}
		test(head,pipe[i],pipe[i+1],fd,all->env);
		fd = 0;
		head=head->next;
	}
	while(size--)
		wait(0);//free pipe;
	if(i>0)
	{
		i = 0;
		free(mas[i++]);
		while(mas[i])
			free(mas[i++]);
		free(mas[i]);
		free(mas);
	}
}

void functions_launch(t_minishell *all)
{
	t_command_and_flag *current_head;
	t_command_and_flag *tmp;
	int size;

	current_head=all->head;
	while(current_head)
	{
		tmp = number_of_pipes(&size,current_head);
		//printf("%d %s\n",size,current_head->command);
		if(size==-1)
			printf("zsh: command not found:%s\n",current_head->command);
		else
			find_function(size,all,current_head);
		current_head=tmp;
	}
}
int main()
{
	//function_lounch test
	/*t_command_and_flag *head1;
	t_command_and_flag *head2;
	t_command_and_flag *head3;
	t_command_and_flag *head4;

	head1 = malloc(sizeof(t_command_and_flag));
	head2 = malloc(sizeof(t_command_and_flag));
	head3 = malloc(sizeof(t_command_and_flag));
	head4 = malloc(sizeof(t_command_and_flag));
	head1->command=ftstrdup("wc");
	head1->next=0;
	head1->pape=1;
	head1->f_error=0;
	head2->command=ft_strdup("head");
	head2->next=0;
	head2->pape=1;
	head2->f_error=1;
	head3->command=ft_strdup("yes");
	head3->next=0;
	head3->pape=1;
	head3->f_error=0;
	head4->command=NULL;
	head4->next=0;
	head4->pape=4;
	head4->f_error=0;
	head1->next=head2;
	head2->next=head3;
	head3->next=head4;
	functions_launch(&head1);
	//make_pipe test
}


