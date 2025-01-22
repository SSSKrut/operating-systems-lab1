#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

int binarySearch(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void searchWorker(size_t repeats, std::atomic<int>& result) {
    for (; repeats > 0; repeats--) {
        std::vector<int> data = {1, 3, 5, 7, 9, 11, 13, 34, 53, 67, 89};
        int index = binarySearch(data, repeats);
        result.fetch_add((index != -1) ? 1 : 0);
    }
}

int main(int argc, char* argv[]) {
    size_t repeats = 1;
    size_t threadCount = 1;
    if (argc > 1) repeats = std::stoi(argv[1]);
    if (argc > 2) threadCount = std::stoi(argv[2]);

    std::atomic<int> totalResult{0};
    std::vector<std::thread> threads;

    for (size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(searchWorker, repeats, std::ref(totalResult));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Result: " << static_cast<double>(totalResult.load()) << std::endl;
    return 0;
}