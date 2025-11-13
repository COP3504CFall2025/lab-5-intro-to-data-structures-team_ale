#ifdef MAIN

#include "ABS.hpp"
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

    LinkedList<int> LL{};
    LLQ<int> RR{};
    LLS<int> WW{};
    LLDQ<int> OO{};
    ABS<int> EE{};
    ABQ<int> QQ{};
    LL.addHead(3);
    std::cout <<LL.getHead() << std::endl;
    std::cout <<LL.getTail()<<"\n";
    std::cout <<LL.getHead()->prev<<"\n";
    LL.removeHead();
    std::cout << LL.getHead() << std::endl;
    std::cout << LL.getTail() << std::endl;


    LL.printForward();
    // ABS<int> FF{};
    // FF.push(45);
    // FF.push(12);
    // FF.push(3);
    // FF.push(11);
    // FF.push(74);
    // std::cout << FF.pop() << std::endl;
    // FF.pop();
    // FF.printForward();
    // std::cout << "Hello" << " " << LL.getSize() <<'\n';
    // ABS<int> BB{};
    // BB.push(4);
    // BB.push(6);
    // BB.push(3);
    // BB.push(9);
    // BB.push(7);
    // BB = LL;
    // BB.printForward();
    //  std::cout << "This: " << LL.peek() << " " << LL.peek() << " " << '\n';
    // std::cout << "That: " << BB.peek() << " " << LL.peek() << " " <<  '\n';
    // ABS<int> CC = BB;
    // CC.printForward();
    // std::cout << "Hello" <<'\n';
    // ABS<int> DD = std::move(CC);
    // DD.printReverse();


    return 0;
}

#endif