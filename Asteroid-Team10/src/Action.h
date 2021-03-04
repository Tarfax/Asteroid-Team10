#pragma once
#include <functional>

	template<typename T>
struct Action {

	/*struct PacketCallback
	{
		template <typename T>
		PacketCallback(void(T::* mf)(), T* obj)
			: object(obj)
		{
			Func = std::bind(mf, obj, std::placeholders::_1);
		}

		std::function<void()> Func;
		void* object = nullptr;
	};*/

	typedef void (T::* Func)();

public:

	/*static Action* GetInstance(T* obj, void(T::* f)()) {
		return new Action<T>(obj, f);
	}*/


	void Invoke() {
		//(object->func());
	}

public:
	//Action() { }
	Action(void(T::* mf)(), T* obj): object(obj), func(mf) {
		//Func = std::bind(mf, obj, std::placeholders::_1);
	}

private:
	T* object;
	//std::function<void()> Func;
	Func func;

};


