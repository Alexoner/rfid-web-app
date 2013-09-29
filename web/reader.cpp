/*************************************************************************
    > File Name: reader.c
    > Author: onerhao
    > Mail: haodu@hustunique.com
    > Created Time: Thu 22 Aug 2013 06:00:45 PM CST
 ************************************************************************/
#include <WinSock2.h>
#include <Windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "..\mysql\src\certmgmt.h"
#include "..\query.h"
#include "reader.h"


std::vector<RFIDTag> tags;

int queryrow(MYSQL *mysql,char *mac)
{
	MYSQL_RES *result;
	//MYSQL_ROW row;
	char query[QUERY_SIZE];
	//int i=0,field_col=-1;
	strcpy(query,"SELECT  * FROM rfidtag WHERE TID=\'");
	strcat(query,mac);
	strcat(query,"\'");

	if(mysql_query(mysql,query))
	{
		return -1;
	}
	result=mysql_store_result(mysql);
	/*while(field=mysql_fetch_field(result))
	{
		if(strcmp(field->name,"uid")==0)
		{
			field=i;
		}
		else
		{
			i++;
		}
	}*/
	if(mysql_num_rows(result)!=1)
		return -1;
	mysql_free_result(result);
	return 0;
}

MYSQL *connectdbs()
{
	MYSQL *mysql=mysql_init(NULL);
	if(mysql_real_connect(mysql,"127.0.0.1","user12","34klq*",
				"testdb",0,NULL,0)==NULL)
	{
		return NULL;
	}
	return mysql;
}

int verify(char *mac)
{
	MYSQL *mysql=connectdbs();
	if(queryrow(mysql,mac)==0)
	{
		printf("TRUE");
	}
	else
	{
		printf("FALSE");
	}
	return 0;
}

int parse_argument(char *request)
{
	char action[16],arg[128],buf[64];
	int i,l;
	if(!request)
	{
		return -1;
	}
	if((i=sscanf(request,"%[^&]",buf))!=1)
	{
		return -1;
	}
	if((i=sscanf(buf,"%*[^=]=%s",action))!=1)
	{
		return -1;
	}
	if(sscanf(request,"%*[^&]&%[^&]",buf))
	{
		sscanf(buf,"%*[^=]=%s",arg);
	}

	if(strcmp(action,"scan")==0)
	{
		scan();
		//printf("E20494546478545324401C10");
	}
	else if(strcmp(action,"read")==0)
	{
		readmac(arg);
	}
	else if(strcmp(action,"verify")==0)
	{
		verify(arg);
	}
	return 0;
}

char *get_argument()
{
	char *request=NULL;
	char *method=getenv("REQUEST_METHOD");
	if(!method)
	{
		return NULL;
	}
	if(strcmp("GET",method)==0)
	{
		request=getenv("QUERY_STRING");
		if(request)
		{
			//printf("%s",request);
		}
		else
		{
			printf("ERROR");
		}
	}
	return request;
}


int scan()
{
	int i=0;
	if(inituhf(uhf,UHF_COM)==0)
	{
		if(inventory(EPC,EPClen)==0)
		{
			printf("%s",b2h_string(EPC[0],EPClen[0]));
		}
		return 0;
	}
	printf("ERROR");
	return -1;
}

int mysql_gettid(unsigned char *EPC)
{
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL *mysql=mysql_init(NULL);
	char query[QUERY_SIZE];
	if(mysql_real_connect(mysql,"127.0.0.1","user12","34klq*",
		"testdb",0,NULL,0)==NULL)
	{
		return -1;
	}


	strcpy(query,"SELECT  TID FROM RFIDTAG WHERE EPC=\'");
	strcat(query,(const char*)EPC);
	strcat(query,"\'");

	if(mysql_query(mysql,query))
	{
		return -1;
	}
	result=mysql_store_result(mysql);
	if(mysql_num_rows(result)!=1)
	{
		printf("ERROR");
		return -1;
	}
	row=mysql_fetch_row(result);
	printf("%s",row[0]);
	return 0;
}

int readmac(char *epc)
{
	unsigned char len=strlen((const char*)epc)/2;
	unsigned char *EPC=new unsigned char[2*len];
	int i;
	if(inituhf(uhf,UHF_COM)!=0)
	{
		printf("ERROR");
		return -1;
	}
	for(i=0;i<len;i++)
	{
		if(sscanf(epc+2*i,"%02X",EPC+i)!=1)
		{
			delete [] EPC;
			return -1;
		}
		//printf("%02X",EPC[i]);
	}
	//getmac(EPC,len);
	//mysql_gettid((unsigned char*)epc);
	gettid(EPC,len);
	delete EPC;
	return 0;
}


