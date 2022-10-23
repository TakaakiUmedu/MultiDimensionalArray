#include "mdarray.hpp"

#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <limits>
#ifdef USE_PYTHON_LIKE_PRINT
// https://github.com/TakaakiUmedu/python_like_print
#include "print.hpp"
#else
template<char SEP = ' ', char END = '\n', class... A> inline void print(A&& ...){}
template<char SEP = ' ', char END = '\n', class... A> inline void printe(A&& ...){}
template<char SEP = ' ', char END = '\n', class... A> inline void printo(A&& ...){}
#define define_print(...)
#define define_print_with_names(...)
#define define_to_tuple(...)
#endif

using namespace std;

template<typename T = int> class range{
	class iter{
		T _v, _d;
	public:
		inline iter(T v, T d): _v(v), _d(d){}
		inline iter operator ++(){ _v += _d; return *this; }
		inline iter operator ++(int){ const auto v = _v; _v += _d; return iter(v, _d); }
		inline operator T() const{ return _v; }
		inline T operator*() const{ return _v; }
		inline bool operator!=(T e) const{ return _d == 0 ? _v != e : (_d >= 0 ? _v < e : _v > e); }
	};
	const iter _i; const T _e;
public:
	template<typename S = int> inline range(S s, T e, T d = 1): _i(s, d), _e(e){}
	inline range(T e): range(0, e){}
	inline iter begin() const{ return _i; }
	inline T end() const{ return _e; }
};

template<typename T> inline T read_int(){
	conditional_t<is_signed_v<T>, int64_t, uint64_t> v; cin >> v;
	if(numeric_limits<T>::max() < v || numeric_limits<T>::min() > v){ throw runtime_error("overflow occured in read_int"); }
	return static_cast<T>(v);
}
template<typename T> inline T read(){ if constexpr(is_integral_v<T>){ return read_int<T>(); }else{ T v; cin >> v; return v; } }
template<size_t N, typename... T> inline void read_tuple_elem(tuple<T...>& v){
	if constexpr(N < sizeof...(T)){ get<N, T...>(v) = read<std::tuple_element_t<N, tuple<T...>>>(); read_tuple_elem<N + 1, T...>(v); }
}
template<typename... T> inline tuple<T...> read_tuple(){ tuple<T...> v; read_tuple_elem<0, T...>(v); return v; }
template<typename T> inline vector<T> read_vec(size_t N){ vector<T> values(N); for(const auto i: range(N)) cin >> values[i]; return values; }


template<typename T> void calc(T& a){
	const auto X = a.size();
	const auto Y = a[0].size();
	const auto Z = a[0][0].size();
	
	for(size_t x = 0; x < X; x ++){
		a[x][0][0] = x;
	}
	for(size_t y = 0; y < Y; y ++){
		a[0][y][0] = y;
	}
	for(size_t z = 0; z < Z; z ++){
		a[0][0][z] = z;
	}
	for(size_t x = 1; x < X; x ++){
		for(size_t y = 1; y < Y; y ++){
			for(size_t z = 1; z < Z; z ++){
				a[x][y][z] = a[x - 1][y][z] + a[x][y - 1][z] + a[x][y][z - 1];
			}
		}
	}
}

template<typename T1, typename T2> void check(T1& a1, T2& a2){
	static_assert(!std::is_same_v<T1, T2>, "same type");
	const auto X1 = a1.size();
	const auto Y1 = a1[0].size();
	const auto Z1 = a1[0][0].size();

	const auto X2 = a2.size();
	const auto Y2 = a2[0].size();
	const auto Z2 = a2[0][0].size();
	
	if(X1 != X2 || Y1 != Y2 || Z1 != Z2){
		cout << "size error" << endl;
		return;
	}
	for(size_t x = 0; x < X1; x ++){
		for(size_t y = 0; y < Y1; y ++){
			for(size_t z = 0; z < Z1; z ++){
				if(a1[x][y][z] != a2[x][y][z]){
					cout << "value error" << endl;
					return;
				}
			}
		}
	}
	
}




int main(void){
	const auto T = read<int64_t>();
	const auto [X, Y, Z] = read_tuple<size_t, size_t, size_t>();
	
	if(T == 1){
		vector<vector<vector<int64_t>>> a1(X, vector<vector<int64_t>>(Y, vector<int64_t>(Z, -1)));
		mdarray::mdarray<int64_t, 3> a2({X, Y, Z}, -1);
		check(a1, a2);
		
		calc(a1);
		calc(a2);
		
		check(a1, a2);
	}else if(T == 2){
		vector<vector<vector<int64_t>>> a1(X, vector<vector<int64_t>>(Y, vector<int64_t>(Z, -1)));
		calc(a1);
	}else if(T == 3){
		mdarray::mdarray<int64_t, 3> a2({X, Y, Z}, -1);
		calc(a2);
	}else if(T == 4){
		auto a = mdarray::mdarray<int64_t, 3>({2, 3, 4}, -1);
		int x = 0;
		{
			for(const auto i: range(2)){
				for(const auto j: range(3)){
					for(const auto k: range(4)){
						a[i][j][k] = x;
						x ++;
					}
				}
			}
		}
	
		{
			int x = 0;
			const auto& b = a;
			for(const auto i: range(2)){
				for(const auto j: range(3)){
					for(const auto k: range(4)){
						print(b[i][j][k]);
					}
				}
			}
		}
	}

	return 0;
}

