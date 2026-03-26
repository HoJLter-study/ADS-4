// Copyright 2021 NNTU-CS
#include <cstdint>

int binSearch(int *arr, int len, int value) {
  int left = 0;
  int right = len - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (arr[mid] == value)
      return mid;
    else if (value > arr[mid])
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
}

int countPairs1(int *arr, int len, int value) {
  uint32_t counter = 0;
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; j++) {
      if ((arr[i] + arr[j]) == value)
        counter++;
    }
  }
  return counter;
}
int countPairs2(int *arr, int len, int value) {
  uint32_t counter = 0;
  uint32_t left = 0;
  uint32_t right = len - 1;
  // Пишу по поводу сложности алгоритма. Конкретнее - почему здесь сложность не
  // квадратичная, а линейная
  while (left < right) {
    uint32_t sum = arr[left] + arr[right];
    if (sum > value) {
      right--;
    } else if (sum < value) {
      left++;
    } else {
      if (arr[left] ==
          arr[right]) { // Условие для обработки ситуаций типа value = 50, arr =
                        // [10, 20, 25, 25, 25, 25, 30, 40]
        // В данный момент arr[left] == arr[right] индекс left указывает на
        // самый левый элемент массива, а right - на самый правы , т.е. [10, 20,
        // 25, 25, 25, 25, 30, 40]
        //             L^              R^
        // Можно заметить, что в данной ситуации не обязательно вручную
        // перебирать комбинации, не зря же комбинаторику учили

        int n = right - left + 1; // количество 25
        // Используем формулу сочетаний C(n, 2) = n*(n-1)/2
        counter += n * (n - 1) / 2;
        break;
      }
      int cur_left_val = arr[left];
      int cur_right_val = arr[right];
      int r_count = 0;
      int l_count = 0;
      // Два цикла снизу не дают сложность O(n)!
      while (left <= right && arr[left] == cur_left_val) { // двигаемся вправо
        l_count++;
        left++;
      }
      while (right >= left && arr[right] == cur_right_val) { // двигаемся влево
        r_count++;
        right--;
      }
      counter += r_count * l_count; // считаю количество комбинаций X (числа
                                    // слева) Y(чисел справа).
      // Предположим, есть такой массив: [10, 10, 10, 20, 20, 30, 40, 40, 40,
      // 40, 40] мы считаем количество 40, и умножаем на количество 10

      // Таким образом, по каждому элементу мы пробегаем ровно ОДИН раз =>
      // сложность алгоритма O(n)
    }
  }
  return counter;
}
int countPairs3(int *arr, int len, int value) {
  int counter = 0;

  for (int k = 0; k < len; k++) {
    int target = value - arr[k];

    // нет смысла перебирать дальше
    if (arr[k] > target)
      break;

    int index = binSearch(arr, len, target);

    // index может оказаться левее k => двигаем index вправо
    while (index != -1 && index <= k) {
      index++;
      if (index >= len || arr[index] != target) {
        index = -1;
        break;
      }
    }

    if (index == -1)
      continue;

    int local_counter = 1;
    // ->
    int i = 1;
    while (index + i < len && arr[index + i] == target) {
      local_counter++;
      i++;
    }
    // <-
    i = 1;
    while (index - i > k && arr[index - i] == target) {
      local_counter++;
      i++;
    }
    counter += local_counter;
  }
  return counter;
}
