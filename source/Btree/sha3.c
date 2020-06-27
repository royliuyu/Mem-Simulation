#include <stdio.h>
#include <string.h>
#include "sha3.h" //keccak-tiny-unrolled.c will be called
#define OUTLEN_MAX_BYTE 64 // 64 Bytes equals to 512 bit
#define SHA3 shake256 //to be set: SHA type, e.g. sha3_224, sha3_512
#pragma warning(disable:4996)

int GenSha3(char* inStr, int outLen)
{	
	//uint8_t (*str)[128]= values;
	//char str[1024]="287.DR97_1056	acsA1	651	Acetyl-coenzyme A synthetase; Catalyzes the conversion of acetate into acetyl-CoA (AcCoA), an essential intermediate at the junction of anabolic and catabolic pathways. AcsA undergoes a two-step reaction. In the first half reaction, AcsA combines acetate with ATP to form acetyl-adenylate (AcAMP) intermediate. In the second half reaction, it can then transfer the acetyl group from AcAMP to the sulfhydryl group of CoA, forming the product AcCoA; Belongs to the ATP-dependent AMP-binding enzyme family";
	uint8_t n;
	//uint32_t i, m;
	uint32_t inLenByte;
	float outLenByte = (float)outLen/8;
	uint8_t out[OUTLEN_MAX_BYTE]={0};
	char getNumber[3]; //use array 3 instead of 2 to avoid around stack corrupt
	//unsigned char* outString = (unsigned char*)malloc(outLen/4); //outLen is of bits
	static char outString[OUTLEN_MAX_BYTE]="";
	int sha3Num=0; 
	
	inLenByte= strlen(inStr); 
	SHA3(out,OUTLEN_MAX_BYTE,inStr,inLenByte);  
	//convert sha3 code from integer array to character array
	for (n=0;n<outLenByte;n++){
		sprintf(getNumber,"%0.2x",out[n]); //keep 0 character when convert
		outString[2*n]=getNumber[0];
		outString[2*n+1]=getNumber[1];
	}
	sscanf(outString,"%x",&sha3Num); //translate char array to int	
	//printf("Sha3 num is£º %d",sha3Num);
	return sha3Num;	

}
