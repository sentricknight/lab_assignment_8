#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
    int i, j, temp;
    int heapSize = n;
    extraMemoryAllocated = sizeof(int) * n;
 
    for (i = (heapSize - 1) / 2; i >= 0; --i) {
        int k = i;
        int v = arr[k];
        int heap = 0;
 
        while (!heap && 2 * k + 1 < heapSize) {
            int j = 2 * k + 1;
            if (j < heapSize - 1 && arr[j] < arr[j + 1])
                ++j;
            if (v >= arr[j])
                heap = 1;
            else {
                arr[k] = arr[j];
                k = j;
            }
        }
        arr[k] = v;
    }
 
    for (j = n - 1; j > 0; --j) {
        temp = arr[0];
        arr[0] = arr[j];
        arr[j] = temp;
        extraMemoryAllocated += sizeof(int);
 
        int k = 0;
        int v = arr[k];
        int heap = 0;
 
        while (!heap && 2 * k + 1 < j) {
            int child = 2 * k + 1;
            if (child < j - 1 && arr[child] < arr[child + 1])
                ++child;
            if (v >= arr[child])
                heap = 1;
            else {
                arr[k] = arr[child];
                k = child;
            }
        }
        arr[k] = v;
    }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);
        int temp[r - l + 1];
        int i, j, k;
        i = l;
        j = m + 1;
        k = 0;
        
        while (i <= m && j <= r) {
            if (pData[i] <= pData[j]) {
                temp[k] = pData[i];
                i++;
            }
            else {
                temp[k] = pData[j];
                j++;
            }
            k++;
        }
        while (i <= m) {
            temp[k] = pData[i];
            i++;
            k++;
        }
        while (j <= r) {
            temp[k] = pData[j];
            j++;
            k++;
        }
        for (i = l, k = 0; i <= r; i++, k++) {
            pData[i] = temp[k];
        }
        extraMemoryAllocated += (r - l + 1) * sizeof(int);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
