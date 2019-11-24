//
//  main.cpp
//  paging
//
//  Created by afieqha mieza azemi on 24/11/2019.
//  Copyright © 2019 afieqha mieza azemi. All rights reserved.
//

#include <iostream>
using namespace std;

int main()
{
    int MemSize=15;
    int PageSize,PageNum;
    int p[100];
    int FrameNum,offset;
    int LogAdd,PhyAdd;
    int choice=0;
    
    cout << "memory size: " << MemSize << endl;
    
    cout << "Enter the page size: ";
    cin  >> PageSize;
    
    PageNum = MemSize/PageSize;
    
    for(int i=0; i<PageNum; i++)
    {
        cout << "Enter the frame of page " << i+1 << ": ";
        cin  >> p[i];
    }
    
    do{
        cout << "Enter a logical address: ";
        cin  >> LogAdd;
        
        FrameNum = LogAdd / PageSize;
        offset = LogAdd % PageSize;
        PhyAdd = (p[FrameNum] * PageSize) + offset;
        
        cout << "Physical address is: " << PhyAdd << endl;
        
        cout << "Do you want to continue(1/0)?: ";
        cin  >> choice;
        
    }while(choice==1);
    
    return 0;
}
