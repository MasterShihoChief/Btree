#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <vector>
#include "B_tree.h"
#include "util.h"

using namespace std;
// create output file pointer
ofstream ofilePtr;

int srcTerm;
int srcTerm2;

B_tree <int, 3> tree3;
B_tree <int, 7> tree7;
int main (int argc, char * argv[]) {
 cout<< "B+Tree, by Joshua Hunter"<<endl;
cout<<"Supreme Commander MasterShihoChief"<<endl;
cout<<"Covenant Battle Net High Command"<<endl;
cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout<<"@@.................................................................................................................................................. C"<<endl;
cout<<"@@                                                                                                                o:                                 C"<<endl;
cout<<"@@                                                                                                               o88:                                C"<<endl;
cout<<"@@                                                                                                              :8OOOc:.                             C"<<endl;
cout<<"@@                                                                                                        :8O88OOOOOOOOO88c                          C"<<endl;
cout<<"@@                                                                                                          :COOOOOOOOOO.                            C"<<endl;
cout<<"@@                                                                                                            COOOOOOO8.                             C"<<endl;
cout<<"@@                                                                                                            OOO8OOOO8c                             C"<<endl;
cout<<"@@                                          .:::::::::::::::::.                                              :C.     :oO                             C"<<endl;
cout<<"@@                                        .::::::::::::::::::::::                                                                                    C"<<endl;
cout<<"@@                                       :::::::::::::::::::::::::                                                                                   C"<<endl;
cout<<"@@                                        :::::::::::::::::::::::.                                                                                   C"<<endl;
cout<<"@@                                          :::::::::::::::::::.                                                                                     C"<<endl;
cout<<"@@                                               ..::::::..                                                                                          C"<<endl;
cout<<"@@                              ..::::::::::::::::::::..                                                                                             C"<<endl;
cout<<"@@                        .::::::::::::::::::::::::::::::::::.                                                                                       C"<<endl;
cout<<"@@                     .::::::::::::::::::::::::::::::::::::::::                                                                                     C"<<endl;
cout<<"@@                    ::::::::::::::::::::::::::::::::::::::::::::                                                                                   C"<<endl;
cout<<"@@                    ::::::::::::::::::::::::::::::::::::::::::::                                                                                   C"<<endl;
cout<<"@@                     :::::::::::::::::::::::::::::::::::::::::.                                                                                    C"<<endl;
cout<<"@@                        .:::::::::::::::::::::::::::::::::.                                                                                        C"<<endl;
cout<<"@@                              ...::::::::::::::::::..                                                                                              C"<<endl;
cout<<"@@                                                ........                                                                                           C"<<endl;
cout<<"@@                                          :::::::::::::::::::.                                                                                     C"<<endl;
cout<<"@@                                       .:::::::::::::::::::::::.                                                                                   C"<<endl;
cout<<"@@                                       :::::::::::::::::::::::::                                                                                   C"<<endl;
cout<<"@@                                        .::::::::::::::::::::::                                                                                    C"<<endl;
cout<<"@@                                          ..::::::::::::::::.                                                                                      C"<<endl;
cout<<"@@                                                                                                                                                   C"<<endl;
cout<<"@@                                                                                                                                                   C"<<endl;
cout<<"@@                                                                                                                                                   C"<<endl;
cout<<"@@                                                                                                                                                   C"<<endl;
cout<<"@@                                                                                                                                                   C"<<endl;
cout<<"@@                                                                                                                                                   C"<<endl;
cout<<"@@                                                                                                                                                   C"<<endl;
cout<<"@@                                                                                                                                                   C"<<endl;
cout<<"@@                                                                                                                                                   C"<<endl;
cout<<"@@                                                                                                                                                   C"<<endl;
cout<<"@@                    o:                                                                                                                             C"<<endl;
cout<<"@@                   o8Oo                                                                                                                            C"<<endl;
cout<<"@@                 .C8OO8c                                                                                                                           C"<<endl;
cout<<"@@            .C8OOOOOOOOOOOO8C                                                                                                                      C"<<endl;
cout<<"@@               oOOOOOOOOOOc                                                                                                                        C"<<endl;
cout<<"@@                c8OOOOOO8c                                                                                                                         C"<<endl;
cout<<"@@               .CO8OOOOO8C                                                                                                                         C"<<endl;
cout<<"@@               cC:      oO.                                                                                                                        C"<<endl;
cout<<"@@...................................................................................................................................................C"<<endl;
    if (argc != 3) {
        cerr << "usage: B+Tree <input-file> <output-file>" << endl;
        return 1;
    }
    
    // cout<<"Reading input and out from command line arguments"<<endl;
    char * ifile = argv[1];
    char * ofile = argv[2];
    
    char * token;
    
    char buffer[100];
    
    
  // cout<<"creating file pointer to read input file"<<endl;
    fstream ifilePtr;
    // cout<<"opening file in read mode"<,endl;
    ifilePtr.open(ifile, ios::in);
    if (!ifilePtr) {
        cout << "Can't find: " << argv[1] << endl;
        cerr << "Failed to open file" << endl;
        return 1;
    }
    
    
    
    ofilePtr.open(ofile, ios::out | ios::app);
    if(!ofilePtr.is_open()) {
        cerr << "Failed to open file:" << ofile << endl;
        return 1;
    }
    
    
        // create the tree 3 dynamically after grabbing the first line of the file
        ifilePtr.getline(buffer, 100);
        token = strtok(NULL, " ");
        token = strtok(buffer, " ");
        int order = atoi(token);
      
        //cout << "Creating a B+ tree3 of order < " << order << " >   ---> B_tree3 <int," << order << "> tree3" << endl;
    
  
    
    
    while (!ifilePtr.eof()) {
        ifilePtr.getline(buffer, 100);
        if (buffer[0] == '\0') {
            continue;
        }
        
        //using strtok()
        token = strtok(buffer, " ");
        
        switch (*token) 
        {
            case 'A':
                // add a new node to the AVL tree3
                token = strtok(NULL, " ");
                srcTerm = atoi(token);
                if(!tree3.insert(srcTerm)) {
                    ofilePtr << "Error: attempt to insert duplicate value of " << token << endl;
                    //cout << "Error: attempt to insert duplicate value of " << token << endl;
                } 
                else 
                {
                    ofilePtr << "Success: " << atoi(token) << " was inserted into the tree3" << endl;
                    //cout << "Success: " << atoi(token) << " was inserted into the tree3" << endl;
                    
                }
				if(!tree7.insert(srcTerm)) {
                    ofilePtr << "Error: attempt to insert duplicate value of " << token << endl;
                   // cout << "Error: attempt to insert duplicate value of " << token << endl;
                } 
                else 
                {
                    ofilePtr << "Success: " << atoi(token) << " was inserted into the tree7" << endl;
                   // cout << "Success: " << atoi(token) << " was inserted into the tree7" << endl;
                    
                }
                break;
            case 'D':
                token = strtok(NULL, " ");
                srcTerm = atoi(token);
                if(tree3.remove(srcTerm)) {
                    ofilePtr << "Success: " << atoi(token) << " was removed from the tree3" << endl;
                    //cout << "Success: " << atoi(token) << " was removed from the tree3" << endl;
                } else {
                    ofilePtr << "Error: attempt to delete a value not found in the tree3 of " << atoi(token) << endl;
                   // cout << "Error: attempt to delete a value not found in the tree3 of " << atoi(token) << endl;
                }
				 if(tree7.remove(srcTerm)) {
                    ofilePtr << "Success: " << atoi(token) << " was removed from the tree7" << endl;
                    //cout << "Success: " << atoi(token) << " was removed from the tree7" << endl;
                } else {
                    ofilePtr << "Error: attempt to delete a value not found in the tree7 of " << atoi(token) << endl;
                   //cout << "Error: attempt to delete a value not found in the tree7 of " << atoi(token) << endl;
                }
                break;
            case 'S':
                token = strtok(NULL, " ");
                if(token!=NULL)
                {
                    //Get a value from a token only if that value is an integer and not NULL
                    srcTerm=atoi(token);
                }
                token = strtok(NULL, " ");
                if(token!=NULL)
                {
                    srcTerm2=atoi(token);
                }
                
                tree3.search_tree(srcTerm, srcTerm2);
                tree7.search_tree(srcTerm, srcTerm2);
                break;
            case 'P':
                tree3.print(ofilePtr);
				tree7.print(ofilePtr);

                
        }
        
        
    }
    
    ifilePtr.close();
    ofilePtr.close();
    cout<<"No runtime errors detected! Please check your specified output file for output."<<endl;
    
    return 0;
}