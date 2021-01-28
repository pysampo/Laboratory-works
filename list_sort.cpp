#include <iostream>
#include <iostream>
int main()
{
}
#include <vector>

using namespace std;

struct Trailer;
struct Lider {
    int key;
    int count;
    Lider * nx;
    Trailer * tr;
};
struct Trailer {
    Lider * ld;
    Trailer * nx;
};


Lider * source_vertexes(const Lider * & v) {
    Lider * Ldnew = new Lider; //it's point out of graph  
    Ldnew -> nx = nullptr;
    Ldnew -> tr = nullptr;
    Ldnew -> key = -1;
    Ldnew -> count = -1;
    Lider * temp;
    int cvertexes = 0; 
    while (v) {
        if (!v -> count) {
            temp = Ldnew;   //to keep previous vertex
                            //vertex I mean pointer to Lider
            Ldnew = new Lider;
            Ldnew -> key = v -> key;
            Ldnew -> tr = v -> tr; //has the same addresses with v
                                   //there is no need to clear memory for it (I mean for Trailer of Ldnew)
            Ldnew -> count = 0;    
            Ldnew -> nx = temp; //next vertex for Ldnew is temp
        }
        ++cvertexes; //to count vertexes of Graph
        v = v -> nx;
    }
    Ldnew -> count = Ldnew -> count + cvertexes; //keep number of count 
    return Ldnew;
}

std::vector <int> sort(const Lider * v) {
    std::vector <int> (vertexes);
    if(!v) {
        std::cerr << "Graph is Empty" << std::endl;
        return vertexes;
    }
    Lider * Ldnew = source_vertexes(v);
    int cvertexes = Ldnew -> count; 
    Ldnew -> count = 0; // return previous value. (0 bc it's a source vertex)
    Lider * p;
    while (Ldnew -> nx) { //before reaching our point  (vertex out of graph)
        p = Ldnew;
        vertexes.push_back(p -> key); //add this vertex
        Ldnew = Ldnew -> nx;  //Ldnew points to next vertex
        while (p -> tr) { 
            p -> tr -> ld -> count--;
            if (!p -> tr -> ld -> count) { //if it became the source vertex
                Lider * temp = new Lider; //create a new vertex which has same field
                temp -> key = p -> tr -> ld -> key;
                temp -> count = 0;
                temp -> tr = p -> tr -> ld -> tr; //same addresses with p => Ldnew => v
                temp -> nx = Ldnew;
                Ldnew = temp;
            }
            p -> tr = p -> tr -> nx; //running along all arcs of vertex P, while p -> tr is not nullr
        }
        delete p; //delete current vertex
    }
    delete Ldnew; //delete point (vertex out of graph)

    if (vertexes.size() != cvertexes) { //sources vertexes != vertexes of graph
        std::cout << "Loop in Graph." << std::endl;
        vertexes.clear();
        vertexes.push_back(-1);
    }
    return vertexes;
}

void DeleteGraph(Lider * & vertexes) {
    while (vertexes) {
        while (vertexes -> tr) {
            Trailer * temp = vertexes -> tr;
            vertexes -> tr = vertexes -> tr -> nx;
            delete temp;
        }
        Lider * temp = vertexes;
        vertexes = vertexes -> nx;
        delete temp;
    }
}

void AddEdge(Lider * & vertexes, int vertexA, int vertexB) {
    //nearly a similar function that was given at lecture
    Lider * ptrA = nullptr, * ptrB = nullptr;
    for (ptrA = vertexes; ptrA && ptrA -> key != vertexA; ptrA = ptrA -> nx)
    ;
    for (ptrB = vertexes; ptrB && ptrB -> key != vertexB; ptrB = ptrB -> nx)
    ;
    bool setEdge = true;
    if (ptrA && ptrB) {
        if (ptrA == ptrB) { // (2,2), (2,2)
            ptrB -> count++;
            Trailer * elemTr = new Trailer;
            elemTr -> ld = ptrB;
            elemTr -> nx = ptrA -> tr;
            ptrA -> tr = elemTr;
            return;
        }
        Trailer * trTmp = ptrA -> tr;
        while (trTmp && trTmp -> ld != ptrB)
            trTmp = trTmp -> nx; 
        setEdge = !(bool) trTmp; //nullptr if trTmp->ld != ptrB =>  setEdge = true
    } else {
        if (!ptrA && !ptrB && vertexA == vertexB) { //the first generation of two similar vertexes. It's a loop
            ptrA = new Lider;
            ptrA -> key = vertexB;
            ptrA -> count = 1;
            ptrA -> nx = vertexes;
            vertexes = ptrA;
            return;
        }
        if (!ptrA) {
            ptrA = new Lider;
            ptrA -> key = vertexA;
            ptrA -> count = 0;
            ptrA -> tr = nullptr;
            ptrA -> nx = vertexes;
            vertexes = ptrA;
        }
        if (!ptrB) {
            ptrB = new Lider;
            ptrB -> key = vertexB;
            ptrB -> count = 0;
            ptrB -> nx = nullptr;
            ptrB -> nx = vertexes;
            vertexes = ptrB;
        }
    }
    if (setEdge) {
        ptrB -> count++;
        Trailer * elemTr = new Trailer;
        elemTr -> ld = ptrB;
        elemTr -> nx = ptrA -> tr;
        ptrA -> tr = elemTr;
    }
    return;
}

void DisplayGraph(Lider * vertexes) {
    if (!vertexes) {
        std::cout << "Graph is empty" << std::endl;
    } else {
        bool fl = false;
        while (vertexes) {
            Trailer * trTmp = vertexes -> tr;
            while (trTmp) {
                fl = true;
                std::cout << vertexes -> key << " -> " << trTmp -> ld -> key << " & st: " << vertexes -> count << std::endl;
                trTmp = trTmp -> nx;
            }
            vertexes = vertexes -> nx;
        }
        if (!fl)
            std::cout << "Graph without any edges" << std::endl;
    }
}
int main() {
    Lider * gp = nullptr;
    int a, b;/*
    AddEdge(gp, 2,1);
    AddEdge(gp,4,5);
    AddEdge(gp,5,1);
    AddEdge(gp,5,3);
    AddEdge(gp,6,2);
    AddEdge(gp,6,3);
    AddEdge(gp,6,5);
    AddEdge(gp,7,1); */
    while (std::cin>> a >> b) {
        AddEdge(gp, a, b);
    }
    DisplayGraph(gp);
    std::vector < int > vertexes = sort(gp);
    for (unsigned long i = 0; i < vertexes.size(); ++i)
        std::cout << vertexes[i] << " ";
    std::cout << std::endl;
    DisplayGraph(gp);
    DeleteGraph(gp);
    return 0;
}
