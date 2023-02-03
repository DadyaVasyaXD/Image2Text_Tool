#include <iostream>
#include <conio.h>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

string RBG2SYMBOLS(int a)
{
    string s;
    if (a <= 30) s = "@@@@";
    else if (a > 30 && a <= 55) s = "@%@%";
    else if (a > 55 && a <= 80) s = "%%%%";
    else if (a > 80 && a <= 105) s = "5%5%";
    else if (a > 105 && a <= 130) s = "4444";
    else if (a > 130 && a <= 155) s = "4343";
    else if (a > 155 && a <= 180) s = "3333";
    else if (a > 180 && a <= 205) s = "3131";
    else if (a > 205 && a <= 230) s = "1111";
    else if (a > 230) s = "1.1.";
    return s;
}

void img2txt()
{
    Vec3b* vec;
    MatIterator_<Vec3b> it;
    string global;
    Mat img = imread("img.jpg");
    Mat templ = imread("template.jpg");
    resize(img, img, templ.size());
    int height = img.rows, wight = img.cols;
    string** arr = new string * [height];
    for (int i = 0; i < wight; ++i)
        arr[i] = new string[wight];

    it = img.begin<Vec3b>();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < wight; ++j) {

            stringstream ss;
            string pix = "";
            int a = img.at<Vec3b>(Point(j, i))[0];
            int b = img.at<Vec3b>(Point(j, i))[1];
            int c = img.at<Vec3b>(Point(j, i))[2];

            int mid = (a + b + c) / 3;

            pix = RBG2SYMBOLS(mid);

            arr[i][j] = pix;
            ++it;
        }
    }

    ofstream out_orig("img2txt.txt");
    for (int i = 0; i < height; ++i) {
        if (i > 0) out_orig << endl;
        for (int j = 0; j < wight; ++j) {
            out_orig << arr[i][j];
        }
    }
    out_orig.close();

    return;
}

int main()
{
        cout << " Waiting for:\n";
        cout << " ----------------------------------------\n";
        cout << "    -- image <img.jpg>\n";
        cout << " ----------------------------------------\n";
        cout << " in tool\'s folder\n\n";
        cout << " Press any button when done...\n"; _getch();
        cout << " Please wait...\n";
        img2txt();
        cout << " Complete!\n";
        cout << " Press any button to exit...\n";

        _getch();
        system("exit");
}