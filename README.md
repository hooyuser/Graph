# Graph

This program implements many basic and important graph algorithms using C++, where the core content is a variety of search algorithms based on priority. A corresponding test sample is provided.

In terms of architecture, the top-level design of this program uses the abstract classes to define the relevant interfaces of the graph, and the specific implementation employs the adjacency matrix. Therefore, depending on the specific situation, this program can be easily reconstructed as an implementation of the adjacency list.

In terms of generality, this program is composed entirely of template classes, capable of handling a wide variety of graph models in the most general framework.

In terms of efficiency, this program makes efforts to deduce the time complexity and introduces the stack to simulate recursion when necessary, thus reducing the time overhead of recursive calls and avoiding possible stack overflow.

The graph algorithm of this program is based on data structures such as vectors, lists, stacks, queues, trees, etc., and provides a large number of efficient methods related to them, which can be used as a cornerstone for building complex programs quickly.
