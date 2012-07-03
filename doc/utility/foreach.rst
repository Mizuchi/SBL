Foreach
###########

What is foreach?
========================

It is an alternative to BOOST_FOREACH and Range-based for-loop in C++11.

Usage
=======

.. c:function:: foreach(value, container)

.. code-block:: cpp

    std::vector<int> a(/* ... */)
    foreach(i, a) {
        do_something();
    }

This code is logically equivalent to the following:

.. code-block:: cpp

    // typeid(a) == typeid(vector<int>)
    for(vector<int>::iterator iter_var = a.begin();
        iter_var != a.end(); iter_var++ ) {
        int i = iter_var;
        do_something();
    }

hello world
--------------

.. code-block:: cpp

    #include <string>
    #include <iostream>
    #include <sbl/utility/foreach.hpp>

    int main() {
        std::string hello( "Hello, world!" );
        foreach(ch, hello) 
            std::cout << ch << "|";
    }

will print ``H|e|l|l|o|,| |w|o|r|l|d|!|``

control the loop body
-----------------------

Like loop in c++, you can use break or continue.

.. code-block:: cpp

    std::deque<int> deque_int( /*...*/ );
    int i = 0;
    foreach(i, deque_int) {
        if (i == 0) return;
        if (i == 1) continue;
        if (i == 2) break;
    }

nested
-------

It can be nested just like for loop.

.. code-block:: cpp

    std::vector<std::vector<int> > matrix;
    foreach(&row, matrix)
        foreach(&i, row)
            ++i;

reference
-------------

You may notice that in the previous example, we used reference for value.

.. code-block:: cpp

    std::vector<int> a(10, 20);
    int j = 0, s2 = 0;
    foreach(i, a) i = j++;
    foreach(i, a) s2 += i;
    // no reference, vector a is not changed.
    assert(s2 == 200);

.. code-block:: cpp

    std::vector<int> a(10, 20);
    int j = 0, s2 = 0;
    foreach(&i, a) i = j++;
    foreach(i, a) s2 += i;
    // with reference, you can modify the container.
    assert(s2 == 45);

In fact, you can not only add reference, but also add const to the value.


Portability
============

Now it works with lvalues and plain rvalues, but not const-qualified rvalues.

