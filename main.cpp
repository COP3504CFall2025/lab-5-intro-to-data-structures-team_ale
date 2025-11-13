//#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    // int* tmp = new int(7);
    // int*arr = new int(8);
    // arr[0] = *(tmp);
    // std::cout << *tmp << " " << *arr << '\n';
    // delete tmp;

    ABDQ<int> LL{};
    LL.pushBack(3);
    LL.pushFront(4);
    LL.pushFront(2);
    LL.pushBack(4);
    LL.pushBack(5);
    LL.pushBack(7);
    LL.popBack();
    LL.popFront();
    LL.popFront();

    LL.printForward();
    ABDQ<int> FF{};
    FF.pushFront(45);
    FF.pushFront(12);
    FF.pushBack(3);
    FF.pushBack(11);
    FF.pushBack(74);
    FF.popFront();
    FF.popBack();
    FF.printForward();
    std::cout << "Hello" << " " << LL.getSize() <<'\n';
    ABDQ<int> BB{};
    BB.pushFront(4);
    BB.pushFront(6);
    BB.pushFront(3);
    BB.pushFront(9);
    BB.pushFront(7);
    BB = LL;
    BB.printForward();
     std::cout << "This: " << LL.front() << " " << LL.back() << " " << '\n';
    std::cout << "This: " << BB.front() << " " << LL.back() << " " <<  '\n';
    ABDQ<int> CC = BB;
    CC.printForward();
    std::cout << "Hello" <<'\n';
    ABDQ<int> DD = std::move(CC);
    DD.printReverse();


    return 0;
}

//#endif