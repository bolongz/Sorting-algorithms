#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<cassert>
#include<stdio.h>
using namespace std;
const int MAX_N = 20000001;

typedef pair<int, string> ID;
/*
struct ID{
	int id;
	string name;
};

*/
int arrayPartion(vector<ID> &a, int p, int r){
	ID x = a[r];
	int i = p, j  = 0;
	for(j = p ; j <= r - 1 ; j++){
		//if(a[j].id <= x.id){
		if(a[j].first <= x.first){
			swap(a[i++], a[j]);
		}
	}
	swap(a[i], a[r]);
	return i;
}

void quickSort(vector<ID> &a, int p, int r){
	if( p < r){
		int q = arrayPartion(a, p, r);
		quickSort(a, p, q-1);
		quickSort(a, q + 1, r);
	}
}

int main(int argc, char *argv[]){

	
	FILE *pFile =  fopen(argv[1], "r");
	assert(pFile);
	
	vector<ID> data(MAX_N);
	int index=0, id = 0;
	char name[20];
	time_t start, end, time;
	printf("Reading data file...\n");
	while(fscanf(pFile, "%d %s", &id, name) == 2){
		ID d{id, name};
		data[index] = d;
		index = index + 1;
	}
	printf("Calling sorting function...\n");
	start = clock();
	quickSort(data, 0, index-1);
	end = clock();
	fclose(pFile);
//	FILE *oFile;
//	oFile = fopen(argv[2], "w+");
//	assert(oFile);
//	printf("Writing the sorted data...\n");
	int init_value = data[0].first;
	for(int i = 0 ; i < index ; i++){
		if(init_value > data[i].first){
			printf("Wrong sorting results\n");
			exit(1);
		}
		printf(" %d %-10.10s \n", data[i].first, &data[i].second[0]);
		//fprintf(oFile, " %d %-10.10s \n", data[i].first, &data[i].second[0]);
	}
	printf("Quicksort time cost:%f \n", (double)(end - start) / CLOCKS_PER_SEC);
	//fclose(oFile);
	printf("END\n");
	return 0;
}
