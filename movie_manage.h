#include <stdio.h>

typedef struct to_movie{
	char * title;
	char * same_title;
	struct to_movie * next;
}to_movie;
typedef struct to_director{
	char * director;
	char * same_director;
}to_director;
typedef struct to_actor{
	char * actor;
	char * same_actor;
	struct to_actor * next;
}to_actor;
typedef struct movie_node{
	int  serial_number;
	char * title;
	char * genre;
	to_director * director;
	char * year;
	char * runtime;
	to_actor * actors;
}m_node; //영화 정보 저장 구조체
typedef struct director_node{
	int serial_number;
	char *name;
	char sex;
	char *birth;
	to_movie * best_movies;
}d_node; //감독 정보 저장 구조체
typedef struct actor_node{
	int serial_number;
	char *name;
	char sex;
	char *birth;
	to_movie *best_movies;
}a_node; //배우 정보 저장 구조체
typedef struct movie_list{
	m_node * m_data;
	struct movie_list * next;
}movie;
typedef struct director_list{
	d_node *d_data;
	struct director_list * next;
}director;
typedef struct actor_list{
	a_node *a_data;
	struct actor_list * next;
}actor;

void link_actor(to_actor * actor)
{
	while(actor->next!=NULL)
		actor=actor->next;
	actor->next = (to_actor *)malloc(sizeof(to_actor));
	actor->next->actor = (char *)malloc(sizeof(char)*100);
	actor->next->actor = strtok(NULL,",");
	actor->next->next = NULL;
}
void movie_log(movie * M_L)
{
	to_actor * tmp=(to_actor*)malloc(sizeof(to_actor));
	tmp->actor = NULL;
	tmp->next=NULL;
	tmp = M_L->m_data->actors;

	while(M_L->next!=NULL)
		M_L=M_L->next;
	FILE *fp1=fopen("movie_log","a");
	fprintf(fp1,"add:");
	fprintf(fp1,"%d:",M_L->m_data->serial_number);
	fputs(M_L->m_data->title,fp1);
	fprintf(fp1,":");
	fputs(M_L->m_data->genre,fp1);
	fprintf(fp1,":");
	fputs(M_L->m_data->director->director,fp1);
	fprintf(fp1,":");
	fputs(M_L->m_data->year,fp1);
	fprintf(fp1,":");
	fputs(M_L->m_data->runtime,fp1);
	fprintf(fp1,":");
	fputs(M_L->m_data->actors->actor,fp1);
	M_L->m_data->actors=M_L->m_data->actors->next;

	if(M_L->m_data->actors!=NULL)
	{
		while(1)
		{
			fprintf(fp1,",");
			fputs(M_L->m_data->actors->actor,fp1);
			M_L->m_data->actors=M_L->m_data->actors->next;
			if(M_L->m_data->actors==NULL)
				break;
		}
	}
	M_L->m_data->actors = tmp;
	fprintf(fp1,"\n");
	fclose(fp1);
}
m_node * input_M_node()
{
	m_node * newnode=(m_node*)malloc(sizeof(m_node));
	newnode->serial_number=0;
	newnode->title=(char*)malloc(sizeof(char)*50);
	newnode->genre=(char*)malloc(sizeof(char)*30);
	newnode->year=(char*)malloc(sizeof(char)*8);
	newnode->runtime=(char*)malloc(sizeof(char)*3);
	char * tmp_actors = (char*)malloc(sizeof(char)*100);
	newnode->actors = (to_actor *)malloc(sizeof(to_actor));
	newnode->actors -> actor  = (char*)malloc(sizeof(char)*100);
	newnode->actors -> next = NULL;
	newnode->actors->same_actor = NULL;
	newnode->director = (to_director *)malloc(sizeof(to_director));
	newnode->director->director = (char*)malloc(sizeof(char)*100);
	newnode->director->same_director = NULL;
	to_actor * tmp=(to_actor*)malloc(sizeof(to_actor));
	tmp->actor = NULL;
	tmp->next=NULL;
	tmp = newnode->actors;

	printf("title > ");
	gets(newnode->title);
	printf("genre > ");
	gets(newnode->genre);
	printf("director > ");
	gets(newnode->director->director);
	printf("year > ");
	gets(newnode->year);
	printf("runtime > ");
	gets(newnode->runtime);
	printf("actors > ");
	gets(tmp_actors);
	printf("@@ Done\n");
	newnode->actors -> actor = strtok(tmp_actors,",");

	while(1)
	{
		link_actor(newnode->actors);
		while(newnode->actors->next->next!=NULL)
			newnode->actors=newnode->actors->next;
		if(newnode->actors->next->actor == NULL)
		{
			free(newnode->actors->next);
			newnode->actors->next=NULL;
			break;
		}
	}
	newnode->actors=tmp;

	char * string = (char*)malloc(200);
	FILE * rfp = fopen("movie_log","r");
	int a=(fseek(rfp,0,0),ftell(rfp)), b=(fseek(rfp,0,2),ftell(rfp));
	if(a==b)
	{
		newnode->serial_number=1;
	}
	else
	{
		rewind(rfp);
		while(!feof(rfp))
		{
			fgets(string,175,rfp);
			if(strcmp(strtok(string,":"),"add") == 0)
			{
				newnode->serial_number+=1;
			}
		}
	}
	fclose(rfp);
	return newnode;
}
void init_M_node(movie ** M_L, m_node * newnode)
{
	*M_L = (movie *)malloc(sizeof(movie));
	(*M_L)->m_data = newnode;
	(*M_L)->next = NULL;

}
void link_M_node(movie * M_L, m_node * newnode)
{
	while(M_L->next!=NULL)
		M_L=M_L->next;
	M_L->next = (movie*)malloc(sizeof(movie));
	M_L->next->m_data = newnode;
	M_L->next->next = NULL;
}
void check_m_node(movie * M_L, m_node * newnode)
{
	to_actor * tmp=(to_actor*)malloc(sizeof(to_actor));
	tmp->next=NULL;
	tmp = M_L->m_data->actors;
	while(M_L->m_data!=newnode)
	{
		if(strcmp(M_L->m_data->title, newnode->title) == 0)
		{
			printf("You have the same record in movie list.\n");
			printf("%d:%s:%s:%s:%s:%s:",M_L->m_data->serial_number,M_L->m_data->title,M_L->m_data->genre,M_L->m_data->director->director,M_L->m_data->year,M_L->m_data->runtime);
			printf("%s,",M_L->m_data->actors->actor);
			while(M_L->m_data->actors->next->next!=NULL)
			{
				printf("%s",M_L->m_data->actors->next->actor);
				printf(",");
				M_L->m_data->actors=M_L->m_data->actors->next;
			}
			printf("%s\n",M_L->m_data->actors->next->actor);
			printf("Do you want to add any way?(Yes/No) ");
			char *c = (char*)malloc(sizeof(char*)*10);
			gets(c);
			while(1)
			{
				if(strcmp(c,"No") == 0 ||  strcmp(c,"N") == 0 || strcmp(c,"no") ==0 || strcmp(c,"n") == 0)
					break;
				else if(strcmp(c,"Yes") == 0 || strcmp(c,"Y") == 0 || strcmp(c,"yes") == 0 || strcmp(c,"y") == 0)
					break;
				else
				{
					printf("Wrong answer. Put again. ");
					gets(c);
				}
			}
			if(strcmp(c,"No") == 0 ||  strcmp(c,"N") == 0 || strcmp(c,"no") == 0 || strcmp(c,"n") == 0)
			{
				while(M_L->next->next!=NULL)
				{
					M_L=M_L->next;
				}
				free(M_L->next);
				M_L->next=NULL;
				return;
			}
			else if(strcmp(c,"Yes") == 0 || strcmp(c,"Y") == 0 || strcmp(c,"yes") == 0 || strcmp(c,"y") == 0)
			{
				break;
			}
		}
		M_L=M_L->next;
	}
	M_L->m_data->actors=tmp;
	movie_log(M_L);
}

void link_title(to_movie * title)
{
	while(title->next!=NULL)
		title=title->next;
	title->next = (to_movie *)malloc(sizeof(to_movie));
	title->next->title = (char *)malloc(sizeof(char)*100);
	title->next->title = strtok(NULL,",");
	title->next->next = NULL;
}
void director_log(director * D_L)
{
	to_movie * tmp=(to_movie*)malloc(sizeof(to_movie));
	tmp->title = NULL;
	tmp->next=NULL;
	tmp = D_L->d_data->best_movies;

	while(D_L->next!=NULL)
		D_L=D_L->next;
	FILE *fp1=fopen("director_log","a");
	fprintf(fp1,"add:");
	fprintf(fp1,"%d:",D_L->d_data->serial_number);
	fputs(D_L->d_data->name,fp1);
	fprintf(fp1,":");
	fputs(&D_L->d_data->sex,fp1);
	fprintf(fp1,":");
	fputs(D_L->d_data->birth,fp1);
	fprintf(fp1,":");
	fputs(D_L->d_data->best_movies->title,fp1);
	D_L->d_data->best_movies=D_L->d_data->best_movies->next;

	if(D_L->d_data->best_movies!=NULL)
	{
		while(1)
		{
			fprintf(fp1,",");
			fputs(D_L->d_data->best_movies->title,fp1);
			D_L->d_data->best_movies=D_L->d_data->best_movies->next;
			if(D_L->d_data->best_movies==NULL)
			break;
		}
	}
	D_L->d_data->best_movies=tmp;
	fprintf(fp1,"\n");
	fclose(fp1);
}
d_node * input_D_node()
{
	d_node * newnode=(d_node*)malloc(sizeof(d_node));
	newnode->serial_number=0;
	newnode->name=(char*)malloc(sizeof(char)*50);
	newnode->birth=(char*)malloc(sizeof(char)*30);
	char * tmp_best_movies = (char*)malloc(sizeof(char)*100);
	newnode->best_movies = (to_movie *)malloc(sizeof(to_movie));
	newnode->best_movies->title  = (char*)malloc(sizeof(char)*100);
	newnode->best_movies -> next = NULL;
	newnode->best_movies->same_title = NULL;
	to_movie * tmp=(to_movie*)malloc(sizeof(to_movie));
	tmp->title = NULL;
	tmp->next=NULL;
	tmp = newnode->best_movies;

	printf("name > ");
	gets(newnode->name);
	printf("genre > ");
	gets(&newnode->sex);
	printf("birth > ");
	gets(newnode->birth);
	printf("best_movies > ");
	gets(tmp_best_movies);
	printf("@@ Done\n");
	newnode->best_movies->title = strtok(tmp_best_movies,",");

	while(1)
	{
		link_title(newnode->best_movies);
		while(newnode->best_movies->next->next!=NULL)
			newnode->best_movies=newnode->best_movies->next;
		if(newnode->best_movies->next->title == NULL)
		{
			free(newnode->best_movies->next);
			newnode->best_movies->next=NULL;
			break;
		}
	}
	newnode->best_movies=tmp;

	char * string = (char*)malloc(200);
	FILE * rfp = fopen("director_log","r");
	int a=(fseek(rfp,0,0),ftell(rfp)), b=(fseek(rfp,0,2),ftell(rfp));
	if(a==b)
	{
		newnode->serial_number=1;
	}
	else
	{
		rewind(rfp);
		while(!feof(rfp))
		{
			fgets(string,175,rfp);
			if(strcmp(strtok(string,":"),"add") == 0)
			{
				newnode->serial_number+=1;
			}
		}
	}
	fclose(rfp);
	return newnode;
}
void init_D_node(director ** D_L, d_node * newnode)
{
	*D_L = (director *)malloc(sizeof(director));
	(*D_L)->d_data = newnode;
	(*D_L)->next = NULL;
}
void link_D_node(director * D_L, d_node * newnode)
{
	while(D_L->next!=NULL)
		D_L=D_L->next;
	D_L->next = (director*)malloc(sizeof(director));
	D_L->next->d_data = newnode;
	D_L->next->next = NULL;
}
void check_d_node(director * D_L, d_node * newnode)
{
	to_movie * tmp=(to_movie*)malloc(sizeof(to_movie));
	tmp->next=NULL;
	tmp = D_L->d_data->best_movies;
	while(D_L->d_data!=newnode)
	{
		if(strcmp(D_L->d_data->name, newnode->name) == 0)
		{
			printf("You have the same record in director list.\n");
			printf("%d:%s:%s:%s:",D_L->d_data->serial_number,D_L->d_data->name,&D_L->d_data->sex,D_L->d_data->birth);
			printf("%s,",D_L->d_data->best_movies->title);
			while(D_L->d_data->best_movies->next->next!=NULL)
			{
				printf("%s",D_L->d_data->best_movies->next->title);
				printf(",");
				D_L->d_data->best_movies=D_L->d_data->best_movies->next;
			}
			printf("%s\n",D_L->d_data->best_movies->next->title);
			printf("Do you want to add any way?(Yes/No) ");
			char *c = (char*)malloc(sizeof(char*)*10);
			gets(c);
			while(1)
			{
				if(strcmp(c,"No") == 0 ||  strcmp(c,"N") == 0 || strcmp(c,"no") ==0 || strcmp(c,"n") == 0)
					break;
				else if(strcmp(c,"Yes") == 0 || strcmp(c,"Y") == 0 || strcmp(c,"yes") == 0 || strcmp(c,"y") == 0)
					break;
				else
				{
					printf("Wrong answer. Put again. ");
					gets(c);
				}
			}
			if(strcmp(c,"No") == 0 ||  strcmp(c,"N") == 0 || strcmp(c,"no") == 0 || strcmp(c,"n") == 0)
			{
				while(D_L->next->next!=NULL)
				{
					D_L=D_L->next;
				}
				free(D_L->next);
				D_L->next=NULL;
				return;
			}
			else if(strcmp(c,"Yes") == 0 || strcmp(c,"Y") == 0 || strcmp(c,"yes") == 0 || strcmp(c,"y") == 0)
			{
				break;
			}
		}
		D_L=D_L->next;
	}
	D_L->d_data->best_movies=tmp;
	director_log(D_L);
}

void actor_log(actor * A_L)
{
	to_movie * tmp=(to_movie*)malloc(sizeof(to_movie));
	tmp->title = NULL;
	tmp->next=NULL;
	tmp = A_L->a_data->best_movies;

	while(A_L->next!=NULL)
		A_L=A_L->next;
	FILE *fp1=fopen("actor_log","a");
	fprintf(fp1,"add:");
	fprintf(fp1,"%d:",A_L->a_data->serial_number);
	fputs(A_L->a_data->name,fp1);
	fprintf(fp1,":");
	fputs(&A_L->a_data->sex,fp1);
	fprintf(fp1,":");
	fputs(A_L->a_data->birth,fp1);
	fprintf(fp1,":");
	fputs(A_L->a_data->best_movies->title,fp1);
	A_L->a_data->best_movies=A_L->a_data->best_movies->next;

	if(A_L->a_data->best_movies!=NULL)
	{
		while(1)
		{
			fprintf(fp1,",");
			fputs(A_L->a_data->best_movies->title,fp1);
			A_L->a_data->best_movies=A_L->a_data->best_movies->next;
			if(A_L->a_data->best_movies==NULL)
			break;
		}
	}
	A_L->a_data->best_movies=tmp;

	fprintf(fp1,"\n");
	fclose(fp1);
}
a_node * input_A_node()
{
	a_node * newnode=(a_node*)malloc(sizeof(a_node));
	newnode->serial_number=0;
	newnode->name=(char*)malloc(sizeof(char)*50);
	newnode->birth=(char*)malloc(sizeof(char)*30);
	char * tmp_best_movies = (char*)malloc(sizeof(char)*100);
	newnode->best_movies = (to_movie *)malloc(sizeof(to_movie));
	newnode->best_movies->title  = (char*)malloc(sizeof(char)*100);
	newnode->best_movies -> next = NULL;
	newnode->best_movies->same_title=NULL;
	to_movie * tmp=(to_movie*)malloc(sizeof(to_movie));
	tmp->title = NULL;
	tmp->next=NULL;
	tmp = newnode->best_movies;

	printf("name > ");
	gets(newnode->name);
	printf("genre > ");
	gets(&newnode->sex);
	printf("birth > ");
	gets(newnode->birth);
	printf("best_movies > ");
	gets(tmp_best_movies);
	printf("@@ Done\n");
	newnode->best_movies->title = strtok(tmp_best_movies,",");

	while(1)
	{
		link_title(newnode->best_movies);
		while(newnode->best_movies->next->next!=NULL)
			newnode->best_movies=newnode->best_movies->next;
		if(newnode->best_movies->next->title == NULL)
		{
			free(newnode->best_movies->next);
			newnode->best_movies->next=NULL;
			break;
		}
	}
	newnode->best_movies=tmp;

	char * string = (char*)malloc(200);
	FILE * rfp = fopen("actor_log","r");
	int a=(fseek(rfp,0,0),ftell(rfp)), b=(fseek(rfp,0,2),ftell(rfp));
	if(a==b)
	{
		newnode->serial_number=1;
	}
	else
	{
		rewind(rfp);
		while(!feof(rfp))
		{
			fgets(string,175,rfp);
			if(strcmp(strtok(string,":"),"add") == 0)
			{
				newnode->serial_number+=1;
			}
		}
	}
	fclose(rfp);
	return newnode;
}
void init_A_node(actor ** A_L, a_node * newnode)
{
	*A_L = (actor *)malloc(sizeof(actor));
	(*A_L)->a_data = newnode;
	(*A_L)->next = NULL;
}
void link_A_node(actor * A_L, a_node * newnode)
{
	while(A_L->next!=NULL)
		A_L=A_L->next;
	A_L->next = (actor*)malloc(sizeof(actor));
	A_L->next->a_data = newnode;
	A_L->next->next = NULL;
}
void check_a_node(actor *A_L, a_node * newnode)
{
	to_movie * tmp=(to_movie*)malloc(sizeof(to_movie));
	tmp->next=NULL;
	tmp = A_L->a_data->best_movies;
	while(A_L->a_data!=newnode)
	{
		if(strcmp(A_L->a_data->name, newnode->name) == 0)
		{
			printf("You have the same record in director list.\n");
			printf("%d:%s:%s:%s:",A_L->a_data->serial_number,A_L->a_data->name,&A_L->a_data->sex,A_L->a_data->birth);
			printf("%s,",A_L->a_data->best_movies->title);
			while(A_L->a_data->best_movies->next->next!=NULL)
			{
				printf("%s",A_L->a_data->best_movies->next->title);
				printf(",");
				A_L->a_data->best_movies=A_L->a_data->best_movies->next;
			}
			printf("%s\n",A_L->a_data->best_movies->next->title);
			printf("Do you want to add any way?(Yes/No) ");
			char *c = (char*)malloc(sizeof(char*)*10);
			gets(c);
			while(1)
			{
				if(strcmp(c,"No") == 0 ||  strcmp(c,"N") == 0 || strcmp(c,"no") ==0 || strcmp(c,"n") == 0)
					break;
				else if(strcmp(c,"Yes") == 0 || strcmp(c,"Y") == 0 || strcmp(c,"yes") == 0 || strcmp(c,"y") == 0)
					break;
				else
				{
					printf("Wrong answer. Put again. ");
					gets(c);
				}
			}
			if(strcmp(c,"No") == 0 ||  strcmp(c,"N") == 0 || strcmp(c,"no") == 0 || strcmp(c,"n") == 0)
			{
				while(A_L->next->next!=NULL)
				{
					A_L=A_L->next;
				}
				free(A_L->next);
				A_L->next=NULL;
				return;
			}
			else if(strcmp(c,"Yes") == 0 || strcmp(c,"Y") == 0 || strcmp(c,"yes") == 0 || strcmp(c,"y") == 0)
			{
				break;
			}
		}
		A_L=A_L->next;
	}
	A_L->a_data->best_movies=tmp;
	actor_log(A_L);
}

void welcome()
{
	printf(">> Welcome to My Movie <<\n");
	printf("File Loading.....\n");
	printf("You can use add, update, delete, search, sort, save, end commands.\n");
}
void m_save(movie *M_L, char * opt2, char* opt3, char* opt4)
{
	if(opt3!=NULL)
		if(strcmp(opt3,"-f")!=0)
		{
			opt4 = "movie_list";
		}
	FILE * fp = fopen(opt4,"w");

	while(M_L!=NULL)
	{
		fprintf(fp,"%d",M_L->m_data->serial_number);
		if(strchr(opt2,'t')!=NULL)
		{
			fprintf(fp,":");
			fputs(M_L->m_data->title,fp);
		}
		if(strchr(opt2,'g')!=NULL)
		{
			fprintf(fp,":");
			fputs(M_L->m_data->genre,fp);
		}
		if(strchr(opt2,'d')!=NULL)
		{
			fprintf(fp,":");
			fputs(M_L->m_data->director->director,fp);
		}
		if(strchr(opt2,'y')!=NULL)
		{
			fprintf(fp,":");
			fputs(M_L->m_data->year,fp);
		}
		if(strchr(opt2,'r')!=NULL)
		{
			fprintf(fp,":");
			fputs(M_L->m_data->runtime,fp);
		}
		if(strchr(opt2,'a')!=NULL)
		{
			to_actor * tmp = (to_actor*)malloc(sizeof(to_actor));
			tmp = M_L->m_data->actors;
			fprintf(fp,":");
			fputs(M_L->m_data->actors->actor,fp);
			while(M_L->m_data->actors->next!=NULL)
				{
					M_L->m_data->actors=M_L->m_data->actors->next;
					fputs(M_L->m_data->actors->actor,fp);
					fprintf(fp,",");
				}
				fputs(M_L->m_data->actors->actor,fp);
				M_L->m_data->actors = tmp;
		}
		if(opt2==NULL)
		{
			to_actor * tmp = (to_actor*)malloc(sizeof(to_actor));
			tmp = M_L->m_data->actors;
			fprintf(fp,":");
			fputs(M_L->m_data->title,fp);
			fprintf(fp,":");
			fputs(M_L->m_data->genre,fp);
			fprintf(fp,":");
			fputs(M_L->m_data->director->director,fp);
			fprintf(fp,":");
			fputs(M_L->m_data->year,fp);
			fprintf(fp,":");
			fputs(M_L->m_data->runtime,fp);
			fprintf(fp,":");
			fputs(M_L->m_data->actors->actor,fp);
			while(M_L->m_data->actors->next!=NULL)
				{
					M_L->m_data->actors=M_L->m_data->actors->next;
					fputs(M_L->m_data->actors->actor,fp);
					fprintf(fp,",");
				}
				fputs(M_L->m_data->actors->actor,fp);
				M_L->m_data->actors = tmp;
		}
		fprintf(fp,"\n");
		M_L= M_L->next;
	}
}
void d_save(director * D_L, char * opt2, char* opt3, char* opt4)
{
	if(opt3!=NULL)
	{
		if(strcmp(opt3,"-f")!=0)
		{
			opt4 = "movie_list";
		}
		FILE * fp = fopen(opt4,"w");

		while(D_L!=NULL)
		{
			fprintf(fp,"%d",D_L->d_data->serial_number);
			if(strchr(opt2,'n')!=NULL)
			{
				fprintf(fp,":");
				fputs(D_L->d_data->name,fp);
			}
			if(strchr(opt2,'s')!=NULL)
			{
				fprintf(fp,":");
				fputs(&D_L->d_data->sex,fp);
			}
			if(strchr(opt2,'b')!=NULL)
			{
				fprintf(fp,":");
				fputs(D_L->d_data->birth,fp);
			}
			if(strchr(opt2,'m')!=NULL)
			{
				to_movie * tmp = (to_movie*)malloc(sizeof(to_movie));
				tmp = D_L->d_data->best_movies;
				fprintf(fp,":");
				fputs(D_L->d_data->best_movies->title,fp);
				while(D_L->d_data->best_movies->next!=NULL)
					{
						D_L->d_data->best_movies=D_L->d_data->best_movies->next;
						fputs(D_L->d_data->best_movies->title,fp);
						fprintf(fp,",");
					}
					fputs(D_L->d_data->best_movies->title,fp);
					D_L->d_data->best_movies = tmp;
			}
			if(opt2==NULL)
			{
				fprintf(fp,":");
				fputs(D_L->d_data->name,fp);
				fprintf(fp,":");
				fputs(&D_L->d_data->sex,fp);
				fprintf(fp,":");
				fputs(D_L->d_data->birth,fp);
				to_movie * tmp = (to_movie*)malloc(sizeof(to_movie));
				tmp = D_L->d_data->best_movies;
				fprintf(fp,":");
				fputs(D_L->d_data->best_movies->title,fp);
				while(D_L->d_data->best_movies->next!=NULL)
					{
						D_L->d_data->best_movies=D_L->d_data->best_movies->next;
						fputs(D_L->d_data->best_movies->title,fp);
						fprintf(fp,",");
					}
					fputs(D_L->d_data->best_movies->title,fp);
					D_L->d_data->best_movies = tmp;
			}
			fprintf(fp,"\n");
			D_L = D_L->next;
		}
	}
}
void a_save(actor * A_L, char * opt2, char* opt3, char* opt4)
{
	if(opt3!=NULL)
	{
		if(strcmp(opt3,"-f")!=0)
		{
			opt4 = "movie_list";
		}
		FILE * fp = fopen(opt4,"w");

		while(A_L!=NULL)
		{
			fprintf(fp,"%d",A_L->a_data->serial_number);
			if(strchr(opt2,'n')!=NULL)
			{
				fprintf(fp,":");
				fputs(A_L->a_data->name,fp);
			}
			if(strchr(opt2,'s')!=NULL)
			{
			fprintf(fp,":");
			fputs(&A_L->a_data->sex,fp);
			}
			if(strchr(opt2,'b')!=NULL)
			{
				fprintf(fp,":");
				fputs(A_L->a_data->birth,fp);
			}
			if(strchr(opt2,'m')!=NULL)
			{
				to_movie * tmp = (to_movie*)malloc(sizeof(to_movie));
				tmp = A_L->a_data->best_movies;
				fprintf(fp,":");
				fputs(A_L->a_data->best_movies->title,fp);
				while(A_L->a_data->best_movies->next!=NULL)
					{
						A_L->a_data->best_movies=A_L->a_data->best_movies->next;
						fputs(A_L->a_data->best_movies->title,fp);
						fprintf(fp,",");
					}
					fputs(A_L->a_data->best_movies->title,fp);
					A_L->a_data->best_movies = tmp;
			}
			if(opt2==NULL)
			{
				fprintf(fp,":");
				fputs(A_L->a_data->name,fp);
				fprintf(fp,":");
				fputs(&A_L->a_data->sex,fp);
				fprintf(fp,":");
				fputs(A_L->a_data->birth,fp);
				to_movie * tmp = (to_movie*)malloc(sizeof(to_movie));
				tmp = A_L->a_data->best_movies;
				fprintf(fp,":");
				fputs(A_L->a_data->best_movies->title,fp);
				while(A_L->a_data->best_movies->next!=NULL)
					{
						A_L->a_data->best_movies=A_L->a_data->best_movies->next;
						fputs(A_L->a_data->best_movies->title,fp);
						fprintf(fp,",");
					}
					fputs(A_L->a_data->best_movies->title,fp);
					A_L->a_data->best_movies = tmp;
			}
			fprintf(fp,"\n");
			A_L = A_L->next;
		}
	}
}
/*int Display_d(director * p){
   int i = 0;
   while(p->next != NULL){
      i++;
      p = p->next;
   }
   return i + 1;
}
void delete_a(actor * p, char * opt2){
  int num = atoi(opt2);
   printf("%d\n",num);
  int number = Display_a(p);
   printf("%d\n", number);
   actor * start = p;
  if(num > number){
    printf("No such record\n");
  }
  else if(num == 1)
  {
    start = p -> next;
    free(p);
      printf("@@Done");
  }
  else
  {
    int y;
    actor * tmp;
    for(y=1; y<num-1; y++)
    {
      p = p->next;
    }
    tmp  = p -> next;
    FILE *fp1=fopen("actor_log","a");
    fprintf(fp1,"delete:");
    fprintf(fp1,"%d:",tmp->a_data->serial_number);
    fputs(tmp->a_data->name,fp1);
    fprintf(fp1,":");
    fputs(&tmp->a_data->sex,fp1);
    fprintf(fp1,":");
    fputs(tmp->a_data->birth,fp1);
    fprintf(fp1,":");
    fputs(tmp->a_data->best_movies,fp1);
    fprintf(fp1,"\n");
    fclose(fp1);
    p -> next = p -> next -> next;
    free(tmp);
    printf("Done@@\n");
  }
}
int Display_a(actor * p){
	int i = 0;
	while(p->next != NULL){
		i++;
		p = p->next;
	}
	return i + 1;
}
void delete_d(director * p, char * opt2){
  int num = atoi(opt2);
   printf("%d\n",num);
  int number = Display_d(p);
   printf("%d\n", number);
  if(num > number){
    printf("No such record\n");
  }
  else if(num == 1)
  {
      director * start;
      start = p;
    p = p -> next;
      FILE *fp1=fopen("director_log","a");
    fprintf(fp1,"delete:");
    fprintf(fp1,"%d:",start->d_data->serial_number);
    fputs(start->d_data->name,fp1);
    fprintf(fp1,":");
    fputs(&start->d_data->sex,fp1);
    fprintf(fp1,":");
    fputs(start->d_data->birth,fp1);
    fprintf(fp1,":");
    fputs(start->d_data->best_movies,fp1);
    fprintf(fp1,"\n");
    fclose(fp1);
    free(start);
    printf("Done@@\n");
  }
  else
  {
    int y;
    director * tmp;
    for(y=1; y<num-1; y++)
    {
      p = p->next;
    }
    tmp  = p -> next;
    FILE *fp1=fopen("director_log","a");
    fprintf(fp1,"delete:");
    fprintf(fp1,"%d:",tmp->d_data->serial_number);
    fputs(tmp->d_data->name,fp1);
    fprintf(fp1,":");
    fputs(&tmp->d_data->sex,fp1);
    fprintf(fp1,":");
    fputs(tmp->d_data->birth,fp1);
    fprintf(fp1,":");
    fputs(tmp->d_data->best_movies,fp1);
    fprintf(fp1,"\n");
    fclose(fp1);
    p -> next = p -> next -> next;
    free(tmp);
    printf("Done@@\n");
  }
}
int Display_m(movie * p){
  int i = 0;
   while(p->next != NULL){
      i++;
      p = p->next;
   }
   return i + 1;
}
void delete_m(movie * p, char * opt2){
	 int num = atoi(opt2);
	 printf("%d\n",num);
	 int number = Display_m(p);
	 printf("%d\n", number);
	 movie * start = p;
	 if(num > number){
		 printf("No such record\n");
	 }
	 else if(num == 1)
	 {
		 start = p -> next;
		 free(p);
		 printf("@@Done");
	 }
	 else
	 {
		 int y;
		 movie * tmp;
		 for(y=1; y<num-1; y++)
		 {
			 p = p->next;
		 }
		 tmp  = p -> next;
		 FILE *fp1=fopen("movie_log","a");
		 fprintf(fp1,"delete:");
		 fprintf(fp1,"%d:",tmp->m_data->serial_number);
		 fputs(tmp->m_data->title,fp1);
		 fprintf(fp1,":");
		 fputs(tmp->m_data->genre,fp1);
		 fprintf(fp1,":");
		 fputs(tmp->m_data->director,fp1);
		 fprintf(fp1,":");
		 fputs(tmp->m_data->year,fp1);
		 fprintf(fp1,":");
		 fputs(tmp->m_data->runtime,fp1);
		 fprintf(fp1,":");
		 fputs(tmp->m_data->actors,fp1);
		 fprintf(fp1,"\n");
		 fclose(fp1);
		 p -> next = p -> next -> next;
		 free(tmp);
		 printf("Done@@\n");
	 }
 }
void print_d(director * D_L){
   while(D_L->next != NULL){
      printf("%s\n",D_L->d_data->name);
      printf("%d\n",D_L->d_data->serial_number);
      D_L = D_L->next;
   }
   printf("%s\n",D_L->d_data->name);
   printf("%d\n",D_L->d_data->serial_number);
}*/
void prompt(char * value, char * command, char * opt1, char * opt2, char * opt3, char * opt4, movie * M_L, director * D_L, actor * A_L,m_node * m_newnode, d_node * d_newnode, a_node * a_newnode)
{
	while(1)
	{
		printf("(movie) ");
		gets(value);
		command = strtok(value," ");
		opt1 = strtok(NULL," ");
		opt2 = strtok(NULL," ");
		opt3 = strtok(NULL," ");
		opt4 = strtok(NULL," ");

		if(strcmp(command,"add")==0)
		{
			if(opt1!=NULL)
			{
				if(!strcmp(opt1,"m"))
				{
					if(M_L==NULL)
					{
						m_newnode = input_M_node();
						init_M_node(&M_L,m_newnode);
						check_m_node(M_L,m_newnode);
					}
					else
					{
						m_newnode = input_M_node();
						link_M_node(M_L,m_newnode);
						check_m_node(M_L,m_newnode);
					}
				}
				else if(!strcmp(opt1,"d"))
				{
					if(D_L==NULL)
					{
						d_newnode = input_D_node();
						init_D_node(&D_L,d_newnode);
						check_d_node(D_L,d_newnode);
					}
					else
					{
						d_newnode = input_D_node();
						link_D_node(D_L,d_newnode);
						check_d_node(D_L,d_newnode);
					}
				}
				else if(!strcmp(opt1,"a"))
				{
					if(A_L==NULL)
					{
						a_newnode = input_A_node();
						init_A_node(&A_L,a_newnode);
						check_a_node(A_L,a_newnode);
					}
					else
					{
						a_newnode = input_A_node();
						link_A_node(A_L,a_newnode);
						check_a_node(A_L,a_newnode);
					}
				}
				else
					printf("Please enter with factor (m|d|a).\n");
			}
			else
				printf("Please enter with factor (m|d|a).\n");
		}
		else if(strcmp(command,"search")==0)
		{

		}
		else if(strcmp(command,"print")==0)
		{

		}
		else if(strcmp(command,"update")==0)
		{

		}
		/*else if(strcmp(command,"delete")==0)
		{
			if(opt1!=NULL)
			{
				if(!strcmp(opt1,"m"))
				{
					delete_m(M_L, opt2);
				}
				else if(!strcmp(opt1,"d"))
				{
					delete_d(D_L, opt2);
				}
				else if(!strcmp(opt1,"a"))
				{
					delete_a(A_L, opt2);
				}
				else
					printf("Please enter with factor (m|d|a).\n");
			}
			else
				printf("Please enter with factor (m|d|a).\n");
		}*/
		else if(strcmp(command,"sort")==0)
		{

		}
		else if(strcmp(command,"save")==0)
		{
			if(opt1!=NULL)
			{
				if(strcmp(opt2,"-f")==0)
				{
					if(strchr(opt1,'m')!=NULL)
					{
						m_save(M_L, opt4, opt2, opt3);
					}
					else if(strchr(opt1,'d')!=NULL)
					{
						d_save(D_L, opt4, opt2, opt3);
					}
					else if(strchr(opt1,'a')!=NULL)
					{
						a_save(A_L, opt4, opt2, opt3);
					}
				}
				else
				{
					if(strchr(opt1,'m')!=NULL)
					{
						m_save(M_L, opt2, opt3, opt4);
					}
					else if(strchr(opt1,'d')!=NULL)
					{
						d_save(D_L, opt2, opt3, opt4);
					}
					else if(strchr(opt1,'a')!=NULL)
					{
						a_save(A_L, opt2, opt3, opt4);
					}
				}
			}
			else
				printf("Please enter necessary factor (m|d|a).\n");
		}
		else if(strcmp(command, "end")==0)
		{
			exit(1);
		}
		else
			printf("Please enter correct command.\n");
	}
}
