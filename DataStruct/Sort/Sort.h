#ifndef __SORT_H__
#define __SORT_H__
#include<iostream>
using std::swap;


void ShellSort(int *arr,int size){
	int gap = size;
	while(gap>1){
		gap = gap/3+1;
		for(int i=gap; i<size; ++i){
			int end = i-gap;
			int key = arr[i];
			while(end>=0 && arr[end] > key){
				arr[end+gap] = arr[end];
				end -= gap;
			}
			arr[end+gap] = key;
		}
	}
}

void AdjustDown(int *arr,int size,int index){
	int parent = index;
	int child = parent*2+1;
	while(child<size){
		if(child+1<size && arr[child+1] > arr[child]){
			child++;
		}
		if(arr[child] > arr[parent]){
			swap(arr[child],arr[parent]);
			parent = child;
			child = parent*2+1;
		}else{
			break;
		}
	}
}

void HeapSort(int *arr,int size){
	for(int i=(size-2)/2; i>=0; --i){
		AdjustDown(arr,size,i);
	}
	int right = size-1;
	while(right>0){
		swap(arr[0],arr[right]);
		AdjustDown(arr,right,0);
		right--;
	}
}

//左右指针法
void QuickSort1(int *arr,int left,int right){
	if(left>=right){
		return ;
	}
	int low = left;
	int high = right;
	int key = right;
	while(low<high){
		while(low<high && arr[low] <= arr[key]){
			++low;
		}
		while(low<high && arr[high] >= arr[key]){
			--high;
		}
		if(low<high)
			swap(arr[low],arr[high]);
	}
	swap(arr[key],arr[low]);

	QuickSort1(arr,left,low-1);
	QuickSort1(arr,low+1,right);
}
//填坑法
void QuickSort2(int *arr,int left,int right){
	if(left>=right){
		return ;
	}
	int low = left;
	int high = right;
	int key = arr[right];
	while(low<high){
		while(low<high && arr[low]<=key){
			++low;
		}
		if(low<high)
			arr[high] = arr[low];
		while(low<high && arr[high]>=key){
			--high;
		}
		if(low<high)
			arr[low] = arr[high];
	}
	arr[low] = key;

	QuickSort2(arr,left,low-1);
	QuickSort2(arr,low+1,right);
}
/*
//前后指针法
void QuickSort3(int *arr,int left,int right){
	if(left>=right){
		return ;
	}
	int prev = left;
	int cur = prev+1;

	int key = right;

	while(cur!=right){
		if(arr[cur] < arr[key] && arr[++prev]!=arr[cur]){
			swap(arr[cur],arr[prev]);
		}
		++cur;
	}

	swap(arr[cur],arr[++prev]);

	QuickSort3(arr,left,prev-1);
	QuickSort3(arr,prev+1,right);
}
*/
//前后指针法
void QuickSort3(int *arr,int left,int right){
	if(left>=right){
		return ;
	}
	int cur = left;
	int prev = cur-1;
	int key = right;
	while(cur!=right){
		if(arr[cur] > arr[key] && ++prev!=cur){
			swap(arr[cur],arr[prev]);
		}
		++cur;
	}
	swap(arr[cur],arr[++prev]);

	QuickSort3(arr,left,prev-1);
	QuickSort3(arr,prev+1,right);
}

void BubbleSort(int *arr,int size){
	bool flag = true;
	for(int i=0; flag&&i<size; ++i){
		flag = false;
		for(int j=size-1; j>i; --j){
			if(arr[j-1] > arr[j]){
				swap(arr[j],arr[j-1]);
				flag = true;
			}
		}
	}
}

void InsertSort(int *arr,int size){
	for(int i=1; i<size; ++i){
		int end = i-1;
		int key = arr[i];
		while(end>=0 && arr[end] > key){
			arr[end+1] = arr[end];
			end--;
		}
		arr[end+1] = key;
	}
}

void SelectSort(int *arr,int size){
	int left = 0;
	int right = size-1;
	while(left<right){
		int max = right;
		int min = left;
		for(int i=left; i<=right; ++i){
			if(arr[max] < arr[i]){
				max = i;
			}
			if(arr[min] > arr[i]){
				min = i;
			}
		}
		swap(arr[left],arr[min]);
		if(max == left){
			max = min;
		}
		swap(arr[right],arr[max]);

		left++;
		right--;
	}
}




#endif


/*
////////////////////////////////////
//文件说明:排序再复习
//作者:高小调
//创建时间:2017年05月29日 星期一 08时20分04秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#ifndef __SORT_H__
#define __SORT_H__
#include<iostream>
using std::swap;
void QuickSort1(int *arr,int left,int right){
	if(left>=right){
		return ;
	}
	int low = left;
	int high = right;
	int key = right;
	while(low<high){
		while(low<high && arr[low] <= arr[key]){
			++low;
		}
		while(low<high && arr[high] >= arr[key]){
			--high;
		}
		if(low<high){
			swap(arr[low],arr[high]);
		}
	}
	swap(arr[low],arr[key]);

	QuickSort1(arr,left,low-1);
	QuickSort1(arr,low+1,right);
}

void QuickSort2(int *arr,int left,int right){
	if(left>=right){
		return ;
	}
	int low = left;
	int high = right;
	int key = arr[right];
	while(low<high){
		while(low<high && arr[low]<=key){
			++low;
		}
		if(low<high)
			arr[high] = arr[low];
		while(low<high && arr[high]>=key){
			--high;
		}
		if(low<high)
			arr[low] = arr[high];
	}
	arr[low] = key;

	QuickSort2(arr,left,low-1);
	QuickSort2(arr,low+1,right);
}

void QuickSort3(int *arr,int left,int right){
	if(left>=right){
		return ;
	}
	int cur = left;
	int prev = cur-1;
	int key = right;
	while(cur!=right){
		if(arr[cur]<arr[key] && arr[++prev] != arr[cur]){
			swap(arr[cur],arr[prev]);
		}
		++cur;
	}
	swap(arr[++prev],arr[cur]);

	QuickSort3(arr,left,prev-1);
	QuickSort3(arr,prev+1,right);
}


void BubbleSort(int *arr,int size){
	bool flag = true;
	for(int i=0; flag&&i<size; ++i){
		flag = false;
		for(int j=size-1; j>i; --j){
			if(arr[j-1] > arr[j]){
				swap(arr[j-1],arr[j]);
				flag = true;
			}
		}
	}
}

void SelectSort(int *arr,int size){
	int left = 0;
	int right = size-1;
	while(left<right){
		int max = right;
		int min = left;
		for(int i=left; i<=right; ++i){
			if(arr[i] > arr[max]){
				max = i;
			}
			if(arr[i] < arr[min]){
				min = i;
			}
		
		}
		swap(arr[min],arr[left]);
		if(max == left){
			max = min;
		}
		swap(arr[max],arr[right]);
		left++;
		right--;
	}
}

void InsertSort(int *arr,int size){
	for(int i=1; i<size; ++i){
		int end = i-1;
		int key = arr[i];
		while(end>=0 && arr[end]>key){
			arr[end+1] = arr[end];
			end--;
		}
		arr[end+1] = key;
	}
}


#endif



/*
////////////////////////////////////
//文件说明:各种排序算法总结
//作者:高小调
//创建时间:2017年05月28日 星期日 17时23分18秒
//开发环境:Kali Linux/g++ v6.3.0
////////////////////////////////////
#ifndef __SORT_H__
#define __SORT_H__
#include<iostream>
using std::swap;

//快速排序1:左右指针法
void QuickSort1(int arr[],int left,int right){
	if(left>=right){
		return ;
	}
	int low = left;
	int high = right;
	int key = arr[right];
	while(low<high){
		while(low<high && arr[low] < key){
			++low;
		}
		while(low<high && arr[high] > key){
			--high;
		}
		swap(arr[low],arr[high]);
	}
	arr[low] = key;

	QuickSort1(arr,left,low-1);
	QuickSort1(arr,low+1,right);
}

//快速排序2:挖坑法
void QuickSort2(int arr[],int left,int right){
	if(left >= right){
		return ;
	}
	int low = left;
	int high = right;
	int key = arr[right];
	while(low<high){
		while(low<high && arr[low] < key){
			++low;
		}
		arr[high] = arr[low];
		while(low<high && arr[high] > key){
			--high;
		}
		arr[low] = arr[high];
	}
	arr[low] = key;
	QuickSort2(arr,left,low-1);
	QuickSort2(arr,low+1,right);
}

//快速排序3:前后指针法
void QuickSort3(int arr[],int left,int right){
	if(left>=right){
		return ;
	}
	int cur = left;
	int prev = cur-1;
	int key = right;
	while(cur!=right){
		if(arr[cur] < arr[key] && arr[++prev] != arr[cur]){
			swap(arr[cur],arr[prev]);
		}
		++cur;
	}
	swap(arr[++prev],arr[cur]);

	QuickSort3(arr,left,prev-1);
	QuickSort3(arr,prev+1,right);
}
//选择排序优化版
void SelectSort(int *arr,int left,int right){
	while(left<right){
		int minIndex = left;
		int maxIndex = right;
		for(int i=left; i<=right; ++i){
			if(arr[maxIndex] < arr[i]){
				maxIndex = i;
			}
			if(arr[minIndex] > arr[i]){
				minIndex = i;
			}
		}
		swap(arr[left],arr[minIndex]);
		if(maxIndex == left){
			maxIndex = minIndex;
		}
		swap(arr[right],arr[maxIndex]);
		left++;
		right--;
	}

}
//堆排序
void AdjustDown(int arr[],int size,int pos){
	int parent = pos;
	int child = parent*2+1;
	while(child<size){
		if(child+1<size && arr[child+1] > arr[child] ){
			child++;
		}
		if(arr[child] > arr[parent]){
			swap(arr[child],arr[parent]);
			parent = child;
			child = parent*2+1;
		}else{
			break;
		}
	}
}
void HeapSort(int arr[],int size){
	//建堆
	for(int i=(size-2)/2; i>=0; --i){
		AdjustDown(arr,size,i);
	}
	//选择
	int right = size-1;
	while(right>0){
		swap(arr[0],arr[right]);
		AdjustDown(arr,right,0);
		right--;
	}
}


//冒泡排序优化版
void BubbleSort(int *arr,int left,int right){
	bool flag = true;
	for(int i=left; flag&&i<right; ++i){
		flag = false;
		for(int j = right; j>i; --j){
			if(arr[j-1]>arr[j]){
				swap(arr[j-1],arr[j]);
				flag = true;
			}
		}
	}
}


//插入排序
void InsertSort(int arr[],int left,int right){
	for(int i=left+1;i<=right;++i){
		int end = i-1;
		int key = arr[i];
		while(end>=0 && arr[end] > key){
			arr[end+1] = arr[end];
			end--;
		}
		arr[end+1] = key;
	}
}

#endif
*/

/***************************************
*文件说明:各种排序算法总结
*作者:高小调
*创建时间:2017年05月03日 星期三 17时53分29秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
/*
//冒泡排序优化
void BubbleSort(int arr[],int size){
	bool flag = true;
	for(int i=0; flag; ++i){
		flag = false;
		for(int j=size-1; j>i; --j){
			if(arr[j-1] > arr[j]){
				int tmp = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = tmp;
				flag = true;
			}
		}
	}
}
//快速排序
void QuickSort(int arr[],int left,int right){
	if(left>=right){
		return ;
	}
	int low = left;
	int high = right;
	int key = right;
	while(low<high){
		while(low<high && arr[low]<=arr[key]){
			++low;
		}
		while(low<high && arr[high]>=arr[key]){
			--high;
		}
		int tmp = arr[low];
		arr[low] = arr[high];
		arr[high] = tmp;
	}
	int tmp = arr[low];
	arr[low] = arr[key];
	arr[key] = tmp;
	QuickSort(arr,left,low-1);
	QuickSort(arr,low+1,right);
}

//选择排序优化
void SelectSort(int arr[],int size){
	for(int i=0; i<size-i;++i){
		int minPos = i;
		int min = arr[i];
		int maxPos = size-i-1;
		int max = arr[size-i-1];
		for(int j=i; j<size-i; ++j){
			if(arr[minPos] > arr[j]){
				minPos = j;
				min = arr[j];
			}
			if(arr[maxPos] < arr[j]){
				maxPos = j;
				max = arr[j];
			}
		}
		arr[minPos] = arr[i];
		arr[i] = min;
		if(i==maxPos){
			maxPos = minPos;
			max = arr[minPos];
		}
		arr[maxPos] = arr[size-i-1];
		arr[size-i-1] = max;
	}
}
//向下调整算法
void AdjustDown(int arr[],int size,int pos){
	int parent = pos;
	int child = pos*2+1;
	while(child<size){
		if(child+1<size && arr[child+1] > arr[child]){
			child++;
		}
		if(arr[child] > arr[parent]){
			int tmp = arr[child];
			arr[child] = arr[parent];
			arr[parent] = tmp;

			parent = child;
			child = parent*2+1;
		}else{
			break;
		}
	}
}

//堆排序
void HeapSort(int arr[],int size){
	//建堆
	for(int i=(size-2)/2; i>=0; --i){
		AdjustDown(arr,size,i);
	}
	//选择排序
	for(int i=0; i<size; ++i){
		int tmp = arr[0];
		arr[0] = arr[size-i-1];
		arr[size-i-1] = tmp;
		AdjustDown(arr,size-i-1,0);
	}
}

//插入排序
void InsertSort(int arr[],int size){
	for(int i=1;i<size;++i){
		int end = i-1;
		int key = arr[i];
		while(end>=0 && arr[end]>key){
			arr[end+1] = arr[end];
			end--;
		}
		arr[end+1] = key;
	}
}

//shell排序
void ShellSort(int arr[],int size){
	int gap = size;
	while(gap>1){
		gap = gap/3+1;
		for(int i=gap; i<size; i++){
			int end = i-gap;
			int key = arr[i];
			while(end>=0 && arr[end]>key){
				arr[end+gap] = arr[end];
				end -= gap;
			}
			arr[end+gap] = key;
		}
	}
}
*/
