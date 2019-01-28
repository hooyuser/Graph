# Graph

This program implements many basic and important graph algorithms using C++, where the core content is a variety of search algorithms based on priority. A corresponding test sample is provided.

Architecturally, the top-level design of this program uses the abstract interface to define the relevant interface of the graph, and the specific implementation uses the adjacency matrix. Therefore, depending on the specific situation, this program can be easily rewritten as an implementation of the adjacency list.

In terms of generality, this program is composed entirely of template classes, and can handle a wide variety of graph models in the most general framework.

In terms of efficiency, this program tries to use the algorithm with the least time complexity and uses the stack to simulate recursion when necessary, thus reducing the time overhead of recursive calls and avoiding possible space overflow.

The graph algorithm of this program is based on data structures such as vectors, lists, stacks, queues, trees, etc., and provides a large number of efficient methods related to these data structures, which can be used as a cornerstone for quickly building complex programs.
