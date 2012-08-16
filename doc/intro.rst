####################
Source Basic Library
####################
:Author: mizuchi <ytj000@gmail.com>

SBL is a general-purpose cross-platform C++ template library which provide many
advanced algorithms and data structures.

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

About Unittest
==============

Unittest require `waf <code.google.com/p/waf/>`_ and `googletest <code.google.com/p/googletest/>`_ .
Contrib is welcome, however you should pass the unit-test first to make sure everything is all right.

License
=======

Copyright (C) 2012, Tianjiao Yin. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
