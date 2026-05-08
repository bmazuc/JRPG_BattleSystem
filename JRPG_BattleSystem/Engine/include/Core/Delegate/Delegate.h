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
		if (isIterating)
		{
			pendingBindFunctionHandles.push_back(delegateFunction);		
		}
		else
		{
			functions.push_back(delegateFunction);
		}
		return nextId++;
	}

	// Register a function
	void Unbind(DelegateHandle handle)
	{
		if (isIterating)
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
		isIterating = true;
		for (auto& function : functions)
		{
			function.function(params...);
		}

		for (DelegateFunction<ReturnType, Parameters...>& function : pendingBindFunctionHandles)
		{
			functions.push_back(function);
		}
		pendingBindFunctionHandles.clear();

		for (DelegateHandle& handle : pendingUnbindFunctionHandles)
		{
			InternalUnbind(handle);
		}
		pendingUnbindFunctionHandles.clear();
		isIterating = false;
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
	
	// Are we iterating the delegate functions list ?
	bool isIterating = false;

	// During call, register bind request handles to bind them after
	std::vector<DelegateFunction<ReturnType, Parameters...>> pendingBindFunctionHandles;
	// During call, register unbind request handles to clear them after
	std::vector<DelegateHandle> pendingUnbindFunctionHandles;
};

#endif // __DELEGATE_H_INCLUDED__