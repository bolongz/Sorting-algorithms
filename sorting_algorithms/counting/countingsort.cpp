#include<iostream>
#include<vector>
#include<cassert>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
using namespace std;
const int MAX_N = 20000001;

typedef pair<int, string> ID;

int main(int argc, char *argv[]){

	FILE *pFile =  fopen(argv[1], "r");
	assert(pFile);
	int k = -1; //= atoi(argv[2]);
	vector<ID> data(MAX_N);
	vector<ID> sortdata(MAX_N);
	int index=0, id = 0;
	char name[20];
	time_t start, end;
	start = clock();

	printf("Reading data file...\n");
	while(fscanf(pFile, "%d %s", &id, name) == 2){
		//string name1(name);
		if( k < id) k = id;
		ID d={id, name};
//		data[index].first = id;
//		data[index].second = name1;
		data[index] = d;
	//	C[data[index].first]++;
		index = index + 1;
	}
	vector<int> C(k + 1);
	for(int  i= 0 ; i < k ; i++){
		C[i] = 0;
	}
	printf("Calling sorting function...\n");
	for(int i = 0 ; i < index ; i++)
		C[data[i].first]++;

	for(int i = 1 ; i < k + 1 ; i++){
		C[i] += C[i-1];
	}
	for(int i = 0 ; i < index; i++){
		sortdata[C[data[i].first]-1] = data[i];
		C[data[i].first]--;
	}
	end = clock();
//	FILE *oFile;
//	oFile = fopen(argv[3], "w+");
//	assert(oFile);
//	printf("Writing the sorted data...\n");
	int init_value = sortdata[0].first;
	for(int i = 0 ; i < index ; i++){
		if(init_value > sortdata[i].first){
			printf("Wrong sorting results\n");
			exit(1);
		}
		init_value = sortdata[i].first;
		printf(" %d %-10.10s \n", sortdata[i].first, &sortdata[i].second[0]);
	}
	fclose(pFile);
	printf("Counting sort time cost: %f \n", (double)(end - start) / CLOCKS_PER_SEC);
//	fclose(oFile);
	printf("END");
	return 0;
}
