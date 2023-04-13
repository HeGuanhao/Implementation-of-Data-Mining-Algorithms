/*作者： 18计科2班 何冠皓 1810300302
  时间：2020.11.26
  version：1.0
  tip：1.本版本尝试以更少得分函数实现整个K-means聚类算法
	   2.以文件读取的形式读取测试数据集

*/

/*
代码思想：以输入的前k个数据点为质心进行一次次迭代更新
直到所有数据点在一次迭代更新中与前一次聚类结果没有差别
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<fstream>
#include<map>
using namespace std;

//存储数据点信息
float xx[10001];
float yy[10001];
float sum[100][10001];
//存储当前每个类的质心
vector<float> x_now;
vector<float> y_now;
/*//感觉用二维数组存储聚类结果不是好选择，但是没有想到别的方法(用二维数组还是一维？？？）kk[类别][数据点编号]=距离？？？ kk[数据点编号]=类别？？？
int kk1[50][10001];//存储上一次聚类结果
int kk2[50][10001];//存储本次聚类结果
*/
/*//存储两次聚类结果 kk[数据点编号]=类别
int kk1[10001];
int kk2[10001];
*/
//存储两次聚类结果
map<int, int> kk1;
map<int, int> kk2;

template<typename K,typename V>
bool Com(const std::map<K, V>&map1, const std::map<K, V>&map2) {
	if (map1.size() != map2.size()) {
		return false;
	}
	for (auto it1 : map1) {
		auto it2 = map2.find(it1.first);
		if (it2 == map2.end()) {
			return false;
		}
		else {
			if (0 != memcmp(&it1.second, &it2->second, sizeof(V))) {
				return false;
			}
		}
	}
	return true;
}

int  main() {
	int i, j;//用于循环
	int k;
	int flag = 0;//用于跳出死循环
	int count = 0;//用于记录数据点个数
	int cnum = 0;
	cout << "请输入K值" << endl;
	cin >> k;
	
	ifstream fin;
	fin.open("data.txt");
	for(i = 0; i < 10001; i++){
		fin >> xx[i] >> yy[i];
		count++;
	if (!xx[i]) {
		count--;
		break;
	}
	}
	for (i = 0; i < count; i++) {
		cout <<"第 "<<i<<" 个数据点坐标为："<< xx[i] << " " << yy[i] << endl;
	}
	for (i = 0; i < k; i++) {
		x_now.push_back(xx[i]);
		y_now.push_back(yy[i]);
	}
	while(1){
		if (flag == 1) {
			break;
		}
		cnum++;
	for ( i = 0; i < x_now.size(); i++) {
		for (j = 0; j < count; j++) {
			sum[i][j] = sqrt((x_now[i] - xx[j])*(x_now[i] - xx[j]) + (y_now[i] - yy[j])*(y_now[i] - yy[j]));//算出每个点与质心的距离 sum[质心i][当前点j]
			}
		}
	//计算出每一个数据点与哪一个质心最接近（这一步其实可以放在上面做，把双循环调整一下）
	float min = 100001;
	int temp;
	for (j = 0; j < count; j++) {
	for (i = 0; i < x_now.size(); i++) {
		if (sum[i][j] < min) {
			min = sum[i][j];
			temp = i;
			}
		}
	kk2[j] = temp;
	min = 100001;
	}
	/*if (Com(kk2, kk1)) {
		flag = 1;
	}
	else {
		kk1 = kk2;
		kk2.clear();
	}*/
	//重新计算质心；
	x_now.clear();
	y_now.clear();
	for (j = 0; j < k; j++) {
		float sum_x_now = 0;
		float sum_y_now = 0;
		int coun = 0;
	for (i = 0; i < kk2.size(); i++) {
			if (kk2[i] == j) {
				sum_x_now += xx[i];
				sum_y_now += yy[i];
				coun++;
			}
		}
	x_now.push_back(sum_x_now / coun);
	y_now.push_back(sum_y_now / coun);
	}
	if (Com(kk2, kk1)) {
		flag = 1;
	}
	else {
		kk1 = kk2;
		kk2.clear();
	}
	}
	cout << "经过了 " << cnum << " 次迭代更新聚类信息,结果为：" << endl;
	for (i = 0; i < x_now.size(); i++) {
		cout << "最后第 " << i + 1 << " 类的质心坐标为： " << x_now[i] << " " << y_now[i] << endl;


	}
	for (i = 0; i < kk1.size(); i++) {
		for (j = 0; j < k; j++) {
			if (kk1[i] == j) {
				cout << "属于第 " << j + 1 << " 类的点有数据点： " << i << endl;
			}
		}
	}
	return 0;


}