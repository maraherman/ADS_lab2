#include "RBTree.h"
#include <iostream>
int main() {
    RBTree t;
    std::cout << "Red-Black Tree demo\n";
    std::cout << "Commands:\n"
              << "  1 x  -> insert x\n"
              << "  2 x  -> delete x\n"
              << "  3 x  -> search x\n"
              << "  4    -> minimum\n"
              << "  5    -> maximum\n"
              << "  6    -> maxRed\n"
              << "  7    -> maxBlack\n"
              << "  8    -> print inorder\n"
              << "  0    -> exit\n";
    int cmd;
    while (true) {
        std::cout << "\n> ";
        if (!(std::cin >> cmd)) break;
        if (cmd == 0) break;
        if (cmd == 1) {
            int x; std::cin >> x;
            t.insert(x);
            std::cout << "Inserted.\n";
        } else if (cmd == 2) {
            int x; std::cin >> x;
            bool ok = t.erase(x);
            std::cout << (ok ? "Deleted.\n" : "Not found.\n");
        } else if (cmd == 3) {
            int x; std::cin >> x;
            std::cout << (t.search(x) ? "Found.\n" : "Not found.\n");
        } else if (cmd == 4) {
            auto m = t.minimum();
            if (m) std::cout << "Min = " << *m << "\n";
            else std::cout << "Tree empty.\n";
        } else if (cmd == 5) {
            auto m = t.maximum();
            if (m) std::cout << "Max = " << *m << "\n";
            else std::cout << "Tree empty.\n";
        } else if (cmd == 6) {
            auto v = t.maxRed();
            if (v) std::cout << "Max RED key = " << *v << "\n";
            else std::cout << "No red nodes (or tree empty).\n";
        } else if (cmd == 7) {
            auto v = t.maxBlack();
            if (v) std::cout << "Max BLACK key = " << *v << "\n";
            else std::cout << "No black nodes (tree empty?).\n";
        } else if (cmd == 8) {
            t.inorderPrint();
        } else {
            std::cout << "Unknown command.\n";
        }
    }
    std::cout << "Bye.\n";
    return 0;
}