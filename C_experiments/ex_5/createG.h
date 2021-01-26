#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

struct Org {//挂牌单位定义
    int id;//单位编号
    string name;//单位名字
    Org(int i,string s):id(i),name(s){}
    Org()=default;
};
struct VR {//图中边的定义
    int pos;//邻接点的位置
    double len;//该边的权值
    VR()=default;
    VR(int a,double b):pos(a),len(b){}
};

struct V {//图中顶点的定义
    int x, y;//顶点坐标
    int onum = 0;//挂牌单位数,初始化为0
    int rnum = 0;//邻接的边数，初始化为0
    vector<Org> org;//挂牌单位
    vector<VR> vr;//邻接的边
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
        while (!forg.eof()) {//读取单位名称并存储到 name 数组中
            getline(forg, oname);
            name.push_back(oname);
        }
        forg.close();
    }
};

class AlG {
public:
    vector<V> v;//表头结点数组
    int vnum = 0, anum = 0;//顶点数和弧数，初始化为0
    AlG(){
        ifstream fv("E:\\Projects\\MY\\C_experiments\\ex5\\Location.txt");
        if (!fv.is_open()) {
            cerr << "Cannot open Location.txt !" << endl;
            exit(-1);
        }
        else {//读取顶点的坐标
            string vpos = "";
            while (!fv.eof()) {
                getline(fv, vpos);
                int sep = vpos.find(',');//查找分隔符位置
                string xp = vpos.substr(0, sep);//读取x、y坐标
                string yp = vpos.substr(sep + 1);//直接截取到字符串末尾
                v.push_back(V(stoi(xp),stoi(yp)));//在表头结点数组末尾添加顶点
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
        else {//读取挂牌单位
            string onum = "";
            for (int pos = 0; pos < vnum; pos++) {
                getline(flo, onum);
                int pre = 0, sep = 0;
                while (pre != onum.npos) {
                    sep = onum.find(',', pre);//找到下一个分隔符
                    string s = onum.substr(pre, sep);//取pre到sep的子串
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
