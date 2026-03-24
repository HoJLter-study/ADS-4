// Copyright 2021 NNTU-CS
#include <cstdint>
int binSearch(int* arr, int len, int value) {
	int left = 0;
	int right = len - 1;
	int mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (arr[mid] == value) return mid;
		else if (value > arr[mid]) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return -1;
}


int countPairs1(int *arr, int len, int value) {
	uint32_t counter = 0;
	for (int i = 0; i < len; i++) {
		for (int j = i+1; j < len; j++) {
			if ((arr[i] + arr[j]) == value) counter++;
		}
	}
	return counter;
}
int countPairs2(int *arr, int len, int value) {
	uint32_t counter = 0;
	uint16_t left = 0;
	uint16_t right = len-1;
	uint32_t sum;
	while (left <= right) {
		 sum = arr[left] + arr[right];
		if (sum > value) {
			right--;
		}
		else if (sum < value) {
			left++;
		}
		else {
			if (arr[left] == arr[right]) {
				int n = right - left + 1;
				counter += n * (n - 1) / 2;
				break;
			}
			int cur_left_val = arr[left];
			int cur_right_val = arr[right];
			int r_count = 0;
			int l_count = 0;

			while (left <= right && arr[left] == cur_left_val) {
				l_count++;
				left++;
			}
			while(right >= left && arr[right] == cur_right_val) {
				r_count ++;
				right--;
			}
			counter += r_count * l_count;
		}
		
	}
	return counter;
}
int countPairs3(int *arr, int len, int value) {
	int counter = 0;

	for (int k = 0; k < len; k++) {
		int target = value - arr[k];
		int index = binSearch(arr, len, target);
		if (index == -1) continue;

		while (index != -1 && index <= k) {
			index++;
			if (index >= len || arr[index] != target) {
				index = -1;
				break;
			}
		}

		if (index <= k) continue;
		int count = 1;

		int i = index + 1;
		while (i < len && arr[i] == target) {
			i++;
			count++;
		}
		i = index - 1;
		while (i > k && arr[i] == target) {
			i--;
			count++;
		}
		counter += count;
	}
  return counter;
}
