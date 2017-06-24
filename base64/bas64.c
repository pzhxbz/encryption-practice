#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

char* base64_encode(const char* data, size_t len)
{
	char *des = (char*)malloc(1 + 4 * len / 3);
	memset(des, 0, 1 + 4 * len / 3);
	size_t index = 0;
	size_t i;
	for (i = 0; i < len - 3; i += 3)
	{
		size_t index1 = data[i] >> 2; //first
		size_t index2 = (data[i] % 4) * 16 + (data[i + 1] >> 4); //second
		size_t index3 = (data[i + 1] % 16) * 4 + (data[i + 2] >> 6); //third
		size_t index4 = data[i + 2] % 64;
		des[index++] = base64_table[index1];
		des[index++] = base64_table[index2];
		des[index++] = base64_table[index3];
		des[index++] = base64_table[index4];
	}
	if (len - i == 1)
	{
		size_t index1 = data[i] >> 2;
		size_t index2 = (data[i] % 4) * 16 + (data[i + 1] >> 4); //second
		des[index++] = base64_table[index1];
		des[index++] = base64_table[index2];
		des[index++] = '=';
		des[index++] = '=';
	}
	else if (len - i == 2)
	{
		size_t index1 = data[i] >> 2;
		size_t index2 = (data[i] % 4) * 16 + (data[i + 1] >> 4); //second
		size_t index3 = (data[i + 1] % 16) * 4 + (data[i + 2] >> 6); //third
		des[index++] = base64_table[index1];
		des[index++] = base64_table[index2];
		des[index++] = base64_table[index3];
		des[index++] = '=';
	}
	else
	{
		size_t index1 = data[i] >> 2; //first
		size_t index2 = (data[i] % 4) * 16 + (data[i + 1] >> 4); //second
		size_t index3 = (data[i + 1] % 16) * 4 + (data[i + 2] >> 6); //third
		size_t index4 = data[i + 2] % 64;
		des[index++] = base64_table[index1];
		des[index++] = base64_table[index2];
		des[index++] = base64_table[index3];
		des[index++] = base64_table[index4];
	}
	des[index++] = 0;
	return des;
}

char* base64_decode(char *data)
{

	size_t index = 0;
	size_t len = strlen(data);
	char* des = (char*)malloc(1 + len * 3 / 4);
	memset(des, 0, 1 + len * 3 / 4);
	for (size_t i = 0; i < len; i += 4)
	{
		size_t index1 = strchr(base64_table, data[i]) - base64_table;
		size_t index2 = strchr(base64_table, data[i + 1]) - base64_table;
		size_t index3 = strchr(base64_table, data[i + 2]) - base64_table;
		size_t index4 = strchr(base64_table, data[i + 3]) - base64_table;
		des[index++] = ((index1 % 64) << 2) + ((index2 % 64) >> 4);
		des[index++] = ((index2 % 16) << 4) + ((index3 % 64) >> 2);
		des[index++] = ((index3 % 4) << 6) + (index4 % 64);
	}
	des[index] = 0;
	return des;
}


int main()
{
	char* test = "it is a test";
	char *en_test = base64_encode(test, strlen(test));
	printf("%s\n", en_test);
	char *de_test = base64_decode(en_test);
	printf("%s\n", de_test);
	system("pause");
	return 0;
}

