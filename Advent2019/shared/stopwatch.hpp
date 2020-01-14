template<typename... Args>
void stopwatch(void (*f)(Args...), Args... args)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	(*f)(args...);
	auto end_time = std::chrono::high_resolution_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
	printf("Time: %lld microseconds\n\n", time);
}