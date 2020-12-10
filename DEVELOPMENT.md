# WEEK 1:

For week 1, we focused on planning and assigning roles. We split up the main part of the project into roles, specifically:

1. Creating the Graph implementation and related functions, as well as read in the dataset to the Graph
2. The Graph traversal, specifically BFS for us
3. Algorithm 1, specifically the Floyd-Warshall shortest path
4. Algorithm 2, specifically the Google Page Rank algorithm

We also decided that updating Development.md, creating documentation, the final video, and developing tests would be shared responsibilities that everyone would contribute to. We decided that all 4 of the major parts above should be mostly functional (excluding edge cases) by the mid-project check in, to allow for time for bux fixing, thorough testing, and creating the presentation.


# WEEK 2:

The first implementation was the Graph. We chose a custom implementation instead of the one provided for lab_ml because we wanted to use an Adjacency Matrix for fast lookup and to be able to more easily perform Google Page Rank, which uses a Markov matrix built off the Adjacency Matrix. We made a simple FileReader class to read from a text file. The Graph implementation can currently read from a FileReader, build the object, and has several helper functions and appropriate getters and setters. It also has an alternate constructor which allows for easier testing, without needing a new text file. 
