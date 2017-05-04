/**************************************
*文件说明:各种排序算法总结
*作者:高小调
*创建时间:2017年05月03日 星期三 17时53分29秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
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
