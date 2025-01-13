# EEET2482-GroupAssignment

Advanced Programming Techniques course - FINAL GROUP ASSIGNMENT

Compiling all files, add more files as the project grow:

1. Go to project root: cd /path/to/project/root
2. Compile all files (add more folders as needed, e.g., src/auction/_.cpp):
   g++ src/main.cpp src/system/_.cpp src/users/\*.cpp -o build/AuctionApp.exe

Running the main app:

1. Go to build folder: cd build
2. ./AuctionApp.exe

For Testing:

1. cd /path/to/project/root
2. g++ tests/test.cpp src/system/_.cpp src/users/_.cpp src/database/\*.cpp -o tests/TestApp.exe
3. cd tests
4. ./TestApp.exe

Admin Account (no registration allowed, hardcoded in System.cpp):

1. username: admin
2. password: Admin@123
