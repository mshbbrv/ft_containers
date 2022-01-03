#include <iostream>
#include "Map.hpp"

int main() {

    // empty map container
    ft::map<int, int> gquiz1;

    // insert elements in random order
    gquiz1.insert(ft::pair<int, int>(1, 40));
    gquiz1.insert(ft::pair<int, int>(2, 30));
    gquiz1.insert(ft::pair<int, int>(3, 60));
    gquiz1.insert(ft::pair<int, int>(4, 20));
    gquiz1.insert(ft::pair<int, int>(5, 50));
    gquiz1.insert(ft::pair<int, int>(6, 50));
    gquiz1.insert(ft::pair<int, int>(7, 10));

    // printing map gquiz1
    ft::map<int, int>::iterator itr;
    std::cout << "\nThe map gquiz1 is : \n";
    std::cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz1.begin(); itr != gquiz1.end(); ++itr) {
        std::cout << '\t' << itr->first
             << '\t' << itr->second << '\n';
    }
    std::cout << std::endl;


    // assigning the elements from gquiz1 to gquiz2
    ft::map<int, int> gquiz2(gquiz1.begin(), gquiz1.end());

    // print all elements of the map gquiz2
    std::cout << "\nThe map gquiz2 after"
         << " assign from gquiz1 is : \n";
    std::cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) {
        std::cout << '\t' << itr->first
             << '\t' << itr->second << '\n';
    }
    std::cout << std::endl;

    // remove all elements up to
    // element with key=3 in gquiz2
    std::cout << "\ngquiz2 after removal of"
            " elements less than key=3 : \n";
    std::cout << "\tKEY\tELEMENT\n";
    gquiz2.erase(gquiz2.begin(), gquiz2.find(3));

    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) {
        std::cout << '\t' << itr->first
             << '\t' << itr->second << '\n';
    }


      // remove all elements with key = 4
      int num;
      num = gquiz2.erase(4);
      std::cout << "\ngquiz2.erase(4) : ";
      std::cout << num << " removed \n";
      std::cout << "\tKEY\tELEMENT\n";
      for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) {
          std::cout << '\t' << itr->first
               << '\t' << itr->second << '\n';
      }

      std::cout << std::endl;

      // lower bound and upper bound for map gquiz1 key = 5
      std::cout << "gquiz1.lower_bound(5) : "
           << "\tKEY = ";
      std::cout << gquiz1.lower_bound(5)->first << '\t';
      std::cout << "\tELEMENT = "
           << gquiz1.lower_bound(5)->second << std::endl;
      std::cout << "gquiz1.upper_bound(5) : "
           << "\tKEY = ";
      std::cout << gquiz1.upper_bound(5)->first << '\t';
      std::cout << "\tELEMENT = "
           << gquiz1.upper_bound(5)->second << std::endl;

    return 0;

}