#ifdef MAIN

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

    ABS<int> LL{};
    LL.push(3);
    LL.push(4);
    LL.push(2);
    LL.push(4);
    LL.push(7);
    LL.pop();
    LL.pop();
    LL.printForward();
    ABS<int> FF{};
    LL.push(45);
    LL.push(12);
    LL.push(3);
    LL.push(11);
    LL.push(74);
    LL.pop();
    LL.pop();
    LL.printForward();
    std::cout << "Hello" << " " << LL.getSize() <<'\n';
    ABS<int> BB{};
    BB.push(4);
    BB.push(6);
    BB.push(3);
    BB.push(9);
    BB.push(7);
    BB = LL;
    BB.printForward();
    std::cout << "This: " << BB.peek() << " " << LL.peek() << " " << BB.peek() << '\n';
    ABS<int> CC = BB;
    CC.printForward();
    std::cout << "Hello" <<'\n';
    ABS<int> DD = std::move(CC);
    DD.printReverse();


    return 0;
}

#endif