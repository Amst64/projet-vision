/*******************************************************************/ 
/*  HPC(3) : TP parallÃ©lisation 
 *  
 *  Eva Dokladalova, 2020
 */
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "functions.h"

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// Function to perform Selection Sort
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
 
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
 
        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}
// Function to print an array
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//-----------------------------------------------------------
// MAIN FUNCTION
//-----------------------------------------------------------
int main (int argc, char *argv[])
{
 
  // noms des fichiers d'entrÃ©e et de sortie
  char *filename=argv[1];
  char *file_out=argv[2];

  // exemples des pointeurs vers les matrices reprÃ©sentant les images
  int *T;
  int *Grad;
  int *Grad_median;

  // dimension de matrice, valeur maximale
  int v;  // max  value in matrix
  int rw; // row size
  int cl; // column size
  int k = 1; // La taille de la matrice à utiliser pour faire le filtrage
  // vÃ©rification des arguments d'entrÃ©e
  if (argc != 3)
    {  fprintf(stderr,"Input parameters missing:\n./program_name <inpout.pgm> <output.pgm>\n");
      return(0);
    }

  
  //-------------------------------------------------------------
  // OPEN DATA FILE AND ALLOCATE INPUT IMAGE MEMORY (float precision)
  //-------------------------------------------------------------
  T = readimg(filename, &rw, &cl, &v);
  Grad = (int *) calloc (rw*cl,sizeof(int));
  Grad_median = (int *) calloc ((rw+(2*k))*(cl+(2*k)),sizeof(int));
 
// for (int j = 1; j < rw-1; j++)
// 	for (int i = 1; i< cl-1; i++)
// 	{
// 		//int n = T[i + (j-1)*rw];
// 	    //int s = T[i + (j+1)*rw];
		
// 		int x = T[i + (j-1)*rw - 1] * (-1) + T[i + j*rw - 1] * (-2) + T[i + (j+1)*rw - 1] * (-1) + T[i + (j-1)*rw + 1] + T[i + j*rw + 1] * 2 + T[i + (j+1)*rw + 1];
// 		if(x<0)
// 		{
// 			x=-x;
// 		}
		
// 		int y = T[i + (j-1)*rw - 1] + T[i + (j-1)*rw] * 2 + T[i + (j-1)*rw + 1] + T[i + (j+1)*rw - 1] * (-1) + T[i + (j+1)*rw] * (-2) + T[i + (j+1)*rw + 1] * (-1);
// 		if(y<0)
// 		{
// 			y=-y;
// 		}
		
// 		Grad[i + j*rw] = (x+y)/2;

// 	}





//----------------------------------------------------------------
// FILTRE MEDIAN 
//---------------------------------------------------------------- 

//copie de la matrice grad dans la matrice grad_median 
for (int i = k; i<(rw + ( 2*k ) - k);i++){
    for (int j = k; j<(cl + ( 2*k ) - k);j++){
        Grad_median[i*(cl+(2*k))+j] = T[(i-k)*cl+(j-k)]; 
    }
}

int n = 2*(k-1) + 3; 
// Parcours de la matrice pour réaliser le filtrage
for (int i = k; i<(rw + ( 2*k ) - k);i++){
    for (int j = k; j<(cl + ( 2*k ) - k);j++){
        int temp[n*n];
        int ind_temp = 0;
        // ajout des valeurs obtenue par la matrice dans temp
        for( int ind_i = -k; ind_i < k+1;ind_i++){
            for( int ind_j = -k; ind_j<k+1; ind_j++){
                temp[ind_temp] = Grad_median[(i+ind_i)*(cl+2*k)+(j+ind_j)];                
                selectionSort(temp,n*n);
                int median_value = temp[(int) (n*n)/2];
                Grad[(i-k)*cl+(j-k)] = median_value;
                ind_temp++;
                // printf("%d",median_value);
                // printf("\n");
                // int taille = n*n;
                // printf(temp,taille);
                // printf("\n");
            }
        }
        // tri du array temp (d'abord tester en sortant la les vector dans le prgm median qui marche)
    }
}

//     printArray(Grad,rw*cl);
// ----------------------------------------------------------------
// FIN FILTRE MEDIAN 
// ---------------------------------------------------------------- 







  //-------------------------------------------------------------
  // WRITE RESULT IN A PGN IMAGE 
  //-------------------------------------------------------------
   writeimg(file_out, Grad, rw, cl, v);
   free(Grad);
   free(Grad_median);
   free(T);
   return(0);
}
  //-------------------------------------------------------------
  // FILTRE DE SOBEL
  //-------------------------------------------------------------

  //-------------------------------------------------------------
  // A COMPLETER :-)
  // exemple d'un traitement de base  
  //Sobel
//   for (int j = 1; j < rw-1; j++)
// 	for (int i = 1; i< cl-1; i++)
// 	{
// 		//int n = T[i + (j-1)*rw];
// 	    //int s = T[i + (j+1)*rw];
		
// 		int x = T[i + (j-1)*rw - 1] * (-1) + T[i + j*rw - 1] * (-2) + T[i + (j+1)*rw - 1] * (-1) + T[i + (j-1)*rw + 1] + T[i + j*rw + 1] * 2 + T[i + (j+1)*rw + 1];
// 		if(x<0)
// 		{
// 			x=-x;
// 		}
		
// 		int y = T[i + (j-1)*rw - 1] + T[i + (j-1)*rw] * 2 + T[i + (j-1)*rw + 1] + T[i + (j+1)*rw - 1] * (-1) + T[i + (j+1)*rw] * (-2) + T[i + (j+1)*rw + 1] * (-1);
// 		if(y<0)
// 		{
// 			y=-y;
// 		}
		
// 		Grad[i + j*rw] = (x+y)/2;

// 	}
// ---------------------------------------------------------------- 