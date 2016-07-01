#ifndef CS540_MAP
#define CS540_MAP

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

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
                    data = it.data;
                }
                Iterator& operator--()
                {
                    Iterator rt = *this;
                    if(data != nullptr)
                        data = data->ll_left;
                    return rt;
                }
                Iterator operator--(int dummy)
                {
                    if(data != nullptr)
                        data = data->ll_left;
                    return *this;
                }
                Iterator &&operator++()
                {
                    Iterator rt = *this;
                    if(data != nullptr)
                        data = data->ll_right;
                    return Iterator(rt);
                }
                Iterator operator++(int dummy)
                {
                    if(data != nullptr)
                        data = data->ll_right;
                    return *this;
                }
                ValueType &operator*() const
                {
                    return data->val;
                }
                ValueType *operator->() const
                {
                    return &(data->val);
                }

                bool operator==(const Iterator & b)
                {
                    if((*this).data == b.data)
                    {
                        if(this->data == nullptr)
                        {
                            return true;
                        }
                        else
                            return this->data->val == b.data->val;
                    }
                    return false;
                }

                bool operator!=(const Iterator & b)
                {return !((*this)==b);}
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
                    data = it.data;
                }
                ConstIterator &operator++()
                {
                    ConstIterator rt = *this;
                    if(data != nullptr)
                        data = data->ll_right;
                    return ConstIterator(rt);
                }
                ConstIterator operator++(int dummy)
                {
                    if(data != nullptr)
                        data = data->ll_right;
                    return *this;
                }
                ConstIterator &operator--()
                {
                    ConstIterator rt = *this;
                    if(data != nullptr)
                        data = data->ll_left;
                    return ConstIterator(rt);
                }
                ConstIterator operator--(int dummy)
                {
                    if(data != nullptr)
                        data = data->ll_left;
                    return *this;
                }
                ValueType &operator*() const
                {
                    return data->val;
                }
                ValueType *operator->() const
                {
                    return &(data->val);
                }

                bool operator==(const ConstIterator & b)
                {
                    if((*this).data == b.data)
                    {
                        if(this->data == nullptr)
                        {
                            return true;
                        }
                        else
                            return this->data->val == b.data->val;
                    }
                    return false;
                }
                bool operator!=(const ConstIterator & b)
                {return !((*this)==b);}
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
                    data = it.data;
                }
                ReverseIterator &operator--()
                {
                    ReverseIterator rt = *this;
                    if(data != nullptr)
                        data = data->ll_right;
                    return ReverseIterator(rt);
                }
                ReverseIterator operator--(int dummy)
                {
                    if(data != nullptr)
                        data = data->ll_right;
                    return *this;
                }
                ReverseIterator &&operator++()
                {
                    ReverseIterator rt = *this;
                    if(data != nullptr)
                        data = data->ll_left;
                    return ReverseIterator(rt);
                }
                ReverseIterator operator++(int dummy)
                {
                    if(data != nullptr)
                        data = data->ll_left;
                    return *this;
                }
                ValueType &operator*() const
                {
                    return data->val;
                }
                ValueType *operator->() const
                {
                    return &(data->val);
                }

                bool operator==(const ReverseIterator & b)
                {
                    if((*this).data == b.data)
                    {
                        if(this->data == nullptr)
                        {
                            return true;
                        }
                        else
                            return this->data->val == b.data->val;
                    }
                    return false;
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
                ValueType val;
                Node<ValueType> *left, *right;
                Node<ValueType> *ll_left, *ll_right;
                bool parCol;     // color of parent link, black=true
                int numChildren; 
                int parDir = 0;

                Node(): val(NULL), left(nullptr), right(nullptr), ll_left(nullptr), ll_right(nullptr), parCol(true), numChildren(0), parDir(0){}
                Node(const ValueType& v, bool col, int nc, int par): 
                left(nullptr), right(nullptr),
                parCol(col), numChildren(nc), parDir(par) 
                {
                    val = std::move(v);
                } 
                
                Node(const Key_T& k, const Mapped_T& mt, bool col, int nc, int par): 
                left(nullptr), right(nullptr),
                ll_left(nullptr), ll_right(nullptr),
                parCol(col), numChildren(nc), parDir(par) 
                {
                    val = std::make_pair(std::move(k),std::move(mt)); 
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
                    void add(Node<ValueType>* n)
                    {
                        //Node<ValueType>* n = new Node<ValueType>(nn.val.first, nn.val.second, false, 1, nn.parDir);
                        
                        if(_root == nullptr)
                        {
                            _root = n;
                            _end = n;
                        }
                        else
                        {
                            Node<ValueType>* c = _root;
                            while(c)
                            {
                                if(n->val.first <= c->val.first)
                                {
                                    Node<ValueType>* t = c->ll_left;
                                    c->ll_left = n;
                                    n->ll_right = c;
                                    n->ll_left = t;
                                    if(t)
                                        t->ll_right = n;
                                    break;
                                }
                                else if(n->val.first > c->val.first)
                                {
                                    if(!c->ll_right)
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
                                else{}
                            }
                        }
                        s_ze++;
                    }
                    void remove(Node<ValueType>* n)
                    {return;
                        bool found = false;
                        Node<ValueType>* cur = _root;
                        Node<ValueType>* del;
                        while(cur != nullptr)
                        {
                            if(cur->val == n->val)
                            {
                                found = true;
                                del = (cur->ll_left)->ll_right;
                                (cur->ll_left)->ll_right = cur->ll_right;
                                delete del;
                            }
                        }
                        if(found)
                            s_ze--;
                    }
                    void t_print()
                    {
                        
                        Node<ValueType>* cur = _root;
                        while(cur != nullptr)
                        {
                            std::cout << cur->val.first;
                            cur = cur->ll_right;
                            if(cur != nullptr)
                                std::cout << ", ";
                        }
                        std::cout << std::endl;
                        
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
                        const ValueType cval = r->val; 

                        if(val.first < cval.first)
                        {
                            Node<ValueType>* next= aux_addNode(r->left, val, -1);
                            r->left = next;
                        }
                        else if(val.first > cval.first)
                        {
                            Node<ValueType>* next= aux_addNode(r->right, val, 1);
                            r->right = next;
                        }
                        else
                        {   //equals
                            r->val = val;
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

                        if (v.first < r->val.first) 
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
                            if (v.first == r->val.first && r->right == nullptr)
                            {
                                return nullptr;
                            }
                            if (isblk(r->right) && isblkL(r->right))
                            {
                                r = mrr(r);
                            }
                            if (v.first == r->val.first)
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

                    }

                    ValueType& find(const Key_T kee) const
                    {
                        Node<ValueType>* cur = root;
                        while(cur != nullptr)
                        {
                            if(cur->val.first == kee)
                            {
                                return cur->val;
                            }
                            else if(cur->val.first < kee)
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
                            if(cur->val.first == kee)
                            {
                                return cur;
                            }
                            else if(cur->val.first < kee)
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
                        ValueType ret = root->val;
                        while(cur != nullptr)
                        {
                            ret = cur;
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
                                ret = cur->val;
                                break;
                            }
                            if(cur == nullptr)
                            {
                                break;
                            }
                        }
                        return ret;
                    }

                    int _print_t(Node<ValueType> *tree, int is_left, int offset, int depth, char s[200][255])
                    {
                        char b[200];
                        int width = 7;

                        if (!tree) return 0;

                        if(!isblk(tree))
                        {
                            sprintf(b, "%s(%d->%d)%s", "", tree->val.first, tree->val.second, "");
                        }
                        else
                        {
                            sprintf(b, "%s(%d->%d)%s", "", tree->val.first, tree->val.second, "");
                        }
                        int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
                        int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

                        #ifdef COMPACT
                            for (int i = 0; i < width; i++)
                                s[depth][offset + left + i] = b[i];

                            if (depth && is_left) {

                                for (int i = 0; i < width + right; i++)
                                    s[depth - 1][offset + left + width/2 + i] = '-';

                                s[depth - 1][offset + left + width/2] = '.';

                            } else if (depth && !is_left) {

                                for (int i = 0; i < left + width; i++)
                                    s[depth - 1][offset - width/2 + i] = '-';

                                s[depth - 1][offset + left + width/2] = '.';
                            }
                        #else
                            for (int i = 0; i < width; i++)
                                s[2 * depth][offset + left + i] = b[i];

                            if (depth && is_left) {

                                for (int i = 0; i < width + right; i++)
                                    s[2 * depth - 1][offset + left + width/2 + i] = '-';

                                s[2 * depth - 1][offset + left + width/2] = '+';
                                s[2 * depth - 1][offset + left + width + right + width/2] = '+';

                            } else if (depth && !is_left) {

                                for (int i = 0; i < left + width; i++)
                                    s[2 * depth - 1][offset - width/2 + i] = '-';

                                s[2 * depth - 1][offset + left + width/2] = '+';
                                s[2 * depth - 1][offset - width/2 - 1] = '+';
                            }
                        #endif

                        return left + width + right;
                    }

                    int print_t(Node<ValueType> *tree)
                    {
                        char s[200][255];
                        for (int i = 0; i < chil(tree); i++)
                            sprintf(s[i], "%80s", " ");

                        _print_t(tree, 0, 0, 0, s);

                        for (int i = 0; i < chil(tree); i++)
                            printf("%s\n", s[i]);
                    }

                    void print_list()
                    { 
                        lldata.t_print();
                    }
            };
            RBT<ValueType> data;

            const ValueType make_blank(const Key_T kee, const Mapped_T mpt) const
            {
                return std::make_pair(kee, Mapped_T());   
            }

        public:
            Map(){}
            Map(const Map &){}
            Map &operator=(const Map & m)
            {
                if(m != *this)
                {
                    this->data = m.data;
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
            const Mapped_T &at(const Key_T & kee) const
            {
                //std::cout << "Looking for: " << kee << std::endl;
                ValueType r = data.find(kee);
                //std::cout << "Got: " << r.first << " " << r.second << std::endl;
                return Mapped_T(r.second);//std::move(r.second));
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
                    ValueType vi = make_pair(kee, Mapped_T());
                    data.addNode(vi);
                    ValueType& v = data.find(kee);
                    return v.second;
                }
            } 

            std::pair<IT, bool> 
            insert(std::initializer_list<Key_T> const& lis)
            {
                if(lis.size() != 2)
                {
                    //throw err
                }
                else
                {
                    data.addNode(std::make_pair(*(lis.begin()), *(lis.begin()+1)));
                }
                std::pair<IT, bool> ret = std::make_pair(find(*(lis.begin())), true);
                return ret;
            }

            std::pair<IT, bool> 
            insert(std::pair<Key_T, Mapped_T> const& lis)
            {
                data.addNode(std::make_pair(lis.first, lis.second));
                std::pair<IT, bool> ret = std::make_pair(find(lis.first), true);
                return ret;
            }
            
            template <typename IT_T>
            void insert(IT_T range_beg, IT_T range_end)
            {

            }

            void erase(IT pos)
            {

            }
            void erase(const Key_T & kee)
            {
                data.removeNode(std::make_pair(kee, Mapped_T()));
            }
            void clear()
            {
                while(data.size() != 0)
                {
                    erase(begin());
                }
            }

            void print()
            {
                //data.print_t(data.root);
                data.print_list();
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
