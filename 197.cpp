/*
 * 这题过得辛苦。很多东西都没有想到。最主要的是连矩阵变换都没有想到。
 * 看了题解之后，才明白思路如此简单。只是思路简单而已。
 * 本来以为实现起来较容易，没有想到遇到了各种问题。
 * 一开始没有采取matrix类的方式，写了一会儿看着自己写的代码就摸不着北了。
 * 后来又遇到了一个问题。itemtype为vector<int>，对vector<itemtype>进行排序
 * 时，估计是直接比较用data()来memcmp的。旋转、平移、去重复纠结了好久，一直
 * 没有写对。最后还是照着http://www.cnblogs.com/devymex/p/3270781.html
 * 一步一步写完的。惭愧，比原作者慢了好多。
 */


#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct matrix {
	int m[3][3];

	bool operator<(const matrix& rh) const {
		return memcmp((void*)m, (void*)rh.m, sizeof(int) * 9) < 0;
	}

	bool operator==(const matrix& rh) const {
		return memcmp((void*)m, (void*)rh.m, sizeof(int) * 9) == 0;
	}

	matrix operator*(const matrix& rh) {
		matrix ret = {0};
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				for (int k = 0; k < 3; ++k)
					ret.m[i][j] += m[i][k] * rh.m[k][j];
		return ret;
	}
};

struct point {
	int p[3];

	bool operator<(const point& rh) const {
		return p[0] < rh.p[0] || p[0] == rh.p[0] && p[1] < rh.p[1] ||
			p[0] == rh.p[0] && p[1] == rh.p[1] && p[2] < rh.p[2];
	}

	bool operator==(const point& rh) const {
		return p[0] == rh.p[0] && p[1] == rh.p[1] && p[2] == rh.p[2];
	}

	point operator+(const point& rh) const {
		point ret = *this;
		ret.p[0] += rh.p[0];
		ret.p[1] += rh.p[1];
		ret.p[2] += rh.p[2];
		return ret;
	}

	const point& operator+=(const point& rh) {
		p[0] += rh.p[0];
		p[1] += rh.p[1];
		p[2] += rh.p[2];
	}

	const point& operator-=(const point& rh) {
		p[0] -= rh.p[0];
		p[1] -= rh.p[1];
		p[2] -= rh.p[2];
	}

	point operator*(const matrix& rh) const {
		point ret = {0};
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				ret.p[j] += p[k] * rh.m[k][j];
		return ret;
	}
};

// 将这个小块的坐标尽量移至原点
void move_to_origin(vector<point>& rotated_coordinates)
{
	point _bottom = rotated_coordinates[0];
	for (int i = 1; i < rotated_coordinates.size(); ++i) {
		_bottom.p[0] = min(_bottom.p[0], rotated_coordinates[i].p[0]);
		_bottom.p[1] = min(_bottom.p[1], rotated_coordinates[i].p[1]);
		_bottom.p[2] = min(_bottom.p[2], rotated_coordinates[i].p[2]);
	}
	for (int i = 0; i < rotated_coordinates.size(); ++i)
		rotated_coordinates[i] -= _bottom;
}

// 计算得到此小块的xyz各个方向上的长度
point piece_size(const vector<point>& coordinates)
{
	point _bottom, _top;
	_bottom = _top = coordinates[0];
	for (int i = 1; i < coordinates.size(); ++i) {
		_bottom.p[0] = min(_bottom.p[0], coordinates[i].p[0]);
		_bottom.p[1] = min(_bottom.p[1], coordinates[i].p[1]);
		_bottom.p[2] = min(_bottom.p[2], coordinates[i].p[2]);
		_top.p[0] = max(_top.p[0], coordinates[i].p[0]);
		_top.p[1] = max(_top.p[1], coordinates[i].p[1]);
		_top.p[2] = max(_top.p[2], coordinates[i].p[2]);
	}
	_top -= _bottom;
	return _top;
}

// 将当前坐标平移p单位
vector<point> translate(const vector<point>& coordinates, const point& p)
{
	vector<point> ret(coordinates.size());
	for (int i = 0; i < coordinates.size(); ++i)
		ret[i] = coordinates[i] + p;
	return ret;
}

// 将坐标转换成掩码
int coordinates2mask(const vector<point>& coordinates)
{
	// 完全hash
	int mask = 0;
	for (int i = 0; i < coordinates.size(); ++i) {
		int val = coordinates[i].p[0] + coordinates[i].p[1] * 3 + coordinates[i].p[2] * 9;
		mask |= (1 << val);
	}
	return mask;
}

// 生成24种旋转矩阵，并应用于bcdefg六种小块上。再加上平移，生成这6种小块
// 的所有构型并去重复。
vector< vector<int> > init()
{
	matrix rotate_x[4] = {
		{1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, -1, 0, 1, 0},
		{1, 0, 0, 0, -1, 0, 0, 0, -1},
		{1, 0, 0, 0, 0, 1, 0, -1, 0}
	};
	matrix rotate_y[4] = {
		{1, 0, 0, 0, 1, 0, 0, 0, 1},
		{0, 0, 1, 0, 1, 0, -1, 0, 0},
		{-1, 0, 0, 0, 1, 0, 0, 0, -1},
		{0, 0, -1, 0, 1, 0, 1, 0, 0}
	};
	matrix rotate_z[4] = {
		{1, 0, 0, 0, 1, 0, 0, 0, 1},
		{0, -1, 0, 1, 0, 0, 0, 0, 1},
		{-1, 0, 0, 0, -1, 0, 0, 0, 1},
		{0, 1, 0, -1, 0, 0, 0, 0, 1}
	};

	// 生成所有的旋转矩阵，去重复，共24种
	vector<matrix> transform_matrixes;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
				transform_matrixes.push_back(rotate_x[i] * rotate_y[j] * rotate_z[k]);
	sort(transform_matrixes.begin(), transform_matrixes.end());
	transform_matrixes.erase(unique(transform_matrixes.begin(), transform_matrixes.end()), transform_matrixes.end());

	// 构造acdefgb的坐标
	int small_cube_number[7] = {4,4,4,4,4,4,3};
	point coordinates[7][4] = {
		{{0,0,0},{0,1,0},{0,2,0},{0,2,1}},// a
		{{0,0,0},{0,1,0},{0,2,0},{0,1,1}},// c
		{{0,0,0},{0,1,0},{0,1,1},{0,2,1}},// d
		{{0,0,0},{0,1,0},{1,0,0},{0,0,1}},// e
		{{0,0,0},{0,1,0},{1,0,0},{0,1,1}},// f
		{{0,0,0},{0,1,0},{1,0,0},{1,0,1}},// g
		{{0,0,0},{0,1,0},{0,0,1}}// b
	};

	// 将各个小块旋转，去重复，加平移
	vector< vector<point> > piece_rotated_coordinates[7];
	for (int i = 0; i < 7; ++i) {
		vector<point> rotated_coordinates(small_cube_number[i]);;
		// 将24种旋转变换应用于小块的每一个坐标
		for (int j = 0; j < transform_matrixes.size(); ++j) {
			for (int k = 0; k < small_cube_number[i]; ++k)
				rotated_coordinates[k] = coordinates[i][k] * transform_matrixes[j];
			// 小块变换成功，可能不在[0,3)之内，因此要尽量移至原点
			move_to_origin(rotated_coordinates);
			sort(rotated_coordinates.begin(), rotated_coordinates.end());// 为了后面的去重复，必须使具有相同的规则
			piece_rotated_coordinates[i].push_back(rotated_coordinates);
		}
		// 旋转完成之后可能存在重复的构型，去重复
		sort(piece_rotated_coordinates[i].begin(), piece_rotated_coordinates[i].end());
		piece_rotated_coordinates[i].erase(unique(piece_rotated_coordinates[i].begin(), 
					piece_rotated_coordinates[i].end()), piece_rotated_coordinates[i].end());

		// 加平移
		for (int j = 0, cur_size = piece_rotated_coordinates[i].size(); j < cur_size; ++j) {
			point size = piece_size(piece_rotated_coordinates[i][j]);
			for (int dx = 0; dx + size.p[0] < 3; ++dx)
				for (int dy = 0; dy + size.p[1] < 3; ++dy)
					for (int dz = 0; dz + size.p[2] < 3; ++dz) {
						if (dx == 0 && dy == 0 && dz == 0)// 避免加入自己
							continue;
						point p = {dx, dy, dz};
						piece_rotated_coordinates[i].push_back(translate(piece_rotated_coordinates[i][j], p));
					}
		}
	}
	
	// 将各种小块的所有构型转换成掩码，方便dfs时匹配
	vector< vector<int> > all_piece_possible_pos(7);
	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < piece_rotated_coordinates[i].size(); ++j)
			all_piece_possible_pos[i].push_back(coordinates2mask(piece_rotated_coordinates[i][j]));
	return all_piece_possible_pos;
}

// 搜索可行解
void dfs(int cur, const vector< vector<int> >& all_piece_possible_pos, int cube_state, vector<int> path,
		vector< vector<int> >& result)
{
	if (cur == 7) {
		result.push_back(path);
		return;
	}

	for (int i = 0; i < all_piece_possible_pos[cur].size(); ++i)
		if ((cube_state & all_piece_possible_pos[cur][i]) == 0) {
			path.push_back(all_piece_possible_pos[cur][i]);
			dfs(cur + 1, all_piece_possible_pos, cube_state | all_piece_possible_pos[cur][i], path, result);
			path.pop_back();
		}
}

// 将一个mask序列转换成输出的string
string convert(const vector<int>& masks)
{
	static const char* ref = "acdefgb";
	static const int map[27] = {25,16,7,26,17,8,27,18,9,22,13,4,23,14,5,24,15,6,19,10,1,20,11,2,21,12,3};
	string ret;

	ret.resize(27);
	for (int i = 0; i < masks.size(); ++i)
		for (int j = 0; j < 27; ++j)
			if ((1 << j) & masks[i])
				ret[map[j] - 1] = ref[i];
	return ret;
}

int main()
{
	// 生成各种小块(acdefgb)的变换后的所有mask值
	const vector< vector<int> > all_piece_possible_pos = init();

	string line;
	while (getline(cin, line) && !line.empty()) {
		vector<point> coordinates;
		vector< vector<int> > result;

		for (int i = 0; i < line.length(); ++i)
			if (line[i] == 'a') {
				point p = { 2-i/9, i%3, 2-(i/3)%3 };// 坐标转化
				coordinates.push_back(p);
			}
		move_to_origin(coordinates);// 转换为基本的24种构型之一
		sort(coordinates.begin(), coordinates.end());

		int idx = find(all_piece_possible_pos[0].begin(), all_piece_possible_pos[0].end(),
				coordinates2mask(coordinates)) - all_piece_possible_pos[0].begin();

		dfs(1, all_piece_possible_pos, all_piece_possible_pos[0][idx], vector<int>(1, all_piece_possible_pos[0][idx]), result);
		for (int i = 0; i < 5; ++i) {
			int pos = idx * 5 + 24;
			dfs(1, all_piece_possible_pos, all_piece_possible_pos[0][i + pos], 
					vector<int>(1, all_piece_possible_pos[0][i + pos]), result);
		}
		vector<string> output;
		for (int i = 0; i < result.size(); ++i)
			output.push_back(convert(result[i]));
		sort(output.begin(), output.end());
		for (int i = 0; i < output.size(); ++i)
			cout << output[i] << endl;
		cout << endl;
	}
	return 0;
}
