#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>

using namespace cv;

int main()
{
    int len = 300;
    int l = 90;
    double cx,cy,r1,r2,r3;
    int cx_in,cy_in;
    srand (time(0));
    std::ofstream pointFiletrain;
    pointFiletrain.open("./imagenew/train/pointdatatrain.csv", std::ios::out); 
    std::ofstream angleFiletrain;
    angleFiletrain.open("./imagenew/train/angledatatrain.csv", std::ios::out); 
    std::ofstream pointFiletest;
    pointFiletest.open("./imagenew/test/pointdatatest.csv", std::ios::out); 
    std::ofstream angleFiletest;
    angleFiletest.open("./imagenew/test/angledatatest.csv", std::ios::out);
    for(int i =0;i<50000;i++)
    {
	Mat blankImage(len,len,CV_8UC1,255);
	char imagename[200];
        //create head
	r1 = rand()%1024 /1024.0;
	r2 = rand()%1024 /1024.0;
    	cx = len/2+(r1-0.5)*len/8;
    	cy = len/4+(r2-0.5)*len/8;
    	cx_in = cvRound(cx);
    	cy_in = cvRound(cy);
    	Point center(cx_in, cy_in);
    	

	//create body
	double angle_neck;
	int bx,by,asx,asy,bxd,byd;
	int upbody = 25;
	int body = 80;
	r3 = rand()%1024 /1024.0;
    	angle_neck = 1.5*CV_PI+(r3-0.5)*CV_PI/2;
	bx = cx_in+cvRound(body*cos(angle_neck));
	by = cy_in-cvRound(body*sin(angle_neck));
	asx = cx_in+cvRound(upbody*cos(angle_neck));
	asy = cy_in-cvRound(upbody*sin(angle_neck));
	bxd = bx-cvRound(50*cos(angle_neck));
	byd = by+cvRound(50*sin(angle_neck));	
	std::cout<<atan2(asy-cy_in,asx-cx_in)<<std::endl;


	ellipse(blankImage, center, Size(12,17),atan2(asy-cy_in,asx-cx_in)/CV_PI*180+90,0,360, Scalar(0), -1, 1, 0);
    	line(blankImage,Point(cx_in,cy_in),Point(asx,asy),0,8,LINE_AA);
    	line(blankImage,Point(bxd,byd),Point(bx,by),0,20,LINE_AA);

	//create arms
	double la1,la2,ra1,ra2;
	double left_upper_arm_angle, left_lower_arm_angle, right_upper_arm_angle, right_lower_arm_angle;
	int luax,luay,ruax,ruay;
	int llax,llay,rlax,rlay;
	int lasx,lasy,rasx,rasy;
	double akl,akr,abl,abr,arm_xc;
	double upan;
        int pass_arm = 0;
	int arm_l = 25;
	std::cout<<"arm"<<std::endl;
	while(pass_arm == 0)
	{
	    pass_arm = 1;
	    la1 = rand()%1024/1024.0;
	    la2 = 2*(rand()%1024/1024.0-0.5);
	    ra1 = rand()%1024/1024.0;
	    ra2 = 2*(rand()%1024/1024.0-0.5);
	    left_upper_arm_angle = angle_neck-0.2-la1*2*CV_PI/4;
	    left_lower_arm_angle = left_upper_arm_angle + la2*3*CV_PI/4;
	    right_upper_arm_angle = angle_neck+0.2+ra1*2*CV_PI/4;
	    right_lower_arm_angle = right_upper_arm_angle + ra2*3*CV_PI/4;
	    
	    upan = 2*CV_PI-atan2(asy-cy_in,asx-cx_in);
	    lasx = cvRound(asx + 14.5*cos(upan-CV_PI/2));
	    lasy = cvRound(asy - 14.5*sin(upan-CV_PI/2));
	    rasx = cvRound(asx + 14.5*cos(upan+CV_PI/2));
	    rasy = cvRound(asy - 14.5*sin(upan+CV_PI/2));
	    //upper arm
	    luax = lasx + cvRound(arm_l*cos(left_upper_arm_angle));
	    luay = lasy - cvRound(arm_l*sin(left_upper_arm_angle));
	    ruax = rasx + cvRound(arm_l*cos(right_upper_arm_angle));
	    ruay = rasy - cvRound(arm_l*sin(right_upper_arm_angle));
	    //lower arm
	    llax = luax + cvRound(arm_l*cos(left_lower_arm_angle));
	    llay = luay - cvRound(arm_l*sin(left_lower_arm_angle));
	    rlax = ruax + cvRound(arm_l*cos(right_lower_arm_angle));
	    rlay = ruay - cvRound(arm_l*sin(right_lower_arm_angle));

	    if (max(rlax,ruax)<min(llax,luax)||max(rlay,ruay)<min(llay,luay)||max(llax,luax)<min(rlax,ruax)||max(llay,luay)<min(rlay,ruay))
	    {
	    	
		
	    	if (((luax-rlax)*(ruay-rlay)-(ruax-rlax)*(luay-rlay))*((llax-rlax)*(ruay-rlay)-(ruax-rlax)*(llay-rlay))<=0&&((ruax-llax)*(luay-llay)-(luax-llax)*(ruay-llay))*((rlax-llax)*(luay-llay)-(luax-llax)*(rlay-llay))<=0)
	    	{
		    pass_arm = 0;
	    	}
	    }
	}

	ellipse(blankImage, Point(asx,asy), Size(19,6),atan2(asy-cy_in,asx-cx_in)/CV_PI*180+90,0,360, Scalar(0), -1, 1, 0);

	line(blankImage,Point(lasx,lasy),Point(luax,luay),0,8,LINE_AA);
	line(blankImage,Point(rasx,rasy),Point(ruax,ruay),0,8,LINE_AA);
	line(blankImage,Point(luax,luay),Point(llax,llay),0,8,LINE_AA);
	line(blankImage,Point(ruax,ruay),Point(rlax,rlay),0,8,LINE_AA);

	//create legs
	//upper
	double ll1,ll2,rl1,rl2;
	double left_upper_leg_angle, left_lower_leg_angle, right_upper_leg_angle, right_lower_leg_angle;
	int lulx,luly,rulx,ruly;
	int lllx,llly,rllx,rlly;
	int rbx,rby,lbx,lby;
	int pass_leg=0;
	int leg_l =40;
	double lkl,lkr,lbl,lbr,leg_xc;
	std::cout<<"leg"<<std::endl;
	while (pass_leg == 0)
	{
	    pass_leg = 1;
	    ll1 = rand()%1024/1024.0;
	    ll2 = rand()%1024/1024.0;
	    rl1 = rand()%1024/1024.0;
	    rl2 = rand()%1024/1024.0;
	    left_upper_leg_angle = angle_neck-0.1-ll1*CV_PI/4;
	    left_lower_leg_angle = left_upper_leg_angle - ll2*3*CV_PI/4;
	    right_upper_leg_angle = angle_neck+0.1+rl1*CV_PI/4;
	    right_lower_leg_angle = right_upper_leg_angle - rl2*3*CV_PI/4;

	    upan = 2*CV_PI-atan2(asy-cy_in,asx-cx_in);
	    lbx = cvRound(bx + 10*cos(upan-CV_PI/2));
	    lby = cvRound(by - 10*sin(upan-CV_PI/2));
	    rbx = cvRound(bx + 10*cos(upan+CV_PI/2));
	    rby = cvRound(by - 10*sin(upan+CV_PI/2));
	    //upper leg
	    lulx = lbx + cvRound(leg_l*cos(left_upper_leg_angle));
	    luly = lby - cvRound(leg_l*sin(left_upper_leg_angle));
	    rulx = rbx + cvRound(leg_l*cos(right_upper_leg_angle));
	    ruly = rby - cvRound(leg_l*sin(right_upper_leg_angle));
	    //lower leg
	    lllx = lulx + cvRound(leg_l*cos(left_lower_leg_angle));
	    llly = luly - cvRound(leg_l*sin(left_lower_leg_angle));
	    rllx = rulx + cvRound(leg_l*cos(right_lower_leg_angle));
	    rlly = ruly - cvRound(leg_l*sin(right_lower_leg_angle));

	    if (max(rllx,rulx)<min(lllx,lulx)||max(rlly,ruly)<min(llly,luly)||max(lllx,lulx)<min(rllx,rulx)||max(llly,luly)<min(rlly,ruly))
	    {
	    	
	    	if (((lulx-rllx)*(ruly-rlly)-(rulx-rllx)*(luly-rlly))*((lllx-rllx)*(ruly-rlly)-(rulx-rllx)*(llly-rlly))<=0&&((rulx-lllx)*(luly-llly)-(lulx-lllx)*(ruly-llly))*((rllx-lllx)*(luly-llly)-(lulx-lllx)*(rlly-llly))<=0)
	    	{
		    pass_leg = 0;
	    	}
	    }
	}
	line(blankImage,Point(bx,by),Point(lulx,luly),0,14,LINE_AA);
	line(blankImage,Point(bx,by),Point(rulx,ruly),0,14,LINE_AA);
	line(blankImage,Point(lulx,luly),Point(lllx,llly),0,8,LINE_AA);
	line(blankImage,Point(rulx,ruly),Point(rllx,rlly),0,8,LINE_AA);
	//save image and data
	if (i%4 == 0)
	{
	angleFiletest<<i<<","<<cx_in<<","<<cy_in<<","<<angle_neck<<","<<l<<","
	<<asx<<","<<asy<<","<<left_upper_arm_angle<<","<<l/2<<","
	<<luax<<","<<luay<<","<<left_lower_arm_angle<<","<<l/2<<","
	<<asx<<","<<asy<<","<<right_upper_arm_angle<<","<<l/2<<","
	<<ruax<<","<<ruay<<","<<right_lower_arm_angle<<","<<l/2<<","
	<<bx<<","<<by<<","<<left_upper_leg_angle<<","<<l/2<<","
	<<lulx<<","<<luly<<","<<left_lower_leg_angle<<","<<l/2<<","
	<<bx<<","<<by<<","<<right_upper_leg_angle<<","<<l/2<<","
	<<rulx<<","<<ruly<<","<<right_lower_leg_angle<<","<<l/2<<std::endl;
	pointFiletest<<i<<","<<cx_in<<","<<cy_in<<","
	<<asx<<","<<asy<<","<<luax<<","<<luay<<","<<llax<<","<<llay<<","<<ruax<<","<<ruay<<","<<rlax<<","<<rlay<<","
	<<bx<<","<<by<<","<<lulx<<","<<luly<<","<<lllx<<","<<llly<<","<<rulx<<","<<ruly<<","<<rllx<<","<<rlly<<std::endl;
	sprintf(imagename,"./imagenew/test/%d.png",i);
	std::cout<<imagename<<std::endl;
	imwrite( imagename, blankImage );
	}
	else
	{
	angleFiletrain<<i<<","<<cx_in<<","<<cy_in<<","<<angle_neck<<","<<l<<","
	<<asx<<","<<asy<<","<<left_upper_arm_angle<<","<<l/2<<","
	<<luax<<","<<luay<<","<<left_lower_arm_angle<<","<<l/2<<","
	<<asx<<","<<asy<<","<<right_upper_arm_angle<<","<<l/2<<","
	<<ruax<<","<<ruay<<","<<right_lower_arm_angle<<","<<l/2<<","
	<<bx<<","<<by<<","<<left_upper_leg_angle<<","<<l/2<<","
	<<lulx<<","<<luly<<","<<left_lower_leg_angle<<","<<l/2<<","
	<<bx<<","<<by<<","<<right_upper_leg_angle<<","<<l/2<<","
	<<rulx<<","<<ruly<<","<<right_lower_leg_angle<<","<<l/2<<std::endl;
	pointFiletrain<<i<<","<<cx_in<<","<<cy_in<<","
	<<asx<<","<<asy<<","<<luax<<","<<luay<<","<<llax<<","<<llay<<","<<ruax<<","<<ruay<<","<<rlax<<","<<rlay<<","
	<<bx<<","<<by<<","<<lulx<<","<<luly<<","<<lllx<<","<<llly<<","<<rulx<<","<<ruly<<","<<rllx<<","<<rlly<<std::endl;
	sprintf(imagename,"./imagenew/train/%d.png",i);
	std::cout<<imagename<<std::endl;
	imwrite( imagename, blankImage );
	}
    //imshow("Display Image", blankImage);
    //waitKey(0);
    }	
    angleFiletrain.close();
    pointFiletrain.close();
    angleFiletest.close();
    pointFiletest.close();

    return 0;
}
