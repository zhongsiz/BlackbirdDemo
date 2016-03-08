#include "YCodec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

YCodec::YCodec()
{
}

YCodec::~YCodec()
{
}


// char to hex code
// error: return -1 
int YCodec::Char2Hex(char ch)
{
	int n = -1;
	switch(ch)
	{
	case '0':	n = 0;	break;
	case '1':	n = 1;	break;
	case '2':	n = 2;	break;
	case '3':	n = 3;	break;
	case '4':	n = 4;	break;
	case '5':	n = 5;	break;
	case '6':	n = 6;	break;
	case '7':	n = 7;	break;
	case '8':	n = 8;	break;
	case '9':	n = 9;	break;
	case 'A':
	case 'a':	n = 10;	break;
	case 'B':
	case 'b':	n = 11;	break;
	case 'C':
	case 'c':	n = 12;	break;
	case 'D':
	case 'd':	n = 13;	break;
	case 'E':
	case 'e':	n = 14;	break;
	case 'F':
	case 'f':	n = 15;	break;
	default:	break;
	}

	return n;
}

// hex to char
// error: return -1 
char YCodec::Hex2Char(unsigned int n)
{
	char ch;
	if(n>=0 && n<=9)	ch = 48 + n;
	else if(n>=10 && n<=15)	ch = 65 - 10 + n;
	else ch = -1;

	return ch;
}

// num^<span style="background-color: rgb(255, 255, 255); ">index</span>
long YCodec::MIndex(int num, int index)
{
	long s = 1;
	int i=0;
	while(i<index)
	{
		s *= num;
		i++;
	}

	return s;
}

// string to hex code
// error: return -1 
long YCodec::String2Hex(char* string, int strlen)
{
	long hex=-1;
	int i=0, n=0;
	char *p = string;
	p += strlen - 1;
	if(string == NULL)	return hex;
	if(strlen <= 0 || strlen > 10)	return hex;

	hex = 0;
	do
	{
		n = Char2Hex(*p--);
		hex += n*MIndex(16, i++);
	}while(i<strlen);

	return hex;
}

// hex to char*
// string==NULL,slen = the size of string(slen as output)
// string!=NULL,input the length of string
// error: return -1
int YCodec::Hex2String(long hex, char* string, int* slen)
{
	char tmp[11] = {0};
	if(hex < 0)	return -1;
	if(string == NULL){// count the length it will be used
		sprintf(tmp, "%x", hex);
		*slen = strlen(tmp);
		return 1;
	}
	memset(string, 0, *slen);
	sprintf(string, "%x", hex);

	return 1;
}

// hex to wchar_t code
// eg: input 0x5e74, return 年
// error: return -1
wchar_t YCodec::Hex2Wchart(long hex)
{
	wchar_t wch = -1;
	if(hex <0)	return wch;
	wch = (wchar_t)hex;

	return wch;
}

// hex string to wchar_t*
// UNICODE十六进制字符串转成中英文
// hexstr每eachchar转换为一个wchar_t
// wchs == NULL, wchsLen as output(the size of wchs will be used)
// error: return -1
int YCodec::HexStr2WChars(char *hexstr, int hexstrlen, int eachchar, wchar_t *wchs, int *wchsLen)
{
	if(hexstr == NULL || hexstrlen <= 0 || eachchar <= 0)	return -1;
	if(wchs == NULL){// count the size wchs it will be used
		*wchsLen = hexstrlen/eachchar + (hexstrlen%eachchar>0 ? 1 : 0);
		return 1;
	}
	memset(wchs, 0, *wchsLen * sizeof(wchar_t));
	char* tmp = new char[eachchar+1];
	char* p = hexstr;
	wchar_t* pwch = wchs;
	for(int i=0; i<hexstrlen; i+=eachchar){
		memset(tmp, 0, eachchar+1);
		// get eachchar char
		for(int j=0; j<eachchar; j++){
			if(i+j > hexstrlen)	break;
			tmp[j] = *p++;
		}
		// char* to hex
		long hex = String2Hex(tmp, strlen(tmp));
		if(hex == -1)	continue;
		// hex to wchar_t
		*pwch++ = Hex2Wchart(hex);
	}

	if(tmp)	delete []tmp;

	return 1;
}

// wchar_t to hex code
long YCodec::Wchart2Hex(wchar_t wch)
{
	return (long)wch;
}

// wchar_t* to char*(hex string)
// 中英文转成UNICODE十六进制字符串
// eachchar用于控制每个wchar_t转换成多少个char字符
// hexstr == NULL,hexstrlen as output(the size of hexstr will be used)
// error: return -1
int YCodec::Wchart2HexStr(wchar_t *wchs, int wchslen, int eachchar, char* hexstr, int* hexstrlen)
{
	if(wchs == NULL || wchslen <= 0 || eachchar <= 0)	return -1;
	if(hexstr == NULL){// count the size of hexstr will be used
		*hexstrlen = wchslen*eachchar;
		return 1;
	}
	memset(hexstr, 0, *hexstrlen);
	char* p = hexstr;
	wchar_t* pwch = wchs;
	char* tmp = new char[eachchar+1];
	for(int i=0; i<wchslen; i++){
		// wchar_t to hex
		long hex = Wchart2Hex(*pwch++);
		// hex to char*
		int charlen = 0;
		if(Hex2String(hex, NULL, &charlen) != -1){
			char* str = new char[charlen+1];
			memset(str, 0, charlen+1);
			int n = Hex2String(hex, str, &charlen);
			if(n != -1){
				int k=0;
				memset(tmp, 0, eachchar+1);
				for(k=0; k<eachchar-charlen; k++)	tmp[k] = '0';
				tmp = strcat(tmp, str);
				p = strcat(p, tmp);
			}
			if(str)	delete []str;
		}
		if(i > *hexstrlen)	break;
	}
	if(tmp)	delete []tmp;

	return 1;
}
