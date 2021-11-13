//
//  main.cpp
//  test
//
//  Created by Julien Ravindrarasa on 29/10/2021.
//

#include <iostream>
#include <opencv2/core.hpp>
#include "opencv2/core/core.hpp"

#include "opencv2/highgui/highgui.hpp"

#include "opencv2/imgproc/imgproc.hpp"

#include <time.h>
#include <sys/time.h>
using namespace std;
using namespace::cv;

int main(int argc, const char * argv[]) {
    // entier pour stocker le nombre de lignes et de colonne de la matrice/image
    
    // n = taille du kernel (matrice qu'on va utiliser pour réaliser le filtre médian)
    int n = 17;
    int k = ((n-3)/2)+1;
    // vecteur contenant les valeurs sur lesquelles on va appliquer les filtres
    auto conteneur = vector<int> {4,3,2,1,3,2,1,4,5,1,6,2,2,3,5,6};
    auto conteneur_i = 0; // index qu'on va utiliser pour mettre les valeurs dans l'objet Mat
   
    
    Mat3b frame; // couleur
    Mat frame1; // niveau de gris 
    Mat frame_gray; // niveau de gris 
    Mat grad_x;
    Mat grad_y;
    Mat abs_grad_y;
    Mat abs_grad_x;
    Mat grad;
  int ddepth = CV_16S;
  int scale = 1;
  int delta = 0;	
  
    frame = imread("/Users/kowsikan/ESIEE/E4/INF-4101/projet/opencv_mac/2_frere.jpg"); // image en couleur
    // réalisation de la conversion en niveau de gris

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );

    
    int row = grad.rows;
    int col = grad.cols;
    

  struct timeval start, end;
  gettimeofday(&start, NULL);
  medianBlur(frame_gray, frame1, n);
  gettimeofday(&end, NULL);
  double e = ((double) end.tv_sec * 1000.0 + (double) end.tv_usec*0.001);
  double s = ((double) start.tv_sec * 1000.0 + (double) start.tv_usec*0.001);
  cout<<"Le temps d'exécution du programme naif pour le filtre de median est "<<(e-s)<<endl;
    
    
    // PARTIE FILTRE DE SOBEL
 gettimeofday(&start, NULL);
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
    

  gettimeofday(&end, NULL);
  e = ((double) end.tv_sec * 1000.0 + (double) end.tv_usec*0.001);
  s = ((double) start.tv_sec * 1000.0 + (double) start.tv_usec*0.001);
  cout<<"Le temps d'exécution du programme naif pour le filtre de Sobel est "<<(e-s)<<endl;
  
    namedWindow( "Test affichage", WINDOW_AUTOSIZE );
    imshow("Test affichage", frame);
    namedWindow( "Test Sobel", WINDOW_AUTOSIZE );
    imshow("Test Sobel", grad);
    namedWindow( "Test Median", WINDOW_AUTOSIZE );
    imshow("Test Median", frame1);
    
    //cout<<grad_Sobel<<endl;
    waitKey(0);
    return 0;
}
