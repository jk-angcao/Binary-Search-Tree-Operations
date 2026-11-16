# Binary-Search-Tree-Operations
Completed Assignment for CS210-11 Class. This contains an implementation of binary search trees.

## Explanation
The three main functions (search, insert, and remove) all share the same time complexity because they all essentially search the tree in the same way to complete their jobs. Binary trees are assumed to be fairly balanced; as we input more values into the tree, the values should spread fairly evenly. Because of this, we can cut half of the remaining possible nodes with every step in a search, giving it a time complexity of O(log n). In the worst case, the tree can be very skewed. If values are being input in either an increasing or decreasing pattern, the time complexity becomes O(n).
