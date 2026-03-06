README.txt — RBTree console app

Files:
- main.cpp
- RBTree.h
- RBTree.cpp

Possible commands:
1 10   -> insert 10
1 20   -> insert 20
3 10   -> search 10
4      -> show minimum
5      -> show maximum
2 10   -> delete 10
0      -> exit

Example run:
g++ -std=c++17 main.cpp RBTree.cpp -o rbt
./rbt                                    
Red-Black Tree demo
Commands:
  1 x  -> insert x
  2 x  -> delete x
  3 x  -> search x
  4    -> minimum
  5    -> maximum
  6    -> maxRed
  7    -> maxBlack
  8    -> print inorder
  0    -> exit
> 1 10
Inserted.
> 1 5
Inserted.
> 1 15
Inserted.
> 1 1
Inserted.
> 1 6
Inserted.
> 1 12
Inserted.
> 3 6
Found.
> 2 6
Deleted.
> 3 6
Not found.
> 4
Min = 1
> 5
Max = 15
> 6
Max RED key = 12
> 7
Max BLACK key = 15
> 0
Bye.