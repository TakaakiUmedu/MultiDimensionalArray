a.exe: test.cpp mdarray.hpp
	c++ -O2 --std=c++17 -D USE_PYTHON_LIKE_PRINT test.cpp

%: a.exe %.in
	time ./a.exe < $@.in
