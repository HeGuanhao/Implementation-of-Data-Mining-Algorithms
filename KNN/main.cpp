/*���ߣ� 18�ƿ�2�� �ι�� 1810300302
  ʱ�䣺2020.11.25
  version��1.0
  tip��1.�����ļ���ʽ�������ݼ�
	   2.���汾����ʹ����class�����һ�������������
	   3.�����汾һ�ν������һ�����Ե�ķ����ж�
	   4.��Դ�ļ�������data.txt(���ݼ���������ģ����ͣ�x��y��label�������ڿ�����Ҫ������

*/
#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<fstream>
#include<map>
using namespace std;

//���ڴ洢���ݼ�
float  xx[10001];
float  yy[10001];
char   cc[10001];
//���ڴ洢����
float sum[10001];
/*//���ڴ洢����ھӵı�ź����
vector<int> co;
vector<char> ch;*/
//�����ҵ���������������
map<char, int> mm;



int main() {
	int i,j;//����ѭ��
	int k;//K������е�kֵ
	cout << "������Kֵ��" << endl;
	cin >> k;
	float x, y;
	cout << "��������Ե�ĺ�����������꣨�Կո�ָ�����" << endl;
	cin >> x >> y;
	ifstream fin;
	fin.open("data.txt");//�������ݼ�
	if (!fin) {
		cout << "�޷��������ݼ��ļ���" << endl;
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
		cout << "�� " << i + 1 << " �����ݵ��ڲ��Ե�ľ��룺 " << sum[i] << endl;
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
		cout << "��������ĵ� " << i+1 << "�����ݵ㣬Ϊ���ݵ㣺" << temp+1 << " ,�����Ϊ��" << min << " �����Ϊ��" << cc[temp] << endl;
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
	cout << "���Ե�����" << ch_i << "��" << endl;
	return 0;
}