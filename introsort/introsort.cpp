#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
#include<cassert>
#include<stdio.h>
#include<algorithm>
using namespace std;
const int MAX_N = 20000001;
const int threshold = 16;
typedef pair<int, string> ID;

inline bool comp(ID &x, ID &y){
	return x.first < y.first;
}
inline void unguarded_linear_insert(vector<ID> &a, int last, ID value){
	int next = last;
	--next;
	while (value.first < a[next].first){
		a[last] = a[next];
		last = next;
		--next;
	}
	a[last]= value;
}
void unguarded_insertion_sort(vector<ID> &a, int first, int last){
	for(int i = first; i!=last; i++){
		unguarded_linear_insert(a, i, a[i]);
	}
}
inline void linear_insert(vector<ID> &a, int first, int last){
	ID value = a[last];
	if ( value.first < a[first].first){
		copy_backward(&a[first], &a[last], &a[last+1]);
			a[first] = value ;
	}else{
		unguarded_linear_insert(a, last, value);
	}
}
void insertion_sort(vector<ID> &a, int first, int last){
	if(first == last) return;
	for(int i = first + 1; i != last; i++){
		linear_insert(a, first, i);
	}
}
void final_insertion_sort(vector<ID> &a, int first, int last){
	if((last -first) > threshold){
		insertion_sort(a, first, first + threshold);
		unguarded_insertion_sort(a, first + threshold, last);
	}else{
		insertion_sort(a, first, last);
	}
}

inline int _lg(int n)
{
	int k;
	for (k = 0; n > 1; n >>= 1)
		++k;
	return k;
}
inline ID median(const ID &fr, const ID &se, const ID &th){
	ID med;
	if(fr.first > se.first){
		if(se.first > th.first) return se;
		else return fr.first > th.first? th:fr;
	}else{
		if(se.first < th.first) return se;
		else return fr.first > th.first? fr:th;
	}
}
inline int unguarded_partion(vector<ID> &a, int first, int last, ID pivot ){
	while(true){
		while(a[first].first < pivot.first) ++ first;
		--last;
		while(pivot.first < a[last].first) --last;
		if(!(first < last)) return first;
		swap(a[first], a[last]);
		++first;
	}
}

void introsort_loop(vector<ID> &a,  int first, int last, int depth_limit){
	while((last -first) > threshold){
		if(depth_limit == 0){
			std::partial_sort(&a[first], &a[last], &a[last], comp);
			return;
		}
		--depth_limit;
		int med = (first + last)/2;
		int llast = last -1;
		ID medi = median(a[first], a[med],a[llast]);
		int cut = unguarded_partion(a, first, last, medi);
		introsort_loop(a, cut, last, depth_limit);
		last = cut;
	}
}
inline void introsort(vector<ID> &a, int first, int last){
	if(first != last){
		introsort_loop(a, first, last,  _lg((last - first)) * 2);
		final_insertion_sort(a, first, last);
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
	//	string name1(name);
		ID d{id, name};
//		data[index].first = id;
//		data[index].second = name1;
		data[index] = d;
		index = index + 1;
	}
	printf("Calling bonus sorting function...\n");
	start = clock();
	introsort(data, 0, index);
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
		init_value = data[i].first;
		printf(" %d %-10.10s \n", data[i].first, &(data[i].second)[0]);
	}
	//fclose(oFile);
	printf("Bonus sort time cost: %f \n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("END\n");
	return 0;
}
