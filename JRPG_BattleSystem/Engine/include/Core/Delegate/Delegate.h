#ifndef __DELEGATE_H_INCLUDED__
#define __DELEGATE_H_INCLUDED__

#include <vector>
#include <functional>

using DelegateHandle = size_t;

/**
 * Internal delegate binding entry.
 */
template<typename ReturnType, typename... Parameters>
struct DelegateFunction
{
public:
	DelegateHandle id;
	std::function<ReturnType(Parameters...)> function;
};

/*
 *	Multicast callbacks supporting deferred bind/unbind operations during iteration.
 */
template<typename ReturnType, typename... Parameters>
class Delegate
{
public:
	/**
	 * Registers a callback function.
	 * If called during delegate execution, the binding is deferred until iteration completes.
	 * @return Handle used to unbind the callback.
	 */
	template<typename T>
	DelegateHandle Bind(T* object, ReturnType(T::* func)(Parameters...))
	{
		return InternalBind(
			[object, func](Parameters... params)
			{
				(object->*func)(params...);
			}
		);
	}

	template<typename T>
	DelegateHandle Bind(T* object, ReturnType(T::* func)(Parameters...) const)
	{
		return InternalBind(
			[object, func](Parameters... params)
			{
				(object->*func)(params...);
			}
		);
	}

	/**
	 * Unregisters a callback function.
	 * If called during delegate execution, removal is deferred until iteration completes.
	 */
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

	/**
	 * Invokes all bound callbacks.
	 * Bind/unbind requests made during iteration are deferred until invocation completes.
	 */
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

	/**
	 * Removes all registered callbacks.
	 */
	void Clear()
	{
		functions.clear();
	}

private:
	DelegateHandle InternalBind(std::function<ReturnType(Parameters...)> func)
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

	void InternalUnbind(DelegateHandle handle)
	{
		functions.erase(
			std::remove_if(functions.begin(), functions.end(),
				[handle](const DelegateFunction<ReturnType, Parameters...>& function) { return function.id == handle; }),
			functions.end()
		);
	}

	// Registered callback functions.
	std::vector<DelegateFunction<ReturnType, Parameters...>> functions;
	DelegateHandle nextId = 0;
	
	// Prevents iterator invalidation during callback execution.
	bool isIterating = false;

	// Bind requests queued during iteration.
	std::vector<DelegateFunction<ReturnType, Parameters...>> pendingBindFunctionHandles;
	// Unbind requests queued during iteration.
	std::vector<DelegateHandle> pendingUnbindFunctionHandles;
};

#endif // __DELEGATE_H_INCLUDED__