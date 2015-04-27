#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 	//UART
#include <fcntl.h> 		//UART
#include <termios.h> 	//UART

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
int configureUART0(int* uart0_Handle, int blockMode);
int transmitData(int* uart0_Handle, char* tx_data, int tx_length);
int receiveData(int* uart0_Handle,char* rx_data, int* rx_length);

int main( int argc, char** argv ) {
	int result;
	char rx_data[256];
	int uart0_Handle = -1;
	int rx_length;

  	configureUART0(&uart0_Handle, 1)
    	
	VideoCapture cap(1); //capture the video from web cam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }

	while(1) {
		result = receiveData(&uart0_Handle, &rx_data[0], &rx_length);
		printf("%x\n", rx_data[0]);
		switch(rx_data[0]) {
			case 0x80:
				Mat imgOriginal;
	        	bool bSuccess = cap.read(imgOriginal); // read a new frame from video
				if (!bSuccess) //if not success, break loop
		        {
		             cout << "Cannot read a frame from video stream" << endl;
		             return -1;
		        }

				/// Load image and template
				img = imgOriginal;
				templ = imread("C:\\Users\\AliciaGpe\\Desktop\\flama.png", 1 );

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
				break;
		}
	}
  return 0;
}

void MatchingMethod( int, void* ) {
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

int configureUART0(int* uart0_Handle, int blockMode) {
  
  if(blockMode) {
    *uart0_Handle = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);
  } else {
    *uart0_Handle = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
  }
  if(*uart0_Handle == -1) {
    printf("Unable to open UART #0\n");
    return -1;
  } else {
    printf("UART #0 openning succesful!!\n");
  }

  struct termios options;
  tcgetattr(*uart0_Handle, &options);
  options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(*uart0_Handle, TCIFLUSH);
  tcsetattr(*uart0_Handle, TCSANOW, &options);

  return 0; 
}

int transmitData(int* uart0_Handle, char* tx_data, int tx_length) {
  if(*uart0_Handle != -1) {
    int count = write(*uart0_Handle, tx_data, tx_length);
    if(count > 0) {
      printf("Send sucessful, sent %d characters\n", count);
      return 0;
    } else {
      printf("Tx error\n");
      return -1;
    }
  }
}

int receiveData(int* uart0_Handle,char* rx_data, int* rx_length) {
  if(*uart0_Handle != -1) {
      *rx_length = read(*uart0_Handle, rx_data, 255);
  }
  if(*rx_length > 0) {
    char* aux = rx_data;
    aux += *rx_length;
    *aux = '\0';
    printf("Data received= %s\n", rx_data);
    return 0;
  }
  return -1;
}
