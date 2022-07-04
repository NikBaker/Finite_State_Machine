#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <cstdlib>

#include "FSM.h"

int main()
{
    std::ofstream out_md("TEST.md");

    /*FSM F;
    F.Input();
    std::cout << F;
    FSM F2;
    F2.Input();
    std::cout << F2;
    FSM F3 = F * F2;
    std::cout << F3;*/

    FSM F4({ '0', '1' }, { 1, 2 }, 1, { 2 }, { { 1, 2 }, { 2, 2 } });
    FSM F5({ '0', '1' }, { 1, 2, 3, 4 }, 1, { 3, 4 }, { { 2, 1 }, { 2, 3 }, { 3, 3 }, { 4, 4 } } );

    std::cout << F4;
    std::cout << F5;
    FSM F6 = F4 * F5;
    std::cout << F6;

    F4.FSM_to_SVG("TEST_LEFT.dot"); 
    out_md << "First:  \n";
    out_md << "![](TEST_LEFT.dot.svg)  \n";

    F5.FSM_to_SVG("TEST_RIGHT.dot");
    out_md << "Second:  \n";
    out_md << "![](TEST_RIGHT.dot.svg)  \n";

    F6.FSM_to_SVG("TEST_RESULT.dot");
    out_md << "Intersection:  \n";
    out_md << "![](TEST_RESULT.dot.svg)  \n";

    FSM F7 = F4 + F5;
    F7.FSM_to_SVG("TEST_RESULT_2.dot");
    out_md << "Union:  \n";
    out_md << "![](TEST_RESULT_2.dot.svg)  \n";

    FSM F10 = F4 - F5;
    F10.FSM_to_SVG("TEST_RESULT_3.dot");
    out_md << "Difference:  \n";
    out_md << "![](TEST_RESULT_3.dot.svg)  \n";

    out_md.close();

    return 0;
}

