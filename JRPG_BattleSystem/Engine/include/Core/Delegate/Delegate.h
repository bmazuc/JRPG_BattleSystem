#ifndef __DELEGATE_H_INCLUDED__
#define __DELEGATE_H_INCLUDED__

#include <vector>
#include <functional>

using DelegateHandle = size_t;

template<typename ReturnType, typename... Parameters>
struct DelegateFunction
{
public:
	DelegateHandle id;
	std::function<ReturnType(Parameters...)> function;
};

/*
 *	Simple system of multicast callbacks.
 *	Should be upgrade by allowing to remove a specified function (handle system ?) ?
 */
template<typename ReturnType, typename... Parameters>
class Delegate
{
public:
	// Register a function
	DelegateHandle Bind(std::function<ReturnType(Parameters...)> func)
	{
		DelegateFunction<ReturnType, Parameters...> delegateFunction = { nextId, func };
		functions.push_back(delegateFunction);
		return nextId++;
	}

	// Register a function
	void Unbind(DelegateHandle handle)
	{
		if (isCalling)
		{
			pendingUnbindFunctionHandles.push_back(handle);
		}
		else
		{
			InternalUnbind(handle);
		}
	}

	// Call all registered functions
	void Call(Parameters... params)
	{
		isCalling = true;
		for (auto& function : functions)
		{
			function.function(params...);
		}

		for (DelegateHandle& handle : pendingUnbindFunctionHandles)
		{
			InternalUnbind(handle);
		}

		pendingUnbindFunctionHandles.clear();
		isCalling = false;
	}

	// Clear registered functions list
	void Clear()
	{
		functions.clear();
	}

private:
	void InternalUnbind(DelegateHandle handle)
	{
		functions.erase(
			std::remove_if(functions.begin(), functions.end(),
				[handle](const DelegateFunction<ReturnType, Parameters...>& function) { return function.id == handle; }),
			functions.end()
		);
	}

	// List of all registered functions.
	std::vector<DelegateFunction<ReturnType, Parameters...>> functions;
	DelegateHandle nextId = 0;
	
	// Are we calling the delegate functions ?
	bool isCalling = false;
	// During call, register unbind request handles to clear them after
	std::vector<DelegateHandle> pendingUnbindFunctionHandles;
};

#endif // __DELEGATE_H_INCLUDED__