#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<cassert>
#include<stdio.h>
using namespace std;
const int MAX_N = 20000001;

typedef pair<int, string> ID;

int sz = 0;
vector<ID> heap(MAX_N);

void heapPush(ID x){
// inseart a number in a heap;
	int i = sz++;
	while ( i > 0){
		int p = (i-1)/2;
		if(heap[p].first >= x.first) break;
		heap[i] = heap[p];
		i = p;
	}
	heap[i] = x;
}
void heapSort(){
	ID small = heap[0]; // the max number of the heap
	ID last = heap[--sz]; // the last element of heap
	heap[sz] = small;
	int i = 0;
	while(i * 2 + 1 < sz){
		int l = i * 2 + 1, r = i * 2 + 2;
		if( r < sz && heap[r].first > heap[l].first) l = r; // take the max number between two leaves
		if( heap[l].first <= last.first) break; 
		heap[i] = heap[l];
		i = l;
	}
	heap[i] = last;
}

int main(int argc, char *argv[]){

	
	FILE *pFile =  fopen(argv[1], "r");
	assert(pFile);
	
	int index=0, id = 0;
	char name[10];
	time_t start, end, time;
	printf("Reading data file...\n");
	while(fscanf(pFile, "%d %s", &id, name) == 2){
	//	string name1(name);
		ID d{id, name};
	//	d.first = id;
	//	d.second = name1;
//		heapPush(d);
		heap[index] = d;
		index = index + 1;
	}
/*	for(int i = i = 0 ; i < index ; i++){
		printf(" %d %-10.10s \n", heap[i].id, &heap[i].name[0]);
	}
	*/
	printf("Calling the sorting function...\n");
	start = clock();
	for(int i = 0 ; i < index ; i++){
			heapPush(heap[i]);
	}
	for(int i = 0 ; i < index ; i++){
		heapSort();
	//	fprintf(oFile, " %d %-10.10s \n", heap[i].id, &heap[i].name[0]);
	}
	end = clock();
	fclose(pFile);
//	FILE *oFile;
//	oFile = fopen(argv[2], "w+");
//	assert(oFile);
//	printf("Writing the sorted data...\n");
	int init_value = heap[0].first;
	for(int i = 0 ; i < index ; i++){
		if(init_value > heap[i].first){
			printf("Wrong sorting results\n");
			exit(1);
		}
		init_value = heap[i].first;
		printf(" %d %-10.10s \n", heap[i].first, &heap[i].second[0]);
	}
//	fclose(oFile);
	printf("Heapsort time cost: %f \n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("END\n");
	return 0;
}
