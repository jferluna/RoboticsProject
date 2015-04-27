#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Global Variables
Mat img; Mat templ; Mat result;
char* image_window = "Source Image";
char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;
int aux=0;

/// Function Headers
void MatchingMethod( int, void* );

/** @function main */
int main( int argc, char** argv )
{
	VideoCapture cap(1); //capture the video from web cam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }

	while(1) {
		Mat imgOriginal;
        bool bSuccess = cap.read(imgOriginal); // read a new frame from video
		if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

		/// Load image and template
		img = imgOriginal;
		templ = imread( "C:\\Users\\AliciaGpe\\Desktop\\flama.png", 1 );

		/// Create windows
		namedWindow( image_window, CV_WINDOW_AUTOSIZE );
		namedWindow( result_window, CV_WINDOW_AUTOSIZE );

		/// Create Trackbar
		char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
		
		createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );


		/// Create Trackbar
		char* trackbar_value = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
		createTrackbar( trackbar_value, image_window, &match_method, max_Trackbar, MatchingMethod );

		MatchingMethod( 0, 0 );

		waitKey(50);
	}
  
  return 0;
}

/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void MatchingMethod( int, void* )
{
  /// Source image to display
  Mat img_display;
  img.copyTo( img_display );

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_cols, result_rows, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( img, templ, result, match_method );
  //normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

  /// Show me what you got
 
  rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  int centX = matchLoc.x + (templ.cols / 2);
  int centY= matchLoc.y;
  if (centY <(img.rows/2) && centY >(img.rows/4) ) {
  if(centX <  (img.cols / 3)) {
	   rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar(255,255,0), 2, 8, 0 );
		  if (aux != 1)
		  {
			cout << "Flama 1"<<endl;
			aux=1;
		  }
			} else if (centX > (img.cols / 3) && centX < ( 2* img.cols / 3)) {
				 rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar(255,0,255), 2, 8, 0 );
			  if (aux != 2)
			  {
				cout << "Flama 2"<<endl;
				aux=2;
			  }
	  } else {
		   rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar(0,255,255), 2, 8, 0 );
		  if (aux != 3)
		  {
			cout << "Flama 3"<<endl;
			aux=3;
		  }
	  }
  }
  else{
	  if (aux !=4)
	  {
		  cout<<"ninguna flama"<<endl;
		  aux=4;
	  }
  }
  

  imshow( image_window, img_display );
  imshow( result_window, result );

  return;
}
