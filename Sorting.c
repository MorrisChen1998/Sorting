#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define ARRAY_SIZE 100000
#define SORT_ALGORITHM "heap"

void printArray(int* array, int arraySize){
    for (int i = 0; i < arraySize; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

bool isSorted(int* array, int arraySize) {
    for (int i = 1; i < arraySize; i++) {
        if (array[i] < array[i - 1]) {
            return false;
        }
    }
    return true;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(int* array, int arraySize){
    printf("now using bubble sorting...\n");
    bool clear = true;
	for (int check_round = 0 ; check_round < arraySize - 1 ; check_round++){
	    for(int i = 0 ; i < arraySize - 1 ; i++){
            if (array[i] > array[i + 1]) {
                swap(&array[i], &array[i + 1]);
                clear = false;
            }
	    }
	    if(clear){
	        break;
	    }
	}
}

void selectionSort(int* array, int arraySize){
    printf("now using selection sorting...\n");
    int done = 0;
    while(done < ARRAY_SIZE){
        int min_index = done;
        for(int i = done ; i < ARRAY_SIZE; i++){
            if(array[i] < array[min_index]){
                min_index = i;
            }
        }
        swap(&array[done], &array[min_index]);
        done++;
    }
}

void insertionSort(int* array, int arraySize){
    printf("now using insertion sorting...\n");
    int insert, now;
    for(int i = 1 ; i < ARRAY_SIZE; i++){
        insert = array[i];
        now = i-1;
        while(now >= 0 && insert < array[now]){
            //shift right if insert is still less than array[now]
            array[now+1] = array[now];
            now--;
        }
        array[now+1] = insert;
    }
}

int partition(int* array, int arraySize, int left, int right) {
    int i = left, pivot = array[right];
    
    for (int j = left; j < right; j++) {
        if (array[j] < pivot) {
            swap(&array[i], &array[j]);
            i++;
        }
    }
    swap(&array[i], &array[right]);
    return i;
}

void quickSort(int* array, int arraySize, int left, int right) {
    printf("now using quick sorting...\n");
    if (left >= right) {
        return;
    }
    int separate_point = partition(array, arraySize, left, right);
    quickSort(array, arraySize, left, separate_point - 1);
    quickSort(array, arraySize, separate_point + 1, right);
}

void mergeSort(int* array, int arraySize, int* reg, int left, int right) {
    printf("now using merge sorting...\n");
    int mid = (left + right) / 2;
    if (left >= right) {
        return;
    }
    mergeSort(array, arraySize, reg, left, mid);
    mergeSort(array, arraySize, reg, mid + 1, right);

    int left_point = left, right_point = mid + 1;

    for (int i = left; i <= right; i++) {
        if (left_point == mid + 1) {
            reg[i] = array[right_point++];
            continue;
        }
        if (right_point == right + 1) {
            reg[i] = array[left_point++];
            continue;
        }

        if (array[left_point] < array[right_point]) {
            reg[i] = array[left_point++];
        }
        else {
            reg[i] = array[right_point++];
        }
    }
    for (int i = left; i <= right; i++) {
        array[i] = reg[i];
    }
}

void heapify(int* array, int arraySize, int index) {
    int top = index, left = 2 * index + 1, right = 2 * index + 2;
    if (left < arraySize && array[left] > array[top]) {
        top = left;
    }
    if (right < arraySize && array[right] > array[top]) {
        top = right;
    }
    if (top != index) {
        swap(&array[index], &array[top]);
        heapify(array, arraySize, top);
    }

}

void heapSort(int* array, int arraySize) {
    printf("now using heap sorting...\n");
    for (int i = arraySize / 2 - 1; i >= 0; i--) {
        heapify(array, arraySize, i);
    }
    for (int i = arraySize - 1; i >= 0; i--) {
        swap(&array[0], &array[i]);
        heapify(array, i, 0);
    }
}

typedef struct node{
    int value;
    struct node* next;
}Node;

void bucketSort(int* array, int arraySize, int k) {
    printf("now using bucket sorting...\n");
    Node** bucket = calloc(k, sizeof(Node*));
    for (int i = 0; i < k; i++) {
        bucket[i] = NULL;
    }

    for (int i = 0; i < arraySize; i++) {
        Node* newNode = calloc(1, sizeof(Node));
        newNode->value = array[i];
        newNode->next = NULL;

        int index = array[i] / k;
        if (bucket[index] == NULL) {
            bucket[index] = newNode;
            continue;
        }
        Node *now = bucket[index], *prev = bucket[index];
        if (now->value > newNode->value) {
            bucket[index] = newNode;
            newNode->next = now;
            continue;
        }

        while (now != NULL) {
            if (now->value > newNode->value) {
                prev->next = newNode;
                newNode->next = now;
                break;
            }
            prev = now;
            now = now->next;
        }
        if (now == NULL) {
            prev->next = newNode;
        }
    }
    for (int i = 0, b_i = 0; b_i < k; b_i++) {
        // printf("index [%d] = {", b_i);
        Node* now = bucket[b_i];
        while (now != NULL) {
            // printf("%d, ", now->value);
            array[i++] = now->value;
            now = now->next;
        }
        // printf("}\n");
    }
}


int main()
{
    int* data = calloc(ARRAY_SIZE, sizeof(int));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = (rand() % ARRAY_SIZE + 1);
    }

    char* method = SORT_ALGORITHM;

    clock_t t1, t2;
    t1 = clock();

    if (method == "bubble") {
        bubbleSort(data, ARRAY_SIZE);
    }
    else if (method == "selection") {
        selectionSort(data, ARRAY_SIZE);
    }
    else if(method == "insertion") {
        insertionSort(data, ARRAY_SIZE);
    }
    else if (method == "quick") {
        quickSort(data, ARRAY_SIZE, 0, ARRAY_SIZE - 1);
    }
    else if (method == "merge") {
        int* reg = calloc(ARRAY_SIZE, sizeof(int));
        mergeSort(data, ARRAY_SIZE, reg, 0, ARRAY_SIZE - 1);
    }
    else if (method == "heap") {
        heapSort(data, ARRAY_SIZE);
    }
    else if (method == "bucket") {
        bucketSort(data, ARRAY_SIZE, (int)sqrt(ARRAY_SIZE) + 1);
        //bucketSort(data, ARRAY_SIZE, ARRAY_SIZE);
    }
    else {
        printf("error input\n");
        return 0;
    }

    t2 = clock();
    //printArray(data, ARRAY_SIZE);
    printf("Sorting %s!\n", isSorted(data, ARRAY_SIZE) ? "success" : "failed");
    printf("%f secs\n", (float)(t2 - t1)/1000);

	return 0;
}

