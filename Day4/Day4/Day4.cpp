// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include <map>

int ToInt(const std::vector<int>& nums)
{
	int ret = 0;
	for (int val : nums)
	{
		ret = ret * 10 + val;
	}
	return ret;
}

std::vector<int> ToVec(int val)
{
	std::vector<int> reverse;
	while (val > 0)
	{
		reverse.push_back(val % 10);
		val /= 10;
	}
	std::vector<int> ret(reverse.rbegin(), reverse.rend());
	return ret;
}

void NextVal(std::vector<int>& nums)
{
	nums = ToVec(ToInt(nums) + 1);

	for (unsigned int i = 1; i < nums.size(); i++)
	{
		if (nums[i] < nums[i - 1])
			nums[i] = nums[i - 1];
	}
}

bool HasRepeat(const std::vector<int>& nums)
{
	for (unsigned int i = 1; i < nums.size(); i++)
	{
		if (nums[i] == nums[i - 1])
			return true;
	}
	return false;
}

bool HasPair(const std::vector<int>& nums)
{
	std::map<int, int> histo;
	for (int val : nums)
	{
		histo[val]++;
	}

	for (auto& iter : histo)
	{
		if (iter.second == 2)
			return true;
	}
	return false;
}

int main()
{
	std::vector<int> lower = { 1, 9, 7, 4, 8, 7 };
	std::vector<int> upper = { 6, 7, 3, 2, 5, 1 };
	int upperInt = ToInt(upper);

	std::vector<int> test = lower;
	NextVal(test);

	std::set<int> valid;

	while (ToInt(test) < upperInt)
	{
		if (HasRepeat(test))
			valid.insert(ToInt(test));
		NextVal(test);
	}

	std::cout << valid.size() << std::endl;

	int count = 0;
	for (int val : valid)
	{
		if (HasPair(ToVec(val)))
			count++;
	}
	std::cout << count << std::endl;
}
