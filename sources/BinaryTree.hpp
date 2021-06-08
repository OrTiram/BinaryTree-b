#pragma once
#include <iostream>
#include <stack>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>

namespace ariel{
template<typename T>
    class BinaryTree{
      private:   
            struct TreeNode
            {
                    T data;
                    TreeNode *left;
                    TreeNode *right;
                    TreeNode *parent;

                    TreeNode(const T &val): data(val),left(nullptr), right(nullptr), parent(nullptr) {}
                    
            };
      public:
       class iteratorPreOrder

            {
                private:

                   TreeNode* point_to_current_node;

                public:
                    iteratorPreOrder(TreeNode* ptr = nullptr): point_to_current_node(ptr){}

                    T& operator*() const
                    {
                        return point_to_current_node->data;
                    }

                    T* operator->() const 
                    {
                        return &(point_to_current_node->data);
                    }
            iteratorPreOrder &operator++() {
                if (point_to_current_node == nullptr) { 
                    throw std::invalid_argument("Cant increment end of iter");
                }
                if (point_to_current_node->left != nullptr) { //  left child
                    point_to_current_node = point_to_current_node->left;
                    return *this;
                }
                if (point_to_current_node->right != nullptr) { // right child
                    point_to_current_node = point_to_current_node->right;
                    return *this;
                }
                if (point_to_current_node->parent != nullptr && point_to_current_node->parent->right != nullptr &&
                    point_to_current_node->parent->left ==
                    point_to_current_node) { 
                    point_to_current_node = point_to_current_node->parent->right;
                    return *this;
                }
                if (point_to_current_node->parent != nullptr) { 
                    while (point_to_current_node == point_to_current_node->parent->right && point_to_current_node ==
                                                                                point_to_current_node->parent->right) {
                        point_to_current_node = point_to_current_node->parent;
                        if (point_to_current_node->parent == nullptr) {
                            point_to_current_node = nullptr;
                            return *this;
                        }
                    }
                    if (point_to_current_node->parent->right != nullptr) { 
                        point_to_current_node = point_to_current_node->parent->right;
                        return *this;
                    }
                }
                if (point_to_current_node->parent != nullptr && point_to_current_node->parent->left == point_to_current_node) {
                    while (point_to_current_node->parent->right == nullptr || point_to_current_node->parent->right == point_to_current_node) { 
                        point_to_current_node = point_to_current_node->parent;
                        if (point_to_current_node->parent == nullptr) {
                            point_to_current_node = nullptr;
                            return *this;
                        }
                    }
                    point_to_current_node = point_to_current_node->parent->right;
                    return *this;
                }
                point_to_current_node = nullptr;
                return *this;
            }

            iteratorPreOrder operator++(int) {
                iteratorPreOrder tmp = *this;
                if (point_to_current_node == nullptr) { 
                    return tmp;
                }
                if (point_to_current_node->left != nullptr) { //  left child
                    point_to_current_node = point_to_current_node->left;
                    return tmp;
                }
                if (point_to_current_node->right != nullptr) { // right child
                    point_to_current_node = point_to_current_node->right;
                    return tmp;
                }
                if (point_to_current_node->parent != nullptr && point_to_current_node->parent->right != nullptr &&
                    point_to_current_node->parent->left ==
                    point_to_current_node) { 
                    point_to_current_node = point_to_current_node->parent->right;
                    return tmp;
                }
                if (point_to_current_node->parent != nullptr && point_to_current_node ==
                                                          point_to_current_node->parent->right) { 
                    while (point_to_current_node == point_to_current_node->parent->right) {
                        point_to_current_node = point_to_current_node->parent;
                        if (point_to_current_node->parent == nullptr) {
                            point_to_current_node = nullptr;
                            return tmp;
                        }
                    }
                    if (point_to_current_node->parent->right != nullptr) { 
                        point_to_current_node = point_to_current_node->parent->right;
                        return tmp;
                    }
                }
                if (point_to_current_node->parent != nullptr) {
                    while (point_to_current_node->parent->right ==
                           nullptr) { 
                        point_to_current_node = point_to_current_node->parent;
                        if (point_to_current_node->parent == nullptr) {
                            point_to_current_node = nullptr;
                            return tmp;
                        }
                    }
                    point_to_current_node = point_to_current_node->parent->right;
                    return tmp;
                }
                point_to_current_node = nullptr;
                return tmp;
            }

                    bool operator==(const iteratorPreOrder& other) const 
                    {
                        return point_to_current_node == other.point_to_current_node;
                    }

                    bool operator!=(const iteratorPreOrder& other) const 
                    {
                        return point_to_current_node != other.point_to_current_node;
                    }
      
           };//End class iteratorPreOrder
       class iteratorInOrder
            {
                private:

                   TreeNode* point_to_current_node;

                public:
                    iteratorInOrder(TreeNode* ptr = nullptr) :point_to_current_node(ptr){}

                    T& operator*() const
                    {
                        return point_to_current_node->data;
                    }

                    T* operator->() const 
                    {
                        return &(point_to_current_node->data);
                    }


            iteratorInOrder &operator++() {
                TreeNode *p = nullptr;
                if (point_to_current_node == nullptr) {
                    throw std::invalid_argument("Cant increment end of iter");
                }
                if (point_to_current_node->right != nullptr) {
                    point_to_current_node = point_to_current_node->right;
                    while (point_to_current_node->left != nullptr) {
                        point_to_current_node = point_to_current_node->left;
                    }
                } else {
                    p = point_to_current_node->parent;
                    while (p != nullptr && point_to_current_node == p->right) {
                        point_to_current_node = p;
                        p = p->parent;
                    }
                    point_to_current_node = p;
                }
                return *this;
            }


            iteratorInOrder operator++(int) {
                iteratorInOrder temp = *this;
                TreeNode *p = nullptr;
                if (point_to_current_node == nullptr) {
                    return temp;
                }
                if (point_to_current_node->right != nullptr) {
                    point_to_current_node = point_to_current_node->right;
                    while (point_to_current_node->left != nullptr) {
                        point_to_current_node = point_to_current_node->left;
                    }
                } else {
                    p = point_to_current_node->parent;
                    while (p != nullptr && point_to_current_node == p->right) {
                        point_to_current_node = p;
                        p = p->parent;
                    }
                    point_to_current_node = p;
                }
                return temp;
            }

                    bool operator==(const iteratorInOrder& other) const 
                    {
                        return point_to_current_node == other.point_to_current_node;
                    }
                    bool operator!=(const iteratorInOrder& other) const 
                    {
                        return point_to_current_node != other.point_to_current_node;
                    }

           };//End class iteratorInOrder
       class iteratorPostOrder
            {
                private:

                   TreeNode* point_to_current_node;

                public:
                    iteratorPostOrder(TreeNode* ptr = nullptr): point_to_current_node(ptr){} 

                    T& operator*() const
                    {
                        return point_to_current_node->data;
                    }

                    T* operator->() const 
                    {
                        return &(point_to_current_node->data);
                    }


            iteratorPostOrder &operator++() {
                if (point_to_current_node == nullptr) {
                    throw std::invalid_argument("Cant increment end of iter");
                }
                if (point_to_current_node->parent == nullptr) {
                    point_to_current_node = nullptr;
                    return *this;
                }
                if (point_to_current_node->parent->right == point_to_current_node) { // right child
                    point_to_current_node = point_to_current_node->parent;
                    return *this;
                }   // left child
                if (point_to_current_node->parent->right != nullptr) {
                    point_to_current_node = point_to_current_node->parent->right;
                    while (point_to_current_node->left != nullptr || point_to_current_node->right != nullptr) {
                        if (point_to_current_node->left != nullptr) {
                            point_to_current_node = point_to_current_node->left;
                        } else if (point_to_current_node->right != nullptr) {
                            point_to_current_node = point_to_current_node->right;
                        }
                    }
                    return *this;
                }
                point_to_current_node = point_to_current_node->parent;
                return *this;
            }


            iteratorPostOrder operator++(int) {
                iteratorPostOrder temp = *this;
                if (point_to_current_node == nullptr) {
                    return temp;
                }
                if (point_to_current_node->parent == nullptr) {
                    point_to_current_node = nullptr;
                    return temp;
                }
                if (point_to_current_node->parent->right == point_to_current_node) { // right child
                    point_to_current_node = point_to_current_node->parent;
                    return temp;
                }   // left child
                if (point_to_current_node->parent->right != nullptr) {
                    point_to_current_node = point_to_current_node->parent->right;
                    while (point_to_current_node->left != nullptr || point_to_current_node->right != nullptr) {
                        if (point_to_current_node->left != nullptr) {
                            point_to_current_node = point_to_current_node->left;
                        } else if (point_to_current_node->right != nullptr) {
                            point_to_current_node = point_to_current_node->right;
                        }
                    }
                    return temp;
                }
                point_to_current_node = point_to_current_node->parent;
                return temp;
            }

                    bool operator==(const iteratorPostOrder& other) const 
                    {
                        return point_to_current_node == other.point_to_current_node;
                    }

                    bool operator!=(const iteratorPostOrder& other) const 
                    {
                        return point_to_current_node != other.point_to_current_node;
                    }
      
           };//End class iteratorPostOrder

       
    private:
        void destroy(TreeNode* node){
            if(node != nullptr){
                destroy(node->left);
                destroy(node->right);
                delete node;
            }
        }

        TreeNode *isInTree(TreeNode *node ,const T& data) {
            if (node != nullptr) {
                if (node->data == data) {
                    return node;
                }
                TreeNode *ans = isInTree(node->left,data);
                if (ans == nullptr) {
                    ans = isInTree(node->right,data);
                }

                return ans;

            }
            return nullptr;
        }

        void insertNodes(TreeNode *thisTree, TreeNode *newTree) {
            if (newTree->left != nullptr) {
                add_left(thisTree->data, newTree->left->data);
                insertNodes(thisTree->left, newTree->left);
            }
            if (newTree->right != nullptr) {
                add_right(thisTree->data, newTree->right->data);
                insertNodes(thisTree->right, newTree->right);
            }
        }
        
        TreeNode *root ;
   public:
        BinaryTree<T>(): root(nullptr){}

        BinaryTree(BinaryTree const &tree) : root(nullptr){
            add_root(tree.root->data);
            insertNodes(this->root, tree.root);
        }
        //move
        BinaryTree(BinaryTree &&other) noexcept {
            this->root = other.root;
            other.root = nullptr;
        }

        ~BinaryTree(){ destroy(this->root);}

        BinaryTree<T> &operator=(const BinaryTree<T> &tree) {
   
            if (this != &tree) {
                add_root(tree.root->data);
                insertNodes(this->root, tree.root);
                return *this;
            }

            return *this;
        }
        //move
        BinaryTree &operator=(BinaryTree &&treeOther) noexcept {

            this->root = treeOther.root;
            treeOther.root = nullptr;
            return *this;
        }
        
        BinaryTree& add_root(const T &rootIn){
            if (this->root == nullptr )
            {
            TreeNode *newNode = new TreeNode{rootIn};
            root = newNode;
            return *this;        
            }

            root->data = rootIn;
            return *this;
            }

        BinaryTree& add_left(const T& rootIn,const T& leftIn)
        {
            TreeNode *help = isInTree(this->root,rootIn);
            
                if(help == nullptr){throw std::invalid_argument{"This node is not in the tree"};}
                  
                  if(help->left != nullptr) 
                  {  
                     help->left->data = leftIn;
                     return *this;
                  }

            TreeNode *tmpNode = new TreeNode{leftIn};
            tmpNode->parent = help;
            help->left = tmpNode;
            return *this;    
            
        }

        BinaryTree& add_right(const T& rootIn,const T& rightIn)
        {
            TreeNode *help = isInTree(root,rootIn);
            
                if(help == nullptr){throw std::invalid_argument{"This node is not in the tree"};}
                  
                  if(help->right != nullptr) 
                  {  
                     help->right->data = rightIn;
                     return *this;
                  }

            TreeNode *tmpNode = new TreeNode{rightIn};
            tmpNode->parent = help;
            help->right = tmpNode;

            return *this;  
        }
        
            iteratorPreOrder begin_preorder()
            {
                if (root == nullptr) {
                    return iteratorPreOrder(nullptr);
                }
                
                return iteratorPreOrder(this->root);                        
            }

            iteratorPreOrder end_preorder(){return iteratorPreOrder(nullptr);}

            iteratorPostOrder begin_postorder()
                {
                if (root == nullptr)
                {
                    return iteratorPostOrder(nullptr);
                }

                TreeNode * tmp = root;
                while (tmp->left != nullptr || tmp->right != nullptr)
                {
                    if (tmp->left != nullptr) {
                        tmp = tmp->left;
                    } 
                    
                    else if (tmp->right != nullptr ) 
                    {
                        tmp = tmp->right;
                    }                        
                }
                
                return iteratorPostOrder(tmp);
                }

            iteratorPostOrder end_postorder()
                {
                    return iteratorPostOrder(nullptr);
                }

            iteratorInOrder begin_inorder()
            {
                if (root == nullptr)
                {
                    return iteratorInOrder(nullptr);
                }

                TreeNode * tmp = root;
                while (tmp->left != nullptr)
                {
                    tmp = tmp->left;
                }
            
                return iteratorInOrder(tmp);
            }

            iteratorInOrder end_inorder()
            {
                return iteratorInOrder(nullptr);
            }

            iteratorInOrder begin() {
            if (root == nullptr) {
                return iteratorInOrder{nullptr};
            }

            TreeNode *tmp = root;
            while (tmp->left != nullptr) {
                tmp = tmp->left;
            }
            return iteratorInOrder(tmp);
            }

            iteratorInOrder end() {
                return iteratorInOrder(nullptr);
            }

            friend std::ostream& operator<<(std::ostream& output,const BinaryTree<T> &tree){return output;}

    };
}





