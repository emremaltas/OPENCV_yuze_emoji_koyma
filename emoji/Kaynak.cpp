#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
//26.05.2021 yuz kordinatlarý icerisine emoji koyan yazýlým.
class emoji {

 public:
     emoji() {};

     void yuzBul()
     {
        
         Mat resim = imread("emo2.png");
         CascadeClassifier yuz;
         yuz.load("haarcascade_frontalface_default.xml");
         VideoCapture vCap;
         vCap.open(0);

         if (vCap.isOpened())
         {
             Mat frame;
             Mat griFrame;
             Mat donusum;

             while (true)
             {
                 vector<Rect>yuzBul;

                 vCap.read(frame);
                 cvtColor(frame, griFrame, COLOR_BGR2GRAY);
                 yuz.detectMultiScale(griFrame, yuzBul, 1.1, 3, 0, Size(10, 10));
                 if (yuzBul.size() >0)
                 {
                     rectangle(frame, yuzBul[0], Scalar(0, 0, 255), 2, 8);
                     resize(resim, resim, Size(yuzBul[0].width, yuzBul[0].height));
                     Point2f ilk[] = { Point2f(1,1),Point2f(0,yuzBul[0].width - 1),
                         Point2f(yuzBul[0].width - 1,yuzBul[0].height - 1),Point2f(1,yuzBul[0].height - 1) };

                     Point2f son[] = { Point2f(yuzBul[0].x,yuzBul[0].y),Point2f(yuzBul[0].x,yuzBul[0].y + yuzBul[0].height),
                     Point2f(yuzBul[0].x + yuzBul[0].width,yuzBul[0].y + yuzBul[0].height),
                         Point2f(yuzBul[0].x + 1,yuzBul[0].y + 1 + yuzBul[0].height) };

                     donusum = getAffineTransform(ilk, son);
                     warpAffine(resim, frame, donusum, frame.size(), 1, BORDER_TRANSPARENT);
                     imshow("emoji:", resim);
                 }
                 imshow("frame", frame);
                 if (waitKey(100)==27)
                 {
                     break;
                 }

             }
         }

     }


};


int main()
{
    emoji proje;
    proje.yuzBul();

    waitKey(0);
}