#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//Global variables declarations:
int blockSize;

int cacheSize;

int maxNumberOfBlocks;		//the real number of blocks in cache
int tagLen;
int indexLen;			//index length
int offsetLen;			//Offset Length
static int BIT_LEN = 48;
static int ADDR_LEN = 12;
//**********************************************************************
// Function Name: get_LRU 
// Description: get the LRU Index using counter array of sets
// Input: 1D array *, int index	
// Return: int 
//**********************************************************************
int get_LRU(int dIndex, int lru[]) {
	if(lru[dIndex] == 4) lru[dIndex] = 0;
	return lru[dIndex]++;
}
//**********************************************************************
// Function Name: get_LRUInst 
// Description: get the LRU Instruction Index using counter array of sets
// Input: 1D array *, int Instruction Index	
// Return: int 
//**********************************************************************
int get_LRUInst(int dIndex, int lruInstr[]) {
	if(lruInstr[dIndex] == 4) lruInstr[dIndex] = 0;
	return lruInstr[dIndex]++;
}
//**********************************************************************
// Function Name: hex_to_bin 
// Description: converts hexadecimal values to binary. If the hexadecimal
//		is not 32 bits, then assigns the remaining bits to 0 after
//		conversion.
// Input: 1D array *, int Instruction Index	
// Return: int 
//**********************************************************************
void hex_to_bin(char hex[], unsigned int binary_number[]) {
	int i, j = 0,k, length;
	unsigned int decimal = 0;
	for (length = 0; hex[length] != '\0'; ++length)
		;

	for (i = 0; hex[i] != '\0'; ++i, --length)

	{

		if (hex[i] >= '0' && hex[i] <= '9')

			decimal += (hex[i] - '0') * pow(16, length - 1);

		if (hex[i] >= 'A' && hex[i] <= 'F')

			decimal += (hex[i] - 55) * pow(16, length - 1);

		if (hex[i] >= 'a' && hex[i] <= 'f')

			decimal += (hex[i] - 87) * pow(16, length - 1);

	}

	//At this point, variable decimal contains the hexadecimal number in decimal format.
	while (decimal != 0)

	{

		binary_number[j++] = decimal % 2;

		decimal /= 2;

	}

	if (j < BIT_LEN) {

		for ( k = j; k < BIT_LEN; k++)

			binary_number[k] = 0;

	}

}
//**********************************************************************
// Function Name: indexBinary_to_long 
// Description:converts Binary to long int decimal to use as Index for 
//		arrays.
// Input: 1D array *	
// Return: long  
//**********************************************************************
long indexBinary_to_long(int bin[]) {
	int length, i;
	long decimal = 0;
	for (i = 0; i < indexLen; i++) {
		decimal += bin[i] * pow(2, i);
	}

	return decimal;

}
//**********************************************************************
// Function Name: tagBinary_to_long 
// Description:converts Binary to long int decimal.
// Input: 1D array *	
// Return: long  
//**********************************************************************
long tagBinary_to_long(int bin[]) {
	int length, i;
	long decimal = 0;
	for (i = 0; i < tagLen; i++) {
		decimal += bin[i] * pow(2, i);
	}

	return decimal;

}
//**********************************************************************
// Function Name: get_index *
// Description: get the index from address into decimal value *
// Input: 1D array *
// Return: int *
//**********************************************************************
void get_index(char addr[], int index[]) {

	int binary_number[BIT_LEN];
	int i,j,k;

	hex_to_bin(addr, binary_number);



	for ( j = 0; j < offsetLen; j++) {

		int n = BIT_LEN;

		for ( i = 0; i < n - 1; i++) {

			binary_number[i] = binary_number[i + 1];

		}
		binary_number[n--] = 0;

	}
	/*printf("Binary Number is: ");
	 for(int l=0;l<BIT_LEN;l++)
	 printf("%d", binary_number[l]); */

	for ( k = 0; k < indexLen; k++) {

		index[k] = binary_number[k];

		//      printf("%d", index[k]);
	}
}

//**********************************************************************
// Function Name: get_tag *
// Description: get the tag from address into decimal value *
// Input: 1D array *
// Return: long long int *
//**********************************************************************
void get_tag(char addr[], int tag[]) {
	int binary_number[BIT_LEN];
	int k;
	int l = tagLen - 1;
	hex_to_bin(addr, binary_number);

	for (k = BIT_LEN - 1; k >= tagLen, l >= 0; k--) {

		tag[l] = binary_number[k];
		l--;
	}

}
//**********************************************************************
// Function Name: main 
// Description: Reads argument value and input file.
// Input: 1D , 1D array *
// Return: int
//**********************************************************************
int main(int argc, char *argv[]) {

	//info about trace.din:
	//file size is 832477 entries
	//2: instrunction fetch
	//0: data read
	//1: data write

	//Data initialization:
	//preparing i/o files
	FILE * pfin;

	char *mode = "r";

	//      FILE *pfout;
	long int i = 0; //counter to know the number of operations
	static long int j = 0;
	static long int k = 0;

	//init hits and misses counters
	int hit=0;
	int hit1 = 0;
	int miss = 0;
	int miss1 = 0;

	int op; //from file
	char address[ADDR_LEN]; //from file*/
	int limit = 1; // used as associativity number
	int lc = 0;
	int mc = 0;
	int flag = 0; //match address flag

	char hitORmiss = 'm'; //for debugging
	int lru_index = 0;
	long long requiredTag;
	int maxIndexValue;

	blockSize = atoi(argv[3]);

	cacheSize = atoi(argv[2]) * 1024;

	char cacheCombinedSeparated = *argv[1]; //c for combined and s for separated.
	char assoc = *argv[4]; //1 means direct map, 4 means 4 set associativity
	maxNumberOfBlocks = (int) (cacheSize / blockSize);

	if (assoc == '4') {

		limit = 4;

	} else {

		limit = 1;

	}

	offsetLen = (int) log2(blockSize);

	if (limit == 1) {

		indexLen = (int) log2(maxNumberOfBlocks);	//direct map
	} else {

		indexLen = (int) log2(maxNumberOfBlocks) - 2;

	}
	
	tagLen = BIT_LEN - (indexLen + offsetLen);
	
	maxIndexValue = pow(2, indexLen);

	long  cacheBlockTag[maxIndexValue][4];//to be used in comparison - our max @32K-8B
	long  cacheTagInstr[maxIndexValue][4];	//same for instr
	//arrays for LRU flags
	int lru[maxIndexValue]; //can take vaue from 0 to 3, 3 is the lru.
	int lruInstr[maxIndexValue]; //same but for instructions.

	

	for (lc = 0; lc < maxIndexValue; lc++) {
		for (mc = 0; mc < 4; mc++) {
			//for (sc = 0; sc < 8; sc++)
			//{
			cacheBlockTag[lc][mc] = 0xffffffff;
			cacheTagInstr[lc][mc] = 0xffffffff;
			//}
		}
		lru[lc] = 0; //means empty
		lruInstr[lc] = 0;
	}
	
	//opening file for reading
	pfin = fopen("trace_dhrystone_4m_O0.txt", mode);

	if (pfin == NULL) {

		printf("Can't open input file\n");

		return (0);

	}

	//loop on file till end of file and read data inside
	while (fscanf(pfin, "%d %s", &op, address) != EOF) {

		

		int index[indexLen];
		int tag[tagLen];
		int l;

		
		//prepare required data

		get_index(address, index);

			

		long int dIndex = indexBinary_to_long(index);
		
		get_tag(address, tag);

		
		long int requiredTag = tagBinary_to_long(tag);

		
		////////////////////
		//for combined or data cache:
		if (cacheCombinedSeparated == 'c'
				|| ((cacheCombinedSeparated == 's') && (op != 2))) {
			//search all set of cache
			for (lc = 0; lc < limit; lc++) {
				//init flag for tag found (0 = false)
				flag = 0;
				//for (sc = 0; sc < tagAddressLength; sc++)
				//{
				
				if (requiredTag == cacheBlockTag[(int)dIndex][lc]) {
					//if tag is found, set the flag, increase hit counter, write
					//h in the output file in front of address (for debugging)
					flag = 1;
					hit++; //we found a hit
					hitORmiss = 'h';
					lc = limit; //exit this entry to check the next entry
				} else {
					flag = 0;
				}

				//}
			}
			if (flag == 0) {//not found in any set
				miss++;
				hitORmiss = 'm';
				//for (sc = 0; sc < tagAddressLength; sc++)
				//{
				if (limit == 1) {
					//replacement policy
					cacheBlockTag[(int)dIndex][0] = requiredTag; //only 1 place in DM
				} else {
					///using LRU policy for replacement
					

					lru_index = get_LRU((int)dIndex, lru);
					cacheBlockTag[(int)dIndex][lru_index] = requiredTag;
				}
				//}
			
			}
			j++;
		} else { //instructions cache
			for (lc = 0; lc < limit; lc++) {
				flag = 0;
				//for (sc = 0; sc < tagAddressLength; sc++)
				//{
				if (requiredTag == cacheTagInstr[(int)dIndex][lc]) {
					flag = 1;
					hit1++; //we found a hit
					hitORmiss = 'h';
					lc = limit; //exit this entry to check the next entry	
				} else {
					flag = 0;
				}

				//}		
			}
			if (flag == 0) //not found in any set
				{
				miss1++;
				hitORmiss = 'm';
				//for (sc = 0; sc < tagAddressLength; sc++)
				//{
				if (limit == 1) {
					cacheTagInstr[(int)dIndex][0] = requiredTag;	//use LRU to get it change 0
				} else {
					lru_index = get_LRUInst((int)dIndex, lruInstr);
					cacheTagInstr[(int)dIndex][lru_index] = requiredTag;
				}
				//}
			}
			k++;
		}
		//count number of entries
		i++;
//		printf("%d %s %ld %ld %c\n", op, address, dIndex, requiredTag, hitORmiss);
	}
	//o/p data in file for debugging
	//     		 fprintf(pfout, "%d %s %d %lld %lld\n",op,address,indx,requiredTag,addrInLong,hitORmiss);
	//     		 }
	
	
	//	 fclose(pfout);
	fclose(pfin);
//	float percent =((float)hit/(float)i) * 100 ;
	//-------------------------
	
	printf("Tag length %d\nindex length %d\noffset length %d\n", tagLen, indexLen, offsetLen);
	if(cacheCombinedSeparated=='c'){
	printf("number of requests: %ld \n", i);
	printf("number of miss = %d \nhits = %d \n", miss, hit);
	printf("Hit Percentage: %.4f%\n",((float)(hit)/(float)i) * 100 );
	}
	else{
	printf("number of irequests: %ld \nnumber of drequests: %ld \n", k,j);
	printf("number of dmiss = %d\timiss = %d\ndhits = %d\tihits = %d \n", miss, miss1, hit, hit1);
	printf("Data Hit Percentage: %.4f %\tInstruction Hit Percentage: %.4f %\n",((float)hit/(float)j) * 100,((float)hit1/(float)k) * 100 );
	}
	//-------------------------
	return 0;
}

