#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc, char** argv )
{

    int len = 300;
    Mat rImage=imread("./testing_painting/7003.png");
    Mat oImage(len,len,CV_8UC3,Scalar(255,255,255));
    Mat aImage;
    
    int l = 90;
    int output[22] = {150,  91, 120, 124,  78, 135,  59,  95, 122, 166, 168, 164,  90, 158,
          56, 175,  34, 155,  67, 201,  18, 188};

    circle(oImage, Point(output[0],output[1]), l/4, Scalar(0,0,255), 3, 8, 0);
    //draw upperbody
    line(oImage,Point(output[0],output[1]),Point(output[2],output[3]),Scalar(0,0,255),3,LINE_AA);
    //draw leftupperarm
    line(oImage,Point(output[2],output[3]),Point(output[4],output[5]),Scalar(0,0,255),3,LINE_AA);
    //draw leftlowerarm
    line(oImage,Point(output[4],output[5]),Point(output[6],output[7]),Scalar(0,0,255),3,LINE_AA);
    //draw rightupperarm
    line(oImage,Point(output[2],output[3]),Point(output[8],output[9]),Scalar(0,0,255),3,LINE_AA);
    //draw rightlowerarm
    line(oImage,Point(output[8],output[9]),Point(output[10],output[11]),Scalar(0,0,255),3,LINE_AA);
    //draw lowerbody
    line(oImage,Point(output[2],output[3]),Point(output[12],output[13]),Scalar(0,0,255),3,LINE_AA);
    //draw leftupperleg
    line(oImage,Point(output[12],output[13]),Point(output[14],output[15]),Scalar(0,0,255),3,LINE_AA);	
    //draw leftlowerleg
    line(oImage,Point(output[14],output[15]),Point(output[16],output[17]),Scalar(0,0,255),3,LINE_AA);	
    //draw rightupperleg
    line(oImage,Point(output[12],output[13]),Point(output[18],output[19]),Scalar(0,0,255),3,LINE_AA);	
    //draw rightlowerleg
    line(oImage,Point(output[18],output[19]),Point(output[20],output[21]),Scalar(0,0,255),3,LINE_AA);
    addWeighted(rImage,0.6,oImage,0.4,0,aImage);
    imshow("compare",aImage);	
    waitKey(0);
    return 0;
}
