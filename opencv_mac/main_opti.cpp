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
#include <cmath> // module pour utiliser les valeurs absolue
#include <time.h>
#include <sys/time.h>

using namespace std;
using namespace::cv;


int main(int argc, const char * argv[]) {
    // entier pour stocker le nombre de lignes et de colonne de la matrice/image
    
    // n = taille du kernel (matrice qu'on va utiliser pour réaliser le filtre médian)
    int n = 9;
    int k = ((n-3)/2)+1;
    // vecteur contenant les valeurs sur lesquelles on va appliquer les filtres
    auto conteneur = vector<int> {4,3,2,1,3,2,1,4,5,1,6,2,2,3,5,6};
    auto conteneur_i = 0; // index qu'on va utiliser pour mettre les valeurs dans l'objet Mat
   
    
    //Mat grad_Sobel = grad.clone(); // matrice/image qui va contenir le résultat du filtrage de Sobel
    Mat grad_Sobel; // création de l'objet Mat qui va garder l'image
    Mat grad_image;
    grad_image = imread("/Users/kowsikan/ESIEE/E4/INF-4101/projet/opencv_mac/2_frere.jpg"); // image en couleur
    // réalisation de la conversion en niveau de gris
    Mat grad; // objet Mat qui va garder l'image en niveau de gris
    cvtColor( grad_image, grad, COLOR_BGR2GRAY );
    grad_Sobel = grad.clone(); // on clone l'image FMA (en gris )  dans cet objet
    
    int row = grad.rows;
    int col = grad.cols;
    
    // Deuxième objet Mat pour faire le calcul du filtre median (il sera plus grand que l'objet Mat contenant l'image)
    Mat grad_median = Mat(row+2*k,col+2*k,CV_8U);
//    cout<<grad<<endl;
//    cout<<"\n\n"<<endl;
//    cout<<grad_median<<endl;
    


struct timeval start, end;
gettimeofday(&start, NULL);    
    //copie de la valeur de l'image dans la matrice grad_median
    for (int i =k; i<grad_median.rows-k;i++){
        for (int j= k; j<grad_median.cols-k;j++){
            grad_median.at<uint8_t>(i,j) = grad.at<uint8_t>(i-k,j-k);
            //grad_median.at<uint8_t>(i+1,j+1) = grad.at<uint8_t>(i+1-k,j-k+1);
        }
        
    }

//    cout<<"Affichage après la copie de l'image dans la matrice median\n"<<endl;
//    cout<<grad<<endl;
//    cout<<"\n\n"<<endl;
//    cout<<grad_median<<endl;

// CODE DEROULAGE DE BOUCLE 
    // // on réalise le filtrage (médian)
    // auto temp = vector<int>(); // vecteur qui va stocker les valeurs que l'on obtient avec la matrice nxn de filtrage
    // auto temp_1 = vector<int>(); // vecteur qui va stocker les valeurs que l'on obtient avec la matrice nxn de filtrage
    // cout<<"Debut du filtrage"<<endl;
    // for (int i = k; i<grad_median.rows-k-1;i+=2){
    //     for (int j = k; j<grad_median.cols-k; j++){
    //         for (int ind_i = -k; ind_i<k+1;ind_i++){
    //             for (int ind_j= -k; ind_j<k+1; ind_j++){
    //                 temp.push_back(grad_median.at<uint8_t>(i+ind_i,j+ind_j));
    //                 temp_1.push_back(grad_median.at<uint8_t>(i+1+ind_i,j+ind_j));
    //                 // mettre les 3 lignes du dessous ici pour ralentir le temps d'exécution du programme ?
    //             }
    //         }
    //         sort (temp.begin(), temp.end()); // tri du vecteur temp
    //         sort (temp_1.begin(), temp_1.end()); // tri du vecteur temp
    //         //cout<<"La valeur de la médiane est "<<temp[(int) temp.size()/2]<<" "<<endl;
    //         grad.at<uint8_t>(i-k,j-k) = temp[(int) temp.size()>>1];
    //         grad.at<uint8_t>(i-k+1,j-k) = temp_1[(int) temp_1.size()>>1];
    //         temp.clear();
    //         temp_1.clear();
    //     }
    // }



// CODE AVEC L'HISTOGRAMME
auto temp = vector<int>(256);
int median = 0;
int pos = 0;
int mid = (n*n)/2; 

// PARTIE FILTRE MEDIAN AVEC LA MOITIE DE L'HISTOGRAMME 
for (int i = k; i<grad_median.rows-k;i++){
    for (int j = k; j<grad_median.cols-k; j++){
        if (j==k){
            for (int ind_i = -k; ind_i<k+1; ind_i++){
                for (int ind_j= -k; ind_j<k+1; ind_j++){
                    temp[(int) grad_median.at<uint8_t>(i+ind_i,j+ind_j)]++;
                }
            }
        }
        else {
            // suppression de la colonne + ajout de la colonne (se trouvant à la distance k de pixel (i,j))
            for (int ind_i = -k; ind_i<k+1; ind_i++){
                temp[(int) grad_median.at<uint8_t>(i+ind_i,j+k)]++;
                temp[(int) grad_median.at<uint8_t>(i+ind_i,j-1-k)]--;
            }
        }
        // on détermine la valeur du médian 
        while(median < mid){
            median+=temp[pos];
            //cout<<temp[pos]<<endl;
            pos++;
        }

        
        grad.at<uint8_t>(i-k,j-k) = pos;
        pos =0; 
        median =0;

    }
    //display(temp);
    temp.clear();
    temp.resize(256);
}

// PARTIE FILTRE MEDIAN AVEC L'HISTOGRAMME COMPLET
// for (int i =k; i<grad_median.rows-k;i++){
//     if (i == k ){
//         for (int j = k; j<grad_median.cols-k; j++){
//             if (j==k){
//                 for (int ind_i = -k; ind_i<k+1; ind_i++){
//                     for (int ind_j = -k; ind_j<k+1;ind_j++){
//                         temp[(int)grad_median.at<uint8_t>(i+ind_i,j+ind_j)]++;
//                     }
//                 }
//             }
//             else {
//                 for (int ind_i = -k; ind_i<k+1; ind_i++){
//                     temp[(int) grad_median.at<uint8_t>(i+ind_i,j+k)]++;
//                     temp[(int) grad_median.at<uint8_t>(i+ind_i,j-1-k)]--;
//                 }
//             }
//             while(median < mid){
//                 median+=temp[pos];
//                 //cout<<temp[pos]<<endl;
//                 pos++;
//             }
//             grad.at<uint8_t>(i-k,j-k) = pos;
//             pos =0; 
//             median =0;
//         }
//     }

//     else if (k%2==0){
//         if (i%2==0){
//             for (int j = grad_median.cols-k-2;j>=k;j--){
//                 for (int ind_i = -k; ind_i<k+1; ind_i++){
//                     temp[(int)grad_median.at<uint8_t>(i+ind_i,j+k+1)]--; 
//                     temp[(int)grad_median.at<uint8_t>(i+ind_i,j-k)]++;
//                 }
//                 while(median < mid){
//                     median+=temp[pos];
//                     //cout<<temp[pos]<<endl;
//                     pos++;
//                 }
                

            
//                 grad.at<uint8_t>(i-k,j-k) = pos;
//                 pos =0; 
//                 median =0;
//             }


//             // travaille sur les valeurs qu'on skip dans la boucle 
//              for (int ind_j = -k;ind_j<k+1;ind_j++){
//                 temp[(int)grad_median.at<uint8_t>(i-k-1,grad_median.cols-k-1+ind_j)]--;
//                 temp[(int)grad_median.at<uint8_t>(i+k,grad_median.cols-k-1+ind_j)]++;
//             }
//             while(median < mid){
//                     median+=temp[pos];
//                     //cout<<temp[pos]<<endl;
//                     pos++;
//                 }
                

            
//                 grad.at<uint8_t>(i-k,grad_median.cols-k-1-k) = pos;
//                 pos =0; 
//                 median =0;
//         }
//         else if (i%2!=0){
//             for (int j = k+1; j<grad_median.cols-k;j++){
//                 for (int ind_i = -k; ind_i<k+1; ind_i++){
//                     temp[(int)grad_median.at<uint8_t>(i+ind_i,j-k-1)]--;
//                     temp[((int)grad_median.at<uint8_t>(i+ind_i,j+k))]++;
//                 }
//                 while(median < mid){
//                     median+=temp[pos];
//                     //cout<<temp[pos]<<endl;
//                     pos++;
//                 }
                

            
//                 grad.at<uint8_t>(i-k,j-k) = pos;
//                 pos =0; 
//                 median =0;
//             }

//             for (int ind_j = -k; ind_j<k+1; ind_j++){
//                 temp[(int)grad_median.at<uint8_t>(i-k-1,k+ind_j)]--;
//                 temp[(int)grad_median.at<uint8_t>(i+k,k+ind_j)]++;
//             }
//             while(median < mid){
//                     median+=temp[pos];
//                     //cout<<temp[pos]<<endl;
//                     pos++;
//                 }
                

            
//                 grad.at<uint8_t>(i-k,k-k) = pos;
//                 pos =0; 
//                 median =0;
//         }
//     }

//     else{
//         if (i%2==0){
//             for (int j = grad_median.cols-k-2;j>=k;j--){
//                 for (int ind_i = -k; ind_i<k+1; ind_i++){
//                     temp[(int)grad_median.at<uint8_t>(i+ind_i,j+k+1)]--;
//                     temp[(int)grad_median.at<uint8_t>(i+ind_i,j-k)]++;
//                 }
//                 while(median < mid){
//                     median+=temp[pos];
//                     //cout<<temp[pos]<<endl;
//                     pos++;
//                 }
                

            
//                 grad.at<uint8_t>(i-k,j-k) = pos;
//                 pos =0; 
//                 median =0;
//             }

//         }

//         else if (i%2!=0){
//             for (int j = k+1; j<grad_median.cols-k; j++){
//                 for (int ind_i = -k; ind_i<k+1; ind_i++){
//                     temp[(int)grad_median.at<uint8_t>(i+ind_i,j-k-1)]--; 
//                     temp[(int)grad_median.at<uint8_t>(i+ind_i,j+k)]++;
//                 }
//                 while(median < mid){
//                     median+=temp[pos];
//                     //cout<<temp[pos]<<endl;
//                     pos++;
//                 }
                

            
//                 grad.at<uint8_t>(i-k,j-k) = pos;
//                 pos =0; 
//                 median =0;
//             }

//             for (int ind_j = -k; ind_j<k+1; ind_j++){
//                 temp[(int)grad_median.at<uint8_t>(i-k-1,k+ind_j)]--;
//                 temp[(int)grad_median.at<uint8_t>(i+k,k+ind_j)]++;
//             }
//             while(median < mid){
//                     median+=temp[pos];
//                     //cout<<temp[pos]<<endl;
//                     pos++;
//                 }
                

            
//                 grad.at<uint8_t>(i-k,k-k) = pos;
//                 pos =0; 
//                 median =0;
//         }
//     }
// }

gettimeofday(&end, NULL);
double e = ((double) end.tv_sec * 1000.0 + (double) end.tv_usec*0.001);
double s = ((double) start.tv_sec * 1000.0 + (double) start.tv_usec*0.001);
cout<<"Le temps d'exécution du programme opti pour le filtre Médian est "<<(e-s)<<" ms"<<endl;
    
    // PARTIE FILTRE DE SOBEL


    gettimeofday(&start, NULL); 
    for (int i = 1; i<grad.rows-2;i+=2) {
        for (int j = 1; j < grad.cols-1;j+=1){
            // int x = grad.at<uint8_t>(i-1,j-1)*(-1)+grad.at<uint8_t>(i-1,j)*(-2)+grad.at<uint8_t>(i-1,j+1)*(-1)+grad.at<uint8_t>(i+1,j-1)+grad.at<uint8_t>(i+1,j)*2+grad.at<uint8_t>(i+1,j+1);
            // int y = grad.at<uint8_t>(i-1,j-1)+grad.at<uint8_t>(i-1,j+1)*(-1)+grad.at<uint8_t>(i,j-1)*2+grad.at<uint8_t>(i,j+1)*(-2)+grad.at<uint8_t>(i+1,j-1)+grad.at<uint8_t>(i+1,j+1)*(-1);
			
			// int x2 = grad.at<uint8_t>(i,j-1)*(-1)+grad.at<uint8_t>(i,j)*(-2)+grad.at<uint8_t>(i,j+1)*(-1)+grad.at<uint8_t>(i+2,j-1)+grad.at<uint8_t>(i+2,j)*2+grad.at<uint8_t>(i+2,j+1);
            // int y2 = grad.at<uint8_t>(i,j-1)+grad.at<uint8_t>(i,j+1)*(-1)+grad.at<uint8_t>(i+1,j-1)*2+grad.at<uint8_t>(i+1,j+1)*(-2)+grad.at<uint8_t>(i+2,j-1)+grad.at<uint8_t>(i+2,j+1)*(-1);
//            cout<<(int)grad.at<uint8_t>(i-1,j-1)<<" "<<(int) grad.at<uint8_t>(i-1,j)<<" "<<(int)grad.at<uint8_t>(i-1,j+1)<<endl;
//            cout<<(int) grad.at<uint8_t>(i,j-1)<<" "<<(int) grad.at<uint8_t>(i,j)<<" "<<(int)grad.at<uint8_t>(i,j+1)<<endl;
//            cout<<(int) grad.at<uint8_t>(i+1,j-1)<<" "<<(int) grad.at<uint8_t>(i+1,j)<<" "<<(int)grad.at<uint8_t>(i+1,j+1)<<endl;
            //cout<<"La valeur de x : "<<x<<"\nLa valeur de y : "<<y<<endl;
            //cout<<"La valeur de Sobel est "<<(x+y)/2<<endl;
            grad_Sobel.at<uint8_t>(i,j) = (abs(grad.at<uint8_t>(i-1,j-1)*(-1)+grad.at<uint8_t>(i-1,j)*(-2)+grad.at<uint8_t>(i-1,j+1)*(-1)+grad.at<uint8_t>(i+1,j-1)+grad.at<uint8_t>(i+1,j)*2+grad.at<uint8_t>(i+1,j+1))+abs(grad.at<uint8_t>(i-1,j-1)+grad.at<uint8_t>(i-1,j+1)*(-1)+grad.at<uint8_t>(i,j-1)*2+grad.at<uint8_t>(i,j+1)*(-2)+grad.at<uint8_t>(i+1,j-1)+grad.at<uint8_t>(i+1,j+1)*(-1)))>>1;
            grad_Sobel.at<uint8_t>(i+1,j)= (abs(grad.at<uint8_t>(i,j-1)*(-1)+grad.at<uint8_t>(i,j)*(-2)+grad.at<uint8_t>(i,j+1)*(-1)+grad.at<uint8_t>(i+2,j-1)+grad.at<uint8_t>(i+2,j)*2+grad.at<uint8_t>(i+2,j+1))+abs(grad.at<uint8_t>(i,j-1)+grad.at<uint8_t>(i,j+1)*(-1)+grad.at<uint8_t>(i+1,j-1)*2+grad.at<uint8_t>(i+1,j+1)*(-2)+grad.at<uint8_t>(i+2,j-1)+grad.at<uint8_t>(i+2,j+1)*(-1)))>>1;
        }
    }
    
    gettimeofday(&end, NULL);
    e = ((double) end.tv_sec * 1000.0 + (double) end.tv_usec*0.001);
    s = ((double) start.tv_sec * 1000.0 + (double) start.tv_usec*0.001);
    cout<<"Le temps d'exécution du programme opti pour le filtre Sobel est "<<(e-s)<<" ms"<<endl;


    namedWindow( "Test affichage", WINDOW_AUTOSIZE );
    imshow("Test affichage", grad_image);
    namedWindow( "Test Sobel", WINDOW_AUTOSIZE );
    imshow("Test Sobel", grad_Sobel);
    namedWindow( "Test Median", WINDOW_AUTOSIZE );
    imshow("Test Median", grad);
    
    //cout<<grad_Sobel<<endl;
    waitKey(0);
    return 0;
}
