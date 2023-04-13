/*作者： 18计科2班 何冠皓 1810300302
  时间：2020.11.25
  version：1.0
  tip：1.导入文件形式导入数据集
	   2.本版本避免使用了class类而在一个主函数中完成
	   3.初代版本一次仅能完成一个测试点的分类判断
	   4.资源文件命名：data.txt(数据集是随意输的：类型（x，y，label），后期可能需要调整）

*/
#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<fstream>
#include<map>
using namespace std;

//用于存储数据集
float  xx[10001];
float  yy[10001];
char   cc[10001];
//用于存储距离
float sum[10001];
/*//用于存储最近邻居的编号和类别
vector<int> co;
vector<char> ch;*/
//用于找到最近邻中最大的类别
map<char, int> mm;



int main() {
	int i,j;//用于循环
	int k;//K最近邻中的k值
	cout << "请输入K值：" << endl;
	cin >> k;
	float x, y;
	cout << "请输入测试点的横坐标和纵坐标（以空格分隔）：" << endl;
	cin >> x >> y;
	ifstream fin;
	fin.open("data.txt");//读入数据集
	if (!fin) {
		cout << "无法读入数据集文件！" << endl;
		return 0;
	}
	for (i = 0; i < 10001; i++) {
		fin >> xx[i] >> yy[i] >> cc[i];
		sum[i] = sqrt((xx[i] - x)*(xx[i] - x) + (yy[i] - y)*(yy[i] - y));
		if (!cc[i]) {
			break;
		}
	}

	for (i = 0; i < 10001; i++) {
		if (sum[i] == 0 || sum[i + 1] == 0) {
			break;
		}
		cout << "第 " << i + 1 << " 个数据点于测试点的距离： " << sum[i] << endl;
	}
	int temp = 0;
	float min = 100000;
	for (i = 0; i < k; i++) {
		
		for ( j = 0; j < 10001; j++) {
			if (sum[j] == 0 || sum[j + 1] == 0) {
				break;
			}
			else if (sum[j] <min) {
				temp = j;
				min = sum[j];
			}
		}
		cout << "距离最近的第 " << i+1 << "个数据点，为数据点：" << temp+1 << " ,其距离为：" << min << " ，类别为：" << cc[temp] << endl;
		//co.push_back(temp);
		//ch.push_back(cc[temp]);
		mm[cc[temp]]++;
		sum[temp]=100000;
		min = 100000;
	}

	map<char, int>::const_iterator map_i = mm.begin();
	int max_i = 0;
	char ch_i;
	while (map_i != mm.end()) {
		if (map_i->second > max_i) {
			max_i = map_i->second;
			ch_i = map_i->first;
		}
		map_i++;
	}
	cout << "测试点属于" << ch_i << "类" << endl;
	return 0;
}