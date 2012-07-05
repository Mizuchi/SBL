####################
Source Basic Library
####################
:Author: Tianjiao Yin <ytj000@gmail.com>

Copyright (C) 2012, Tianjiao Yin. All Rights Reserved.

SBL is a C++ template library which provide many advanced algorithms and data
structures. You can find  an incomplete list below.

This library is designed for teaching purposes. To reach this goal, here is
some principles of design:

* Keep it simple and stupid
* Short and clear (No unnecessary error handling)
* Hard to misuse
* Header-file only
* no external dependencies (only uses standard C++ libraries)
* C++03 with a small subset of GCC's extensions (long long, typeof, etc.)
* C++11 Compatible.

This project is still unstable and under heavy development. 
It is not tested widely. Use At Your Own Risk.

Algorithms
===========

* Z algorithm
* Merge sorting for counting inversion
* djb2 hash function

* Polya-Burnside Method
* Formulas in Combinatorial Mathematics
* Chinese remainder theorem
* Miller–Rabin primality test
* Finding Privitive roots
* Baby-step giant-step (Discrete logarithm)
* Pollard's rho algorithm (integer factorization)
* Euclidean algorithm (greatest common divisor)

* Longest Common Prefix
* Longest Common Substring

Data Structure
===============

* Unlimited precision integer (Java's BigInteger equivalent)
* Suffix Array
* Fenwick Tree
* Leftist Tree 
* Treap
* Splay Tree
* Disjoint-set
* Trie

Graph
======

* Prim
* Dijkstra

* Hopcroft-Karp
* Hungarian
* Prüfer coding
* Tarjan's off-line Least Common Ancestors
* On-line Least Common Ancestors
* Topological sort

* Dinic
* Edmonds-Karp
* Push-relabel

* Edmonds
* Kruskal
* Floyd-Warshall
* Johnson

* Tarjan (Strongly Connected Components)

Geometry
========

* Closest pair
* Graham Scan (Convex hull)
* Gilbert–Johnson–Keerthi distance
* Point in polygon
* Delaunay triangulation
* Voronoi diagrams
* Line segment intersection


Utility
=========

* foreach (inspired by BOOST_FOREACH)
* lexical_cast (inspired by boost::lexical_cast)
* copy_if (inspired by C++11)
* filter (inspired by Haskell's filter)
* Time (inspired by boost::progress_timer)
* Pretty Printer for STL container 
