/**
 * @file Demo.cpp
 * @author shaked levi
 * @brief this is the main demonstartion for the presentation i will give
 * @version 0.1
 * @date 2022-05-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "iostream"
#include "OrgChart.hpp"

using namespace ariel;
using namespace std;

int main()
{

    OrgChart demo_chart;

    /*simple root creation*/
    string root;
    cout << "Insert the root of the chart:"
         << "\n";
    cin >> root;
    demo_chart.add_root(root);

    string choice;
    string sub;

    while (true)
    {

        cout << "A. To add subs to the tree enter: addsub"
             << "\n";
        cout << "B. To apply a certain order insert: \n "
             << "1. level order \n 2. reverse order \n 3. preorder"
             << "\n";
        cout << "C. at anytime you wish to end program and display the chart insert Exit"
             << "\n";
        cin >> choice;
        if (choice == "addsub")
        {
            cout << "Enter the root of the sub: "
                 << "\n";
            cin >> root;
            cout << "Enter the sub of the root: "
                 << "\n";
            cin >> sub;
            demo_chart.add_sub(root, sub);
        }
        else if (choice == "1")
        {
            /*level order*/
            for (auto it = demo_chart.begin_level_order(); it != demo_chart.end_level_order(); ++it)
            {
                cout << (*it) << " ";
            }
            cout << "\n";
        }
        else if (choice == "2")
        {
            /*reverse order*/
            for (auto it = demo_chart.begin_reverse_order(); it != demo_chart.reverse_order(); ++it)
            {
                cout << (*it) << " ";
            }
            cout << "\n";
        }
        else if (choice == "3")
        {
            /*preorder*/
            for (auto it = demo_chart.begin_preorder(); it != demo_chart.end_preorder(); ++it)
            {
                cout << (*it) << " ";
            }
            cout << "\n";
        }
        else if (choice == "Exit")
        {
            cout << "Exit program"
                 << "\n";
            break;
        }
        else
        {
            cout << "Bad choice enter again..."
                 << "\n";
        }
    }
    cout << "printing chart in someway... : "
         << "\n";
    cout << demo_chart << "\n";
    cout << endl;
}