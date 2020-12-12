# WEEK 1:

For week 1, we focused on planning and assigning roles. We split up the main part of the project into roles, specifically:

1. Creating the Graph implementation and related functions, as well as read in the dataset to the Graph
2. The Graph traversal, specifically BFS for us
3. Algorithm 1, specifically the Floyd-Warshall shortest path
4. Algorithm 2, specifically the iterative-deepening DFS algorithm (original plan was Google Page Rank)

We also decided that updating Development.md, creating documentation, the final video, and developing tests would be shared responsibilities that everyone would contribute to. We decided that all 4 of the major parts above should be mostly functional (excluding edge cases) by the mid-project check in, to allow for time for bux fixing, thorough testing, and creating the presentation.


# WEEK 2:

The first implementation was the Graph. We chose a custom implementation instead of the one provided for lab_ml because we wanted to use an Adjacency Matrix for fast lookup and to be able to more easily perform Google Page Rank, which uses a Markov matrix built off the Adjacency Matrix. We made a simple FileReader class to read from a text file. The Graph implementation can currently read from a FileReader, build the object, and has several helper functions and appropriate getters and setters. It also has an alternate constructor which allows for easier testing, without needing a new text file. Over the next few days we implemented the iterative-deepening DFS. This method should combine DFS's space efficiency with BFS's speed. This method has space complexity O(bd) and time complexity O(b^d), where b is the Breadth and d is the depth of the graph.

# WEEK 3:

The Graph class received some small modifications, including a few extra helper functions to help with some of the other algorithms. We also began developing our tests, and testing the Graph functionality found a few small bugs which were easily remedied. The BFS and DFS algorithms were fully implemented and tested, along with the Floyd-Warshall shortest (and longest) path algorithm which was also tested. We also developed a simple text-based UI for the project, so that the user can 'explore' the different algorithms, the corresponding results, and time complexities. We then developed and implemented our plan for the presentation video.
