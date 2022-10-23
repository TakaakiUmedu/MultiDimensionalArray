# MultiDimensionalArray
Multi Dimensional Array for C++

* mdarray::mdarray<int64_t, 2> a({X, Y}, -1) can replace vector<vector<vector<int64_t>>> a(X, vector<vector<int64_t>>(Y, -1));
* mdarray::mdarray<int64_t, 3> a({X, Y, Z}, -1) can replace vector<vector<vector<int64_t>>> a(X, vector<vector<int64_t>>(Y, vector<int64_t>(Z, -1)));
* mdarray::mdarray<int64_t, 4> a({X, Y, Z, W}, -1) can replace vector<vector<vector<int64_t>>> a(X, vector<vector<int64_t>>(Y, vector<int64_t>(Z, vector<int64_t>(W, -1))));
* :
* and faster
