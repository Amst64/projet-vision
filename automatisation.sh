g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_base # commande pour compiler le code 

echo "*************Temps de calcul pour n fixe, différentes taille d'image*************" >> result.txt 
./projet_base 240 320 3 >> result.txt #rows, cols, n 
./projet_base 480 640 3 >> result.txt #rows, cols, n 
./projet_base 1280 720 3 >> result.txt #rows, cols, n 
./projet_base 1080 1920 3 >> result.txt #rows, cols, n  
echo "*********************************************************************" >> result.txt 

echo "*************Temps de calcul avec taille d'image fixe, différents n*************" >> result.txt 
./projet_base 480 640 3 >> result.txt #rows, cols, n   
./projet_base 480 640 5 >> result.txt #rows, cols, n   
./projet_base 480 640 7 >> result.txt #rows, cols, n   
./projet_base 480 640 9 >> result.txt #rows, cols, n   
./projet_base 480 640 11 >> result.txt #rows, cols, n   
./projet_base 480 640 13 >> result.txt #rows, cols, n   
./projet_base 480 640 15 >> result.txt #rows, cols, n   
./projet_base 480 640 17 >> result.txt #rows, cols, n   
echo "*********************************************************************" >> result.txt 

echo "*************Temps de calcul avec taille d'image et n fixe mais niveau d'opti différent*************" >> result.txt 
g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_base -O0# commande pour compiler le code 
./projet_base 480 640 5 >> result.txt #rows, cols, n      
g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_base -O1 # commande pour compiler le code 
./projet_base 480 640 5 >> result.txt #rows, cols, n      
g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_base -O2 # commande pour compiler le code 
./projet_base 480 640 5 >> result.txt #rows, cols, n      
g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_base -O3 # commande pour compiler le code 
./projet_base 480 640 5 >> result.txt #rows, cols, n      
g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_base -Ofast # commande pour compiler le code 
./projet_base 480 640 5 >> result.txt #rows, cols, n      
g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_base -Og # commande pour compiler le code 
./projet_base 480 640 5 >> result.txt #rows, cols, n      
echo "*********************************************************************" >> result.txt 

