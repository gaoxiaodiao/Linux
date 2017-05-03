/**************************************
*文件说明:各种排序算法总结
*作者:高小调
*创建时间:2017年05月03日 星期三 17时53分29秒
*开发环境:Kali Linux/g++ v6.3.0
****************************************/
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

void SelectSort(int arr[],int size){
	for(int i=0; i<size-i;++i){
		int minPos = i;
		int min = arr[i];
		int maxPos = size-i-1;
		int max = arr[size-i-1];
		for(int j=i+1; j<size-i; ++j){
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
