#ifndef CS540_MAP
#define CS540_MAP

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <memory>

#define COMPACT
#define COLOR_RESET   "\x1b[0m"
#define COLOR_GREEN   COLOR_RESET//"\x1b[32m"
#define COLOR_RED     "\x1b[31m"


using std::string;
namespace cs540
{
    template < typename Key_T, typename Mapped_T> class Map
    { 
        typedef std::pair<Key_T, Mapped_T> ValueType;
        //Forward Decl;
        template <typename ValueType> 
        struct Node;

    public:
            struct Iterator
            {
                Node<ValueType>* data;
                bool end = false;
                Iterator(): data(nullptr){}
                Iterator(Node<ValueType>* _dt): data(_dt){}
                Iterator(Node<ValueType>* _dt, bool e): data(_dt), end(e){}
                Iterator(const Iterator & it)
                {
                    data = it.data;
                    end = it.end;
                }
                ~Iterator()
                {

                }
                Iterator& operator=(const Iterator & it)
                {
                    if(it == *this)
                        return *this;
                    data = it.data;
                    return *this;
                }
                Iterator& operator--()
                {
                    if(end)
                    {
                        end = false;
                        return *this;
                    }
                    if(data != nullptr)
                        data = data->ll_left;
                    return *this;
                }
                Iterator operator--(int )
                {
                    Iterator rt = *this;
                    operator--();
                    return rt;
                }
                //iter++
                Iterator& operator++()
                {
                    if(data != nullptr)
                    {
                        if(data->ll_right == nullptr)
                        {
                            end = true;
                        }
                        else
                        {
                            data = data->ll_right;
                        }
                    }
                    return *this;
                }
                //++iter
                Iterator operator++(int )
                {
                    Iterator rt = *this;
                    operator++();
                    return rt;
                }
                ValueType &operator*() const
                {
                    return *(data->val);
                }
                ValueType *operator->() const
                {
                    return (data->val).get();
                }

                friend bool operator==(cs540::Map<Key_T, Mapped_T>::Iterator&a, cs540::Map<Key_T, Mapped_T>::Iterator & b)
                {
                    if(a.end == b.end)
                        return true;
                    else if(a.end || b.end)
                    {
                        return false;
                    }

                    if(a.data == b.data)
                    {
                        if(a.data == nullptr)
                        {
                            return true;
                        }
                        else
                            return a.data->val == b.data->val;
                    }
                    return false;
                }
                friend bool operator==(const cs540::Map<Key_T, Mapped_T>::Iterator&a, const cs540::Map<Key_T, Mapped_T>::Iterator & b)
                {
                    if(a.end == b.end)
                        return true;
                    else if(a.end || b.end)
                    {
                        return false;
                    }
                    
                    if(a.data == b.data)
                    {
                        if(a.data == nullptr)
                        {
                            return true;
                        }
                        else
                            return a.data->val == b.data->val;
                    }
                    return false;
                }
                friend bool operator==(const cs540::Map<Key_T, Mapped_T>::Iterator&a,  cs540::Map<Key_T, Mapped_T>::Iterator & b)
                {
                    return (a == const_cast<const cs540::Map<Key_T, Mapped_T>::Iterator&>(b));
                }
                friend bool operator==( cs540::Map<Key_T, Mapped_T>::Iterator&a, const cs540::Map<Key_T, Mapped_T>::Iterator & b)
                {
                    return (const_cast<const cs540::Map<Key_T, Mapped_T>::Iterator&>(a) == b);
                }
                
                bool operator!=(const Iterator & b)
                {return !((*this)==b);}

            };
            struct ConstIterator
            {
                Node<ValueType>* data;
                bool end = false;
                ConstIterator(): data(nullptr){}
                ConstIterator(Node<ValueType>* _dt): data(_dt){}
                ConstIterator(Node<ValueType>* _dt, bool e): data(_dt), end(e){}
                ConstIterator(const ConstIterator & it)
                {
                    data = it.data;
                    end = it.end;
                }
                ~ConstIterator()
                {

                }
                ConstIterator& operator=(const ConstIterator & it)
                {
                    if(it == *this)
                        return *this;
                    data = it.data;
                    return *this;
                }
                ConstIterator& operator--()
                {
                    if(end)
                    {
                        end = false;
                        return *this;
                    }
                    if(data != nullptr)
                        data = data->ll_left;
                    return *this;
                }
                ConstIterator operator--(int )
                {
                    ConstIterator rt = *this;
                    operator--();
                    return rt;
                }
                //iter++
                ConstIterator& operator++()
                {
                    if(data != nullptr)
                    {
                        if(data->ll_right == nullptr)
                        {
                            end = true;
                        }
                        else
                        {
                            data = data->ll_right;
                        }
                    }
                    return *this;
                }
                //++iter
                ConstIterator operator++(int )
                {
                    ConstIterator rt = *this;
                    operator++();
                    return rt;
                }
                ValueType &operator*() const
                {
                    return *(data->val);
                }
                ValueType *operator->() const
                {
                    return (data->val).get();
                }

                friend bool operator==(cs540::Map<Key_T, Mapped_T>::ConstIterator&a, cs540::Map<Key_T, Mapped_T>::ConstIterator & b)
                {
                    if(a.end == b.end)
                        return true;
                    else if(a.end || b.end)
                    {
                        return false;
                    }

                    if(a.data == b.data)
                    {
                        if(a.data == nullptr)
                        {
                            return true;
                        }
                        else
                            return a.data->val == b.data->val;
                    }
                    return false;
                }
                friend bool operator==(const cs540::Map<Key_T, Mapped_T>::ConstIterator&a, const cs540::Map<Key_T, Mapped_T>::ConstIterator & b)
                {
                    if(a.end == b.end)
                        return true;
                    else if(a.end || b.end)
                    {
                        return false;
                    }

                    if(a.data == b.data)
                    {
                        if(a.data == nullptr)
                        {
                            return true;
                        }
                        else
                            return a.data->val == b.data->val;
                    }
                    return false;
                }
                friend bool operator==(const cs540::Map<Key_T, Mapped_T>::ConstIterator&a,  cs540::Map<Key_T, Mapped_T>::ConstIterator & b)
                {
                    return (a == const_cast<const cs540::Map<Key_T, Mapped_T>::ConstIterator&>(b));
                }
                friend bool operator==( cs540::Map<Key_T, Mapped_T>::ConstIterator&a, const cs540::Map<Key_T, Mapped_T>::ConstIterator & b)
                {
                    return (const_cast<const cs540::Map<Key_T, Mapped_T>::ConstIterator&>(a) == b);
                }
                
                bool operator!=(const ConstIterator & b)
                {return !((*this)==b);}

            };
            struct ReverseIterator
            {
                Node<ValueType>* data;
                bool end = false;
                ReverseIterator(): data(nullptr){}
                ReverseIterator(Node<ValueType>* _dt): data(_dt){}
                ReverseIterator(Node<ValueType>* _dt, bool e): data(_dt), end(e){}
                ReverseIterator(const ReverseIterator & it)
                {
                    data = it.data;
                    end = it.end;
                }
                ~ReverseIterator()
                {

                }
                ReverseIterator& operator=(const ReverseIterator & it)
                {
                    if(it == *this)
                        return *this;
                    data = it.data;
                    return *this;
                }
                ReverseIterator& operator--()
                {
                    if(end)
                    {
                        end = false;
                        return *this;
                    }
                    if(data != nullptr)
                        data = data->ll_right;
                    return *this;
                }
                ReverseIterator operator--(int )
                {
                    ReverseIterator rt = *this;
                    operator--();
                    return rt;
                }
                //iter++
                ReverseIterator& operator++()
                {
                    if(data != nullptr)
                    {
                        if(data->ll_left == nullptr)
                        {
                            end = true;
                        }
                        else
                        {
                            data = data->ll_left;
                        }
                    }
                    return *this;
                }
                //++iter
                ReverseIterator operator++(int )
                {
                    ReverseIterator rt = *this;
                    operator++();
                    return rt;
                }
                ValueType &operator*() const
                {
                    return *(data->val);
                }
                ValueType *operator->() const
                {
                    return (data->val).get();
                }

                friend bool operator==(cs540::Map<Key_T, Mapped_T>::ReverseIterator&a, cs540::Map<Key_T, Mapped_T>::ReverseIterator & b)
                {
                    if(a.end == b.end)
                        return true;
                    else if(a.end || b.end)
                    {
                        return false;
                    }

                    if(a.data == b.data)
                    {
                        if(a.data == nullptr)
                        {
                            return true;
                        }
                        else
                            return a.data->val == b.data->val;
                    }
                    return false;
                }
                friend bool operator==(const cs540::Map<Key_T, Mapped_T>::ReverseIterator&a, const cs540::Map<Key_T, Mapped_T>::ReverseIterator & b)
                {
                    if(a.end == b.end)
                        return true;
                    else if(a.end || b.end)
                    {
                        return false;
                    }

                    if(a.data == b.data)
                    {
                        if(a.data == nullptr)
                        {
                            return true;
                        }
                        else
                            return a.data->val == b.data->val;
                    }
                    return false;
                }
                friend bool operator==(const cs540::Map<Key_T, Mapped_T>::ReverseIterator&a,  cs540::Map<Key_T, Mapped_T>::ReverseIterator & b)
                {
                    return (a == const_cast<const cs540::Map<Key_T, Mapped_T>::ReverseIterator&>(b));
                }
                friend bool operator==( cs540::Map<Key_T, Mapped_T>::ReverseIterator&a, const cs540::Map<Key_T, Mapped_T>::ReverseIterator & b)
                {
                    return (const_cast<const cs540::Map<Key_T, Mapped_T>::ReverseIterator&>(a) == b);
                }
                
                bool operator!=(const ReverseIterator & b)
                {return !((*this)==b);}

            };
            typedef cs540::Map<Key_T, Mapped_T>::Iterator Iterator;
            typedef cs540::Map<Key_T, Mapped_T>::ConstIterator ConstIterator;
            typedef cs540::Map<Key_T, Mapped_T>::ReverseIterator ReverseIterator;
            typedef std::shared_ptr<ValueType> VTptr;
        private:
            template <typename ValueType> 
            struct Node
            {
                VTptr val;
                Node<ValueType> *left = nullptr, *right = nullptr;
                Node<ValueType> *ll_left = nullptr, *ll_right = nullptr;
                bool parCol = false;     // color of parent link, black=true
                int numChildren = 1; 
                int parDir = 0;

                Node(): val(NULL), left(nullptr), right(nullptr), ll_left(nullptr), ll_right(nullptr), parCol(true), numChildren(0), parDir(0){}
                Node(const ValueType& v, bool col, int nc, int par): 
                left(nullptr), right(nullptr),
                parCol(col), numChildren(nc), parDir(par) 
                {  
                    val = VTptr(new ValueType(v));
                } 
                
                Node(const Key_T& k, const Mapped_T& mt, bool col, int nc, int par): 
                left(nullptr), right(nullptr),
                ll_left(nullptr), ll_right(nullptr),
                parCol(col), numChildren(nc), parDir(par) 
                {
                    val = VTptr(std::make_pair(std::move(k),std::move(mt))); 
                } 
                
                Node(const Node<ValueType>& r)
                {
                    val = r.val;
                    left = r.left;
                    right = r.right;
                    parCol = r.parCol;
                    numChildren = r.numChildren;
                    parDir = r.parDir;
                }
                Node<ValueType>& operator=(const Node<ValueType>& r)
                {
                    val = r.val;
                    left = r.left;
                    right = r.right;
                    parCol = r.parCol;
                    numChildren = r.numChildren;
                    parDir = r.parDir;
                    return *this;
                }
                ~Node()
                {
                    if(right != nullptr)
                        delete right;
                    if(left != nullptr)
                        delete left;
                }

            };

            template <typename ValueType> 
            class LinkedList
            {
                //This is a tree where we only use the right child
                public:
                    Node<ValueType>* _root;
                    Node<ValueType>* _end;
                    int s_ze;
                    LinkedList(): _root(nullptr), _end(nullptr), s_ze(0)
                    {

                    }
                    int size()
                    {
                        return s_ze;
                    }
                    void add(Node<ValueType>* n)
                    {
                        if(_root == nullptr)
                        {
                            _root = n;
                            _end = n;
                        }
                        else
                        {
                            Node<ValueType>* c = _root;
                            while(c)//if we havent hit the end yet
                            {
                                //if we are less than or equal, add us
                                if(n->val->first < c->val->first || n->val->first == c->val->first)
                                {
                                    Node<ValueType>* t = c->ll_left;
                                    if(t == nullptr) //we are first;
                                    {
                                        n->ll_left = nullptr;
                                        n->ll_right = _root;
                                        _root->ll_left = n;
                                        _root = n;
                                    }
                                    else
                                    {
                                        c->ll_left = n;
                                        n->ll_right = c;
                                        n->ll_left = t;
                                        t->ll_right = n;
                                    }
                                    break;
                                }
                                else // if(n->val->first > c->val->first) otherwise continue 
                                {
                                    //if the next node is null, put us in that spot
                                    if(c->ll_right == nullptr)
                                    {
                                        c->ll_right = n;
                                        n->ll_left = c;
                                        _end = n;
                                        break;
                                    }
                                    else
                                    {
                                        c = c->ll_right; 
                                    }
                                }
                            }
                        }
                        s_ze++;
                    }
                    void remove(Node<ValueType>* n)
                    {
                        Node<ValueType>* cur = _root;
                        while(cur != nullptr)
                        {
                            if(cur->val->first == n->val->first)
                            {
                                //time to remove
                                s_ze--;
                                if(!cur->ll_left) //we are root
                                {
                                    _root = cur->ll_right;
                                }
                                else
                                {
                                    Node<ValueType>* l = cur->ll_left;
                                    l->ll_right = cur->ll_right;
                                }
                                break;
                            }
                            cur = cur->ll_right;
                        }
                    }
                    void print()
                    {
                        Node<ValueType>* cur = _root;
                        while(cur != nullptr)
                        {
                            std::cout << cur->val->first << ", ";
                            cur = cur->ll_right;
                        }
                        std::cout <<std::endl;
                    }

            };

            #define IT cs540::Map<Key_T, Mapped_T>::Iterator 
            #define CIT cs540::Map<Key_T, Mapped_T>::ConstIterator 
            #define RIT cs540::Map<Key_T, Mapped_T>::ReverseIterator 

            template <typename ValueType> 
            class RBT
            {
                private:
                    int chil(Node<ValueType>* r)
                    {
                        if(r == nullptr)
                            return 0;
                        return r->numChildren;
                    }

                    bool isblk(Node<ValueType>* r)
                    {
                        if(r == nullptr)
                            return true;
                        return r->parCol;
                    }
                    //to handle checking left child of r
                    bool isblkL(Node<ValueType>* r)
                    {
                        if(r == nullptr)
                            return true;
                        if(r->left == nullptr)
                            return true;
                        return r->left->parCol;
                    }

                    void flipColor(Node<ValueType>* r)
                    {
                        if(r == nullptr)
                            return;
                        else
                            r->parCol = !r->parCol;
                    }

                    Node<ValueType>* rotateRight(Node<ValueType>* r) 
                    {
                        Node<ValueType>* x = r->left;
                        if(x == nullptr)
                        {
                            return r;
                        }
                        r->left = x->right;
                        x->right = r;
                        x->parCol = x->right->parCol;
                        x->right->parCol = false;
                        x->numChildren = r->numChildren;
                        r->numChildren = chil(r->left) + chil(r->right) + 1;
                        return x;
                    }
              
                    Node<ValueType>* rotateLeft(Node<ValueType>* r) 
                    {
                        Node<ValueType>* x = r->right;
                        if(x == nullptr)
                        {
                            return r;
                        }
                        r->right = x->left;
                        x->left = r;
                        x->parCol = x->left->parCol;
                        x->left->parCol = false;
                        x->numChildren = r->numChildren;
                        r->numChildren = chil(r->left) + chil(r->right) + 1;
                        return x;
                    }

                    void flip(Node<ValueType>* r) {
                        flipColor(r);
                        flipColor(r->left);
                        flipColor(r->right);
                    }

                    Node<ValueType>* aux_addNode(Node<ValueType>* r, const ValueType& val, int dir) 
                    {
                        if(r == nullptr)
                        {
                            Node<ValueType>* nnode = new Node<ValueType>(val, false, 1, dir);
                            lldata.add(nnode);
                            return nnode;
                        }
                        const ValueType cval = *(r->val); 

                        if(val.first < cval.first)
                        {
                            Node<ValueType>* next= aux_addNode(r->left, val, -1);
                            r->left = next;
                        }
                        else if(val.first == cval.first)
                        {  //equals
                            r->val = VTptr(new ValueType(std::make_pair(val.first, val.second)));
                        }
                        else
                        { 
                            Node<ValueType>* next= aux_addNode(r->right, val, 1);
                            r->right = next;
                        }
                        
                        if( (!isblk(r->right)) && (isblk(r->left)) )
                        {
                            r = rotateLeft(r);
                        }
                        if( (!isblk(r->left)) && (!isblkL(r->left)) )
                        {
                            r = rotateRight(r);
                        }
                        if( (!isblk(r->left)) && (!isblk(r->right)) )
                        {
                            flip(r);
                        }
                        
                        r->numChildren = chil(r->left) + chil(r->right) + 1;
                        return r;
                    }

                public:

                    LinkedList<ValueType> lldata;
                    Node<ValueType>* root;

                    RBT(): root(nullptr){}
                    RBT(Node<ValueType>* r): root(r){}
                    ~RBT()
                    {
                        if(root != nullptr)
                            delete root;
                        /*int i=0;
                        while(root != nullptr)
                        {
                            std::cout << i++ << ": " << lldata.s_ze << std::endl;
                            removeNode(*(lldata._root->val), true);
                        }
                        */
                    }

                    int size()
                    {
                        return lldata.size();
                    }

                    void addNode(const ValueType& v) 
                    {
                        root = aux_addNode(root, v, 0);
                        root->parCol = true;
                    }

                    Node<ValueType>* rebal(Node<ValueType>* r) 
                    {
                        if(!isblk(r->right))
                        {
                            r = rotateLeft(r);
                        }
                        if( (!isblk(r->left)) && (!isblkL(r->left)) )
                        {
                            r = rotateRight(r);
                        }
                        if( (!isblk(r->left)) && (!isblk(r->right)) )
                        {
                            flip(r);
                        }
                        
                        r->numChildren = chil(r->left) + chil(r->right) + 1;
                        return r;
                    }

                    
                    Node<ValueType>* mrl(Node<ValueType>* r)
                    {
                        flip(r);
                        if (!isblkL(r->right)) 
                        { 
                            r->right = rotateRight(r->right);
                            r = rotateLeft(r);
                            flip(r);
                        }
                        return r;
                    }
                    Node<ValueType>* mrr(Node<ValueType>* r)
                    {
                        flip(r);
                        if (!isblkL(r->left)) 
                        { 
                            r = rotateRight(r);
                            flip(r);
                        }
                        return r;
                    }

                    Node<ValueType>* r_min(Node<ValueType>* r)
                    {
                        if(r->left == nullptr)
                        {
                            return nullptr;
                        }
                        if(isblk(r->left) && isblkL(r->left))
                        {
                            r = mrl(r);
                        }
                        r->left = r_min(r->left);
                        return rebal(r);
                    }

                    Node<ValueType>* g_min(Node<ValueType>* r)
                    {
                        if(r->left == nullptr)
                            return r;
                        return r_min(r->left);
                    }

                    Node<ValueType>* aux_remove(Node<ValueType>* r, ValueType v, Node<ValueType>* par=nullptr)
                    {
                        //std::cout << "AUX rem" << std::endl;
                        if(r != nullptr)
                        {
                            if(r->val->first < v.first)
                            {
                                //l subtree
                                r->left = aux_remove(r->left, v, r);
                            }
                            else if(r->val->first > v.first)
                            {
                                //r subtree
                                r->right = aux_remove(r->right, v, r);
                            }
                            else
                            {
                                //we found it
                                if(r->left == nullptr && r->right == nullptr)
                                {
                                    //both children are null
                                    delete r;
                                    return nullptr;
                                }
                                else if(r->left != nullptr && r->right != nullptr)
                                {
                                    //both children are not null
                                    //find largest of left subtree
                                    Node<ValueType>* largest = r->left;
                                    while(largest->right != nullptr)
                                    {
                                        largest = largest->right;
                                    }
                                    //attach right subtree to it;
                                    largest->right = r->right;
                                    delete r;
                                    return largest;
                                }
                                else if(r->right != nullptr)
                                { 
                                    //only right is not null
                                    Node<ValueType>* tmp = r->right;
                                    delete r;
                                    return tmp;
                                }
                                else
                                {
                                    //left is not null
                                    Node<ValueType>* tmp = r->left;
                                    delete r;
                                    return tmp;   
                                }
                            }
                            
                        return rebal(r);
                        }
                        /*
                            //if val to remove is on left of cur root
                            if (v.first < r->val->first) 
                            {
                                //check black and rotatr
                                if (isblk(r->left) && isblkL(r->left))
                                {
                                    r = mrl(r);
                                }
                                //set left to ret of (delete in subtree)
                                r->left = aux_remove(r->left, v);
                            }
                            //if val is on right
                            else {
                                //handle rotate
                                if (!isblk(r->left))
                                {
                                    r = rotateRight(r);
                                }
                                //if we found our node and the right subtree is null
                                if (v.first == r->val->first && r->right == nullptr)
                                {
                                    return nullptr;
                                }
                                //handle rotates
                                if (isblk(r->right) && isblkL(r->right))
                                {
                                    r = mrr(r);
                                }
                                //if we found our node
                                if (v.first == r->val->first)
                                {
                                    //find smalles thing in right subtree
                                    Node<ValueType>* tmp = g_min(r->right);
                                    r->val = tmp->val;
                                    r->right = r_min(t2->right);
                                }
                                else
                                {
                                    r->right = aux_remove(r->right, v);
                                }
                            }
                        */
                        return nullptr;
                    }

                    void removeNode(const ValueType v, bool cleanup = false)
                    {
                        if(cleanup)
                        {
                            Node<ValueType>* cur = find_node(v.first);
                            if(cur == nullptr) return;
                            root = aux_remove(root, v);
                            return;
                        }
                        //std::cout << "REMOVE NODE" << std::endl;
                        Node<ValueType>* cur = find_node(v.first);
                        //std::cout << "NODE FOUND" << std::endl;
                        if(cur == nullptr)
                        {
                        //    std::cout << "NULL REMOVE NODE" << std::endl;
                            return;
                        }
                        //std::cout << "LinkedList rem" << std::endl;
                        lldata.remove(cur);
                        //std::cout << "LinkedList done rem" << std::endl;

                        if(isblk(root->left) && isblk(root->right))
                        {
                            root->parCol = false;
                        }
                        root = aux_remove(root, v);
                        if (root != nullptr) 
                            root->parCol = true;
                        std::cout << "DONE REMOVE NODE" << std::endl;
                    }

                    void removeNode(const IT iter, bool cleanup = false)
                    {
                        removeNode(*iter, cleanup);
                    }

                    Node<ValueType>* find_node(const Key_T kee) const
                    {
                        //std::cout << "TRYING TO FIND NODE" << std::endl;
                        Node<ValueType>* cur = root;
                        while(cur != nullptr)
                        {
                            if(cur->val->first == kee)
                            {
                            //    std::cout << "FOUND" << std::endl;
                                return cur;
                            }
                            else if(cur->val->first < kee)
                            {
                            //    std::cout << "Move RIGHT" << std::endl;
                                cur = cur->right;
                            }
                            else
                            {
                            //    std::cout << "Move LEFT" << std::endl;
                                cur = cur->left;
                            }
                        }

                        //std::cout << "NOT FOUND" << std::endl;
                        return nullptr;
                    }

                    ValueType& find(const Key_T kee) const
                    {
                        Node<ValueType>* nn = find_node(kee);
                        if(nn == nullptr)
                            throw std::out_of_range("");
                        return *(nn->val);
                    }

                    ValueType& at(size_t ind) const
                    {
                        Node<ValueType>* cur = root;
                        VTptr ret = (root->val);
                        while(cur != nullptr)
                        {
                            ret = cur->val;
                            if(ind < (size_t) cur->numChildren)
                            {
                                cur = cur->left;
                            }
                            else if(ind > (size_t) cur->numChildren)
                            {
                                cur = cur->right;
                            }
                            else
                            {
                                ret = (cur->val);
                                break;
                            }
                            if(cur == nullptr)
                            {
                                break;
                            }
                        }
                        return *ret;
                    }
                    void print_aux(Node<ValueType>* r)
                    {
                        if(r == nullptr)
                        {
                            return;
                        }
                        else
                        {
                            std::cout << r->val->first << ", ";
                            print_aux(r->left);
                            print_aux(r->right);
                        }
                    }
                    void print()
                    {
                        Node<ValueType>* r = root;
                        print_aux(root);
                        std::cout << std::endl;
                    }
            };
            
        public:
            RBT<ValueType> data;

            Map(){}
            Map(const Map & m)
            {
                if(m.data.root != nullptr)
                {
                    for(auto i : m)
                    {
                        this->insert(std::make_pair(i.first, i.second));
                    }
                }
                else 
                {
                    data = RBT<ValueType>(nullptr);
                }
            }
            Map &operator=(const Map & m)
            {
                if(m.data.root != nullptr)
                {
                    for(auto i : m)
                    {
                        this->insert(std::make_pair(i.first, i.second));
                    }
                }
                else 
                {
                    data = RBT<ValueType>(nullptr);
                }
                return *this;
            }
            Map(std::initializer_list<ValueType> lis)
            {
                std::cout << lis.size() << std::endl;
                for(auto iter = lis.begin(); iter != lis.end(); iter++)
                {
                    data.addNode(*iter);
                }
            }
            ~Map(){}

            size_t size() const
            {
                if(empty())
                    return 0;
                else
                    return data.root->numChildren+1;
            }
            bool empty() const
            {
                return data.root == nullptr;
            }

            IT begin()
            {
                return IT(data.lldata._root);
            }
            IT end()
            {
                return IT(data.lldata._end, true);
            }

            CIT begin() const{return CIT(data.root);}
            CIT end() const{return CIT(data.lldata._end, true);}
            
            RIT rbegin()
            {return RIT(data.lldata._end);}

            RIT rend(){return RIT(data.root, true);}
            
            //TODO
            IT find(const Key_T &){return IT();}
            CIT find(const Key_T &) const{return CIT();}

            const Mapped_T& at(const Key_T & kee) const
            {
                ValueType r = data.find(kee);
                return data.find(kee).second;
            }

            const ValueType &index(size_t ind) const
            {
                return (data.at(ind));
            }

            Mapped_T& operator[](const Key_T & kee)
            {
                try{
                    ValueType& v = data.find(kee);
                    return v.second;
                }catch(const std::out_of_range& e)
                {
                    ValueType vi = std::make_pair(kee, Mapped_T());
                    data.addNode(vi);
                    ValueType& v = data.find(kee);
                    return v.second;
                }
            } 

            std::pair<IT, bool> 
            insert(std::pair<Key_T, Mapped_T> const& lis)
            {
                bool inserted = false;
                try{
                    data.addNode(std::make_pair(lis.first, lis.second));
                    inserted = true;
                }
                catch(const std::runtime_error e)
                {
                }
                std::pair<IT, bool> ret = std::make_pair(find(lis.first), inserted);
                return ret;
            }

            std::pair<IT, bool> 
            insert(std::initializer_list<Key_T> const& lis)
            {
                if(lis.size() != 2)
                {
                    //throw err
                }
                return insert(std::make_pair(*(lis.begin()),Mapped_T()));
            }

            void erase(IT pos)
            {
                std::cout << "it erase" << std::endl;
                data.removeNode(pos);
                std::cout << "done it erase" << std::endl;
            }
            void erase(const Key_T & kee)
            {
                std::cout << "erase" << std::endl;
                data.removeNode(std::make_pair(kee, Mapped_T()));
                std::cout << "done erase" << std::endl;
            }

            void print()
            {
                std::cout << "START" << std::endl;
                data.print();
                std::cout << "END" <<std::endl;
            }

            void clear()
            {
                while(data.size() != 0)
                {
                    erase(begin());
                }
            }      
    };

    template < typename Key_T, typename Mapped_T>  
    bool static operator==(const Map< Key_T, Mapped_T>  & a, const Map< Key_T, Mapped_T>  & b)
    {return false;}
    template < typename Key_T, typename Mapped_T>  
    bool static operator!=(const Map< Key_T, Mapped_T>  & a, const Map< Key_T, Mapped_T>  & b)
    {return false;}
    template < typename Key_T, typename Mapped_T>  
    bool static operator<(const Map< Key_T, Mapped_T>  & a, const Map< Key_T, Mapped_T>  & b)
    {return false;}

    

}

#endif
