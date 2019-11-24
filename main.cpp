//
//  main.cpp
//  LRU
//
//  Created by afieqha mieza azemi on 19/11/2019.
//  Copyright © 2019 afieqha mieza azemi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int fault=0, hit=0;

struct QNode
{
    struct QNode *prev, *next;
    int pageNumber;
};

struct Queue
{
    int count;
    int numberOfFrames;
    QNode *front, *rear;
};

struct Hash {
    int capacity;
    QNode** array;
};

QNode* newQNode(int pageNumber)
{
    QNode* temp = new QNode();
    temp->pageNumber = pageNumber;
    
    temp->prev = temp->next = NULL;
    
    return temp;
}

Queue* createQueue(int numberOfFrames)
{
    Queue* queue = new Queue();
    
    queue->count = 0;
    queue->front = queue->rear = NULL;
    
    queue->numberOfFrames = numberOfFrames;
    
    return queue;
}

Hash* createHash(int capacity)
{
    Hash* hash = new Hash();
    hash->capacity = capacity;
    
    hash->array = new QNode*();
    
    for (int i = 0; i < hash->capacity; ++i)
        hash->array[i] = NULL;
    
    /*for (int i = 0; i < hash->capacity; ++i)
    {
        cout << "here" << endl;
        if (hash->array[i] == NULL) {
            cout << i << " is null\t";
        }
    }
    
    cout << endl;*/
    
    
    return hash;
}

int AreAllFramesFull(Queue* queue)
{
    return queue->count == queue->numberOfFrames;
}

int isQueueEmpty(Queue* queue)
{
    return queue->rear == NULL;
}

void deQueue(Queue* queue)
{
    if (isQueueEmpty(queue))
        return;
    
    if (queue->front == queue->rear)
        queue->front = NULL;
    
    QNode* temp = queue->rear;
    queue->rear = queue->rear->prev;
    
    if (queue->rear)
        queue->rear->next = NULL;
    
    delete temp;
    
    queue->count--;
}

void Enqueue(Queue* queue, Hash* hash, int pageNumber)
{
    if (AreAllFramesFull(queue)) {
        hash->array[queue->rear->pageNumber] = NULL;
        deQueue(queue);
    }
    
    QNode* temp = new QNode();
    temp -> pageNumber = pageNumber;
    temp->next = queue->front;
    
    if (isQueueEmpty(queue))
        queue->rear = queue->front = temp;
    else
    {
        queue->front->prev = temp;
        queue->front = temp;
    }
    
    hash->array[pageNumber] = temp;
    
    queue->count++;
}

void ReferencePage(Queue* queue, Hash* hash, int pageNumber)
{
    QNode* reqPage = hash->array[pageNumber];
    
    if (reqPage == NULL)
    {
        Enqueue(queue, hash, pageNumber);
        fault++;
    }
    
    else if (reqPage != queue->front)
    {
        reqPage->prev->next = reqPage->next;
        if (reqPage->next)
            reqPage->next->prev = reqPage->prev;
        
        if (reqPage == queue->rear) {
            hit++;
            queue->rear = reqPage->prev;
            queue->rear->next = NULL;
        }
        
        reqPage->next = queue->front;
        reqPage->prev = NULL;
        
        reqPage->next->prev = reqPage;
        
        queue->front = reqPage;
    }
}

int main()
{
    int frames, x;
    
    cout << "num of frames: ";
    cin  >> frames;
    
    cout << "num of pages: ";
    cin  >> x;
    
    int seq[x];
    
    cout << "now, we will enter the sequence of pages...\n\tnote: the referenced page should be 0 to 9 only" << endl;
    
    for (int i=0; i<x; i++) {
        cout << "page " << i+1 << ": ";
        cin >> seq[i];
    }
    
    Queue* queue = createQueue(frames);
    Hash* hash = createHash(10);
    
    for (int i=0; i<x; i++) {
        ReferencePage(queue, hash, seq[i]);
    }
    
    printf("%d ", queue->front->pageNumber);
    printf("%d ", queue->front->next->pageNumber);
    printf("%d ", queue->front->next->next->pageNumber);
    //printf("%d ", queue->front->next->next->next->pageNumber);
    
    cout << "\nFault: " << fault << "\thit: " << hit << endl;
    
    return 0;
}

