lib_LIBRARIES = libDSA.a
libDSA_a_SOURCES = \
    Algorithms/BitManipulation/BitManipulationAlgo.cpp \
    Algorithms/DynamicProgramming/DynamicProgrammingAlgo.cpp \
    Algorithms/Geometric/GeometricAlgo.cpp \
    Algorithms/Numeric/NumericAlgo.cpp \
    Algorithms/Searching/SearchingAlgo.cpp \
    Algorithms/Sorting/SortingAlgo.cpp \
    DataStructures/Array/Array.cpp \
    DataStructures/DisjointSet/UnionFind.cpp \
    DataStructures/Graph/GraphTraversal.cpp \
    DataStructures/Graph/MinSpanningTree.cpp \
    DataStructures/Graph/ShortestPath.cpp \
    DataStructures/HashTable/HashTable.cpp \
    DataStructures/Heap/Heap.cpp \
    DataStructures/LinkedList/DoubleLinkedList.cpp \
    DataStructures/LinkedList/SingleLinkedList.cpp \
    DataStructures/Queue/Queue.cpp \
    DataStructures/Stack/Stack.cpp \
    DataStructures/String/String.cpp \
    DataStructures/Tree/BinaryIndexedTree.cpp \
    DataStructures/Tree/BinarySearchTree.cpp \
    DataStructures/Tree/Trie.cpp

libDSA_a_CXXFLAGS = -I$(top_srcdir)/Algorithms \
                    -I$(top_srcdir)/DataStructures \
                    -Wall
libDSA_a_LDFLAGS = 

libDSA_a_includedir = $(includedir)/DSA
libDSA_a_include_HEADERS = \
    $(top_srcdir)/Algorithms/*/*.h \
    $(top_srcdir)/DataStructures/*/*.h

lib_LTLIBRARIES = libDSA.la
libDSA_la_SOURCES = $(libDSA_a_SOURCES)
libDSA_la_CPPFLAGS = $(libDSA_a_CPPFLAGS)
libDSA_la_LDFLAGS = $(libDSA_a_LDFLAGS)

ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = subdir-objects
