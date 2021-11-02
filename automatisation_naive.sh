g++ -std=c++11 `pkg-config --cflags opencv` projet_naive.cpp `pkg-config --libs opencv` -o projet_naive # commande pour compiler le code 

echo "*************Temps de calcul pour n fixe, différentes taille d'image*************" >> result_naive.txt 
./projet_naive 240 320 3 >> result_naive.txt #rows, cols, n 
./projet_naive 480 640 3 >> result_naive.txt #rows, cols, n 
./projet_naive 1280 720 3 >> result_naive.txt #rows, cols, n 
./projet_naive 1080 1920 3 >> result_naive.txt #rows, cols, n  
echo "*********************************************************************" >> result_naive.txt 

echo "*************Temps de calcul avec taille d'image fixe, différents n*************" >> result_naive.txt 
./projet_naive 480 640 3 >> result_naive.txt #rows, cols, n   
./projet_naive 480 640 5 >> result_naive.txt #rows, cols, n   
./projet_naive 480 640 7 >> result_naive.txt #rows, cols, n   
./projet_naive 480 640 9 >> result_naive.txt #rows, cols, n   
./projet_naive 480 640 11 >> result_naive.txt #rows, cols, n   
./projet_naive 480 640 13 >> result_naive.txt #rows, cols, n   
./projet_naive 480 640 15 >> result_naive.txt #rows, cols, n   
./projet_naive 480 640 17 >> result_naive.txt #rows, cols, n   
echo "*********************************************************************" >> result_naive.txt 

echo "*************Temps de calcul avec taille d'image et n fixe mais niveau d'opti différent*************" >> result_naive.txt 
g++ -std=c++11 -O0`pkg-config --cflags opencv` projet_naive.cpp `pkg-config --libs opencv` -o projet_naive # commande pour compiler le code 
./projet_naive 480 640 5 >> result_naive.txt #rows, cols, n      
g++ -std=c++11 -O1`pkg-config --cflags opencv` projet_naive.cpp `pkg-config --libs opencv` -o projet_naive # commande pour compiler le code 
./projet_naive 480 640 5 >> result_naive.txt #rows, cols, n      
g++ -std=c++11 -O2`pkg-config --cflags opencv` projet_naive.cpp `pkg-config --libs opencv` -o projet_naive # commande pour compiler le code 
./projet_naive 480 640 5 >> result_naive.txt #rows, cols, n      
g++ -std=c++11 -O3`pkg-config --cflags opencv` projet_naive.cpp `pkg-config --libs opencv` -o projet_naive # commande pour compiler le code 
./projet_naive 480 640 5 >> result_naive.txt #rows, cols, n      
echo "*********************************************************************" >> result_naive.txt 

