#include "Video.hpp"

int Video::conversionCanales()
{
    Mat canny;
    Mat result;

    bool checked = false;
    bool checkedHSV = false;
    bool checkedYCrCb = false;
    bool checkedLAB = false;

    Mat frame;
     Mat frame2;

    VideoCapture video(0); 

    if (!video.isOpened()) 
        return -1;

   
    //cvui::init("Guzman_Tene");
     //cvui::watch("B.Guzman_A.Tene");
    const cv::String window[]= {"Guzman_Tene","B.Guzman_A.Tene"};
    cvui::init(window,2);
    
    while (true)
    {
      

        video >> frame; 
        frame2 = frame;
        frame.copyTo(canny);
        //frame2.copyTo(result);
         //cvu::context("Guzman_Tene");
         

        if (checked)
        {
           

            cvtColor(frame, frame2, COLOR_BGR2GRAY);

        }
        else if (checkedHSV)
        {
            cvtColor(frame, frame2, COLOR_BGR2HSV);
        }
        else if (checkedYCrCb)
        {   
            cvtColor(frame, frame2, COLOR_BGR2YCrCb);
        }
        else if (checkedLAB)
        {
            cvtColor(frame, frame2, COLOR_BGR2Lab);
        }
        else
        {
            
            //frame.copyTo(result);

        }

        cvui::text(canny, 10, 10, "Original", 1.0, 0xff0000);
        cvui::text(frame2, 10, 10, "Conversion, Espacios de Color", 1.0, 0xff0000);
        if (cvui::button(canny, 550, 10, "Salir"))
            break;
        
        if (cvui::button(canny, 10, 110, "Escala de grises")){
            checked = true;
            checkedHSV = false;
            checkedYCrCb = false;
            checkedLAB = false;
        }
        
        if (cvui::button(canny, 10, 70, "Original")){
            checked = false;
            checkedHSV = false;
            checkedYCrCb = false;
            checkedLAB = false;
        }
        if (cvui::button(canny, 10, 150, "HSV")){
            checkedHSV = true;
            checked = false;
            checkedYCrCb = false;
            checkedLAB = false;
        }
            
        if (cvui::button(canny, 10, 190, "YCrCB")){
            checkedYCrCb = true;
            checked = false;
            checkedHSV = false;
            checkedLAB = false;
        }

        if (cvui::button(canny, 10, 230, "Lab")){
            checkedLAB = true;
            checkedHSV = false;
            checkedYCrCb = false;
            checked = false;
        }

        if (cvui::button(canny, 10, 270, "Guardar Imagen Conversion")){
          cv::imwrite("actual.png", frame2);

        }

        cvui::update();
        imshow("Guzman_Tene", canny); 
        imshow("B.Guzman_A.Tene", frame2);
        waitKey(10); 
    }
};
