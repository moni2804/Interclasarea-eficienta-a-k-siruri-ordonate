/*
 * Complexitatea algoritmului este de O(n * lg k)
 * Algoritmul setecteaza elementul minim dintre primele elemente ale celor k liste ordonate crescator
 *
 * Complexitatea heap-ului (make_heap): O(k)
 * Complexitatea merge: O(n * lg k)
 *
 * Algoritmul necesita spatiu suplimentar de memorie
 * Algoritmul nu este stabil
*/

#include <iostream>
#include "Profiler.h"
#include <queue>
#include <vector>
#include <cstdlib>
using namespace std;
Profiler profiler;

#define STEP_SIZE 100
#define MAX_SIZE 10000

//lista trebuie sa aiba n/k elemente
queue <int> sol;

struct node{
    int key;
    node *next;
};

struct list{
    node *first;
    node *last;
};

list *create_list(){
    list *my_list=new list;
    if(my_list == NULL){
        return NULL;
    }
    my_list->first=NULL;
    my_list->last=NULL;
    return my_list;
}

void print_list(const list *my_list){
    if(my_list==NULL){
        cout<<"NULL";
        return;
    }
    node *current=my_list->first;
    while (current!=NULL){
        cout<<current->key<<" ";
        current=current->next;
    }
    cout<<endl;
}

node* create_node(int key){
    node *new_node=new node; //l-am instantat
    new_node->key=key;
    new_node->next=NULL;
    return new_node;
}

void adaugare_nod(list *my_list,int key){
    node *new_node= create_node(key);
    if(my_list->first == NULL){
        my_list->first=new_node;
        my_list->last=new_node;
    } else{
        my_list->last->next=new_node;
        my_list->last=new_node;
    }
}

void sink(node *h[],int index,int k,Operation &comp,Operation &atr){   //k-heap_size

    while(2*index <= k){
        comp.count();
        int minim = 2*index; //minim ii un index,nu o valoare
        atr.count();
        comp.count();
        if(minim+1 <= k && h[minim]->key > h[minim+1]->key){
            minim++;
        }
        comp.count();
        if(h[minim]->key < h[index]->key){
            swap(h[minim],h[index]);
            atr.count(3);
            index=minim;
        }
        else
            break;
    }
}

void make_heap(node *h[],int k,Operation &comp,Operation &atr){
    for(int i=k/2;i>=1;i--){
        sink(h,i,k,comp,atr);
    }
}

void merge_key_ordered_lists(node *h[],int k,Operation &comp,Operation &atr){
    make_heap(h,k,comp,atr);
    int heap_size=k; //pentru generarea graficelor
    atr.count();
    while(heap_size>0){
        comp.count();
        sol.push(h[1]->key);
        if(h[1]->next!=NULL){
            node *aux=h[1];
            h[1]=h[1]->next;
            atr.count(2);
            free(aux);
        } else{
            free(h[1]);
            h[1]=h[heap_size];
            atr.count();
            heap_size--;
        }
        sink(h,1,heap_size,comp,atr);
    }
}

list* create_list_sorted(int size){
    int a[10000];
    FillRandomArray(a,size,-5000,5000,false,ASCENDING);
    list *my_list=create_list();
    for(int i=0;i<size;i++){
        adaugare_nod(my_list,a[i]);
    }
    return my_list;
}

void average_k(int k) {

    for (int i = STEP_SIZE; i <= MAX_SIZE; i += STEP_SIZE) {

        for (int test = 0; test < 5; test++) {
            Operation comp = profiler.createOperation("average_comp_k", i);
            Operation atr = profiler.createOperation("average_atr_k", i);

            vector<list *> lists;
            int size = i / k;
            for (int j = 0; j < k; j++) {
                lists.push_back(create_list_sorted(size));
            }

            node *h[k + 1];
            for (int j = 1; j <= k; j++) {
                h[j] = lists[j - 1]->first;
            }

            merge_key_ordered_lists(h, k, comp, atr);

            while (!sol.empty()) {
                sol.pop();
            }
        }
    }
    profiler.divideValues("average_comp_k", 5);
    profiler.divideValues("average_atr_k", 5);
    profiler.addSeries("average_k", "average_comp_k", "average_atr_k");


}

void average_n(int n) {
    for (int i = 10; i <= 500; i += 10) {

        for (int test = 0; test < 5; test++) {
            Operation comp = profiler.createOperation("average_comp_n", i);
            Operation atr = profiler.createOperation("average_atr_n", i);

            vector<list *> lists;
            int size = n / i;
            for (int j = 0; j < i; j++) {
                if(j==i-1){
                    lists.push_back(create_list_sorted(size+n%i));
                    break;
                }
                lists.push_back(create_list_sorted(size));
            }

            node *h[i + 1];
            for (int j = 1; j <= i; j++) {
                h[j] = lists[j - 1]->first;
            }

            merge_key_ordered_lists(h, i, comp, atr);

            while (!sol.empty()) {
                sol.pop();
            }
        }
    }
    profiler.divideValues("average_comp_n", 5);
    profiler.divideValues("average_atr_n", 5);
    profiler.addSeries("average_n", "average_comp_n", "average_atr_n");

}
void demo(int n,int k){
    Operation comp=profiler.createOperation("demo_comp",n);
    Operation atr=profiler.createOperation("demo_atr",n);
    vector<list*> lists;
    int size_lists = n/k;

    for(int i=0;i<k;i++){
        if(i==k-1){
            list *my_list=create_list_sorted(size_lists+n%k);
            lists.push_back(my_list);
            break;
        }
        list *my_list=create_list_sorted(size_lists);
        lists.push_back(my_list);
    }


    cout<<"Liste:"<<endl;
    for(int i=0;i<k;i++){
        cout<<"Lista: "<<i+1<<endl;
        print_list(lists[i]);
    }

    //array de pointeri
    node *h[k+1];
    for(int i=1;i<=k;i++){
        h[i]=lists[i-1]->first;
    }

    merge_key_ordered_lists(h,k,comp,atr);

    cout<<"Final: "<<endl;

    while(!sol.empty()){
        cout<<sol.front()<< " ";
        sol.pop();
    }
}

void perf(){
    average_k(5);
    average_k(10);
    average_k(100);

    average_n(10000);

    profiler.showReport();
}

int main() {
    //demo(20,4);
    perf();
    return 0;
}