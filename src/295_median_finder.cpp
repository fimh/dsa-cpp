#include <iostream>
#include <vector>
#include <queue>

// Time - O(nlogn), Space - O(n)
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

// Time - O(n), Space - O(n)
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

// Time - O(logn), Space - O(n)
class MedianFinderTwoHeaps
{
    std::priority_queue<int> lo;                                      // max heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> hi; // min heap

public:
    // Adds a number into the data structure.
    void addNum(int num)
    {
        lo.push(num); // Add to max heap

        hi.push(lo.top()); // balancing step
        lo.pop();

        // maintain size property
        if (lo.size() < hi.size())
        {
            lo.push(hi.top());
            hi.pop();
        }
    }

    // Returns the median of current data stream
    double findMedian()
    {
        return lo.size() > hi.size() ? (double)lo.top() : (lo.top() + hi.top()) * 0.5;
    }

    static void test()
    {
        std::cout << "Q295 - find median from data stream (two heaps)" << std::endl;

        MedianFinderTwoHeaps finder = MedianFinderTwoHeaps();
        finder.addNum(5);
        finder.addNum(2);
        finder.addNum(1);
        finder.addNum(39);
        finder.addNum(20);

        std::cout << finder.findMedian() << std::endl;
    }
};