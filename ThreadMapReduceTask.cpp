#include <iostream>
#include <future>
#include <thread>
#include <list>
#include <mutex>

template <typename Iterator, typename MapFunc, typename ReduceFunc>
auto map_reduce(Iterator begin, Iterator end, MapFunc map, ReduceFunc reduce) -> decltype(reduce(map(*begin), map(*begin)))
{
    auto result = map(*begin);
    while (++begin != end)
    {
        result = reduce(result, map(*begin));
    }
    return result;
}

template <typename Iterator, typename MapFunc, typename ReduceFunc>
auto map_reduce(Iterator begin, Iterator end, MapFunc map, ReduceFunc reduce, size_t threads) -> decltype(reduce(map(*begin), map(*begin)))
{
    using T = decltype(map(*begin));

    // calculate chunk size
    auto size = std::distance(begin, end);
    size_t chunk_size = size / threads;
    size_t last_chunk_size = chunk_size + size % threads;

    // make pairs of iterators
    Iterator chunk_begin = begin;
    std::list<std::pair<Iterator, Iterator>> chunks;
    for (size_t i = 0; i < threads; ++i)
    {
        Iterator chunk_end = std::next(chunk_begin, i == threads - 1 ? last_chunk_size : chunk_size);
        chunks.push_back(std::make_pair(chunk_begin, chunk_end));
        chunk_begin = chunk_end;
    }

    // create threads
    std::mutex mutex;
    std::list<T> intermediate_results;
    std::list<std::thread> threads_list;
    for (auto& chunk : chunks)
    {
        threads_list.push_back(std::thread(
            [&mutex, &intermediate_results, &chunk, map, reduce]()
            {
                T result = map(*chunk.first);
                while (++chunk.first != chunk.second)
                {
                    result = reduce(result, map(*chunk.first));
                }

                std::lock_guard<std::mutex> lock(mutex);
                intermediate_results.push_back(result);
            }));
    }

    // wait for threads to finish
    for (auto& thread : threads_list)
    {
        thread.join();
    }

    // reduce intermediate results
    T result = intermediate_results.front();
    intermediate_results.pop_front();
    for (auto& intermediate_result : intermediate_results)
    {
        result = reduce(result, intermediate_result);
    }

    return result;
}

int main()
{
    std::list<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = map_reduce(numbers.begin(), numbers.end(), [](int x) { return x; }, std::plus<int>());
    std::cout << "Sum result: " << result << std::endl;

    auto async_result = map_reduce(numbers.begin(), numbers.end(), [](int x) { return x; }, std::plus<int>(), 3);
    std::cout << "Async sum result: " << async_result << std::endl;

    auto has_even = map_reduce(numbers.begin(), numbers.end(), [](int i) { return i % 2 == 0; }, std::logical_or<bool>());
    std::cout << "Has even result: " << has_even << std::endl;

    auto async_has_even = map_reduce(numbers.begin(), numbers.end(), [](int i) { return i % 2 == 0; }, std::logical_or<bool>(), 4);
    std::cout << "Async has even result: " << async_has_even << std::endl;

    return 0;
}