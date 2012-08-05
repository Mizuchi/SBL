#ifndef _sbl_chain2
#define _sbl_chain2
/**
 * @file chain_v2.cpp
 * @brief A vector like container which can be insert and delete element in log time.
 * @author Tianjiao Yin
 * @version 2.0
 * @date 2008-07-17
 */

#include<algorithm>
#include<vector>
namespace sbl {

struct ChainRK {
    typedef unsigned long long qword;
    typedef unsigned long dword;
    static const char l = 2;
    static const dword prime[l];
    static std::vector<dword> base[l];
    dword p[l];
    void update(int s, const ChainRK &p1, const qword x, const ChainRK &p2) {
        for (int i = 0; i < l; i++) {
            if (base[i].size() < s + 1) {
                int j = base[i].size();
                base[i].resize(s + 1);
                for (; j != s + 1; j++)
                    base[i][j] = (qword(base[i][j - 1]) << 32) % prime[i];
            }
            p[i] = (p1.p[i] + base[i][s] * ((x + (qword(p2.p[i]) << 32)) % prime[i])) % prime[i];
        }
    }
    bool operator==(const ChainRK &b) {
        for (int i = 0; i < l; i++)if (p[i] != b.p[i])return 0;
        return 1;
    }
};

//int ten=10;
//const unsigned long ChainRK::prime[l]={429496729*ten+1,429496727*ten+9};
const unsigned long ChainRK::prime[l] = {4294967291LL, 4294967279LL};
std::vector<unsigned long> ChainRK::base[l] = {std::vector<unsigned long>(1, 1), std::vector<unsigned long>(1, 1)};

template<class value_type> class Chain;
template<class value_type> class ChainNode {
        int size;
        ChainNode *left, *right, *father;
        ChainNode(int mode, const value_type &x = value_type());
        void expand();
        void update();
        friend class Chain<value_type>;

        bool make_same, reverse;
        value_type max_sum, max_left_sum, max_right_sum, sum;
        void Reverse();
        void Make_same(value_type &);

        ChainRK h;
    public:
        value_type element;
};
template<class value_type> class Chain {
        typedef ChainNode<value_type> node;
    public:
        struct iterator {
            // TODO improve iterator
            Chain *c;
            node *p;
            iterator() {}
            iterator(Chain *a, node *b): c(a), p(b) {}
            iterator operator+(int k) {
                (*c)[c->size(*this) + k];
                return iterator(c, c->root);
            }
            iterator operator-(int k) {
                (*c)[c->size(*this) - k];
                return iterator(c, c->root);
            }
            bool operator!=(const iterator &b) {
                return c != b.c || p != b.p;
            }
            bool operator==(const iterator &b) {
                return c == b.c && p == b.p;
            }
            value_type &operator*() {
                c->size(*this);
                return p->element;
            }
            void operator+=(int k) {
                (*c)[c->size(*this) + k];
                p = c->root;
            }
            void operator-=(int k) {
                (*c)[c->size(*this) - k];
                p = c->root;
            }
            iterator &operator++() {
                (*c)[c->size(*this) + 1];
                p = c->root;
                return *this;
            }
            iterator &operator--() {
                (*c)[c->size(*this) - 1];
                p = c->root;
                return *this;
            }
        };

        Chain() {
            // XXX I can't figure out a better way to do this.
            static bool b = 1;
            if (b) {
                null_node = new node(0);
                b = 0;
            }
            root = new node(2);
            node *k = new node(2);
            root->right = k;
            k->father = root;
            root->update();
        }

        value_type &operator[](int k);
        template<class T>
        void insert(int k, T l, T r);
        template<class T>
        void insert(iterator &k, T l, T r) {
            insert(size(k), l, r);
        }
        void erase(int k);
        void erase(int l, int r);
        int size() {
            return root->size - 2;
        }
        void replace(int i, int j, value_type &);
        void reverse(int i, int j);
        const value_type &get_sum(int i, int j);
        const value_type &max_sum(int i, int j);
        void swap(Chain &b) {
            node *c = root;
            root = b.root;
            b.root = c;
        }
        iterator begin() {
            (*this)[0];
            return iterator(this, root);
        }
        iterator end() {
            (*this)[size()];
            return iterator(this, root);
        }
        void clear() {
            erase(0, size());
        }
        ~Chain() {
            remove(root);
        }
        Chain &operator=(const Chain &s) {
            if (this != &s) {
                clear();
                insert(0, s.begin(), s.end());
            }
        }
        int compare(int l, int r);

        void erase(const iterator &l, const iterator &r) {
            erase(size(l), size(r));
        }
        void replace(const iterator &i, const iterator &j, value_type &k) {
            replace(size(i), size(j), k);
        }
        void reverse(const iterator &i, const iterator &j) {
            reverse(size(i), size(j));
        }
        const value_type &get_sum(const iterator &i, const iterator &j) {
            return get_sum(size(i), size(j));
        }
        const value_type &max_sum(const iterator &i, const iterator &j) {
            return max_sum(size(i), size(j));
        }
        int compare(const iterator &i, const iterator &j) {
            return compare(size(i), size(j));
        }

        // XXX below should be private.

        static node *null_node;
        node *root;
        void rotate(node *x);
        void splay(node *t);
        void remove(node *&t);
        int size(const iterator &x);
        void segment(int l, int r);
        friend class ChainNode<value_type>;
};

template<class value_type> ChainNode<value_type> *Chain<value_type>::null_node;

template<class value_type> inline int Chain<value_type>::size(const iterator &x) {
    node *p = x.p;
    int k = p->left->size;
    while (p != root)
        if (p->father->right == p) {
            p = p->father;
            k += p->left->size + 1;
        } else p = p->father;
    (*this)[--k];
    return k;
}
template<class value_type> inline value_type &Chain<value_type>::operator[](int k) {
    node *p = root;
    k += 2;
    while (p != null_node) {
        p->expand();
        if (p->left->size + 1 == k) {
            splay(p);
            break;
        } else if (p->left->size >= k)p = p->left;
        else {
            k -= p->left->size + 1;
            p = p->right;
        }
    }
    return p->element;
}
template<class value_type> template<class T> void Chain<value_type>::insert(int k, T l, T r) {
    if (l == r)return;
    node *p = root;
    node *t = new node(1, *l);
    node *q = t;
    T x = l;
    for (++x; x != r; ++x) {
        q->right = new node(1, *x);
        q->right->father = q;
        q = q->right;
    }
    k++;
    while (1) {
        p->expand();
        if (k <= p->left->size) {
            if (p->left == null_node) {
                p->left = t;
                break;
            } else p = p->left;
        } else {
            k -= p->left->size + 1;
            if (p->right == null_node) {
                p->right = t;
                break;
            } else p = p->right;
        }
    }
    t->father = p;
    splay(q);
}
template<class value_type> void Chain<value_type>::erase(int k) {
    (*this)[k];
    root->expand();
    node *k1 = root->left, *k2 = root->right;
    delete root;
    k1->father = null_node;
    for (k1->expand(); k1->right != null_node; k1->expand())
        k1 = k1->right;
    splay(k1);
    k1->right = k2;
    k2->father = k1;
    root->update();
}
template<class value_type> void Chain<value_type>::erase(int l, int r) {
    segment(l, r);
    root->expand();
    root->right->expand();
    remove(root->right->left);
    root->right->update();
    root->update();
}
template<class value_type> inline void Chain<value_type>::rotate(node *x) {
    node *y = x->father;
    if (y->father != null_node)
        if (y->father->left == y)
            y->father->left = x;
        else
            y->father->right = x;
    x->father = y->father;
    if (y->left == x) {
        y->left = x->right;
        x->right = y->left->father = y;
    } else {
        y->right = x->left;
        x->left = y->right->father = y;
    }
    y->father = x;
    y->update();
    x->update();
}
template<class value_type> inline void Chain<value_type>::splay(node *t) {
    while (t->father != null_node) {
        node *y = t->father;
        if (y->father == null_node)
            rotate(t);
        else if (y->father->left == y && y->left == t || y->father->right == y && y->right == t) {
            rotate(y);
            rotate(t);
        } else {
            rotate(t);
            rotate(t);
        }
    }
    root = t;
}
template<class value_type> inline void Chain<value_type>::segment(int l, int r) {
    (*this)[l - 1];
    root->expand();
    node *t = root;
    node *k = t->right;
    k->father = null_node;
    (*this)[r];
    k = root;
    root = t;
    root->right = k;
    k->father = root;
    root->update();
}
template<class value_type> inline void Chain<value_type>::remove(node *&t) {
    t->father = null_node;
    node *p = t, *q;
    while (p != null_node)
        if (p->left != null_node)p = p->left;
        else if (p->right != null_node)p = p->right;
        else {
            q = p;
            p = p->father;
            if (p->left == q)p->left = null_node;
            else p->right = null_node;
            delete q;
        }
    t = null_node;
}

template<class value_type> ChainNode<value_type>::ChainNode(int mode, const value_type &x): element(x) {
    if (mode == 0) {
        father = left = right = this;
        size = 0;

        make_same = reverse = 0;
        sum = max_sum = max_right_sum = max_left_sum = x;

        h.p[0] = h.p[1] = 0;
    }
    if (mode == 1) {
        father = left = right = Chain<value_type>::null_node;
        update();
    }
    if (mode == 2) {
        father = left = right = Chain<value_type>::null_node;
        update();
    }
}

template<class value_type> void ChainNode<value_type>::Make_same(value_type &l) {
    if (this == Chain<value_type>::null_node)return;
    element = l;
    make_same = 1;
    sum = l * size;
    max_sum = max_right_sum = max_left_sum = std::max(sum, l);
}

template<class value_type> void ChainNode<value_type>::Reverse() {
    reverse ^= 1;
    std::swap(max_left_sum, max_right_sum);
}

template<class value_type> inline void ChainNode<value_type>::expand() {

    if (make_same) {
        left->Make_same(element);
        right->Make_same(element);
        make_same = reverse = 0;
    }
    if (reverse) {
        std::swap(left, right);
        left->Reverse();
        right->Reverse();
        reverse = 0;
    }

}
template<class value_type> inline void ChainNode<value_type>::update() {
    // XXX I know it looks like a shit and indeed it is.
    size = left->size + right->size + 1;
    h.update(left->size, left->h, element, right->h);

    sum = left->sum + element + right->sum;
    make_same = reverse = 0;
    max_sum = max_left_sum = max_right_sum = element;

    if (left != Chain<value_type>::null_node) {
        if (max_sum < left->max_sum)
            max_sum = left->max_sum;
        if (max_sum < left->max_right_sum + element)
            max_sum = left->max_right_sum + element;
    }
    if (right != Chain<value_type>::null_node) {
        if (max_sum < right->max_sum)
            max_sum = right->max_sum;
        if (max_sum < element + right->max_left_sum)
            max_sum = element + right->max_left_sum;
    }
    if (left != Chain<value_type>::null_node && right != Chain<value_type>::null_node)
        if (max_sum < left->max_right_sum + element + right->max_left_sum)
            max_sum = left->max_right_sum + element + right->max_left_sum;
    if (left != Chain<value_type>::null_node) {
        max_left_sum = left->max_left_sum;
        if (max_left_sum < left->sum + element)
            max_left_sum = left->sum + element;
        if (right != Chain<value_type>::null_node)
            if (max_left_sum < left->sum + element + right->max_left_sum)
                max_left_sum = left->sum + element + right->max_left_sum;
    } else if (right != Chain<value_type>::null_node)
        if (max_left_sum < element + right->max_left_sum)
            max_left_sum = element + right->max_left_sum;
    if (right != Chain<value_type>::null_node) {
        max_right_sum = right->max_right_sum;
        if (max_right_sum < element + right->sum)
            max_right_sum = element + right->sum;
        if (left != Chain<value_type>::null_node)
            if (max_right_sum < left->max_right_sum + element + right->sum)
                max_right_sum = left->max_right_sum + element + right->sum;
    } else if (left != Chain<value_type>::null_node)
        if (max_right_sum < left->max_right_sum + element)
            max_right_sum = left->max_right_sum + element;
}

template<class value_type> void Chain<value_type>::replace(int l, int r, value_type &x) {
    segment(l, r);
    root->expand();
    root->right->expand();
    root->right->left->Make_same(x);
    root->right->update();
    root->update();
}
template<class value_type> void Chain<value_type>::reverse(int l, int r) {
    segment(l, r);
    root->expand();
    root->right->expand();
    root->right->left->Reverse();
    root->right->update();
    root->update();
}
template<class value_type> const value_type &Chain<value_type>::get_sum(int l, int r) {
    segment(l, r);
    return root->right->left->sum;
}
template<class value_type> const value_type &Chain<value_type>::max_sum(int l, int r) {
    segment(l, r);
    node *p = root->right->left;
    return p->max_sum;
}

template<class value_type> int Chain<value_type>::compare(int s, int t) { // 正确概率：1-(1-((2^31-1)/2^31)^(Log[size()]))^2
    if (s > t)std::swap(s, t);
    if ((*this)[s] != (*this)[t])return 0;
    int l = 0, r = size() - t + 1, mid;
    ChainRK tmp;
    while (r - l > 1) {
        mid = (l + r) / 2;
        segment(s, s + mid);
        tmp = root->right->left->h;
        segment(t, t + mid);
        if (tmp == root->right->left->h)l = mid;
        else r = mid;
    }
    return l;
}

} // namespace sbl
#endif
