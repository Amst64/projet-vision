g++ `pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet # commande pour compiler le code 

echo "*************Temps de calcul pour n fixe, différentes taille d'image*************" >> result.txt 
./projet 240 320 3 >> result.txt #rows, cols, n 
./projet 480 640 3 >> result.txt #rows, cols, n 
./projet 1280 720 3 >> result.txt #rows, cols, n 
./projet 1080 1920 3 >> result.txt #rows, cols, n  
echo "*********************************************************************" >> result.txt 

echo "*************Temps de calcul avec taille d'image fixe, différents n*************" >> result.txt 
./projet 480 640 3 >> result.txt #rows, cols, n   
./projet 480 640 5 >> result.txt #rows, cols, n   
./projet 480 640 7 >> result.txt #rows, cols, n   
./projet 480 640 9 >> result.txt #rows, cols, n   
./projet 480 640 11 >> result.txt #rows, cols, n   
./projet 480 640 13 >> result.txt #rows, cols, n   
./projet 480 640 15 >> result.txt #rows, cols, n   
./projet 480 640 17 >> result.txt #rows, cols, n   
echo "*********************************************************************" >> result.txt 

echo "*************Temps de calcul avec taille d'image et n fixe mais niveau d'opti différent*************" >> result.txt 
g++ -O0`pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet # commande pour compiler le code 
./projet 480 640 5 >> result.txt #rows, cols, n      
g++ -O1`pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet # commande pour compiler le code 
./projet 480 640 5 >> result.txt #rows, cols, n      
g++ -O2`pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet # commande pour compiler le code 
./projet 480 640 5 >> result.txt #rows, cols, n      
g++ -O3`pkg-config --cflags opencv` projet_base.cpp `pkg-config --libs opencv` -o projet # commande pour compiler le code 
./projet 480 640 5 >> result.txt #rows, cols, n      
echo "*********************************************************************" >> result.txt 

