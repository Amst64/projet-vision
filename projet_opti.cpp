/*
 * Fichier source pour le projet d'unité
 *  INF-4101C
 *---------------------------------------------------------------------------------------------------
 * Pour compiler : g++ `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet
 *---------------------------------------------------------------------------------------------------
 * auteur : Eva Dokladalova 09/2015
 * modification : Eva Dokladalova 10/2021
 */

// utiliser soit le tri fusion, par tas ou quicksort pour trier la liste du median 
/* 
 * Libraries stantards 
 *
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <signal.h>
#include <cmath> // module pour utiliser les valeurs absolue

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


int rows,cols,n; 
double moy_median =0;
int n_median =0;
double moy_sobel =0; 
int n_sobel =0; 

// fonction pour gérer l'exeception keyboard interrupt 
void signal_callback_handler(int signum){
  cout<<"======================================================================================================================================================="<<endl;
  cout<<"La valeur de n pour le filtre de median est "<<n<<endl;
  cout<<"La résolution de l'image est :\nrows : "<<rows<<"col : "<<cols<<endl;
  cout<<"nb image pour le filtre median "<<n_median<<" moy pour median "<<moy_median/n_median<<" ms"<<endl;
  cout<<"nb image pour le filtre sobel "<<n_sobel<<" moy pour sobel "<< moy_sobel/n_sobel<<" ms"<<endl;
  cout<<"======================================================================================================================================================="<<endl;
  exit(signum);
}


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
  
  signal(SIGINT,signal_callback_handler);
  // s'il y a plus d'une valeur on va laisser l'utilisateur choisir les valeurs 
  if (argc>1){ // plus d'un argument l'utilisateur veut changer les valeurs
    rows = stoi(argv[1]); // premier argument est la taille des lignes 
    cols = stoi(argv[2]); // second argument est la taille des colonnes 
    n = stoi(argv[3]); // troisième argument est la taille de la matrice median 
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
  int k = ((n-3)/2)+1;
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

    

  
  #ifdef PROFILE
  struct timeval start, end;
  gettimeofday(&start, NULL);
  #endif
        
      // ------------------------------------------------
      // calcul de la mediane - librairie OpenCV

      // medianBlur(frame_gray, frame1, n);

      // filtre median optimisée 

    frame1 = frame_gray.clone();
    Mat grad_median = Mat(frame_gray.rows+2*k,frame_gray.cols+2*k,CV_8U);
    for (int i=k; i<grad_median.rows-k; i++){
      for (int j=k; j<grad_median.cols-k;j++){
        grad_median.at<uint8_t>(i,j) = frame_gray.at<uint8_t>(i-k,j-k);
      }
    }

    // début du filtrage 
    


auto temp = vector<int>(256);
int median = 0;
int pos = 0;
int mid = (n*n)/2; 

// // PARTIE FILTRE MEDIAN AVEC LA MOITIE DE L'HISTOGRAMME 
// for (int i = k; i<grad_median.rows-k;i++){
//     for (int j = k; j<grad_median.cols-k; j++){
//         if (j==k){
//             for (int ind_i = -k; ind_i<k+1; ind_i++){
//                 for (int ind_j= -k; ind_j<k+1; ind_j++){
//                     temp[(int) grad_median.at<uint8_t>(i+ind_i,j+ind_j)]++;
//                 }
//             }
//         }
//         else {
//             // suppression de la colonne + ajout de la colonne (se trouvant à la distance k de pixel (i,j))
//             for (int ind_i = -k; ind_i<k+1; ind_i++){
//                 temp[(int) grad_median.at<uint8_t>(i+ind_i,j+k)]++;
//                 temp[(int) grad_median.at<uint8_t>(i+ind_i,j-1-k)]--;
//             }
//         }
//         // on détermine la valeur du médian 
//         while(median < mid){
//             median+=temp[pos];
//             //cout<<temp[pos]<<endl;
//             pos++;
//         }

        
//         frame1.at<uint8_t>(i-k,j-k) = pos;
//         pos =0; 
//         median =0;

//     }
//     //display(temp);
//     temp.clear();
//     temp.resize(256);
// }

//PARTIE FILTRE MEDIAN AVEC L'HISTOGRAMME COMPLET
for (int i =k; i<grad_median.rows-k;i++){
    if (i == k ){
        for (int j = k; j<grad_median.cols-k; j++){
            if (j==k){
                for (int ind_i = -k; ind_i<k+1; ind_i++){
                    for (int ind_j = -k; ind_j<k+1;ind_j++){
                        temp[(int)grad_median.at<uint8_t>(i+ind_i,j+ind_j)]++;
                    }
                }
            }
            else {
                for (int ind_i = -k; ind_i<k+1; ind_i++){
                    temp[(int) grad_median.at<uint8_t>(i+ind_i,j+k)]++;
                    temp[(int) grad_median.at<uint8_t>(i+ind_i,j-1-k)]--;
                }
            }
            while(median < mid){
                median+=temp[pos];
                //cout<<temp[pos]<<endl;
                pos++;
            }
            frame1.at<uint8_t>(i-k,j-k) = pos;
            pos =0; 
            median =0;
        }
    }

    else if (k%2==0){
        if (i%2==0){
            for (int j = grad_median.cols-k-2;j>=k;j--){
                for (int ind_i = -k; ind_i<k+1; ind_i++){
                    temp[(int)grad_median.at<uint8_t>(i+ind_i,j+k+1)]--; 
                    temp[(int)grad_median.at<uint8_t>(i+ind_i,j-k)]++;
                }
                while(median < mid){
                    median+=temp[pos];
                    //cout<<temp[pos]<<endl;
                    pos++;
                }
                

            
                frame1.at<uint8_t>(i-k,j-k) = pos;
                pos =0; 
                median =0;
            }


            // travaille sur les valeurs qu'on skip dans la boucle 
             for (int ind_j = -k;ind_j<k+1;ind_j++){
                temp[(int)grad_median.at<uint8_t>(i-k-1,grad_median.cols-k-1+ind_j)]--;
                temp[(int)grad_median.at<uint8_t>(i+k,grad_median.cols-k-1+ind_j)]++;
            }
            while(median < mid){
                    median+=temp[pos];
                    //cout<<temp[pos]<<endl;
                    pos++;
                }
                

            
                grad.at<uint8_t>(i-k,grad_median.cols-k-1-k) = pos;
                pos =0; 
                median =0;
        }
        else if (i%2!=0){
            for (int j = k+1; j<grad_median.cols-k;j++){
                for (int ind_i = -k; ind_i<k+1; ind_i++){
                    temp[(int)grad_median.at<uint8_t>(i+ind_i,j-k-1)]--;
                    temp[((int)grad_median.at<uint8_t>(i+ind_i,j+k))]++;
                }
                while(median < mid){
                    median+=temp[pos];
                    //cout<<temp[pos]<<endl;
                    pos++;
                }
                

            
                frame1.at<uint8_t>(i-k,j-k) = pos;
                pos =0; 
                median =0;
            }

            for (int ind_j = -k; ind_j<k+1; ind_j++){
                temp[(int)grad_median.at<uint8_t>(i-k-1,k+ind_j)]--;
                temp[(int)grad_median.at<uint8_t>(i+k,k+ind_j)]++;
            }
            while(median < mid){
                    median+=temp[pos];
                    //cout<<temp[pos]<<endl;
                    pos++;
                }
                

            
                grad.at<uint8_t>(i-k,k-k) = pos;
                pos =0; 
                median =0;
        }
    }

    else{
        if (i%2==0){
            for (int j = grad_median.cols-k-2;j>=k;j--){
                for (int ind_i = -k; ind_i<k+1; ind_i++){
                    temp[(int)grad_median.at<uint8_t>(i+ind_i,j+k+1)]--;
                    temp[(int)grad_median.at<uint8_t>(i+ind_i,j-k)]++;
                }
                while(median < mid){
                    median+=temp[pos];
                    //cout<<temp[pos]<<endl;
                    pos++;
                }
                

            
                frame1.at<uint8_t>(i-k,j-k) = pos;
                pos =0; 
                median =0;
            }

        }

        else if (i%2!=0){
            for (int j = k+1; j<grad_median.cols-k; j++){
                for (int ind_i = -k; ind_i<k+1; ind_i++){
                    temp[(int)grad_median.at<uint8_t>(i+ind_i,j-k-1)]--; 
                    temp[(int)grad_median.at<uint8_t>(i+ind_i,j+k)]++;
                }
                while(median < mid){
                    median+=temp[pos];
                    //cout<<temp[pos]<<endl;
                    pos++;
                }
                

            
                frame1.at<uint8_t>(i-k,j-k) = pos;
                pos =0; 
                median =0;
            }

            for (int ind_j = -k; ind_j<k+1; ind_j++){
                temp[(int)grad_median.at<uint8_t>(i-k-1,k+ind_j)]--;
                temp[(int)grad_median.at<uint8_t>(i+k,k+ind_j)]++;
            }
            while(median < mid){
                    median+=temp[pos];
                    //cout<<temp[pos]<<endl;
                    pos++;
                }
                

            
                grad.at<uint8_t>(i-k,k-k) = pos;
                pos =0; 
                median =0;
        }
    }
}
  #ifdef PROFILE
  gettimeofday(&end, NULL);
  double e = ((double) end.tv_sec * 1000.0 + (double) end.tv_usec*0.001);
  double s = ((double) start.tv_sec * 1000.0 + (double) start.tv_usec*0.001);
  moy_median +=(e-s); // convertir en miliseconde pour ne pas dépasser la vleur des doubles et donc saturer les valeurs 
  n_median++;
  //printf("Mediane : %lf ms\n", n, (e - s));

  #endif

  #ifdef PROFILE
  // struct timeval start, end;
  gettimeofday(&start, NULL);
  #endif  
  
    //   // ------------------------------------------------
    //   // calcul du gradient- librairie OpenCV
    //   /// Gradient Y
    //   Sobel( frame1, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    // /// absolute value
    //   convertScaleAbs( grad_x, abs_grad_x );
    //   /// Gradient Y
    //   Sobel( frame1, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    // /// absolute value
    //   convertScaleAbs( grad_y, abs_grad_y );
    //   /// Total Gradient (approximate)
    //   addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad ); 	
    

    // filtre Sobel avec le déroulement de bouble
    grad = frame_gray.clone();
    for (int j =1;j<cols-1;j++){
      for (int i = 1;i<rows-2;i+=2){
        int x = frame_gray.at<uint8_t>(i-1,j-1)*(-1)+frame_gray.at<uint8_t>(i-1,j)*(-2)+frame_gray.at<uint8_t>(i-1,j+1)*(-1)+frame_gray.at<uint8_t>(i+1,j-1)+frame_gray.at<uint8_t>(i+1,j)*2+frame_gray.at<uint8_t>(i+1,j+1);
        int y = frame_gray.at<uint8_t>(i-1,j-1)+frame_gray.at<uint8_t>(i-1,j+1)*(-1)+frame_gray.at<uint8_t>(i,j-1)*2+frame_gray.at<uint8_t>(i,j+1)*(-2)+frame_gray.at<uint8_t>(i+1,j-1)+frame_gray.at<uint8_t>(i+1,j+1)*(-1);
			  int x2 = frame_gray.at<uint8_t>(i,j-1)*(-1)+frame_gray.at<uint8_t>(i,j)*(-2)+frame_gray.at<uint8_t>(i,j+1)*(-1)+frame_gray.at<uint8_t>(i+2,j-1)+frame_gray.at<uint8_t>(i+2,j)*2+frame_gray.at<uint8_t>(i+2,j+1);
        int y2 = frame_gray.at<uint8_t>(i,j-1)+frame_gray.at<uint8_t>(i,j+1)*(-1)+frame_gray.at<uint8_t>(i+1,j-1)*2+frame_gray.at<uint8_t>(i+1,j+1)*(-2)+frame_gray.at<uint8_t>(i+2,j-1)+frame_gray.at<uint8_t>(i+2,j+1)*(-1);

        grad.at<uint8_t>(i,j) = (abs(x)+abs(y))/2;
        grad.at<uint8_t>(i+1,j)= (abs(x2)+abs(y2))/2;
      }
    }

  #ifdef PROFILE
  gettimeofday(&end, NULL);
  e = ((double) end.tv_sec * 1000.0 + (double) end.tv_usec*0.001);
  s = ((double) start.tv_sec * 1000.0 + (double) start.tv_usec*0.001);
  moy_sobel += (e-s); 
  n_sobel++; 
  //printf("Sobel : %lf ms \n", (e - s));

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
  cout<<"======================================================================================================================================================="<<endl;
  cout<<"La valeur de n pour le filtre de median est "<<n<<endl;
  cout<<"La résolution de l'image est :\nrows : "<<rows<<"col : "<<cols<<endl;
  cout<<"nb image pour le filtre median "<<n_median<<" moy pour median "<<moy_median/n_median<<" ms"<<endl;
  cout<<"nb image pour le filtre sobel "<<n_sobel<<" moy pour sobel "<< moy_sobel/n_sobel<<" ms"<<endl;
  cout<<"======================================================================================================================================================="<<endl;
}

