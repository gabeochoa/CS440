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
                Iterator(): data(nullptr){}
                Iterator(Node<ValueType>* _dt): data(_dt){}
                Iterator(const Iterator & it)
                {
                    data = it.data;
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
                    if(data->val != nullptr)
                        data = data->ll_left.get();
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
                    if(data->val != nullptr)
                        data = data->ll_right.get();
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

                bool operator!=(const Iterator & b)
                {return !((*this)==b);}

                friend bool operator==(cs540::Map<Key_T, Mapped_T>::Iterator&a, cs540::Map<Key_T, Mapped_T>::Iterator & b)
                {
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
                friend bool operator==(const cs540::Map<Key_T, Mapped_T>::Iterator&a, const cs540::Map<Key_T, Mapped_T>::Iterator & b){return false;}
                friend bool operator==(const cs540::Map<Key_T, Mapped_T>::Iterator&a,  cs540::Map<Key_T, Mapped_T>::Iterator & b){return false;}
                friend bool operator==( cs540::Map<Key_T, Mapped_T>::Iterator&a, const cs540::Map<Key_T, Mapped_T>::Iterator & b){return false;}

            };
            struct ReverseIterator
            {
                Node<ValueType>* data;
                ReverseIterator(): data(nullptr){}
                ReverseIterator(Node<ValueType>* _dt): data(_dt){}
                ReverseIterator(const ReverseIterator & it)
                {
                    data = it.data;
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
                    if(data != nullptr)
                        data = data->ll_left.get();
                    return *this;
                }
                ReverseIterator operator--(int )
                {
                    ReverseIterator rt = *this;
                    operator--();
                    return rt;
                }
                //ReverseIter++
                ReverseIterator& operator++()
                {
                    if(data != nullptr)
                        data = data->ll_right.get();
                    return *this;
                }
                //++ReverseIter
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

                bool operator!=(const ReverseIterator & b)
                {return !((*this)==b);}

                friend bool operator==(cs540::Map<Key_T, Mapped_T>::ReverseIterator&a, cs540::Map<Key_T, Mapped_T>::ReverseIterator & b)
                {
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
                friend bool operator==(const cs540::Map<Key_T, Mapped_T>::ReverseIterator&a, const cs540::Map<Key_T, Mapped_T>::ReverseIterator & b){return false;}
                friend bool operator==(const cs540::Map<Key_T, Mapped_T>::ReverseIterator&a,  cs540::Map<Key_T, Mapped_T>::ReverseIterator & b){return false;}
                friend bool operator==( cs540::Map<Key_T, Mapped_T>::ReverseIterator&a, const cs540::Map<Key_T, Mapped_T>::ReverseIterator & b){return false;}

            };
            struct ConstIterator
            {
                Node<ValueType>* data;
                ConstIterator(): data(nullptr){}
                ConstIterator(Node<ValueType>* _dt): data(_dt){}
                ConstIterator(const ConstIterator & it)
                {
                    data = it.data;
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
                    if(data != nullptr)
                        data = data->ll_left.get();
                    return *this;
                }
                ConstIterator operator--(int )
                {
                    ConstIterator rt = *this;
                    operator--();
                    return rt;
                }
                //ConstIter++
                ConstIterator& operator++()
                {
                    if(data != nullptr)
                        data = data->ll_right.get();
                    return *this;
                }
                //++ConstIter
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

                bool operator!=(const ConstIterator & b)
                {return !((*this)==b);}

                friend bool operator==(cs540::Map<Key_T, Mapped_T>::ConstIterator&a, cs540::Map<Key_T, Mapped_T>::ConstIterator & b)
                {
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
                friend bool operator==(const cs540::Map<Key_T, Mapped_T>::ConstIterator&a, const cs540::Map<Key_T, Mapped_T>::ConstIterator & b){return false;}
                friend bool operator==(const cs540::Map<Key_T, Mapped_T>::ConstIterator&a,  cs540::Map<Key_T, Mapped_T>::ConstIterator & b){return false;}
                friend bool operator==( cs540::Map<Key_T, Mapped_T>::ConstIterator&a, const cs540::Map<Key_T, Mapped_T>::ConstIterator & b){return false;}

            };

            typedef cs540::Map<Key_T, Mapped_T>::Iterator Iterator;
            typedef cs540::Map<Key_T, Mapped_T>::ConstIterator ConstIterator;
            typedef cs540::Map<Key_T, Mapped_T>::ReverseIterator ReverseIterator;
            typedef std::shared_ptr<ValueType> VTptr;
            typedef std::shared_ptr<Node<ValueType>> NVTptr;
        private:
            template <typename ValueType> 
            struct Node
            {
                VTptr val;
                Node<ValueType> *left = nullptr, *right = nullptr;
                NVTptr ll_left, ll_right;
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
                    ll_left = r.ll_left;
                    ll_right = r.ll_right;
                    parCol = r.parCol;
                    numChildren = r.numChildren;
                    parDir = r.parDir;
                }
                Node<ValueType>& operator=(const Node<ValueType>& r)
                {
                    val = r.val;
                    left = r.left;
                    right = r.right;
                    ll_left = r.ll_left;
                    ll_right = r.ll_right;
                    parCol = r.parCol;
                    numChildren = r.numChildren;
                    parDir = r.parDir;
                    return *this;
                }
                ~Node()
                {
                    if(left != nullptr)
                        delete left;
                    if(right != nullptr)
                        delete right;
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
                    void add(Node<ValueType>* no)
                    {
                        //Node<ValueType>* n = new Node<ValueType>(nn.val->first, nn.val.second, false, 1, nn.parDir);
                        
                        if(_root == nullptr)
                        {
                            _root = no;
                            _end = no;
                        }
                        else
                        {
                            NVTptr c = NVTptr(_root);
                            NVTptr n = NVTptr(no);
                            while(c)
                            {
                                if(n->val->first < c->val->first || n->val->first == c->val->first)
                                {
                                    NVTptr t = c->ll_left;
                                    c->ll_left = n;
                                    n->ll_right = c;
                                    n->ll_left = t;
                                    if(t != nullptr)
                                        t->ll_right = NVTptr(n);
                                    break;
                                }
                                else // if(n->val->first > c->val->first)
                                {
                                    if(c->ll_right.get() == nullptr)
                                    {
                                        c->ll_right = NVTptr(n.get());
                                        n->ll_left = c;
                                        _end = no;
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
                        bool found = false;
                        NVTptr cur = NVTptr(_root);
                        Node<ValueType>* del;
                        while(cur != nullptr)
                        {
                            if(cur->val == n->val)
                            {
                                found = true;
                                del = (cur->ll_left)->ll_right.get();
                                (cur->ll_left)->ll_right = cur->ll_right;
                                delete del;
                            }
                        }
                        if(found)
                            s_ze--;
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
                        {
                            delete root;
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

                    Node<ValueType>* aux_remove(Node<ValueType>* r, ValueType v)
                    {

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
                                Node<ValueType>* tmp = g_min(r->right);
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

                    void removeNode(const ValueType v)
                    {
                        Node<ValueType>* cur = find_node(v.first);
                        if(cur == nullptr)
                            return;
                        lldata.remove(cur);

                        if(isblk(root->left) && isblk(root->right))
                        {
                            root->parCol = false;
                        }

                        root = aux_remove(root, v);
                        if (root == nullptr) 
                            root->parCol = true;
                    }

                    void removeNode(const IT v)
                    {
                        removeNode(*v);
                    }

                    ValueType& find(const Key_T kee) const
                    {
                        Node<ValueType>* cur = root;
                        while(cur != nullptr)
                        {
                            if(cur->val->first == kee)
                            {
                                return *(cur->val);
                            }
                            else if(cur->val->first < kee)
                            {
                                cur = cur->right;
                            }
                            else
                            {
                                cur = cur->left;
                            }
                        }
                        throw std::out_of_range ("Out of range");
                    }

                    Node<ValueType>* find_node(const Key_T kee) const
                    {
                        Node<ValueType>* cur = root;
                        while(cur != nullptr)
                        {
                            if(cur->val->first == kee)
                            {
                                return cur;
                            }
                            else if(cur->val->first < kee)
                            {
                                cur = cur->right;
                            }
                            else
                            {
                                cur = cur->left;
                            }
                        }
                        return nullptr;
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
                    void postorder(NVTptr p, int indent=0)
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

                    void print_aux(NVTptr r)
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
                        NVTptr r = root;
                        postorder(r);
                        std::cout <<"++++++++++++++++" <<std::endl;
                        print_aux(root);
                    }
            };
            
            const ValueType make_blank(const Key_T kee, const Mapped_T mpt) const
            {
                return std::make_pair(kee, Mapped_T());   
            }

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
                return IT();
            }

            CIT begin() const{return CIT(data.root);}
            CIT end() const{return CIT();}
            
            RIT rbegin()
            {return RIT(data.lldata._end);}

            RIT rend(){return RIT();}
            
            IT find(const Key_T &){return IT();}
            CIT find(const Key_T &) const{return CIT();}
            const Mapped_T& at(const Key_T & kee) const
            {
                //std::cout << "Looking for: " << kee << std::endl;
                ValueType r = data.find(kee);
                //std::cout << "Got: " << r.first << " " << r.second << std::endl;
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
                data.removeNode(*pos);
            }
            void erase(const Key_T & kee)
            {
                data.removeNode(std::make_pair(kee, Mapped_T()));
            }

            void print()
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
    {return false;}
    template < typename Key_T, typename Mapped_T>  
    bool static operator!=(const Map< Key_T, Mapped_T>  & a, const Map< Key_T, Mapped_T>  & b)
    {return false;}
    template < typename Key_T, typename Mapped_T>  
    bool static operator<(const Map< Key_T, Mapped_T>  & a, const Map< Key_T, Mapped_T>  & b)
    {return false;}

    

}

#endif
