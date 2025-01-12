#include <iostream>
#include <vector>

int binarySearch(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int main(int argc, char* argv[]) {
    size_t repeats = 1;
    if (argc > 1) repeats = std::stoi(argv[1]);

    double result = 0;
    for (; repeats > 0; repeats--) {
        std::vector<int> data = {1, 3, 5, 7, 9, 11, 13, 34, 53, 67, 89};
        int target = repeats;
        int index = binarySearch(data, target);
        if (index != -1) {
            result += 1;
        } else {
            result += 0;
        }
    }

    std::cout << "Result: " << result << std::endl;
    return 0;
}