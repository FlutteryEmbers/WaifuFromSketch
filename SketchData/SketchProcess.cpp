#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc, char** argv )
{

    Mat srcImage,sImage;
    Mat rImage(300,300,CV_8UC1);
    char data_set[200];
    char data_set1[200];
    std::ofstream pointFile;
    int num = 300;
    pointFile.open("./data_deal/pointdata.csv", std::ios::out); 

    for (int i = 1;i<num+1;i++)
    {
		pointFile<<i;
		for (int j = 1;j<12;j++)
		{
			sprintf(data_set,"./data_deal/%d/%d.png",j,i);
			srcImage = imread(data_set);
			Mat midImage(srcImage.rows,srcImage.cols,CV_8UC1);
			for (int m =0;m<srcImage.rows;m++)
			{
				for (int n = 0;n<srcImage.cols;n++)
				{
					Vec3b pixel;
					pixel = srcImage.at<Vec3b>(m,n);
					//std::cout<<pixel<<std::endl;
					if (pixel[2]>200&&pixel[0]<100&&pixel[1]<100)
					{
						 midImage.ptr<uchar>(m)[n]=0;
					}
					else
					{
						midImage.ptr<uchar>(m)[n]=255;
					}
					
					
				}
			}
			//imshow("test",midImage);
			std::vector<Vec3f> circles;
			HoughCircles(midImage, circles, CV_HOUGH_GRADIENT, 1, midImage.rows/15, 50, 20, 0, 0);

    		printf("before\n");
			int cx,cy,cr;
			//draw circle
    		std::cout <<"size: "<<circles.size()<<std::endl;
			
    		for (size_t i = 0; i < circles.size(); i++)
			{
				printf("for\n");
				std::cout<<"x: "<<circles[i][0]<<", y: "<<circles[i][1]<<", r: "<<circles[i][2]<<std::endl;
				cx = circles[i][0];
				cy = circles[i][1];
				cr = circles[i][2];

			}
			
			pointFile<<","<<cx<<","<<cy;
		}
		pointFile<<std::endl;
    }
    pointFile.close();

    return 0;
}
