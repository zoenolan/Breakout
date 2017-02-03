#ifndef pqueue_h
#define pqueue_h

// Node Class
template <class T> class TPointerNode
{
 private:
   TPointerNode *_Next,*_Prev ; // Previous and Next Nodes in the queue
   T *_Item ;

 public:
   // Constructor and destructor
   TPointerNode (T *Item) ;
   TPointerNode (T *Item, TPointerNode *Next, TPointerNode *Prev) ;
   ~TPointerNode () ;

   // Selectors
   T* Item() { return _Item; }
   TPointerNode *Next() { return _Next;}
   TPointerNode *Prev() { return _Prev;}

} ;

template <class T> class TPointerQueue
{
 private:

   TPointerNode<T>  *_Head ;
                         // A pointer pointing to the head node in the queue
   int  _NumOfElements ; // The current size of the queue

 public:
   // Constructors and Destructors
   TPointerQueue(void) ;
   TPointerQueue(TPointerQueue<T> &Queue);
   ~TPointerQueue();

   void operator=(TPointerQueue &Queue) ;

   // Selectors
   int Size() const { return _NumOfElements; }

   // Modifiers
   void Add(T *Item); // Add a data item to thr tail of the queue
   void Delete();    // Remove the item at the head of the queue
   void Flush();     // Remove all items from the queue
   void ResetIterator() ;// Reset Iteration's pointer and index
   T * operator[](int Index)const ;
                          // Retrieve the data item from the node at
                          // the specified index

} ;

// Create the first node of the list, and ensure that the list is circular
template <class T> TPointerNode<T>::TPointerNode ( T *Item)
  : _Item(Item)
{
  _Next=_Prev=this;
}

// Create a new node containing the data item and inserts it between the
// previous and next nodes.
template <class T> TPointerNode<T>::TPointerNode (T *Item,TPointerNode *Next,
                                                  TPointerNode *Prev)
: _Next(Next),
  _Prev(Prev),
  _Item(Item)
{
 Prev->_Next=Next->_Prev=this;
}

// Delete the node and links the previous and next nodes
template <class T>TPointerNode<T>::~TPointerNode()
{
 delete (_Item);
 _Prev->_Next=_Next;
 _Next->_Prev=_Prev;
}

// Create an empty queue
template <class T> TPointerQueue<T>::TPointerQueue(void)
: _Head(NULL),
  _NumOfElements(0)
{}

// Destroy the queue
template <class T> TPointerQueue<T>::~TPointerQueue()
{
 Flush();
}

// Add an item to the queue
template <class T> void TPointerQueue<T>::Add(T *Item)
{
  if (_NumOfElements++>0)  // Check if the queue is currently empty
    {
     new TPointerNode<T>(Item,_Head,_Head->Prev());
                           // Create a new node on the tail of the queue
    }
  else
    {
     _Head=new TPointerNode<T> (Item) ; // Create the first node on the queue
    }
}

template <class T> void TPointerQueue<T>::Delete ()
{
 TPointerNode<T> *Ptr=_Head;
 if ( _Head != NULL)
   {
    if (--_NumOfElements >0) // Check if the queue contains one item
      {
       _Head=_Head->Next() ; // The Head of the queue moves to the next node
      }
    else
      {
       _Head=NULL ;
      }

    delete Ptr; // Delete the node

   }
}

template <class T> void TPointerQueue<T>::Flush()
{
  while (Size()) // Delete the head node until the queue is empty
   {
    Delete();
   }
}

template <class T> void TPointerQueue<T>::ResetIterator()
{
 _CurrentNode=_Head ;
 _CurrentIndex=0 ;
}

template <class T> T* TPointerQueue<T>::operator[](int Index) const
{
 TPointerNode<T> * CurrentNode=_Head ;
 int CurrentIndex=0 ;

 while (CurrentIndex<Index)
   {
    CurrentNode=CurrentNode->Next() ;
    CurrentIndex++ ;
   }

 // now we are in the right place  return the item
 return (CurrentNode->Item()) ;
}

template <class T> TPointerQueue<T>::TPointerQueue(TPointerQueue<T> &Queue)
{
 // copy the queue across
  int counter ;

 (*this).Flush() ;

 for (counter=0;counter<Queue.Size();counter++)
   {
    (*this).Add(Queue[counter]) ;
   }
}

template <class T> void TPointerQueue<T>::operator=(TPointerQueue<T> &Queue)
{
 int counter ;

 (*this).Flush() ;

 for (counter=0;counter<Queue.Size();counter++)
   {
    (*this).Add(Queue[counter]) ;
   }
}
#endif
