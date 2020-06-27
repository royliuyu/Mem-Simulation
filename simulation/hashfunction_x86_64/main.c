//**********************************************************************
//                                                                     *
//               University Of North Carolina Charlotte                *
//                                                                     *
//Program: shake 256 code generator                                    *
//Description: This program is to generate the string of path to SHA3  *
//             generated code length is 1-32                           *
//			   called the program of libkeccak-tiny by David Leon Gil  *
//File Name: main.c                                                    *
//File Version: 2.0                                                    *
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
#include "keccak-tiny.h"
#define OUTLEN_MAX_BYTE 64 // 64 Bytes equals to 512 bit
#define SHA3 shake256 //to be set: SHA type, e.g. sha3_224, sha3_512

//set below to select output bit width and file
#define OUTLEN 32// to be set: output bit length
#include "input_100000.h"
#define inputLen 200000
#define FILENAME_OUTPUT "shake_200k_32.dat" // to be set


int main(int argc, char **argv)
{	
	uint8_t (*str)[128]= values;
	uint8_t n,j;
	uint32_t i;
	uint32_t outMask;	
	uint32_t inLenByte;
	uint8_t outLenByte =OUTLEN/8;
	uint8_t outLenChar =OUTLEN/4;
	static uint8_t out[OUTLEN_MAX_BYTE];
	static char fullString[128];
	char getNumber[2];
	
	//time_t time_log = time(NULL);
	//struct tm* tm_log = localtime(&time_log);
	//uint8_t errNum =0;

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
	
	//for(i=0; str[i][0] != NULL;i++)
	for(i=0;i<inputLen;i++)
	{
		inLenByte= strlen(str[i]);
		/* output to .h format
		fprintf(outputFile,"\"%s,",str[i]);
		fprintf(outputFile,"\"%d:",i);
		*/

		SHA3(out,OUTLEN_MAX_BYTE,str[i],inLenByte);  

		//convert sha3 code from integer array to character array
		for (n=0;n<64;n++){
			//itoa(out[n],getCode,16); 
			sprintf(getNumber,"%0.2x",out[n]); //keep 0 character when convert
			fullString[2*n]=getNumber[0];
			fullString[2*n+1]=getNumber[1];			
		}


		for (j=0; j< outLenChar;j++) //output by Byte
			{
				fprintf(outputFile,"%c",fullString[j]);
			}

			fprintf(outputFile,"\n");	
	}
	printf("%d items are coded.\n",i);
	printf("Data are output in the file of %s.",FILENAME_OUTPUT);
	
	/* output to .h format
	fprintf(outputFile,"};\n");
	fprintf(outputFile,"#endif\n");
	*/
		
  	fflush(outputFile);
 	fclose(outputFile);
	return 0;
}

