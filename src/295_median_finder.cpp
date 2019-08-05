#include <iostream>
#include <vector>

class MedianFinderSimpleSorting
{
    std::vector<int> store;

public:
    // Adds a number into the data structure.
    void addNum(int num)
    {
        store.push_back(num);
    }

    // Returns the median of current data stream
    double findMedian()
    {
        sort(store.begin(), store.end());

        int n = store.size();
        return n & 1 ? store[n / 2] : (store[n / 2 - 1] + store[n / 2]) * 0.5;
    }

    static void test()
    {
        std::cout << "Q295 - find median from data stream (simple sorting)" << std::endl;

        MedianFinderSimpleSorting finder = MedianFinderSimpleSorting();
        finder.addNum(5);
        finder.addNum(2);
        finder.addNum(1);
        finder.addNum(39);
        finder.addNum(20);

        std::cout << finder.findMedian() << std::endl;
    }
};

class MedianFinderInsertionSort
{
    std::vector<int> store; // resize-able container

public:
    // Adds a number into the data structure.
    void addNum(int num)
    {
        if (store.empty())
            store.push_back(num);
        else
            store.insert(lower_bound(store.begin(), store.end(), num), num); // binary search and insertion combined
    }

    // Returns the median of current data stream
    double findMedian()
    {
        int n = store.size();
        return n & 1 ? store[n / 2] : (store[n / 2 - 1] + store[n / 2]) * 0.5;
    }

    static void test()
    {
        std::cout << "Q295 - find median from data stream (insertion sort)" << std::endl;

        MedianFinderInsertionSort finder = MedianFinderInsertionSort();
        finder.addNum(5);
        finder.addNum(2);
        finder.addNum(1);
        finder.addNum(39);
        finder.addNum(20);

        std::cout << finder.findMedian() << std::endl;
    }
};