
#ifndef _MY_BASE64_H
#define _MY_BASE64_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
char* base64_encode(const char *src);

int main_test(int argc , char *argv[])
{
	const char in[] = "levin";
	char *res = base64_encode(in);
	printf("%s\n" , res);
	free(res);
	return 0;
}
char* base64_encode(const char *src){

	char* dest;
	char in[4];
	long buf = 0 , tmp = 0;
	unsigned int i = 0 , j = 0 , count = 0;
	char table[] = {
		'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G'
		, 'H' , 'I' , 'J' , 'K' , 'L' , 'M' , 'N'
		, 'O' , 'P' , 'Q' , 'R' , 'S' , 'T' , 'U'
		, 'V' , 'W' , 'X' , 'Y' , 'Z' , 'a' , 'b'
		, 'c' , 'd' , 'e' , 'f' , 'g' , 'h' , 'i'
		, 'j' , 'k' , 'l' , 'm' , 'n' , 'o' , 'p'
		, 'q' , 'r' , 's' , 't' , 'u' , 'v' , 'w'
		, 'x' , 'y' , 'z' , '0' , '1' , '2' , '3'
		, '4' , '5' , '6' , '7' , '8' , '9' , '+'
		, '/' 
	};

	count = strlen(src) / 3 + (strlen(src) % 3 == 0 ? 0 : 1);
	dest = (char*)malloc(count * 4 + 1);
	dest[count * 4] = 0;
	for( ; j < count ; j++){

		memset(in ,0, sizeof(in));
		strncpy(in , src + j * 3 , 3 );

		buf = 0 , buf = 0 , i = 0; 

		for(; i < strlen(in) ; i++){
			tmp = (long)in[i];
			tmp <<= (16 - i * 8);
			buf |= tmp;
		}

		for(i = 0; i < 4 ; i ++){
			if(strlen(in) + 1 > i){
				tmp = buf >> (18 - i * 6);//这里对汉字的操作有问题
				tmp &= 0x3F;
				dest[j * 4 + i] = table[tmp];
			}else{
				dest[j * 4 + i] = '=';
			}
		}
	}
	return dest;
}
char* base64_encode2(const char *src)
{
	char* dest;
	int  count = 0,tail;
	char table[] = {
		'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G'
		, 'H' , 'I' , 'J' , 'K' , 'L' , 'M' , 'N'
		, 'O' , 'P' , 'Q' , 'R' , 'S' , 'T' , 'U'
		, 'V' , 'W' , 'X' , 'Y' , 'Z' , 'a' , 'b'
		, 'c' , 'd' , 'e' , 'f' , 'g' , 'h' , 'i'
		, 'j' , 'k' , 'l' , 'm' , 'n' , 'o' , 'p'
		, 'q' , 'r' , 's' , 't' , 'u' , 'v' , 'w'
		, 'x' , 'y' , 'z' , '0' , '1' , '2' , '3'
		, '4' , '5' , '6' , '7' , '8' , '9' , '+'
		, '/' 
	};
	
	count = strlen(src)/3;
	tail = strlen(src)%3;
	dest = (char*)malloc(4*(count+(tail?1:0))+1);
	dest[4*(count+(tail?1:0))] = 0;
	const char* p_current =src ;
	char *p_dcurrent =dest ;
	int k =0;
	while(count)//处理连续的3个字符
	{
		
		p_dcurrent[0] = table[
			(p_current[0]>>2)&0x3F
			];
		int te = (p_current[0]>>2)&0x3F;
		p_dcurrent[1] = table[
			((p_current[1]>>4)&0xF)|((p_current[0]&0x3)<<4)
			];
		te = ((p_current[1]>>4)&0xF)|((p_current[0]&0x3)<<4);
		p_dcurrent[2] = table[
			((p_current[1]&0xF)<<2)|(((p_current[2]&0xC0)>>6)&0x3)
			];
		te = ((p_current[1]&0xF)<<2)|(((p_current[2]&0xC0)>>6)&0x3);
		p_dcurrent[3] = table[
			p_current[2]&0x3F
			];
		te = p_current[2]&0x3F;
		++k;
		p_current = src+k*3;
		p_dcurrent = dest +k*4;
		--count;
	}
	if(tail == 2)
	{
		p_dcurrent[0] = table[
			(p_current[0]>>2)&0x3F
			];
		p_dcurrent[1] = table[
			((p_current[1]>>4)&0xF)|((p_current[0]&0x3)<<4)
			];
		p_dcurrent[2] = table[
			((p_current[1]&0xF)<<2)
			];
		p_dcurrent[3] = '=';
	}
	else if( tail == 1)
	{
		p_dcurrent[0] = table[
			(p_current[0]>>2)&0x3F
			];
		p_dcurrent[1] = table[
			((p_current[0]&0x3)<<4)
			];
		p_dcurrent[2] = '=';
		p_dcurrent[3] = '=';

	}
	return dest;
}
char* base64_decode(const char *src)
{

	char* dest;
	const char /*in[5],*/*p_current;//4个字符为一组，注意末尾的'\0'
	unsigned int _4bytes,*_3bytes;
	long buf = 0 , tmp = 0;
	unsigned int i = 0 , j = 0 , count = 0;
	i;
	tmp;buf;
	char table[] = {
		'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G'
		, 'H' , 'I' , 'J' , 'K' , 'L' , 'M' , 'N'
		, 'O' , 'P' , 'Q' , 'R' , 'S' , 'T' , 'U'
		, 'V' , 'W' , 'X' , 'Y' , 'Z' , 'a' , 'b'
		, 'c' , 'd' , 'e' , 'f' , 'g' , 'h' , 'i'
		, 'j' , 'k' , 'l' , 'm' , 'n' , 'o' , 'p'
		, 'q' , 'r' , 's' , 't' , 'u' , 'v' , 'w'
		, 'x' , 'y' , 'z' , '0' , '1' , '2' , '3'
		, '4' , '5' , '6' , '7' , '8' , '9' , '+'
		, '/' 
	};
	std::map<char,int> map_ch2i;
	for(int i=0;i<sizeof(table);++i)
	{
		map_ch2i[table[i]] = i;
	}
	map_ch2i['='] = 0xFF;//
	//如果算上末尾的=（最多2个），src的字符长度一定是4的倍数
	count = strlen(src) / 4 ;//+ (strlen(src) % 3 == 0 ? 0 : 1);
	/*
	if(*(src+count-1) == '=')
	{
	//--count;
	if(*(src+count-2) == '=')
	{

	}
	}*/


	dest = (char*)malloc(count * 3 + 1);
	memset(dest,0,count * 3 + 1);
	p_current = dest;
	for( ; j < count ; ++j){
		p_current = src+j*4;
		_4bytes = 0;
		//需要处理src的字符流，转为base64匹配的流
		for(int i=0;i<4;++i)
		{
			//if(p_current[i]!= '=')
				_4bytes |= map_ch2i[p_current[i]]<<i*8;
			//p_current[i] = map_ch2i[p_current[i]];
		}
		//memcpy(&_4bytes,src+j*4,4);//[8=][8=][8][8]
		_3bytes = (unsigned int *)(dest+j*3);
		//
		if((_4bytes&0xFF000000)>>24 == 0xFF)
		{
			if((_4bytes&0x00FF0000)>>16 == 0xFF)//转换为1个字节
			{
				//_3bytes = 0;
				*_3bytes = (_4bytes&0x000000FF)<<2;
				*_3bytes |=(_4bytes&0x00003000)>>12;
			}
			else//转换为2个字节
			{
				*_3bytes = (_4bytes&0x000000FF)<<2;
				*_3bytes |=(_4bytes&0x00003000)>>12;

				*_3bytes |= (_4bytes&0x00000F00)<<4;
				*_3bytes |=(_4bytes&0x003C0000)>>10;
			}

		}
		else//转换为3字节
		{
			*_3bytes =( _4bytes&0x000000FF)<<2;
			*_3bytes |=(_4bytes&0x00003000)>>12;

			*_3bytes |= (_4bytes&0x00000F00)<<4;
			*_3bytes |=(_4bytes&0x003C0000)>>10;

			*_3bytes |= (_4bytes&0x00030000)<<6;
			*_3bytes |= (_4bytes&0x3f000000)>>8;
		}
	}
	return dest;
}
#endif