#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

struct Org {//���Ƶ�λ����
    int id;//��λ���
    string name;//��λ����
    Org(int i,string s):id(i),name(s){}
    Org()=default;
};
struct VR {//ͼ�бߵĶ���
    int pos;//�ڽӵ��λ��
    double len;//�ñߵ�Ȩֵ
    VR()=default;
    VR(int a,double b):pos(a),len(b){}
};

struct V {//ͼ�ж���Ķ���
    int x, y;//��������
    int onum = 0;//���Ƶ�λ��,��ʼ��Ϊ0
    int rnum = 0;//�ڽӵı�������ʼ��Ϊ0
    vector<Org> org;//���Ƶ�λ
    vector<VR> vr;//�ڽӵı�
    V(int posx,int posy):x(posx),y(posy){}
    V()=default;
};


class ReadOrg{
public:
    vector<string> name;
    ReadOrg(){
        ifstream forg("E:\\Projects\\MY\\C_experiments\\ex5\\Organization.txt");
        if (!forg.is_open()) {
            cerr << "Cannot open Organization.txt !" << endl;
            exit(-1);
        }

        string oname = "";
        while (!forg.eof()) {//��ȡ��λ���Ʋ��洢�� name ������
            getline(forg, oname);
            name.push_back(oname);
        }
        forg.close();
    }
};

class AlG {
public:
    vector<V> v;//��ͷ�������
    int vnum = 0, anum = 0;//�������ͻ�������ʼ��Ϊ0
    AlG(){
        ifstream fv("E:\\Projects\\MY\\C_experiments\\ex5\\Location.txt");
        if (!fv.is_open()) {
            cerr << "Cannot open Location.txt !" << endl;
            exit(-1);
        }
        else {//��ȡ���������
            string vpos = "";
            while (!fv.eof()) {
                getline(fv, vpos);
                int sep = vpos.find(',');//���ҷָ���λ��
                string xp = vpos.substr(0, sep);//��ȡx��y����
                string yp = vpos.substr(sep + 1);//ֱ�ӽ�ȡ���ַ���ĩβ
                v.push_back(V(stoi(xp),stoi(yp)));//�ڱ�ͷ�������ĩβ��Ӷ���
                vnum++;
            }
        }
        fv.close();

        ReadOrg OrgName;
        ifstream flo("E:\\Projects\\MY\\C_experiments\\ex5\\Locorg.txt");
        if (!flo.is_open()) {
            cerr << "Cannot open Locorg.txt !" << endl;
            exit(-1);
        }
        else {//��ȡ���Ƶ�λ
            string onum = "";
            for (int pos = 0; pos < vnum; pos++) {
                getline(flo, onum);
                int pre = 0, sep = 0;
                while (pre != onum.npos) {
                    sep = onum.find(',', pre);//�ҵ���һ���ָ���
                    string s = onum.substr(pre, sep);//ȡpre��sep���Ӵ�
                    pre = sep;
                    if (pre != -1) pre++;
                    int id = stoi(s);
                    v[pos].org.push_back(Org(id,OrgName.name[id]));
                    v[pos].onum++;
                }
            }
        }
        flo.close();

        ifstream fvr("E:\\Projects\\MY\\C_experiments\\ex5\\Edge.txt");
        if (!fvr.is_open()) {
            cerr << "Cannot open Edge.txt !" << endl;
            exit(-1);
        }
        else {
            string edge = "";
            while (!fvr.eof()) {
                getline(fvr, edge);
                anum++;
                int sep = edge.find(',');
                string pos1 = edge.substr(0, sep);
                string pos2 = edge.substr(sep + 1);
                V& v1 = v[stoi(pos1)];
                V& v2 = v[stoi(pos2)];
                double len = sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
                v1.vr.push_back(VR(stoi(pos2),len));
                v1.rnum++;
                v2.vr.push_back(VR(stoi(pos1),len));
                v2.rnum++;
            }
        }
        fvr.close();
    }
};
