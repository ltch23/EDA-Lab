#include <iostream>
#include "CGraph.h"
#include "CTraits.h"

using namespace std;

int main()
{
    CGraph<Traits_1> cgraph;
    cgraph.insert_node(1);
    cgraph.insert_node(2);
    cgraph.insert_node(3);
    cgraph.insert_node(4);
    cgraph.insert_edge("a",1,2);
    cgraph.insert_edge("b",1,3);
    cgraph.insert_edge("c",1,4);
    cgraph.insert_edge("d",2,3);
    cgraph.insert_edge("e",2,4);
    cgraph.insert_edge("f",3,4);

	cgraph.print();
    return 0;
}

