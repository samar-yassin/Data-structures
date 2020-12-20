#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct node{
    int data;
    node **forward;
    node(int data , int level){
        this->data=data;
        forward = new node*[level+1];
        int size = sizeof(node*)*(level+1);
        memset(forward,0,size);
    }
};

class skipList{
public :
    node *header;
    int currentLevel;
    int size;
    int maxLevel;
    float P;
    skipList(){
        maxLevel=3;
        header=new node(0,maxLevel);
        P=.5;
        this->currentLevel=0;
        size=0;

    }

    ~skipList(){
        delete header;
    }

    int getRandLevel(){
        float random = (float)rand()/RAND_MAX;
        int level = 0;
        while(random < P && level < maxLevel)
        {
            level++;
            random = (float)rand()/RAND_MAX;
        }
        return level;


    }


    void search(int key){
        node *current =header;


        for(int i=currentLevel ; i >= 0 ; i--){
            while(current->forward[i]!= nullptr && current->forward[i]->data<key)
                current= current->forward[i];
        }


        current = current->forward[0];

        if(current != nullptr && current->data == key)
            cout<<key<<" is in the list"<<endl;

        else cout<<"not founded"<<endl;

    }



    void insert(int key){
        node *current =header;
        node *path[maxLevel+1];

        int size = sizeof(node*)*(maxLevel+1);
        memset(path,0,size);


        for(int i=currentLevel ; i >= 0 ; i--){
            while(current->forward[i]!= nullptr && current->forward[i]->data<key)
                current= current->forward[i];

            path[i]=current;

        }


        current = current->forward[0];

        if(current == nullptr || current->data != key ){
            int randlevel = getRandLevel();

            if(randlevel>currentLevel){
                for(int i = currentLevel+1 ; i<randlevel+1 ; i++)
                    path[i]= header;

                currentLevel=randlevel;
            }

            node* tmp = new node(key,randlevel);


            for(int i=0 ; i <=randlevel ;i++){
                tmp->forward[i]= path[i]->forward[i];
                path[i]->forward[i] = tmp;
            }


            cout<<"inserted : "<<key<<endl;

        }

        this->size+=1;


    }


    void displayList()
    {
        cout << "\n\n";
        node *current = header;
        for(int i=0 ; i<=currentLevel ;i++)
        {
            current = header->forward[i];
            cout<<"Level "<<i<<": ";
            while(current != nullptr)
            {
                cout<<current->data<<" ";
                current = current->forward[i];
            }
            cout<<"\n\n";
        }
    }





};





int main() {



    return 0;
}
