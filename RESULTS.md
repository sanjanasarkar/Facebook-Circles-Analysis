# Whew! It's been an intense few weeks. Here's what we did:
1. Graph Creation
2. Traversals
3. Floyd-Warshall Shortest Path Algorithm

## Conclusions

### Traversals

#### IDDFS vs DFS vs BFS
This algorithm has the same asymptotic time complexity as BFS and DFS; however, it has higher constant factors so in practice it is slower than both. While implementing it, we had expected IDDFS to be a lot faster than it was; we thought that since the graph is relatively well-connected with a low maximum depth of 8, it would be faster than BFS. However, we discovered that DFS was far and away the fastest at usually less than 100 microseconds for the full dataset. It was followed by BFS, and then IDDFS could take almost a minute. In some cases IDDFS was actually faster than BFS. This seemed to happen when there was a shorter path between nodes. We figured that BFS and IDDFS should have similar time complexities with smaller connections (which we found to generally be true). However bigger datasets and more complex connections add up in calculating the time complexity which causes it to be longer. We realized that IDDFS is more useful for a tree, because having cycles in the graph slows it down considerably. This could easily be solved with a visited array, but then this would take more memory, at which point IDDFS loses it advantage. The main advantage of IDDFS over BFS and DFS is that it has much lower space complexity, and unlike DFS it will work better on 'infinite' datasets.

### Floyd-Warshall Shortest Path Algorithm

#### The Time Complexity

Floyd-Warshall is a powerful algorithm, but in the process of completing our project we found that it is also one of the slowest. Floyd-Warshall has a runtime complexity of O(n^3). With the Facebook dataset's 4093 nodes it would take approximately 18 million hours (760,000 days) to run. Hmm...
#### The Power of This Algorithm
When we applied Floyd-Warshall to smaller subsets of data, it worked like a charm. On these smaller datasets, it can quickly determine the shortest and longest paths within the smaller graphs.

## More Additions
### Better UI
If given more time, we would try to develop a graphical representation of the data using Graphviz, Cinder, or another GUI library to better demonstrate the connectivity and algorithms running on the visual depiction.
### Compatability with more Datasets
We could make it compatible with more, similar datasets (Twitter, Instagram, Reddit, etc) in order to perform similar analyses and even comparisons between social networks.
