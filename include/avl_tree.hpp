#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <algorithm>
#include <cstddef>

// TODO map 本体ではほとんどavl_treeの関数を借用する感じ
// とりあえずmapで必要な関数を書き下す

namespace ft
{
    class node
    {
    public:
        unsigned int height;
        int          key;
        int          value;
        node*        lst;
        node*        rst;

        node();
    };

    class avl_tree
    {
    private:
        avl_tree* root;
        bool      should_change;
        int       lmax;
        int       value;

    public:
        int bias(node* t) { return height(t->lst) - height(t->rst); }
        int height(node* t) {
            if (t == NULL) {
                return 0;
            } else {
                t->height;
            }
        }
        void modHeight(node* t) {
            t->height = 1 + std::max(height(t->lst), height(t->rst));
        }
        node* rotateL(node* v) {
            node* u  = v->rst;
            node* t2 = u->lst;
            u->lst   = v;
            v->rst   = t2;
            modHeight(u->lst);
            modHeight(u);
            return u;
        }
        node* rotateR(node* u) {
            node* v  = u->lst;
            node* t2 = v->rst;
            v->rst   = u;
            u->lst   = t2;
            modHeight(v->rst);
            modHeight(v);
            return v;
        }
        node* rotateLR(node* t) {
            t->lst = rotateL(t->lst);
            return rotateR(t);
        }
        node* rotateRL(node* t) {
            t->rst = rotateR(t->rst);
            return rotateL(t);
        }

        node* balanceLi(node* t) { return balanceL(t); }

        node* balanceL()
    };
} // namespace ft

#endif
