/*���ߣ� 18�ƿ�2�� �ι�� 1810300302
  ʱ�䣺2020.11.26
  version��1.0
  tip��1.���汾�����Ը��ٵ÷ֺ���ʵ������K-means�����㷨
	   2.���ļ���ȡ����ʽ��ȡ�������ݼ�

*/

/*
����˼�룺�������ǰk�����ݵ�Ϊ���Ľ���һ�δε�������
ֱ���������ݵ���һ�ε�����������ǰһ�ξ�����û�в��
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<fstream>
#include<map>
using namespace std;

//�洢���ݵ���Ϣ
float xx[10001];
float yy[10001];
float sum[100][10001];
//�洢��ǰÿ���������
vector<float> x_now;
vector<float> y_now;
/*//�о��ö�ά����洢���������Ǻ�ѡ�񣬵���û���뵽��ķ���(�ö�ά���黹��һά��������kk[���][���ݵ���]=���룿���� kk[���ݵ���]=��𣿣���
int kk1[50][10001];//�洢��һ�ξ�����
int kk2[50][10001];//�洢���ξ�����
*/
/*//�洢���ξ����� kk[���ݵ���]=���
int kk1[10001];
int kk2[10001];
*/
//�洢���ξ�����
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
	int i, j;//����ѭ��
	int k;
	int flag = 0;//����������ѭ��
	int count = 0;//���ڼ�¼���ݵ����
	int cnum = 0;
	cout << "������Kֵ" << endl;
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
		cout <<"�� "<<i<<" �����ݵ�����Ϊ��"<< xx[i] << " " << yy[i] << endl;
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
			sum[i][j] = sqrt((x_now[i] - xx[j])*(x_now[i] - xx[j]) + (y_now[i] - yy[j])*(y_now[i] - yy[j]));//���ÿ���������ĵľ��� sum[����i][��ǰ��j]
			}
		}
	//�����ÿһ�����ݵ�����һ��������ӽ�����һ����ʵ���Է�������������˫ѭ������һ�£�
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
	//���¼������ģ�
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
	cout << "������ " << cnum << " �ε������¾�����Ϣ,���Ϊ��" << endl;
	for (i = 0; i < x_now.size(); i++) {
		cout << "���� " << i + 1 << " �����������Ϊ�� " << x_now[i] << " " << y_now[i] << endl;


	}
	for (i = 0; i < kk1.size(); i++) {
		for (j = 0; j < k; j++) {
			if (kk1[i] == j) {
				cout << "���ڵ� " << j + 1 << " ��ĵ������ݵ㣺 " << i << endl;
			}
		}
	}
	return 0;


}