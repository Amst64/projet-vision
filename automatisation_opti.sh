g++ -std=c++11 `pkg-config --cflags opencv` projet_opti.cpp `pkg-config --libs opencv` -o projet_opti # commande pour compiler le code 

echo "*************Temps de calcul pour n fixe, différentes taille d'image*************" >> result_opti.txt 
./projet_opti 240 320 3 >> result_opti.txt #rows, cols, n 
./projet_opti 480 640 3 >> result_opti.txt #rows, cols, n 
./projet_opti 1280 720 3 >> result_opti.txt #rows, cols, n 
./projet_opti 1080 1920 3 >> result_opti.txt #rows, cols, n  
echo "*********************************************************************" >> result_opti.txt 

echo "*************Temps de calcul avec taille d'image fixe, différents n*************" >> result_opti.txt 
./projet_opti 480 640 3 >> result_opti.txt #rows, cols, n   
./projet_opti 480 640 5 >> result_opti.txt #rows, cols, n   
./projet_opti 480 640 7 >> result_opti.txt #rows, cols, n   
./projet_opti 480 640 9 >> result_opti.txt #rows, cols, n   
./projet_opti 480 640 11 >> result_opti.txt #rows, cols, n   
./projet_opti 480 640 13 >> result_opti.txt #rows, cols, n   
./projet_opti 480 640 15 >> result_opti.txt #rows, cols, n   
./projet_opti 480 640 17 >> result_opti.txt #rows, cols, n   
echo "*********************************************************************" >> result_opti.txt 

echo "*************Temps de calcul avec taille d'image et n fixe mais niveau d'opti différent*************" >> result_opti.txt 
g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_opti -O0 # commande pour compiler le code 
./projet_opti 480 640 5 >> result_opti.txt #rows, cols, n      
g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_opti -O1 # commande pour compiler le code 
./projet_opti 480 640 5 >> result_opti.txt #rows, cols, n      
g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_opti -O2 # commande pour compiler le code 
./projet_opti 480 640 5 >> result_opti.txt #rows, cols, n      
g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_opti -O3 # commande pour compiler le code 
./projet_opti 480 640 5 >> result_opti.txt #rows, cols, n      
g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_opti -Ofast # commande pour compiler le code 
./projet_opti 480 640 5 >> result_opti.txt #rows, cols, n      
g++ -std=c++11 `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet_opti -Og # commande pour compiler le code 
./projet_opti 480 640 5 >> result_opti.txt #rows, cols, n      
echo "*********************************************************************" >> result_opti.txt 

