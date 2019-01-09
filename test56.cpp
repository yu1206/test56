#include "MSRCR.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <io.h>
#include <Windows.h>
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <direct.h>

using namespace cv;
using namespace std;

extern void SplitString(const string& s, vector<string>& v, const string& c);
// 先写图片对应的txt，然后再画图
int test56(int argc, char *argv[])
{

	string imgpath = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip13";
	string imgpath1 = "E:\\LISA-Traffic-Light\\dayTrainingclass";


	fstream finRead;
	string inputPathtxt = imgpath + "\\" + "frameAnnotationsBOX.csv";
	finRead.open(inputPathtxt, ios::in);
	if (!finRead.is_open())
	{
		cout << "finRead1 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}





	map<string, int> mapclass;
	mapclass[string("go")] = 1;  mapclass[string("goLeft")] = 2; mapclass[string("stop")] = 3;
	mapclass[string("stopLeft")] = 4; mapclass[string("warning")] = 5; mapclass[string("warningLeft")] = 6;

	string line;
	getline(finRead, line);
	while (getline(finRead, line))
	{
		vector<string> vs;
		SplitString(line, vs, ";");

		int npos = vs[0].find_last_of('/');
		int npos2 = vs[0].find_last_of('.');

		string name1 = vs[0].substr(npos + 1, npos2 - npos - 1);

		cout << name1.c_str() << endl;

		string outputtxt = imgpath1 + "\\" + vs[1]+"\\"+ name1 + ".txt";
		fstream finWrite;
		finWrite.open(outputtxt, ios::app);

		if (!finWrite.is_open())
		{
			cout << "finRead2 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		int x1, y1, x2, y2, label;
		label = mapclass[vs[1]];
		x1 = atoi(vs[2].c_str());
		y1 = atoi(vs[3].c_str());
		x2 = atoi(vs[4].c_str());
		y2 = atoi(vs[5].c_str());

		finWrite << label << " " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;

		finWrite.close();

		string infile = imgpath + "\\" + "frames" + "\\" + name1 + ".png";
		Mat img = imread(infile);
		string outfile = imgpath1 + "\\" + vs[1] + "\\" + name1 + ".png";
		imwrite(outfile,img);

	}

	return 0;
}