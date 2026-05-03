#ifndef __DELEGATE_H_INCLUDED__
#define __DELEGATE_H_INCLUDED__

#include <vector>
#include <functional>

/*
 *	Simple system of multicast callbacks.
 *	Should be upgrade by allowing to remove a specified function (handle system ?) ?
 */
template<typename ReturnType, typename... Parameters>
class Delegate
{
public:
	// Register a function
	void Bind(std::function<ReturnType(Parameters...)> func)
	{
		functions.push_back(func);
	}

	// Call all registered functions
	void Call(Parameters... params)
	{
		for (auto& function : functions)
		{
			function(params...);
		}
	}

	// Clear registered functions list
	void Clear()
	{
		functions.clear();
	}

private:
	// List of all registered functions.
	std::vector<std::function<ReturnType(Parameters...)>> functions;
};

#endif // __DELEGATE_H_INCLUDED__