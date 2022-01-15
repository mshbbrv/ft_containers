#if 0//CREATE A REAL STL EXAMPLE
#include <map>
namespace ft = std;
#else
#include "map.hpp"
#endif

#include <iostream>

int main() {

    std::cout << "--------CONSTR TEST---------\n";
    {
        ft::map<int, int> m;

        m.insert(ft::pair<int, int>(1, 40));
        m.insert(ft::pair<int, int>(2, 30));
        m.insert(ft::pair<int, int>(3, 60));
        m.insert(ft::pair<int, int>(4, 20));
        m.insert(ft::pair<int, int>(5, 50));
        m.insert(ft::pair<int, int>(6, 50));
        m.insert(ft::pair<int, int>(7, 10));

        ft::map<int, int>::iterator itr;

        std::cout << "\nThe map m is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m.begin(); itr != m.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;


        ft::map<int, int> m2(m.begin(), m.end());

        std::cout << "\nThe map m2 is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m2.begin(); itr != m2.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;

        ft::map<int, int> m3(m2);

        std::cout << "\nThe map m3 is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m3.begin(); itr != m3.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;

        ft::map<int, int> m4 = m3;

        std::cout << "\nThe map m4 is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m4.begin(); itr != m4.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;

    }

    std::cout << "\n--------CAPACITY TEST---------";
    {
        ft::map<int, int> m;

        m.insert(ft::pair<int, int>(1, 40));
        m.insert(ft::pair<int, int>(2, 30));
        m.insert(ft::pair<int, int>(3, 60));
        m.insert(ft::pair<int, int>(4, 20));
        m.insert(ft::pair<int, int>(5, 50));
        m.insert(ft::pair<int, int>(6, 50));
        m.insert(ft::pair<int, int>(7, 10));

        std::cout << "\nSize : " << m.size();
        std::cout << "\nMax_Size : " << m.max_size();

        if ( m.empty() == false )
            std::cout << "\nVector is not empty";
        else
            std::cout << "\nVector is empty";
    }

    std::cout << "\n--------ELEMENT ACCESS TEST---------";
    {
        ft::map<int, int> m;

        m.insert(ft::pair<int, int>(1, 40));
        m.insert(ft::pair<int, int>(2, 30));
        m.insert(ft::pair<int, int>(3, 60));
        m.insert(ft::pair<int, int>(4, 20));
        m.insert(ft::pair<int, int>(5, 50));
        m.insert(ft::pair<int, int>(6, 50));
        m.insert(ft::pair<int, int>(7, 10));

        std::cout << "\nReference operator [m] : m[2] = " << m[2];
    }

    std::cout << "\n--------MODIFIERS TEST---------";
    {
        ft::map<int, int> m;

        m.insert(ft::pair<int, int>(1, 40));
        m.insert(ft::pair<int, int>(2, 30));
        m.insert(ft::pair<int, int>(3, 60));
        m.insert(ft::pair<int, int>(4, 20));
        m.insert(ft::pair<int, int>(5, 50));
        m.insert(ft::pair<int, int>(6, 50));
        m.insert(ft::pair<int, int>(7, 10));

        m.insert(m.begin(), ft::pair<int, int>(10, 10));

        ft::map<int, int>::iterator itr;
        std::cout << "\nThe map m is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m.begin(); itr != m.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;

        ft::map<int, int> m2;
        m2.insert(m.begin(), m.end());

        std::cout << "\nThe map m2 is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m2.begin(); itr != m2.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;

        m.erase(m.begin());

        std::cout << "\nThe map m is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m.begin(); itr != m.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;

        m.erase(m.begin(), m.end());

        std::cout << "\nThe map m is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m.begin(); itr != m.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;

        m2.erase(10);

        std::cout << "\nThe map m2 is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m2.begin(); itr != m2.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;

        m2.clear();
        std::cout << "\nThe map m2 is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m2.begin(); itr != m2.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;
        std::cout << "\nm2 after clear(): " << m2.size();

        ft::map<int, int> m3, m4;
        m3.insert(ft::pair<int, int>(1, 10));
        m3.insert(ft::pair<int, int>(2, 20));
        m4.insert(ft::pair<int, int>(3, 30));
        m4.insert(ft::pair<int, int>(4, 40));

        std::cout << "\nThe map m3 is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m3.begin(); itr != m3.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;

        std::cout << "\nThe map m4 is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m4.begin(); itr != m4.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;

        // Swaps v1 and v2
        m3.swap(m4);

        std::cout << "\nThe map m3 is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m3.begin(); itr != m3.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;

        std::cout << "\nThe map m4 is : \n";
        std::cout << "\tKEY\tELEMENT\n";
        for (itr = m4.begin(); itr != m4.end(); ++itr) {
            std::cout << '\t' << itr->first
                      << '\t' << itr->second << '\n';
        }
        std::cout << std::endl;
    }

    std::cout << "\n--------OPERATIONS TEST---------";
    {

        ft::map<int, int> m;

        m.insert(ft::pair<int, int>(1, 40));
        m.insert(ft::pair<int, int>(2, 30));
        m.insert(ft::pair<int, int>(3, 60));
        m.insert(ft::pair<int, int>(4, 20));
        m.insert(ft::pair<int, int>(5, 50));
        m.insert(ft::pair<int, int>(6, 50));
        m.insert(ft::pair<int, int>(7, 10));

        std::cout << "\nFind key = 3 : \n";
        std::cout << "\tKEY\tELEMENT\n";
        std::cout << '\t' << m.find(3)->first
                  << '\t' << m.find(3)->second << '\n';
        std::cout << std::endl;

        std::cout << "\nCount elements with key = 3 : \n";
        std::cout << '\t' << m.count(3);
        std::cout << std::endl;
        std::cout << "\nCount elements with key = 10 : \n";
        std::cout << '\t' << m.count(10);
        std::cout << std::endl;

        ft::map<int,int>::iterator itlow,itup;

        itlow = m.lower_bound(2);
        std::cout << "\nLower bound at key = 2 : \n";
        std::cout << "\tKEY\tELEMENT\n";
        std::cout << '\t' << itlow->first
                  << '\t' << itlow->second << '\n';
        std::cout << std::endl;

        itup = m.upper_bound(6);
        std::cout << "\nUpper bound at key = 6 : \n";
        std::cout << "\tKEY\tELEMENT\n";
        std::cout << '\t' << itup->first
                  << '\t' << itup->second << '\n';
        std::cout << std::endl;

        ft::pair<ft::map<int,int>::iterator,ft::map<int,int>::iterator> ret;
        ret = m.equal_range(3);

        std::cout << "lower bound points to: ";
        std::cout << ret.first->first << " => " << ret.first->second << '\n';

        std::cout << "upper bound points to: ";
        std::cout << ret.second->first << " => " << ret.second->second << '\n';

    }
    return 0;
}