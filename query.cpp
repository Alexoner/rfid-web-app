#include ".\query.h"
#include <iostream>
#include <tchar.h>

CommandLib *uhf;

unsigned char **EPC=NULL;
int *EPClen=NULL;

RFIDTag::RFIDTag(unsigned char *EPC,int EPClen)
{
	memcpy(RFIDTag::EPC,EPC,EPClen);
	//memcpy(Tag::TID,TID,TIDlen);
	RFIDTag::EPClen=EPClen;
	//Tag::TIDlen=TIDlen;
	strcpy(RFIDTag::epc,b2h_string(EPC,EPClen));
	//strcpy(Tag::tid,b2h_string(TID,TIDlen));
}


char *b2h_string(unsigned char*array,int len)
{
	int i;
	char *string=new char[2*len+1];
	for(i=0;i<len;i++)
	{
		sprintf(string+2*i,"%02X",array[i]);
	}
	string[2*len]='\0';
	return string;
}

int inituhf(CommandLib *&uhf,char * com)
{
	uhf = new CommandLib(com);
	unsigned char *firmid,*hardwid;
	uhf->getFirmID(firmid);
	uhf->getHardWID(hardwid);
	if(firmid&&hardwid)
	{
		uhf->setUSAFreq();
		//printf("setting to USA frequency profile");
		return 0;
	}
	else
	{
		return -1;
	}
}

int inventory(unsigned char **&EPC,int *&EPClen)
{
	int ntag;
	//int *EPClen;
	int *rssi;
	int *rssi_i;
	int *rssi_q;
	unsigned char **freq;
	int i=0;
	if(uhf->getInventoryRSSI(EPC,ntag,EPClen,rssi,rssi_i,rssi_q,freq))
	{
		//for(i=0;i<ntag;i++)
		{
			//std::cout<<"EPCLen: "<<EPClen[i]<<" "<<std::endl;
		}
		return 0;
	}
	else
	{
		std::cout<<"Error when getting inventory"<<std::endl;
		return -1;
	}
}

int readuser(unsigned char *EPC,unsigned char len,char *uid,char *mac)
{
	int n=5,flag;
	unsigned char *content,datalen;
	char buf[MAXBUF];
	while(n--)
	{
		flag=uhf->selectTag(EPC,len);
		//printf("select failed");
		if(flag)
		{
			break;
		}
		else
		{
			Sleep(5);
			continue;
		}
	}
	if(!flag)
	{
		return -1;
	}

	uhf->readUser(datalen,content);
	//if(sscanf((char*)content,"%s",buf))
	if(memcpy(content,buf,10))
	{
		if(uid)
		{
			memcpy(buf,uid,10);
			//strcpy(uid,buf);
		}
		//sscanf((char*)content+strlen((char*)buf)+1,"%s",buf);
		memcpy(content+10,buf,10);
		if(mac)
		{
			memcpy(buf,mac,10);
			strcpy(mac,buf);
		}
		return 0;
		//std::cout<<uid<<std::endl; //standard output
	}
	else
	{
		std::cout<<"error in reading uid"<<std::endl;
		return -1;
	}
	return 0;
}

int gettid(unsigned char *EPC,unsigned char len)
{
	int n=5,flag;
	unsigned char datalen;
	unsigned char *data;
	while(n--)
	{
		flag=uhf->selectTag(EPC,len);
		if(flag)
		{
			break;
		}
		else
		{
			Sleep(5);
			continue;
		}
	}
	uhf->readCompleteTID(datalen,data);
	std::cout<<b2h_string(data,datalen)<<std::endl;
	return 0;
}

int getuid(unsigned char *EPC,unsigned char len)
{
	char uid[MAXUID];
	if(readuser(EPC,len,uid,NULL)==0)
	{
		std::cout<<uid<<std::endl;
	}
	else
		return -1;
	return 0;
}

int getmac(unsigned char *EPC,unsigned char len)
{
	char mac[MAXMAC];
	if(readuser(EPC,len,mac,NULL)==0)
	{
		std::cout<<mac<<std::endl;
	}
	else
		return -1;
	return 0;
}
