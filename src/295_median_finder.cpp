#include <iostream>
#include <vector>
#include <queue>
#include <set>

// Approach 1 - Simple Sorting
// Store the numbers in a resizable container. Every time you need to output the median,
// sort the container and output the median.
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

// Approach 2 - Insertion Sort
// Keeping our input container always sorted (i.e. maintaining the sorted nature of the container
// as an invariant) via the idea of insertion sort.
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
            // http://www.cplusplus.com/reference/algorithm/lower_bound/?kw=lower_bound
            // equivalent to bisect.bisect_left() in python
            // https://docs.python.org/3.6/library/bisect.html
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

// Approach 3 - Two Heaps
// Maintain two heaps.
// A max-heap to store the smaller half of the input numbers
// A min-heap to store the larger half of the input numbers
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

// Time - O(logn), Space - O(n)
class MedianFinderTwoPointers
{
    std::multiset<int> data;
    std::multiset<int>::iterator lo_median, hi_median;

public:
    MedianFinderTwoPointers() : lo_median(data.end()), hi_median(data.end())
    {
    }

    // Adds a number into the data structure.
    void addNum(int num)
    {
        const size_t n = data.size(); // store previous size

        // std::multiset::insert inserts an element after all elements of equal value
        data.insert(num); // insert into multiset

        if (!n)
        {
            // no elements before, one element now
            lo_median = hi_median = data.begin();
        }
        else if (n & 1)
        {
            // odd size before (i.e. lo == hi), even size now (i.e. hi = lo + 1)
            if (num < *lo_median) // num < lo
                lo_median--;
            else             // num >= hi
                hi_median++; // insertion at end of equal range
        }
        else
        {
            // even size before (i.e. hi = lo + 1), odd size now (i.e. lo == hi)
            if (num > *lo_median && num < *hi_median) // num in between lo and hi
            {
                lo_median++;
                hi_median--;
            }
            else if (num >= *hi_median) // num inserted after hi
                lo_median++;
            else // num <= lo < hi
                // https://stackoverflow.com/a/24858
                lo_median = --hi_median; // insertion at end of equal range spoils lo
        }
    }

    // Returns the median of current data stream
    double findMedian()
    {
        return (*lo_median + *hi_median) * 0.5;
    }

    static void test()
    {
        std::cout << "Q295 - find median from data stream (multiset and two pointers)" << std::endl;

        MedianFinderTwoPointers finder = MedianFinderTwoPointers();
        finder.addNum(5);
        finder.addNum(2);
        finder.addNum(1);
        finder.addNum(39);
        finder.addNum(20);

        std::cout << finder.findMedian() << std::endl;
    }
};