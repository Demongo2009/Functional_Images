//
// Created by demongo on 31.01.2020.
//

#ifndef PROJETK7_FUNCTIONAL_H
#define PROJETK7_FUNCTIONAL_H


#include <functional>

template <typename ...Fs>
auto compose(){
	return [&] (auto x) {return x;};
};



// base condition
template <typename F>
auto compose(F&& f)
{
	return [a = std::move(f)](auto&&... args){
		return a(std::move(args)...);
	};
}

// recursive composition
// from compose(a, b, c...) to compose(ab, c...)
template <typename F1, typename F2, typename... Fs>
auto compose(F1&& f1, F2&& f2, Fs&&... fs)
{
	return compose(
			[first = std::move(f1), second = std::move(f2)]
					(auto&&... args){
				return second(first(std::move(args)...));
			},
			std::move(fs)...
	);
}



template <typename F>
auto lift(F&& f)
{
	return [a = std::move(f)](auto&&... args){
		return a(std::move(args)...);
	};
}
//
//template <typename F1, typename  F2>
//auto lift(F1&& f1, F2&& f2)
//{
//	return [a = std::move(f1), b =std::move(f2)](auto x){
//		return b(x);
//	};
//
//}



template <typename F1, typename... Fs>
auto lift(F1&& f1, Fs&&... fs)
{
//	return lift(
//			[first = std::move(f1), second = std::move(f2), ...rest = std::move(fs)]
//					(auto&&... args){
//			},
//			std::move(fs)...
//	);
//	return [a = std::move(f)](auto&&... args){
//		return a(std::move(args)...);
//	}


	return [first = std::move(f1), ...args = std::move(fs)] (auto x) { return std::invoke(first, std::invoke(args , x)... ); };

//	auto fn = std::bind(std::move(f1), std::bind(std::move(f2),std::placeholders::_1));
//	return helper(fn, std::move(fs)...);

}






//template <int I, class... Ts>
//decltype(auto) get(Ts&&... ts) {
//	return std::get<I>(std::forward_as_tuple(ts...));
//}
//
//template <class T, class ...Ts>
//void helper(std::vector<T>& fVector ,T const& first, Ts const&... rest){
//	fVector.push_back(first);
//	if constexpr (sizeof...(rest) > 0) {
//		helper(rest...);
//	}
//}
//
//template <typename ...Args>
//auto compose(Args... args){
//	int argsCount = sizeof...(args);
//	std::vector<void*> functionVector;
////	std::function<void*> previousFunction(int x) = ;
////	for(int i=0; i<argsCount; i++){
////
////	}
//	if(argsCount == 0){
//		return [&, args...] (auto x) { };
//	}
//
//	helper(functionVector, args...);
////	auto function = [&] (auto f) { f(functionVector[argsCount-1]); };
//	void* function = [&] (auto f) { return functionVector[argsCount-1](f); };
//
//	for(int i=argsCount-2; i>=0; i--){
//		(void*)function = (void*)function((void*)functionVector[i]);
//	}
//
////	auto f = [&] (int i) { functionVector[i]; };
//
////	return [] (auto x) { f(argsCount-1)(); };
//	return [&] (auto x)  { return function([&] (auto x) {return x;})(x); };
//
////	auto f = [&, args...] (auto x) {
////		if constexpr (sizeof...(args) > 0) {
////			return [&, args...] (auto x) {};
////		}
////
////	};
////
////	return [&, args...] (auto x) {
//////		return get<0>(args...)(compose(args...)(x));
////		return [&, args...] (auto x) { return f;};
////	};
//}
//
//
//



#endif //PROJETK7_FUNCTIONAL_H
