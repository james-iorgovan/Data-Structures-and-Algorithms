#ifndef _BST_H
#define _BST_H
#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class bst{

    //-------------------------------------------------------------------------
    public:
        struct bst_node{
            T val;
            int leftNodes; //number of nodes in left subtree
            int rightNodes; //number of nodes in right subtree
            int counter;  //number of nodes in subtree including the root
            bst_node *left;
            bst_node *right;

            bst_node(const T &_val = T{}, bst_node *l = nullptr, bst_node *r = nullptr, int numberOfLeft = 0, int numberOfRight = 0, int numberOfTotal = 1)
                : val { _val }, left { l }, right {r}, leftNodes{numberOfLeft}, rightNodes{numberOfRight}, counter{numberOfTotal}
            {}
        };

        //-------------------------------------------------------------------------
    public:
        // constructor:  initializes an empty tree
        bst(){
            root = nullptr;
        }


        //-------------------------------------------------------------------------
    private:
        // helper function which recursively deallocates nodes
        //   in a tree.
        static void delete_nodes(bst_node *r){
            if (r==nullptr) return;
            delete_nodes(r->left);
            delete_nodes(r->right);
            delete r;
        }

        //-------------------------------------------------------------------------
    public:
        // destructor
        ~bst(){
            delete_nodes(root);
        }

        //-------------------------------------------------------------------------
        //function: size balancing

        static bst_node * bst_balance(bst_node* r){
            int min, max;
            if(r==nullptr){

            return r;
            }

        //    cout << r->rightNodes;
            vector<T> *vec;
            if(r->leftNodes >= r->rightNodes){
                min = r->rightNodes;
                max = r->leftNodes;
            }else{
                min = r->leftNodes;
                max = r->rightNodes;
            }
            
            if(max>2*min+1){
                vec = new vector<T>();
                _to_vector(*vec, r);
                int size = vec->size();
                delete_nodes(r);
                r = _from_vec(*vec, 0, size-1);
                delete (vec);  //prevent memory leaks
            }
            return r;
        }
        //end bst_balance
        //-------------------------------------------------------------------------
    private:
        /**
         * function:  insert()
         * desc:      recursive helper function inserting x into
         *            binary search tree rooted  at r.
         *
         * returns:   pointer to root of tree after insertion.
         *
         * notes:     if x is already in tree, no modifications are made.
         */
        static bst_node *_insert(bst_node *r, T &x, bool &success){
            if(r == nullptr){
                success = true;
                return new bst_node(x, nullptr, nullptr);
            }
            if(r->val == x){
                success = false;
                return r;
            }
            if(x < r->val){
                r->left = _insert(r->left, x, success);
                if(success){
                    r->leftNodes++;
                    r->counter++;
                }
                bst_balance(r);
               
                return r;

            }else{
                r->right = _insert(r->right, x, success);
                if(success){
                    r->rightNodes++;
                    r->counter++;
                }
                bst_balance(r);
                return r;
            }
        }


        //end insert helper()
        //-------------------------------------------------------------------------
    public:
        /**
         * function:  insert
         * desc:      inserts x into BST given by t.  Note that
         *            a BST stores a SET -- no duplicates.  Thus,
         *            if x is already in t when call made, no
         *            modifications to tree result.
         *
         * note:      helper function does most of the work.
         *
         */
        bool insert(T &x){
            bool success;
            root = _insert(root, x, success);
            return success;
        }

        //end insert()
        //-------------------------------------------------------------------------

    public:
        /**
         * function:  contains()
         * desc:      returns true or false depending on whether x is an
         *            element of BST (calling object)
         *
         */
        bool contains(const T &x){
            bst_node *p = root;

            while(p != nullptr){

                if(p->val == x)
                    return true;
                if(x < p->val){
                    p = p->left;
                }
                else
                    p = p->right;
            }
            return false;
        }


        //end contains()
        //-------------------------------------------------------------------------
    private:
        // returns pointer to node containing
        //   smallest value in tree rooted at r
        static bst_node *_min_node(bst_node *r){
            if (r==nullptr)
                return nullptr; // should never happen!
            while (r->left != nullptr)
                r = r->left;
            return r;
        }

        // returns pointer to node containing
        //   smallest value in tree rooted at r
        static bst_node *_max_node(bst_node *r){
            if (r==nullptr)
                return nullptr; // should never happen!
            while (r->right != nullptr)
                r = r->right;
            return r;
        }

        //end min and max nodes
        //-------------------------------------------------------------------------
        // recursive helper function for node removal
        //   returns root of resulting tree after removal.
        static bst_node *_remove(bst_node *r, T &x, bool &success){
            bst_node *tmp;
            bool sanity;

            if (r==nullptr){
                success = false;
                return nullptr;
            }
            if (r->val == x){
                success = true;

                if (r->left == nullptr){
                    tmp = r->right;
                    delete r;
                    return tmp;
                }
                if (r->right == nullptr){
                    tmp = r->left;
                    delete r;
                    return tmp;
                }
                // if we get here, r has two children
                r->val = _min_node(r->right)->val;
                r->right = _remove(r->right, r->val, sanity);
                if (!sanity)
                    std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
                else{
                    r->rightNodes--;
                    r->counter--;
                } return r;

            }

            if(x < r->val){
                r->left = _remove(r->left, x, success);
                if(success){
                    r->leftNodes--;
                    r->counter--;
                }
            }else{
                r->right = _remove(r->right, x, success);
                if(success){
                    r->rightNodes--;
                    r->counter--;
                }
            }

            return r;
        }

        //end remove helper
        //-------------------------------------------------------------------------
    public:

        bool remove(T &x){
            bool success;
            root = _remove(root, x, success);
            return success;
        }

    private:
        static int _size(bst_node *r){
            if (r == nullptr) return 0;
            return _size(r->left) + _size(r->right) + 1;
        }

    public:
        int size(){
            return _size(root);
        }
        //-------------------------------------------------------------------------
    private:

        static int _height(bst_node *r){
            int l_h, r_h;

            if (r==nullptr)
                return -1;
            l_h = _height(r->left);
            r_h = _height(r->right);
            return 1 + (l_h > r_h ? l_h : r_h);
        }
        //-------------------------------------------------------------------------
    public:

        int height(){
            return _height(root);
        }

        bool min(T &answer) {
            if (root == nullptr){
                return false;
            }
            answer = _min_node(root)->val;
            return true;
        }

        T max(){
            return _max_node(root)->val;
        }
        //------------------------------------------------------------------------
        /******************************************
         *
         * "stubs" for assigned TODO functions below
         *
         ******************************************/

        // TODO
        std::vector<T> *to_vector(){
            vector<T> *vec = new vector<T>();
            _to_vector(*vec, root);
            return vec;
        }

    private:
        static void _to_vector(vector<T> &v, bst_node *node){
            if (node == nullptr)
                return;
       
            _to_vector(v, node->left);
            (v).push_back(node->val);
            _to_vector(v, node->right);
        }
        //end vector + helper
        //-------------------------------------------------------------------------
    public:
        /* TODO
         * Function:  get_ith
         * Description:  determines the ith smallest element in t and
         *    "passes it back" to the caller via the reference parameter x.
         *    i ranges from 1..n where n is the number of elements in the
         *    tree.
         *
         *    If i is outside this range, false is returned.
         *    Otherwise, true is returned (indicating "success").
         *
         * Runtime:  O(h) where h is the tree height
         */
        bool get_ith(int i, T &x){
            return _get_ith(root, i, x);
        }

    private:
        //get_ith helper
        bool _get_ith(bst_node *r, int i, T &x){
            if(r == nullptr)
                return false;

            if((1+(r->leftNodes)+(r->rightNodes)) == 1){
                if( i == 1){
                    x = r->val;
                    return true;
                }
                return false;
            }

            if (r->leftNodes + 1 == i){
                x = r->val;
                return true;
            }else if (r->leftNodes < i){
                _get_ith(r->right, i - (r->leftNodes + 1), x);
            }else{
                _get_ith(r->left, i, x);
            }
        }


        //end get ith + helper
        //-------------------------------------------------------------------------
    public:
        bool get_ith_SLOW(int i, T &x){
            int n = size();
            int sofar = 0;

            if (i < 1 || i > n)
                return false;

            _get_ith_SLOW(root, i, x, sofar);
            return true;
        }

        //end get ith slow
        //-------------------------------------------------------------------------

        /* TODO
         * Function:  num_geq
         * Description:  returns the number of elements in tree which are
         *       greater than or equal to x.
         *
         * Runtime:  O(h) where h is the tree height
         */
        int num_geq(const T &x){
            return _num_geq(root, x);
        }

    private:
        //num_geq recursive helper
        int _num_geq(bst_node *r, const T &x){

            if (r==nullptr) return 0;
            if (r->val >= x)
                return 1 + r->rightNodes + _num_geq(r->left, x);
            else
                return _num_geq(r->right, x);
        }


        //end num_geq + helper
        //-------------------------------------------------------------------------
    public:
        /*
         * function:     num_geq_SLOW
         * description:  same functionality as num_geq but sloooow (linear time)
         *
         */
        int num_geq_SLOW(const T &x){
            return _num_geq_SLOW(root, x);
        }
        //-------------------------------------------------------------------------
        /* TODO
         * Function:  num_leq
         * Description:  returns the number of elements in tree which are less
         *      than or equal to x.
         *
         * Runtime:  O(h) where h is the tree height
         *
         **/
        int num_leq(const T &x){
            return _num_leq(root, x);
        }

    private:
        //num_leq recursive helper
        int _num_leq(bst_node *r, const T &x){
            if(r==nullptr) return 0;
            if(r->val<=x)
                return 1 + r->leftNodes + _num_leq(r->right,x);
            else
                return _num_leq(r->left, x);
        }


        //end num_leq + helper
        //-------------------------------------------------------------------------
    public:
        /*
         * function:     num_leq_SLOW
         * description:  same functionality as num_leq but sloooow (linear time)
         *
         */
        int num_leq_SLOW(const T &x){
            return _num_leq_SLOW(root, x);
        }


        //-------------------------------------------------------------------------
        /* TODO
         * Function:  num_range
         * Description:  returns the number of elements in tree which are
         *       between min and max (inclusive).
         *
         * Runtime:  O(h) where h is the tree height
         *
         **/
        int num_range(const T &min, const T &max){
            if(root == nullptr) return 0;
            int nodesTotal = root->counter;
            int rightNodesTotal = num_geq(min);     //number of right subtree nodes
            int leftNodesTotal = num_leq(max);      //number of left subtree nodes
            return (rightNodesTotal + leftNodesTotal) - nodesTotal; //get root node
        }


        //end num_range
        //-------------------------------------------------------------------------
    public:
        int num_lq(const T &x){
            return _num_lq(root, x);
        }
    private:
        int _num_lq(bst_node *r, const T &x){

            if (r == nullptr) return 0;
            if (r->val < x)
                return 1 + r->leftNodes + _num_lq(r->right, x);
            else
                return _num_lq(r->left, x);
        }


        //end num_lq
        //-------------------------------------------------------------------------
        int num_gq(const T &x){
            return _num_gq(root, x);
        }
        int _num_gq(bst_node *r, const T &x){

            if (r == nullptr) return 0;
            if (r->val > x)
                return 1 + r->rightNodes + _num_gq(r->left, x);
            else
                return _num_gq(r->right, x);
        }


        //end num_gq
        //-------------------------------------------------------------------------
    public:
        /*
         * function:     num_range_SLOW
         * description:  same functionality as num_range but sloooow (linear time)
         *
         */
        int num_range_SLOW(const T &min, const T &max){
            return _num_range_SLOW(root, min, max);
        }

        //-------------------------------------------------------------------------
    private:


        static void _get_ith_SLOW(bst_node *t, int i, T &x, int &sofar){
            if(t == nullptr)
                return;
            _get_ith_SLOW(t->left, i, x, sofar);

            if(sofar == i)
                return;
            sofar++;
            if(sofar == i){
                x = t->val;
                return;
            }
            _get_ith_SLOW(t->right, i, x, sofar);
        }


        //end get ith slow helper
        //-------------------------------------------------------------------------
        static int _num_geq_SLOW(bst_node *t, const T &x){
            int total;

            if (t==nullptr) return 0;
            total = _num_geq_SLOW(t->left, x) + _num_geq_SLOW(t->right, x);

            if (t->val >= x)
                total++;
            return total;
        }

        //end num geq slow helper
        //-------------------------------------------------------------------------
        static int _num_leq_SLOW(bst_node *t, const T &x){
            int total;

            if (t==nullptr) return 0;
            total = _num_leq_SLOW(t->left, x) + _num_leq_SLOW(t->right, x);

            if (t->val <= x)
                total++;
            return total;
        }


        //end num leq slow helper
        //-------------------------------------------------------------------------
        static int _num_range_SLOW(bst_node *r, const T &min, const T &max){
            int total;

            if(r == nullptr) return 0;
            total = _num_range_SLOW(r->left, min, max) +
                _num_range_SLOW(r->right, min, max);

            if (r->val >= min && r->val <= max)
                total++;
            return total;
        }


        //end num range slow helper
        //-------------------------------------------------------------------------
    private:
        static void indent(int m){
            int i;
            for (i = 0; i < m; i++)
                std::cout << "-";
        }

        static void _inorder(bst_node *r)
        {
            if (r == nullptr)
                return;
            _inorder(r->left);
            std::cout << "[ " << r->val << " ]\n";
            _inorder(r->right);
        }

        static void _preorder(bst_node *r, int margin){
            if (r == nullptr){
                indent(margin);
                std::cout << " nullptr \n";
            }else{
                indent(margin);
                std::cout << "[ " << r->val << " ]\n";
                _preorder(r->left, margin + 3);
                _preorder(r->right, margin + 3);
            }
        }


        //end inorder, and preorder helper
        //-------------------------------------------------------------------------
        /*
         * TODO:
         * Complete the (recursive) helper function for the post-order traversal.
         * Remember: the indentation needs to be proportional to the height of the node!
         */
        static void _postorder(bst_node *r, int margin){
            if (r == nullptr){
                indent(margin);
                std::cout << " nullptr \n";
            }else{
                indent(margin);
                _postorder(r->left, margin + 3);
                _postorder(r->right, margin + 3);
                std::cout << "[ " << r->val << " ]\n";
            }
        }

    public:
        void inorder(){
            std::cout << "\n======== BEGIN INORDER ============\n";
            _inorder(root);
            std::cout << "\n========  END INORDER  ============\n";
        }

        void preorder(){
            std::cout << "\n======== BEGIN PREORDER ============\n";
            _preorder(root, 0);
            std::cout << "\n========  END PREORDER  ============\n";
        }

        void postorder(){
            std::cout << "\n======== BEGIN POSTORDER ============\n";
            _postorder(root, 0);
            std::cout << "\n========  END POSTORDER  ============\n";
        }


        //-------------------------------------------------------------------------

        // private:
        /*
         * Recursive  helper function _from_vec, used by
         * bst_from_sorted_arr(...). The function must return a sub-tree that is
         * perfectly balanced, given a sorted array of elements a.
         */
        static bst_node *_from_vec(const std::vector<T> &a, int low, int hi){
            int m;
            bst_node *root;

            if (hi < low) return nullptr;
            m = (low+hi)/2;
            root = new bst_node(a[m]);
            root->left  = _from_vec(a, low, m -1);
            root->right = _from_vec(a, m+1, hi);
            return root;
        }


        //-------------------------------------------------------------------------
    public:
        static bst *from_sorted_vec(const std::vector<T> &a, int n){

            bst *t = new bst();
            t->root = _from_vec(a, 0, n - 1);
            return t;
        }

        // TODO:  num_leaves
        //   Hint:  feel free to write a helper function!!
        int num_leaves(){
            return _num_leaves(root);
        }


        //-------------------------------------------------------------------------
        //num_leaves recursive helper
    private:
        int _num_leaves(bst_node *r){
            if (r == nullptr)
                return 0;
            if (r->left == nullptr && r->right == nullptr)
                return 1;
            return _num_leaves(r->left) + _num_leaves(r->right);
        }


        //-------------------------------------------------------------------------
    public:
        // TODO:  num_at_level
        // description:  returns the number of nodes at specified level
        //   in tree.
        // note:  the root is at level 0.
        // Hint:  recursive helper function?
        int num_at_level(int level){
            return _num_at_levels(root, level);
        }


        //-------------------------------------------------------------------------
    private:
        int _num_at_levels(bst_node *r, int level){
            if (r == nullptr)
                return 0;
            if (level == 0)
                return 1;
            return _num_at_levels(r->left, level - 1) + _num_at_levels(r->right, level - 1);
        }

        //-------------------------------------------------------------------------
    private:
        bst_node *root;


}; // end class bst

#endif
