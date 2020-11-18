# Team Goals

## dataset: Social Circles - Facebook 
## http://snap.stanford.edu/data/ego-Facebook.html

This dataset contains friends lists of people on Facebook. This will let us see who are friends with who and their “social circles”. Each node represents a profile, the connections make circles (friend lists), and all can be combined into ego networks. These all can be easily represented with graphs. This dataset is really interesting because we have the ability to analyze the network built between people and even some dynamics between them.

### Planned Implementation:

We plan to use an undirected graph, using an adjacency matrix. Since we will not be adding or removing nodes frequently, the slower running time of these operations will be irrelevant. We will need fast lookups, especially since the shortest-path algorithm is O(n3). The Google Page Rank algorithm also needs the Markov matrix, which can easily be obtained from the adjacency matrix.

### Traversal: BFS - Breadth First Traversal

We chose the BFS traversal because it would allow us to easily display friends in terms of how “closely” people are connected. The earlier they appear in the traversal, the closer they are to you. This way, you can see the layers of your friend circle as they expand outward, going from close friends and family to people you only know by association.

### Algorithm #1: Shortest Path: Floyd-Warshall Algorithm

This algorithm will be used to find the shortest path and degrees of separation between any two people in the graph/social network. It is O(n3), but because we are planning on using an adjacency matrix, we have fast lookups.

### Algorithm #2 (Complex): Google Page Rank Algorithm

This will be used to determine which Facebook pages a user is most likely to end up on if they randomly click on pages. The purpose of doing this is to understand how popular different pages are. The page rank algorithm will return a probability distribution which details which pages a user is more likely to end up on. Pages with higher probabilities are considered to be more popular.

Signed, Pranav Goel, Shiven Kumar, Ben Xie, Sanjana Sarkar

