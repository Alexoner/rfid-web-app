/*************************************************************************
    > File Name: retrieve_data.c
    > Author: onerhao
    > Mail: haodu@hustunique.com
    > Created Time: Fri 23 Aug 2013 10:53:57 AM CST
 ************************************************************************/

#include <my_global.h>
#include <mysql.h>

void finish_with_error(MYSQL *con)
{
	fprintf(stderr,"%s\n",mysql_error(con));
	mysql_close(con);
	exit(1);
}

int main(int argc,char **argv)
{
	MYSQL *con=mysql_init(NULL);

	if(con==NULL)
	{
		fprintf(stderr,"mysql_init() failed\n");
		exit(1);
	}

	if(mysql_real_connect(con,"127.0.0.1","user12","34klq*",
				"testdb",0,NULL,0)==NULL)
	{
		finish_with_error(con);
	}

	if(mysql_query(con,"SELECT * FROM Cars"))
	{
		finish_with_error(con);
	}

	MYSQL_RES *result=mysql_store_result(con);
	if(result==NULL)
	{
		finish_with_error(con);
	}

	int num_fields=mysql_num_fields(result);
	//number of fields of this table

	MYSQL_ROW row;			//char **
	MYSQL_FIELD *field;
	while(field=mysql_fetch_field(result))
	{
		printf("%s ",field->name);
	}
	printf("\n");

	while((row=mysql_fetch_row(result)))
	{
		for(int i=0;i<num_fields;i++)
		{
			printf("%s ",row[i]?row[i]:"NULL");
		}
		printf("\n");
	}
	mysql_free_result(result);
	mysql_close(con);
	exit(0);
}
