#ifndef CTRAITS
#define CTRAITS

struct Traits_1
{
	typedef int n;
	typedef string e;
	typedef int C;
};

template <class T>
struct CLess
{
	bool operator()(T a, T b)
	{
		return a < b;
	}
};

template <class T>
struct CGreater
{
	bool operator()(T a, T b)
	{
		return a > b;
	}
};

struct CListTraits
{
	typedef int T;
	typedef CLess<T> C;
};

struct CListTraits2
{
	typedef int T;
	typedef CGreater<T> C;
};

#endif //CTRAITS

