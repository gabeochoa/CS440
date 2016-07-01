#ifndef CS540_MAP
#define CS540_MAP

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <memory>

using std::string;
namespace cs540
{
    template < typename Key_T, typename Mapped_T> class Map
    {
        typedef std::pair<Key_T, Mapped_T> ValueType;
        typedef std::shared_ptr<ValueType> VTptr;


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
                void* getPointer() const
                {
                    return data.get();
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

                    if(a.end && b.end)
                    {
                        return true;
                    }
                    else if(a.end || b.end)
                    {
                        return false;
                    }

                    if(a.getPointer() == b.getPointer())
                    {
                        return true;
                    }
                    else if(a.data == b.data)
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




                    if(a.getPointer() && b.getPointer())
                    {


                    }
                    if(a.end && b.end)
                    {

                        return true;
                    }

                    if(a.end != b.end)
                    {

                        return false;
                    }
                    if(a.getPointer() && b.getPointer())
                    {
                        if(a->first == b->first){}
                        else
                        {

                            return false;
                        }
                        if(a->second == b->second){}
                        else
                        {

                            return false;
                        }
                    }

                    return true;
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

                void* getPointer() const
                {
                    return data.get();
                }
                friend bool operator==(cs540::Map<Key_T, Mapped_T>::ConstIterator& a, cs540::Map<Key_T, Mapped_T>::ConstIterator & b)
                {

                    if(a.end && b.end)
                    {
                        return true;
                    }
                    else if(a.end || b.end)
                    {
                        return false;
                    }

                    if(a.getPointer() == b.getPointer())
                    {
                        return true;
                    }
                    else if(a.data == b.data)
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
                    if(a.end && b.end)
                    {
                        return true;
                    }
                    else if(a.end || b.end)
                    {
                        return false;
                    }

                    if(a.getPointer() == b.getPointer())
                    {
                        return true;
                    }
                    else if(a.data == b.data)
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
                void* getPointer() const
                {
                    return data.get();
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
                    if(a.end && b.end)
                    {
                        return true;
                    }
                    else if(a.end || b.end)
                    {
                        return false;
                    }

                    if(a.getPointer() == b.getPointer())
                    {
                        return true;
                    }
                    else if(a.data == b.data)
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
                    if(a.end && b.end)
                    {
                        return true;
                    }
                    else if(a.end || b.end)
                    {
                        return false;
                    }

                    if(a.getPointer() == b.getPointer())
                    {
                        return true;
                    }
                    else if(a.data == b.data)
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
                NVTptr parent = nullptr;
                bool parCol = false;
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


                            NVTptr c = _root;
                            while(c)
                            {

                                if(n->val->first < c->val->first || n->val->first == c->val->first)
                                {
                                    NVTptr t = c->ll_left;

                                    if(t == nullptr)
                                    {
                                        n->ll_left = nullptr;
                                        n->ll_right = _root;
                                        _root->ll_left = n;
                                        _root = n;
                                    }
                                    else if(t->ll_left == nullptr)
                                    {
                                        NVTptr hold = t->ll_right;

                                        t->ll_right = n;

                                        n->ll_left = t;

                                        n->ll_right = hold;

                                        hold->ll_left = n;

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
                                else
                                {

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
                        int i =0;
                        NVTptr h = _root;
                        while(h->ll_right)
                        {
                            h = h->ll_right;
                            i++;
                            if(i > 10)
                            {
                                break;
                            }
                        }
                        _end = h;
                        s_ze++;

                    }
                    void remove(NVTptr n)
                    {

                        NVTptr temproot = _root;

                        while(temproot != nullptr)
                        {
                            if(temproot->val->first == n->val->first)
                            {

                                s_ze--;

                                if(!temproot->ll_left)
                                {

                                    _root = temproot->ll_right;
                                    if(_root)
                                        _root->ll_left = NVTptr(nullptr);
                                }
                                else
                                {

                                    NVTptr a = temproot->ll_left;
                                    NVTptr b = temproot->ll_right;



                                    a->ll_right = b;
                                    if(b != nullptr)
                                        b->ll_left = a;
                                }
                                break;
                            }
                            temproot = temproot->ll_right;
                        }


                        NVTptr h = _root;
                        if(h == nullptr)
                        {
                            _end = _root;
                        }
                        else
                        {
                            if(h->ll_right == nullptr)
                                _end = _root;
                            else
                            {
                                while(h->ll_right)
                                {
                                    h = h->ll_right;
                                }
                                _end = h;
                            }
                        }

                        if(_root == _end)
                        {
                            if(!_root || !_root->val)
                                s_ze = 0;
                            else
                                s_ze = 1;
                        }
                    }
                    void print() const
                    {
                        NVTptr cur = _root;
                        while(cur != nullptr)
                        {

                            cur = cur->ll_right;
                        }
                        std::cout <<std::endl;
                        cur = _end;
                        while(cur != nullptr)
                        {

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

                    bool isblkL(NVTptr r)
                    {
                        if(r == nullptr)
                            return true;
                        if(r->left == nullptr)
                            return true;
                        return r->left->parCol;
                    }
                    bool isblkLL(NVTptr r)
                    {
                        if(r == nullptr)
                            return true;
                        return isblkL(r->left);
                    }
                    bool isblkR(NVTptr r)
                    {
                        if(r == nullptr)
                            return true;
                        if(r->right == nullptr)
                            return true;
                        return r->right->parCol;
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

                    NVTptr aux_addNode(NVTptr parent, NVTptr r, const ValueType& val, int dir)
                    {

                        if(r == nullptr)
                        {


                            NVTptr nnode = NVTptr(new Node<ValueType>(val, false, 1, dir));
                            nnode->parent = parent;
                            lldata.add(nnode);
                            return nnode;
                        }
                        const ValueType cval = *(r->val);

                        if(val.first < cval.first)
                        {

                            NVTptr next= aux_addNode(r, r->left, val, -1);
                            r->left = next;
                        }
                        else if(val.first == cval.first)
                        {

                            r->val = VTptr(new ValueType(std::make_pair(val.first, val.second)));
                        }
                        else
                        {

                            NVTptr next= aux_addNode(r, r->right, val, 1);
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
                        root = aux_addNode(nullptr, root, v, 0);
                        root->parCol = true;
                    }

                    NVTptr rebal(NVTptr r)
                    {
                        if(r == nullptr)
                            return r;
                        if(!isblkR(r))
                        {
                            r = rotateLeft(r);
                        }
                        if( (!isblkL(r)) && (!isblkLL(r)) )
                        {
                            r = rotateRight(r);
                        }
                        if( (!isblkL(r)) && (!isblkR(r)) )
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
                        if(isblk(r->left) && isblkLL(r))
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

                    NVTptr max(NVTptr r)
                    {
                        if(r == nullptr)
                            return r;
                        return max(r->right);
                    }
                    NVTptr aux_remove(NVTptr r, ValueType v)
                    {
                        if (v.first < r->val->first)
                        {
                            if (isblkL(r) && isblkLL(r))
                            {
                                r = mrl(r);
                            }
                            r->left = aux_remove(r->left, v);
                        }
                        else {
                            if (!isblkL(r))
                            {
                                r = rotateRight(r);
                            }
                            if (v.first == r->val->first && r->right == nullptr)
                            {
                                return nullptr;
                            }
                            if (isblkR(r) && isblkL(r->right))
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


                        if(lldata._root==nullptr || root == nullptr)
                        {

                            return;
                        }

                        NVTptr cur = find_node(v.first);

                        if(cur == nullptr)
                        {

                            return;
                        }

                        lldata.remove(cur);


                        if(isblkL(root) && isblkR(root))
                        {
                            root->parCol = false;
                        }
                        root = aux_remove(root, v);
                        if (root != nullptr)
                            root->parCol = true;

                    }

                    void removeNode(const IT iter, bool cleanup = false)
                    {
                        removeNode(*iter, cleanup);
                    }

                    NVTptr find_node(const Key_T kee) const
                    {
                        /*
                        NVTptr cur = lldata._root;
                        while(cur != nullptr)
                        {
                            if(cur->val->first == kee)
                            {
                                return cur;
                            }
                            cur = cur->ll_right;
                        }
                        return nullptr;
                        */
                        NVTptr cur = root;
                        while(cur != nullptr)
                        {
                            if(cur->val->first == kee)
                            {
                                return cur;
                            }
                            else if(kee < cur->val->first)
                            {
                                cur = cur->left;
                            }
                            else
                                cur = cur->right;
                        }
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

                                idd = indent;
                            }
                            if (p->right){
                                std::cout<<" /\n";
                                while(idd--)

                                idd = indent;
                            }
                            std::cout<< p->val->first << "\n ";
                            if(p->left)
                            {
                                while(idd--)

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

                            print_aux(r->left);
                            print_aux(r->right);
                        }
                    }
                    void print() const
                    {
                        NVTptr r = root;
                        postorder(r);
                        lldata.print();


                    }
            };

        public:
            RBT<ValueType> data;
            int clean = 0;
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

                for(auto iter = lis.begin(); iter != lis.end(); iter++)
                {
                    data.addNode(*iter);
                }
            }
            ~Map(){}

            size_t size() const
            {
                return data.lldata.size();
            }
            bool empty() const
            {
                return size() == 0;
            }

            IT begin()
            {
                if(empty())
                    return IT(data.lldata._root, true);

                return IT(data.lldata._root);
            }
            IT end()
            {
                return IT(data.lldata._end, true);
            }

            CIT begin() const
            {

                if(empty() )
                    return CIT(data.lldata._root, true);

                return CIT(data.lldata._root);
            }
            CIT end() const{return CIT(data.lldata._end, true);}

            RIT rbegin()
            {
                if(empty() )
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
                }
                catch(const std::out_of_range& e)
                {
                    return end();
                }
                return CIT(v);
            }

            const Mapped_T& at(const Key_T & kee) const
            {
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

                }

                std::pair<IT, bool> ret = std::make_pair(find(lis.first), inserted);
                return ret;
            }

            void erase(IT pos)
            {

                data.removeNode(pos);

                auto lltemp = data.lldata;
                data = RBT<ValueType>(nullptr);
                NVTptr r = lltemp._root;
                while(r != nullptr)
                {
                    data.addNode(std::make_pair(r->val->first, r->val->second));
                    r = r->ll_right;
                }
            }
            void erase(const Key_T & kee)
            {
                data.removeNode(find(kee));
            }

            void print() const
            {
                data.print();
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
    {
        auto aiter = a.begin();
        auto biter = b.begin();
        for(; aiter != a.end() || biter != b.end(); aiter++, biter++)
        {
            if(aiter->first == biter->first)
            {
                if(aiter->second == biter->second)
                {}
                else
                    return false;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    template < typename Key_T, typename Mapped_T>
    bool static operator!=(const Map< Key_T, Mapped_T>  & a, const Map< Key_T, Mapped_T>  & b)
    {return !(a == b);}

    template < typename Key_T, typename Mapped_T>
    bool static operator<(const Map< Key_T, Mapped_T>  & a, const Map< Key_T, Mapped_T>  & b)
    {
        if(a.size() >= b.size())
            return false;
        else
        {
            auto aiter = a.begin();
            auto biter = b.begin();
            for(; aiter != a.end() || biter != b.end(); aiter++, biter++)
            {
                if(aiter->first < biter->first || aiter->first == biter->first){}
                else
                {
                    return false;
                }
            }
        }
        return true;
    }



}

#endif
