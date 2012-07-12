#include<gtest/gtest.h>
#include<algorithm>
#include<vector>

//#include<acml/json.hpp>
//#include<acml/acml.hpp>
//#include<iostream>

//#define private public
//#define protected public
//using namespace std;
//#include"../../sbl/debug.hpp"
#include"../../sbl/structure/vector_tree.hpp"

namespace vt {
struct Node {
    sbl::VectorTreeNode<Node *> node;
    Node(int s): same(false), value(s),  maxValue(s) {}
    bool same;
    int value, maxValue;
};

struct GetNode {
    sbl::VectorTreeNode<Node *> &
    operator()(Node *a) const {
        return a->node;
    }
};

struct Update {
    void operator()(Node *p, Node *l, Node *r) const {
        if (p->same) {
            p->maxValue = p->value;
        } else {
            if (l and r)
                p->maxValue = std::max(l->maxValue, r->maxValue);
            else if (l)
                p->maxValue = l->maxValue;
            else if (r)
                p->maxValue = r->maxValue;
            else
                p->maxValue = p->value;
            p->maxValue = std::max(p->maxValue, p->value);
        }
    }
};
struct Expand {
    void operator()(Node *p, Node *l, Node *r) const {
        if (p->same) {
            l->value = r->value = p->value;
            l->same = r->same = p->same;
            p->same = false;
        }
    }
};
struct GetMax {
    int *value;
    GetMax(): value(new int) {}
    void operator()(Node *a) {
        *value = a->maxValue;
    }
};
struct SetValue {
    int value;
    SetValue(int _): value(_) {}
    void operator()(Node *a) {
        a->value = value;
        a->maxValue = value;
        a->same = true;
    }
};

}

//ACML_REGISTER_HANDLE(vt::Node *, visitor, value) {
//    if (value) {
//        visitor(value->value, "value");
//        visitor(value->maxValue, "max_value");
//        visitor(value->same ? "True" : "False", "same");
//        visitor(value->node.size, "size");
//        if (value->node.left) {
//            assert(value->node.left->node.parent == value);
//            visitor(value->node.left, "left");
//        }
//        if (value->node.right) {
//            assert(value->node.right->node.parent == value);
//            visitor(value->node.right, "right");
//        }
//    }
//}

//void print(vt::Node *a) {
//    cout << ::acml::json::dumps(a) << endl;
//}

TEST(structure, vector_tree) {
    using namespace vt;
    sbl::VectorTree<Node *, GetNode, Expand, Update> t;
    static_cast<void>(t);

    Node x[] = {1, 5, 2, 8, 6, 3, 7};
    static_cast<void>(x);

    t.insert(0, x, x + 7);
    GetMax getMax;
    t.call_segment(0, 7, getMax);
    EXPECT_EQ(*(getMax.value), 8);
    t.call_segment(4, 7, getMax);
    EXPECT_EQ(*getMax.value, 7);
    t.call_segment(0, 3, getMax);
    EXPECT_EQ(*getMax.value, 5);
    t.call_segment(1, 3, SetValue(6));
    t.call_segment(0, 3, getMax);
    EXPECT_EQ(*getMax.value, 6);
    t.call_segment(1, 5, SetValue(2));
    t.call_segment(0, 6, getMax);
    EXPECT_EQ(*getMax.value, 3);
};
