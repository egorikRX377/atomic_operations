#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

void foo(atomic<int>& counter)
{
	for (int i = 0; i < 100000; i++)
	{
		counter++;
	}
	mtx.lock();
	cout << "Incrementing has been executed by the thread with id: " << this_thread::get_id() << endl;
	mtx.unlock();
}

int main()
{
	atomic<int> counter(0);

	thread th1(foo, ref(counter));
	thread th2(foo, ref(counter));

	th1.join();
	th2.join();

	cout << "Counter after incrementing: " << counter << endl;

	counter.store(200);
	cout << counter << endl;

	int res = counter.load();
	cout << res << endl;

	int result = counter.fetch_add(200);
	cout << result << endl;

	cout << counter << endl;

	counter += 300;
	cout << counter << endl;

	counter.fetch_sub(300);
	cout << counter << endl;

	if (counter.is_lock_free())
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}

	std::atomic<int> atomicInt(42);
	int expected = 42;
	int desired = 50;

	bool success_weak = atomicInt.compare_exchange_weak(expected, desired);
	std::cout << "Weak exchange: " << std::boolalpha << success_weak << ", atomicInt: " << atomicInt.load() << std::endl;

	return 0;
}