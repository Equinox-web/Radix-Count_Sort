#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

/*Radix sort for an array of integers*/

int getDigitInt(int num, int digit) {
    while (digit > 0) {
        num /= 10;
        -- digit;
    }
    return (num % 10);
}

int getDigitStr(std::string str, int digit) {
    return (str[str.size() - digit - 1] - 'a');
}

int radixSortInt(int *arr, int size, int numDigits) { 
    clock_t start, finish;
    start = clock();
    const int len = 10;
    int cnt[len]; 
    int *res = new int[size];
    for (int i = 0; i < numDigits; ++i) {
        for (int j = 0; j < len; ++j)
            cnt[j] = 0;
        for (int j = 0; j < size; ++j) {
            int d = getDigitInt(arr[j], i);
            cnt[d]++;
        }
        int count = 0;
        for (int j = 0; j < len; ++j) {
            int tmp = cnt[j];
            cnt[j] = count;
            count += tmp;
        }
        for (int j = 0; j < size; ++j) {
            int d = getDigitInt(arr[j], i);
            res[cnt[d]] = arr[j];
            cnt[d]++;
        }
        for (int j = 0; j < size; ++j)
            arr[j] = res[j];
    }
    finish = clock();
    return ((double)(finish - start) / CLOCKS_PER_SEC);
}

/*Radix sort for an array to strings*/

double radixSortStr(std::string *arr, int size, int numDigits) {
    clock_t start, finish;
    start = clock();
    const int len = 26;
    int cnt[len]; 
    std::string *res = new std::string[size] {""};
    for (int i = 0; i < numDigits; ++i) {
        for (int j = 0; j < len; ++j)
            cnt[j] = 0;
        for (int j = 0; j < size; ++j) {
            int d = getDigitStr(arr[j], i);
            cnt[d]++;
        }
        int count = 0;
        for (int j = 0; j < len; ++j) {
            int tmp = cnt[j];
            cnt[j] = count;
            count += tmp;
        }
        for (int j = 0; j < size; ++j) {
            int d = getDigitStr(arr[j], i);
            res[cnt[d]] = arr[j];
            cnt[d]++;
        }
        for (int j = 0; j < size; ++j)
            arr[j] = res[j];
    }
    finish = clock();
    return ((double)(finish - start) / CLOCKS_PER_SEC);
}

/*Count sort for an array of integers*/

double countSortInt(int *arr, int size, int num) {
    clock_t start, finish;
    start = clock();
    int *cnt = new int[num];
    for (int i = 0; i < num; ++i)
        cnt[i] = 0;
    for (int i = 0; i < size; ++i)
        ++cnt[arr[i]];
    int idx = 0;
    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < cnt[i]; ++j)
            arr[idx++] = i;
    }
    finish = clock();
    return ((double)(finish - start) / CLOCKS_PER_SEC);
}

/*Count sort for an array to strings*/

double countSortStr(std::string *arr, int size) {
    clock_t start, finish;
    start = clock();
    int *cnt = new int[size];
    std::string *res = new std::string[size] {""};
    for (int i = 0; i < size; ++i)
        cnt[i] = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] < arr[j])
                ++cnt[j];
            else
                ++cnt[i];
        }
    }
    for (int i = 0; i < size; ++i) {
        res[cnt[i]] = arr[i];
    }
    for (int i = 0; i < size; ++i) {
        arr[i] = res[i];
    }
    finish = clock();
    return ((double)(finish - start) / CLOCKS_PER_SEC);
}

int main() {
    int size;
    int *intArr, *copyIntArr;
    std::string *strArr, *copyStrArr;

    std::cout << "size = ";
    std::cin >> size;

    intArr = new int[size];
    copyIntArr = new int[size];
    strArr = new std::string[size];
    copyStrArr = new std::string[size];

    srand(time(NULL));
    for (int i = 0; i < size; ++i) {
        intArr[i] = rand() % 10000;
        strArr[i] = "";
        for (int j = 0; j < 5; ++j)
        strArr[i] += (char) (rand () % 26) + 97; 
        copyIntArr[i] = intArr[i];
        copyStrArr[i] = strArr[i];
    }

    std::cout << "Radix sort, integer array: " << radixSortInt(copyIntArr, size, 5) << std::endl;
    std::cout << "Radix sort, string array: " << radixSortStr(copyStrArr, size, 5) << std::endl;

    for (int i = 0; i < size; ++i) {
        copyIntArr[i] = intArr[i];
        copyStrArr[i] = strArr[i];
    }

    std::cout << "Count sort, integer array: " << countSortInt(copyIntArr, size, 10000) << std::endl;
    std::cout << "Count sort, string array: " << countSortStr(copyStrArr, size) << std::endl;

    delete intArr;
    delete strArr;
    return 0;
}
