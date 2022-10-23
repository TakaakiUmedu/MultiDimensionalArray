#ifndef MULTI_DIMENSIONAL_ARRAY
#define MULTI_DIMENSIONAL_ARRAY

#include <vector>
#include <array>
#include <cstddef>

#define self (*this)

namespace mdarray{
	template<typename T, int D> class mdarray;
	
	template<typename T, int D, int N, bool C> class iter{
			using I = iter<T, D, N, C>;
			static const bool L = N == D;
			using A = std::conditional_t<C, const mdarray<T, D>&, mdarray<T, D>&>;
			using V = std::conditional_t<C, std::conditional_t<L, const T&, const iter<T, D, N + 1, C>>, std::conditional_t<L, T&, iter<T, D, N + 1, C>>>;
			A _array;
			size_t _index;
			inline size_t delta() const{ if constexpr(L){ return 1; }else{ return _array.raw_sizes()[N]; }}
			friend class mdarray<T, D>;
			friend class iter<T, D, N - 1, C>;
			iter(A array, size_t index): _array(array), _index(index){ }
		public:
			iter(const I& iter) = default;
			inline I& operator=(const I& iter) = default;
			
			inline size_t size() const{ return _array.sizes()[N - 1]; }
			inline size_t index() const{ return _index; }
	
			inline V operator*() const{ if constexpr(L){ return _array.value(_index); }else{ return iter<T, D, N + 1, C>(_array, _index); }}
			
			inline friend auto operator+(const I& iter, size_t offset){ return I(iter._array, iter._index + offset * iter.delta()); }
			inline friend auto operator-(const I& iter, size_t offset){ return iter + (-offset); }
	
			inline auto begin() const{ return self; }
			inline auto end() const{ return begin() + size(); }
			
			inline V operator[](size_t offset) const{ return *(begin() + offset); }
			
			inline auto operator++(){ _index += delta(); return self; }
			inline auto operator--(){ _index -= delta(); return self; }
			inline auto operator++(int){ auto ret = self; _index += delta(); return ret; }
			inline auto operator--(int){ auto ret = self; _index -= delta(); return ret; }
			
			inline friend auto operator!=(const I& a, const I& b) { return &a._array != &b._array || a._index != b._index; }
			inline friend auto operator==(const I& a, const I& b) { return !(a != b); }
			
			inline auto operator->() const{ return &self; }
	};
	
	template<typename T, int D> class mdarray{
			std::array<size_t, D> _sizes;
			std::array<size_t, D> _raw_sizes;
			std::vector<T> _values;
		public:
			mdarray(std::array<size_t, D> sizes, const T& init): _sizes(sizes){
				size_t prod = 1;
				for(int i = D - 1; i >= 0 ; i --){
					prod *= _sizes[i];
					_raw_sizes[i] = prod;
				}
				_values = std::vector<T>(_raw_sizes[0], init);
			}
			mdarray(const mdarray<T, D>& ) = default;
			inline mdarray<T, D>& operator=(const mdarray<T, D>& ) = default;
			
			inline size_t total_size() const{ return _raw_sizes[0]; }
			inline size_t size() const{ return _sizes[0]; }
			inline const auto& sizes() const{ return _sizes; }
			inline const auto& raw_sizes() const{ return _raw_sizes; }
			
			inline const T& value(size_t index) const{ return _values[index]; }
			inline       T& value(size_t index)      { return _values[index]; }
			
			inline auto begin() const{ return iter<T, D, 1, true>(self, 0); }
			inline auto begin()      { return iter<T, D, 1, false>(self, 0); }
			inline auto end()   const{ return begin() + _sizes[0]; }
			inline auto end()        { return begin() + _sizes[0]; }
			inline auto operator[](size_t i) const{ return *(begin() + i); }
			inline auto operator[](size_t i)      { return *(begin() + i); }
	};
}

#undef self

#endif
