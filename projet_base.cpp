/*
 * Fichier source pour le projet d'unité
 *  INF-4101C
 *---------------------------------------------------------------------------------------------------
 * Pour compiler : g++ `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet
 *---------------------------------------------------------------------------------------------------
 * auteur : Eva Dokladalova 09/2015
 * modification : Eva Dokladalova 10/2021
 */


/* 
 * Libraries stantards 
 *
 */ 
#include <stdio.h>
#include <stdlib.h>

/* 
 * Libraries OpenCV "obligatoires" 
 *
 */ 
#include "highgui.h"
#include "cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
  
/* 
 * Définition des "namespace" pour évite cv::, std::, ou autre
 *
 */  
using namespace std;
using namespace cv;
using std::cout;

/*
 * Some usefull defines
 * (comment if not used)
 */
#define PROFILE
#define VAR_KERNEL
#define N_ITER 100

#ifdef PROFILE
#include <time.h>
#include <sys/time.h>
#endif


/*
 *
 *--------------- MAIN FUNCTION ---------------
 *
 */
int main (int argc, char *argv[]) {
//----------------------------------------------
// Video acquisition - opening
//----------------------------------------------
  VideoCapture cap(0); // le numéro 0 indique le point d'accès à la caméra 0 => /dev/video0
  if(!cap.isOpened()){
    cout << "Error"; return -1;
  
  }
  
  int rows,cols,n; 
  // s'il y a plus d'une valeur on va laisser l'utilisateur choisir les valeurs 
  if (argc>1){ // plus d'un argument l'utilisateur veut changer les valeurs
    cout<<"L'utilisateur va changer les valeurs"<<endl; 
    cout<<"La valeur pour le nombre de lignes : "<<endl;
    cin>>rows; 
    cout<<"La valeur pour le nombre de colonnes : "<<endl;
    cin>>cols; 
    cout<<"La valeur de n pour le filtre median : "<<endl; 
    cin>>n; 
  }
  else {
  // HD resolution  1 920 × 1 080,
    rows = 240; // 480, 1080	
    cols = 320; // 640, 1920
  // image smoothing by median blur
    
    n = 17;
  }

  cap.set(CAP_PROP_FRAME_WIDTH, cols);	 
  cap.set(CAP_PROP_FRAME_HEIGHT, rows);

//----------------------------------------------
// Déclaration des variables - imagesize
// Mat - structure contenant l'image 2D niveau de gris
// Mat3b - structure contenant l'image 2D en couleur (trois cannaux)
//
  Mat3b frame; // couleur
  Mat frame1; // niveau de gris 
  Mat frame_gray; // niveau de gris 
  Mat grad_x;
  Mat grad_y;
  Mat abs_grad_y;
  Mat abs_grad_x;
  Mat grad;

// variable contenant les paramètres des images ou d'éxécution  
  int ddepth = CV_16S;
  int scale = 1;
  int delta = 0;	
  double moy_median =0;
  int n_median =0;
  double moy_sobel =0; 
  int n_sobel =0; 
  unsigned char key = '0';

 #define PROFILE
  
#ifdef PROFILE
// profiling / instrumentation libraries
#include <time.h>
#include <sys/time.h>
#endif
  
//----------------------------------------------------
// Création des fenêtres pour affichage des résultats
// vous pouvez ne pas les utiliser ou ajouter selon ces exemple
// 
  cvNamedWindow("Video input", WINDOW_AUTOSIZE);
  cvNamedWindow("Video gray levels", WINDOW_AUTOSIZE);
  cvNamedWindow("Video Mediane", WINDOW_AUTOSIZE);
  cvNamedWindow("Video Edge detection", WINDOW_AUTOSIZE);
// placement arbitraire des  fenêtre sur écran 
// sinon les fenêtres sont superposée l'une sur l'autre
  cvMoveWindow("Video input", 10, 30);
  cvMoveWindow("Video gray levels", 800, 30);
  cvMoveWindow("Video Mediane", 10, 500);
  cvMoveWindow("Video Edge detection", 800, 500);
  
  
// --------------------------------------------------
// boucle infinie pour traiter la séquence vidéo  
//
  while(key!='q'){
  //	  
  // acquisition d'une trame video - librairie OpenCV
    cap.read(frame);
  //conversion en niveau de gris - librairie OpenCV
    cvtColor(frame, frame_gray, CV_BGR2GRAY);

	
   // image smoothing by median blur
   // 
 int n = 17;
 
 #ifdef PROFILE
 struct timeval start, end;
 gettimeofday(&start, NULL);
 #endif
     	
    // ------------------------------------------------
    // calcul de la mediane - librairie OpenCV
     medianBlur(frame_gray, frame1, n);
 #ifdef PROFILE
 gettimeofday(&end, NULL);
 double e = ((double) end.tv_sec * 1000000.0 + (double) end.tv_usec);
 double s = ((double) start.tv_sec * 1000000.0 + (double) start.tv_usec);
moy_median +=(e-s); // convertir en miliseconde pour ne pas dépasser la vleur des doubles et donc saturer les valeurs 
n_median++;
 printf("Mediane : %lf\n", n, (e - s));

 #endif

#ifdef PROFILE
// struct timeval start, end;
 gettimeofday(&start, NULL);
 #endif  
 
    // ------------------------------------------------
    // calcul du gradient- librairie OpenCV
    /// Gradient Y
    Sobel( frame1, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
	/// absolute value
    convertScaleAbs( grad_x, abs_grad_x );
    /// Gradient Y
    Sobel( frame1, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
	/// absolute value
    convertScaleAbs( grad_y, abs_grad_y );
    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad ); 	
 
#ifdef PROFILE
 gettimeofday(&end, NULL);
 e = ((double) end.tv_sec * 1000000.0 + (double) end.tv_usec);
 s = ((double) start.tv_sec * 1000000.0 + (double) start.tv_usec);
 moy_sobel += (e-s); 
 n_sobel++; 
 printf("Sobel : %lf\n", (e - s));

 #endif


    
    
    // -------------------------------------------------
    // visualisation
    // taille d'image réduite pour meuilleure disposition sur écran
    //    resize(frame, frame, Size(), 0.5, 0.5);
    //    resize(frame_gray, frame_gray, Size(), 0.5, 0.5);
    //    resize(grad, grad, Size(), 0.5, 0.5);
    imshow("Video input",frame);
    imshow("Video gray levels",frame_gray);
    imshow("Video Mediane",frame1);    
    imshow("Video Edge detection",grad);  
    
    
    key=waitKey(5);
  }
cout<<"nb image pour le filtre median "<<n_median<<"moy pour median "<<moy_median/n_median<<endl;
cout<<"nb image pour le filtre sobel "<<n_sobel<<" moy pour sobel "<< moy_sobel/n_sobel<<endl;
}

