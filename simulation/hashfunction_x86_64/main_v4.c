//**********************************************************************
//                                                                     *
//               University Of North Carolina Charlotte                *
//                                                                     *
//Program: shake 256 code generator                                    *
//Description: This program is                                         *
//             1. select 's' to generate the SHA3 code of on demanding *
//             bit width , or,                                         *
//			   2. select 't' to cut a dataset from a large dataset     *
//File Name: main.c                                                    *
//File Version: 3.0                                                    *
//                                                                     *
//Programmed by: Yu Liu                                                * 
//                                                                     *
//Input file: input.h											       *
//Output file:output_shake_XXX.dat                                     *
//**********************************************************************  

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "keccak-tiny.h" //keccak-tiny-unrolled.c will be called
#define OUTLEN_MAX_BYTE 64 // 64 Bytes equals to 512 bit
#define SHA3 shake256 //to be set: SHA type, e.g. sha3_224, sha3_512


//defining what of simply cutting dataset
#define SOURCE_DATA "d:/study/protein.info.v11.0.txt"  // // this file has 20 milliion records which shall be download individually
#define TARGET_DATA "d:/temp/dataSet_202K.dat" 

//define what of SHA3
//define FILENAME_INPUT "d:/study/protein.info.v11.0.txt" // 
#define FILENAME_INPUT "d:/temp/dataSet_200k.dat"
#define FILENAME_OUTPUT "d:/temp/shake_200K_32b.dat" // to be set
#define OUTLEN 32// to be set: output bit length
#define DATA_SIZE 200000 //data size to be transfered

#pragma warning(disable:4996)
int main(int argc, char **argv)
{	
	//uint8_t (*str)[128]= values;
	char str[1024];
	char c,ch, test;
	uint8_t n,j;
	uint32_t i, m;
	uint32_t outMask;	
	uint32_t inLenByte;
	uint8_t outLenByte =OUTLEN/8;
	uint8_t outLenChar =OUTLEN/4;
	static uint8_t out[OUTLEN_MAX_BYTE];
	static char fullString[128];
	char getNumber[2];
	uint32_t count;
		

	printf("Please select the function:\n\n\"t\" To transfer the dataset unshaked, \n\"s\" to transfer to sha3 codes. \n ");
	//putchar(ch);
	ch= getchar();
	
	//sha3 translation
	if (ch== 's' | ch=='S')
	{
				//time_t time_log = time(NULL);
				//struct tm* tm_log = localtime(&time_log);
				//uint8_t errNum =0;
	
				FILE  *inputFile;
				inputFile = fopen(FILENAME_INPUT, "r");
				if (!inputFile)
				{
					printf("File of %s can NOT be opened !",FILENAME_INPUT);
					exit(0);
				}
				
			
				FILE *outputFile;//Open file to outpur result
				char *filename=FILENAME_OUTPUT; 
				outputFile=fopen(filename,"w");	
			
				/* output to .h format
				fprintf(outputFile,	"//Shake256-%dbits\n",OUTLEN);
				fprintf(outputFile, "//Log time: %04d-%02d-%02d %02d:%02d:%02d\n\n", tm_log->tm_year + 1900, tm_log->tm_mon + 1, tm_log->tm_mday, tm_log->tm_hour, tm_log->tm_min, tm_log->tm_sec);
				fprintf(outputFile,	"#ifndef OUTPUT_H_ \n");
				fprintf(outputFile,	"#define OUTPUT_H_ \n\n");
				fprintf(outputFile,"extern char sha3Codes[101900][%d]={\n",OUTLEN);
				*/
				
				count = 0;
				//while (fscanf(inputFile,"%[^\n]",str) != EOF) //to translate all data set
				for (i=0;i<DATA_SIZE;i++) //to translate first 200K data record
				{	
					str[1024] = "";
					fscanf(inputFile,"%[^\n]",str);
					getc(inputFile); // skip to \n character
					inLenByte= strlen(str); // the result with this function is incorrect when detect very long words

					SHA3(out,OUTLEN_MAX_BYTE,str,inLenByte);  
			
					//convert sha3 code from integer array to character array
					for (n=0;n<64;n++){
						sprintf(getNumber,"%0.2x",out[n]); //keep 0 character when convert
						fullString[2*n]=getNumber[0];
						fullString[2*n+1]=getNumber[1];			
					}
			
			
					for (j=0; j< outLenChar;j++) //output by Byte
						{
							fprintf(outputFile,"%c",fullString[j]);
							//printf(fullString[j]);
						}
			
						fprintf(outputFile,"\n");	
				count ++;
				}
				printf("%d items are translated to SHA3.\n",count);
				printf("generated data are in the file of %s.",FILENAME_OUTPUT);

				fflush(inputFile);
			 	fclose(inputFile);	
			  	fflush(outputFile);
			 	fclose(outputFile);
	}
	
	//data import
	else if (ch== 't' | ch=='T')
	{
				count = 0;
				FILE  *inputFile;
				inputFile = fopen(SOURCE_DATA, "rb");
				if (!inputFile)
				{
					printf("File of %s can NOT be opened !",SOURCE_DATA);
					exit(0);
				}
				
				FILE *outputFile;//Open file to outpur result
				char *filename=TARGET_DATA; 
				outputFile=fopen(filename,"w");	
				
				for (i=0;i<DATA_SIZE;i++) //to translate first 200K data record
				{	
					fscanf(inputFile,"%[^\n]",str);
					getc(inputFile); // skip to \n character
					
					fprintf(outputFile,"%s\n",str);
				count++; 
				}
				printf("%d items are translated to SHA3.\n",count);
				printf("generated data are in the file of %s.",TARGET_DATA);
				fflush(inputFile);
			 	fclose(inputFile);	
			  	fflush(outputFile);
			 	fclose(outputFile);
	}
	else
	{
		printf("Please input the correct character, Bye !");	
	}

	return 0;
}
