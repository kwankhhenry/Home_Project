#include <iostream>
#include <unordered_map>

using namespace std;

int calculation(int arr[], int n, int k)
{
	unordered_map<int, int> myMap;
	int sum = 0, count = 0;

	if(n == 0)
		return 0;

	for(int i = 0; i < n; i++)
	{
		sum += (arr[i] - k);

		if(sum == 0)
			count++;

		if(myMap.find(sum) != myMap.end())
		{
			myMap[sum]++;
			count++;

			//count +=myMap[sum];
		}

		myMap[sum]++;
	}
	return count;
}

int main() 
{
	int K = 4;
	int arr[] = {1, 4, 2, 6, 10};
	int N = sizeof(arr)/sizeof(arr[0]); 
	int result = 0;

	result = calculation(arr, N, K);
	cout << "Result is: " << result << endl;
	return 0;
}