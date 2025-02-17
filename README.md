# Introduction:
Mario Kart Sorting algorithm. There is a weekly bracket and we are told to sort a graph of who has beaten who. We can introduce SCC's and Graph theory in order to determine 3 sets. 
- Winners (Set A): Can reach all other players but cannot be reached by anyone outside of A.
- Mid Tier (Set C): Can win and lose, meaning they will have connections to both A and B.
- Losers (Set B) Can only reach others within B, but cannot reach A or C.


## Algorithms:
- I use a modified DFS and a modified Kosaraju's algorithm to sort each node into a Condensed graph which is a graph containing each SCC treated as a node. From here I check which node's have outgoing or incoming edges and can define them from there.

## Problems:
- Right now the input relies on CIN, but we can modify it to read in *CSV's* using `<fstrea>` library if we so please.
- Another would be data that doesn't follow the 3 set groups, It is entirely possible that someone could have an instance where their exists 4 SETS, so it is limited by this.

## Interesting Facts:
- We can build upon this to actually work this into any competition in which 3 sets of people would apply. This could mean golf, chess, Boardgames, anything that follows this 3 set rule.

# Usage:
In order to use follow these steps: 
1. git clone the directory
2. Compile using your choice or use `g++ -std=c++11 -o a.out Assignment1.cpp`
3. run `./a.out` or if on windows use `./a.out.exe`
4. finally input will come from `cin`
5. the first line is two integers, `n` and `m`, separated by a space
6. `n` is the number of *vertices* and `m` is the number of *edges*
7. the next `m` lines will contain two integers `u` and `v` separated by a space
8. each of these pairs will represent a directed edge (u,v)
9. Output will be in format `|A| = A Size,  |B| = B Size, |C| = C size` with no trailing spaces or newlines. 
