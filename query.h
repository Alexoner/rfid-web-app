#ifndef QUERY_H
#define QUERY_H

#include "uhf\CommandLib.h"

#define MAXUID 11
#define MAXMAC 10
#define MAXBUF 64
#define MAX_EPC 128
#define MAX_TID 128

#define UHF_COM "COM9"

class RFIDTag
{
public:
	unsigned char EPC[MAX_EPC];//epc data in the tag
	char epc[2*MAX_EPC];//epc converted to string formate
	int EPClen;//EPC data length
	//unsigned char TID[MAX_TID];//tid data in the tag;
	//char tid[2*MAX_TID];//tid converted to string formate
	//int TIDlen;

	RFIDTag(unsigned char *EPC,int EPClen);
};

extern CommandLib *uhf;
extern unsigned char **EPC;
extern int *EPClen;


//function prototypes

char *b2h_string(unsigned char*array,int len);

//initial ultra high frequency reader
int inituhf(CommandLib *&uhf,char *com);

//get inventory and output to the stdout
int inventory(unsigned char **&EPC,int *&EPClen);

//get tid
int gettid(unsigned char *EPC,unsigned char EPClen);

//read the user bank and get the uid,mac
int readuser(unsigned char *EPC,unsigned char len,char *uid,char *mac);

//get uid
int getuid(unsigned char *EPC,int EPClen);

//get mac
int getmac(unsigned char *EPC,unsigned char EPClen);

//get user contents
int getuser(unsigned char *EPC,int EPClen);

//verify the certificate with data stored in the server
int verifycert(unsigned char *TID,unsigned char *MAC);

#endif