#pragma once

namespace AgoraClrLibrary {
	template<typename ...T>
	public ref struct AT {
		delegate void Type(T...);
	};

	template<>
	public ref struct AT<> {
		delegate void Type();
	};

	template<typename R, typename ...T>
	public ref struct FT {
		using Pointer = R(__stdcall*)(T...);
		delegate R Type(T...);
	};

	template<typename R>
	public ref struct FT<R> {
		using Pointer = R(_stdcall*)();
		delegate R Type();
	};

	template<typename ...T>
	public ref struct ET {
		using Pointer = void(__stdcall*)(T...);
		delegate void Type(T...);
	};

	template<>
	public ref struct ET<void> {
		using Pointer = void(__stdcall*)();
		delegate void Type();
	};


}