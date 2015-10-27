#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<cassert>
#include<stdio.h>
#include<algorithm>
using namespace std;

const int MAX_N = 20000001;

typedef pair<int, string> ID;

void insertsort(vector<ID> &a, int size){
	for(int i = 1 ; i < size; i++){
		int index = i;
		while(index > 0 && (a[index-1].first > a[index].first)){
			swap(a[index-1], a[index]);
			--index;
		}
	}
}
int main(int argc, char *argv[]){
	
	FILE *pFile =  fopen(argv[1], "r");
	assert(pFile);
	
	vector<ID> data(MAX_N);
	int index=0, id = 0;
	time_t start, end, time;
	char name1[20];
	fscanf(pFile, "%d %s", &data[0].first, name1);
	string name_1(name1);
	data[0].second = name_1;
	index = index + 1;
	char name[20];
	printf("Reading data file...\n");
	while(fscanf(pFile, "%d %s", &id, name) == 2){
		ID d(id, name);
		data[index] = d;
/*		int i = index;
		while(i > 0 && (data[i-1].first > data[i].first)){
			swap(data[i-1], data[i]);
			--i;
		}
		*/
		index = index + 1;
	}
/*	for(int i = 0 ; i < index ; i++){
		printf( " %d %-10.10s \n", data[i].first, &(data[i].second)[0]);
	}
	*/
	printf("Calling the sorting function...\n");
	start = clock();
	insertsort(data, index);
	end = clock();
	fclose(pFile);
//	FILE *oFile;
//	oFile = fopen(argv[2], "w+");
//	assert(oFile);
//	printf("Writing the sorted data...\n");
	int init_value = data[0].first;
	for(int i = 0 ; i < index ; i++){
		if(init_value > data[i].first){
			printf("Wrong sorting restults\n");
			exit(1);
		}
		init_value = data[i].first;
		printf(" %d %-10.10s \n", data[i].first, &(data[i].second)[0]);
	}
	printf("Insertionsort time cost: %f \n", (double)(end - start) / CLOCKS_PER_SEC);
//	fclose(oFile);
	printf("END\n");
	return 0;
}
