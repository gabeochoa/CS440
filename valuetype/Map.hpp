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
        typedef std::shared_ptr<ValueType> VTptr;
        
        //Forward Decl;
        template <typename ValueType> 
        struct Node;
        typedef std::shared_ptr<Node<ValueType>> NVTptr;
    public:
            struct Iterator
            {
                NVTptr data;
                bool end = false;
                Iterator() = delete;
                Iterator(NVTptr _dt): data(_dt){}
                Iterator(NVTptr _dt, bool e): data(_dt), end(e){}
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
                NVTptr data;
                bool end = false;
                ConstIterator() = delete;
                ConstIterator(NVTptr _dt): data(_dt){}
                ConstIterator(NVTptr _dt, bool e): data(_dt), end(e){}
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

                void* getPointer()
                {
                    return data.get();
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
                NVTptr data;
                bool end = false;
                ReverseIterator() = delete;
                ReverseIterator(NVTptr _dt): data(_dt){}
                ReverseIterator(NVTptr _dt, bool e): data(_dt), end(e){}
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
            
        private:
            template <typename ValueType> 
            struct Node
            {
                VTptr val;
                NVTptr left = nullptr, right = nullptr;
                NVTptr ll_left = nullptr, ll_right = nullptr;
                bool parCol = false;     // color of parent link, black=true
                int numChildren = 1; 
                int parDir = 0;

                Node(): val(NULL), left(NULL), right(NULL), ll_left(NULL), ll_right(NULL), parCol(true), numChildren(0), parDir(0){}
                Node(const ValueType& v, bool col, int nc, int par):
                left(NULL), right(NULL),
                parCol(col), numChildren(nc), parDir(par) 
                {  
                    val = (VTptr(new ValueType(v))); 
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
                    left.reset();
                    right.reset();
                }

            };

            template <typename ValueType> 
            class LinkedList
            {
                //This is a tree where we only use the right child
                public:
                    NVTptr _root;
                    NVTptr _end;
                    int s_ze;
                    LinkedList(): _root(nullptr), _end(nullptr), s_ze(0)
                    {

                    }
                    int size() const
                    {
                        return s_ze;
                    }
                    void add(NVTptr n)
                    {

                        if(_root == nullptr)
                        {
                            _root = n;
                            _end = n;
                        }
                        else
                        {
                            std::cout << "(add) I AM THE CURRENT ROOT: " << _root->val->first << std::endl;
                        
                            NVTptr c = _root;
                            while(c)//if we havent hit the end yet
                            {
                                
                                   
                                //if we are less than or equal, add us
                                if(n->val->first < c->val->first || n->val->first == c->val->first)
                                {
                                       NVTptr t = c->ll_left;
                                    if(t == nullptr)
                                        std::cout << "T is : null" << std::endl;
                                    else
                                        std::cout << "T is : " << t->val->first << std::endl;
                                    std::cout << "ROOT is : " << _root->val->first << std::endl;
                                    std::cout << "TIME TO INSERT" << std::endl;
                                    std::cout << "SPOT TO INSRT BEFORE " << c->val->first << std::endl;
                                    //std::cout << "insert after: " << t->val->first << std::endl;
                                    if(t == nullptr) //we are first;
                                    {
                                        n->ll_left = nullptr;
                                        n->ll_right = _root;
                                        _root->ll_left = n;
                                        _root = n;
                                    }
                                    else if(t->ll_left == nullptr)//trying to insert between the root and second node
                                    {
                                        //T is the root
                                        //N is the insertable 
                                        //C is the second (soon to be third)
                                        //R <-> (2)
                                        NVTptr hold = t->ll_right; //get the (2)
                                        //R <-> (2)
                                        
                                        t->ll_right = n; //set root next to insertable
                                        //R -> n
                                        
                                        n->ll_left = t; //set insertable left to root
                                        //R <-> n
                                        
                                        n->ll_right = hold; //set insertable to (2)
                                        //R <-> n -> (2)

                                        hold->ll_left = n; //change (2)-left from root to insertable
                                        //R <-> n <-> (2)
                                        //std::cout << "T is : " << t->val->first << std::endl;
                                        //std::cout << "ROOT is : " << _root->val->first << std::endl;
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
                        std::cout << " (postadd) I AM THE CURRENT ROOT: " << _root->val->first << std::endl;
                    }
                    void remove(NVTptr n)
                    {
                        std::cout << "REMOVED" << std::endl;
                        NVTptr temproot = _root;
                        std::cout << "I AM THE CURRENT ROOT: " << _root->val->first << std::endl;
                        while(temproot != nullptr)
                        {
                            if(temproot->val->first == n->val->first)
                            {
                                std::cout << "time to remove" << std::endl;
                                s_ze--;

                                if(!temproot->ll_left) //we are root
                                {
                                    std::cout << "We are groot" << std::endl;
                                    _root = temproot->ll_right;
                                    if(_root)
                                        _root->ll_left = NVTptr(nullptr);
                                }
                                else 
                                {
                                    std::cout << "not trying to delete the root" << std::endl;
                                    NVTptr a = temproot->ll_left;
                                    NVTptr b = temproot->ll_right;
                                    //we are deleting temproot
                                    // a <-> temproot <-> b
                                    a->ll_right = b;
                                    b->ll_left = a;
                                }
                                break;
                            }
                            temproot = temproot->ll_right;
                        }//end of while loop
                        std::cout << "I AM THE CURRENT ROOT: " << _root->val->first << std::endl;   
                    }
                    void print() const
                    {
                        NVTptr cur = _root;
                        while(cur != nullptr)
                        {
                            std::cout << cur->val->first << ", ";
                            cur = cur->ll_right;
                        }
                        std::cout <<std::endl;
                        cur = _end;
                        while(cur != nullptr)
                        {
                            std::cout << cur->val->first << ", ";
                            cur = cur->ll_left;
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
                    int chil(NVTptr r)
                    {
                        if(r == nullptr)
                            return 0;
                        return r->numChildren;
                    }

                    bool isblk(NVTptr r)
                    {
                        if(r == nullptr)
                            return true;
                        return r->parCol;
                    }
                    //to handle checking left child of r
                    bool isblkL(NVTptr r)
                    {
                        if(r == nullptr)
                            return true;
                        if(r->left == nullptr)
                            return true;
                        return r->left->parCol;
                    }

                    void flipColor(NVTptr r)
                    {
                        if(r == nullptr)
                            return;
                        else
                            r->parCol = !r->parCol;
                    }

                    NVTptr rotateRight(NVTptr r) 
                    {
                        NVTptr x = r->left;
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
              
                    NVTptr rotateLeft(NVTptr r) 
                    {
                        NVTptr x = r->right;
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

                    void flip(NVTptr r) {
                        flipColor(r);
                        flipColor(r->left);
                        flipColor(r->right);
                    }

                    NVTptr aux_addNode(NVTptr r, const ValueType& val, int dir) 
                    {
                        if(r == nullptr)
                        {
                            NVTptr nnode = NVTptr(new Node<ValueType>(val, false, 1, dir));
                            lldata.add(nnode);
                            return nnode;
                        }
                        const ValueType cval = *(r->val); 

                        if(val.first < cval.first)
                        {
                            NVTptr next= aux_addNode(r->left, val, -1);
                            r->left = next;
                        }
                        else if(val.first == cval.first)
                        {  //equals
                            r->val = VTptr(new ValueType(std::make_pair(val.first, val.second)));
                        }
                        else
                        { 
                            NVTptr next= aux_addNode(r->right, val, 1);
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
                    NVTptr root;

                    RBT(): root(nullptr){}
                    RBT(NVTptr r): root(r){}
                    ~RBT()
                    {
                        int i=lldata.s_ze;
                        while(root != nullptr)
                        {
                            removeNode(*(root->val), true);
                            i--;
                            if(i < 0)
                                break;
                        }
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

                    NVTptr rebal(NVTptr r) 
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

                    
                    NVTptr mrl(NVTptr r)
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
                    NVTptr mrr(NVTptr r)
                    {
                        flip(r);
                        if (!isblkL(r->left)) 
                        { 
                            r = rotateRight(r);
                            flip(r);
                        }
                        return r;
                    }

                    NVTptr r_min(NVTptr r)
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

                    NVTptr g_min(NVTptr r)
                    {
                        if(r->left == nullptr)
                            return r;
                        return r_min(r->left);
                    }

                    NVTptr aux_remove(NVTptr r, ValueType v)
                    {
                        if(r == nullptr)
                            return r;

                        if (v.first < r->val->first) 
                        {
                            if (isblk(r->left) && isblkL(r->left))
                            {
                                r = mrl(r);
                            }
                            r->left = aux_remove(r->left, v);
                        }
                        else {
                            if (!isblk(r->left))
                            {
                                r = rotateRight(r);
                            }
                            if (v.first == r->val->first && r->right == nullptr)
                            {
                                return nullptr;
                            }
                            if (isblk(r->right) && isblkL(r->right))
                            {
                                r = mrr(r);
                            }
                            if (v.first == r->val->first)
                            {
                                NVTptr tmp = g_min(r->right);
                                if(tmp.get() != nullptr)
                                    r->val = tmp->val;
                                r->right = r_min(r->right);
                            }
                            else
                            {
                                r->right = aux_remove(r->right, v);
                            }
                        }
                        return rebal(r);
                    }

                    void removeNode(const ValueType v, bool cleanup = false)
                    {
                        if(cleanup)
                        {
                            NVTptr cur = find_node(v.first);
                            if(cur == nullptr) return;
                            root = aux_remove(root, v);
                            return;
                        }
                        //std::cout << "REMOVE NODE" << std::endl;
                        NVTptr cur = find_node(v.first);
                        //std::cout << "NODE FOUND" << std::endl;
                        if(cur == nullptr)
                        {
                        //std::cout << "NULL REMOVE NODE" << std::endl;
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
                        //std::cout << "DONE REMOVE NODE" << std::endl;
                    }

                    void removeNode(const IT iter, bool cleanup = false)
                    {
                        removeNode(*iter, cleanup);
                    }

                    NVTptr find_node(const Key_T kee) const
                    {
                        //TODO
                        //std::cout << "TO FIND: " << kee << std::endl;
                        NVTptr cur = lldata._root;
                        while(cur != nullptr)
                        {
                            //std::cout << cur->val->first << std::endl;
                            if(cur->val->first == kee)
                            {
                                return cur;
                            }
                            cur = cur->ll_right;
                        }
                        /*
                            std::cout << "TRYING TO FIND: " << kee << std::endl;
                            NVTptr cur = root;
                            while(cur != nullptr)
                            {
                                std::cout << cur->val->first << std::endl;
                                if(cur->val->first == kee)
                                {
                                std::cout << "FOUND" << std::endl;
                                    return cur;
                                }
                                else if(cur->val->first < kee)
                                {
                                std::cout << "Move RIGHT" << std::endl;
                                    cur = cur->right;
                                }
                                else
                                {
                                std::cout << "Move LEFT" << std::endl;
                                    cur = cur->left;
                                }
                            }
                        */

                        //std::cout << "NOT FOUND" << std::endl;
                        //throw std::out_of_range("");
                        return nullptr;
                    }

                    ValueType& find(const Key_T kee) const
                    {
                        NVTptr nn = find_node(kee);
                        if(nn.get() == nullptr)
                            throw std::out_of_range("");
                        return *(nn->val);
                    }

                    ValueType& at(size_t ind) const
                    {
                        NVTptr cur = root;
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
                    void postorder(NVTptr p, int indent=0) const
                    {
                        int idd = indent;
                        if(p != NULL) 
                        {
                            if(p->right) 
                            {
                                postorder(p->right, indent+4);
                            }
                            if (indent) 
                            {
                                while(idd--)
                                    std::cout << ' ';
                                idd = indent;
                            }
                            if (p->right){
                                std::cout<<" /\n";
                                while(idd--)
                                    std::cout << ' ';
                                idd = indent;
                            }
                            std::cout<< p->val->first << "\n ";
                            if(p->left) 
                            {
                                while(idd--)
                                std::cout << ' ';
                                std::cout <<" \\\n";
                                postorder(p->left, indent+4);
                            }
                        }  
                    }

                    void print_aux(NVTptr r) const
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
                    void print() const 
                    {
                        NVTptr r = root;
                        postorder(r);
                        lldata.print();
                        //print_aux(root);
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
                    return data.lldata.size(); //data.root->numChildren+1;
            }
            bool empty() const
            {
                return data.root.get() == nullptr;
            }

            IT begin()
            {
                if(data.root == nullptr)
                    return IT(data.lldata._root, true);
                //std::cout <<"BEGIN" << data.lldata._root->val->first << std::endl;
                return IT(data.lldata._root);
            }
            IT end()
            {
                return IT(data.lldata._end, true);
            }

            CIT begin() const
            {

                if(data.root == nullptr)
                    return CIT(data.lldata._root, true);
                //std::cout <<"CONST BEGIN" << data.lldata._root->val->first << std::endl;
                return CIT(data.lldata._root);
            }
            CIT end() const{return CIT(data.lldata._end, true);}
            
            RIT rbegin()
            {
                if(data.root == nullptr)
                    return RIT(data.lldata._root, true);
                return RIT(data.lldata._end);
            }

            RIT rend(){return RIT(data.lldata._root, true);}
            
            IT find(const Key_T& kee)
            {
                IT a = end();
                NVTptr v;
                try{
                    v = data.find_node(kee);
                    if(v == nullptr)
                        return end();
                    //std::cout << "KEY:" << v->val->first << ", ";
                    //std::cout << "VALUE:" << v->val->second << std::endl;
                }
                catch(const std::out_of_range& e)
                {
                    return end();
                }
                return IT(v);
            }
            CIT find(const Key_T & kee) const
            {
                CIT a = end();
                NVTptr v;
                try{
                    v = data.find_node(kee);
                    //std::cout << "KEY:" << v->val->first << ", ";
                    //std::cout << "VALUE:" << v->val->second << std::endl;
                }
                catch(const std::out_of_range& e)
                {
                    return end();
                }
                return CIT(v);
            }

            const Mapped_T& at(const Key_T & kee) const
            {
                ValueType& r = data.find(kee);
                return data.find(kee).second;
            }

            const ValueType &index(size_t ind) const
            {
                return (data.at(ind));
            }

            Mapped_T& operator[](const Key_T & kee)
            {
                try
                {
                    ValueType& v = data.find(kee);
                    return v.second;
                }
                catch(const std::out_of_range& e)
                {
                    ValueType vi = std::make_pair(kee, Mapped_T());
                    data.addNode(vi);
                    ValueType& v = data.find(kee);
                    return v.second;
                }
            } 

            std::pair<IT, bool> 
            insert(const ValueType& lis)
            {
                std::cout << "--------------------PAIR " << lis.first << " " << lis.second << std::endl;
                bool inserted = false;    
                IT a = find(lis.first);
                if(a.end)
                {
                    try
                    {
                        data.addNode(std::make_pair(lis.first, lis.second));
                        inserted = true;
                    }
                    catch(const std::runtime_error e)
                    {
                        
                    }
                }
                else
                {
                  //  std::cout << "Alread inserted" << std::endl;
                }
                //this->print();
                std::pair<IT, bool> ret = std::make_pair(find(lis.first), inserted);
                return ret;
            }

            void erase(IT pos)
            {
                //std::cout << "it erase" << std::endl;
                data.removeNode(pos);
                //std::cout << "done it erase" << std::endl;
            }
            void erase(const Key_T & kee)
            {
                //std::cout << "erase" << std::endl;
                data.removeNode(find(kee));
                //std::cout << "done erase" << std::endl;
            }

            void print() const
            {
                //std::cout << "START" << std::endl;
                data.print();
                //std::cout << "END" <<std::endl;
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
    bool static operator==(const Map< Key_T, Mapped_T>  & , const Map< Key_T, Mapped_T>  & )
    {return false;}
    template < typename Key_T, typename Mapped_T>  
    bool static operator!=(const Map< Key_T, Mapped_T>  & , const Map< Key_T, Mapped_T>  & )
    {return false;}
    template < typename Key_T, typename Mapped_T>  
    bool static operator<(const Map< Key_T, Mapped_T>  & , const Map< Key_T, Mapped_T>  & )
    {return false;}

    

}

#endif
