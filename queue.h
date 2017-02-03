#ifndef queue_h
#define queue_h

// Node Class
template <class T> class TNode
{
 private:
   TNode *_Next,*_Prev ; // Previous and Next Nodes in the queue
   T _Item ;

 public:
   // Constructor and destructor
   TNode (T Item) ;
   TNode (T Item, TNode *Next, TNode *Prev) ;
   ~TNode () ;

   // Selectors
   T Item() { return _Item; }
   TNode *Next() { return _Next;}
   TNode *Prev() { return _Prev;}

} ;

template <class T> class TQueue
{
 private:
   TNode<T>  *_Head ; // A pointer pointing to the head node in the queue
   int  _NumOfElements ; // The current size of the queue

   TNode<T> *_CurrentNode ; // Pointer to the current node
   int _CurrentIndex ;   // Index of the current node

 public:
   // Constructors and Destructors
   TQueue() ;
   ~TQueue();

   // Selectors
   int Size() const { return _NumOfElements; }

   // Modifiers
   void Add(T Item); // Add a data item to thr tail of the queue
   void Delete();    // Remove the item at the head of the queue
   void Flush();     // Remove all items from the queue
   void ResetIterator() ;// Reset Iteration's pointer and index
   T operator[](int Index); // Retrieve the data item from the node at
                             // the specified index

};

#include "iostream.h"

// Create the first node of the list, and ensure that the list is circular
template <class T> TNode<T>::TNode ( T Item)
  : _Item(Item)
{
  _Next=_Prev=this;
}

// Create a new node containing the data item and inserts it between the
// previous and next nodes.
template <class T> TNode<T>::TNode (T Item,TNode *Next,TNode *Prev)
: _Next(Next),
  _Prev(Prev),
  _Item(Item)
{
 Prev->_Next=Next->_Prev=this;
}

// Delete the node and links the previous and next nodes
template <class T>TNode<T>::~TNode()
{
 _Prev->_Next=_Next;
 _Next->_Prev=_Prev;
}

// Create an empty queue
template <class T> TQueue<T>::TQueue()
: _Head(NULL),
  _NumOfElements(0),
  _CurrentNode(NULL),
  _CurrentIndex(0)
{}

// Destroy the queue
template <class T> TQueue<T>::~TQueue()
{
 Flush();
}

// Add an item to the queue
template <class T> void TQueue<T>::Add(T Item)
{
  if (_NumOfElements++>0)  // Check if the queue is currently empty
    {
     new TNode<T>(Item,_Head,_Head->Prev());
                           // Create a new node on the tail of the queue
    }
  else
    {
      _Head=new TNode<T> (Item) ; // Create the first node on the queue
    }
}

template <class T> void TQueue<T>::Delete ()
{
 TNode<T> *Ptr=_Head;
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

template <class T> void TQueue<T>::Flush()
{
  while (Size()) // Delete the head node until the queue is empty
   {
    Delete();
   }
}

template <class T> void TQueue<T>::ResetIterator()
{
 _CurrentNode=_Head ;
 _CurrentIndex=0 ;
}

template <class T> T TQueue<T>::operator[](int Index)
{
 cout<<"Yo" ;
 if (_CurrentIndex==Index)
   {
    return (_CurrentNode->Item()) ;
   }

 else if (_CurrentIndex>Index)
   {
    // the current position is greater than the required position
    // so move back along the list to the right place

    while (_CurrentIndex>Index)
      {
       _CurrentNode=_CurrentNode->Prev() ;
       _CurrentIndex-- ;
      }

    // now we are in the right place so return the item
    return (_CurrentNode->Item()) ;
   }

 else
   {
    // the current node is less than the required position
    // so move forwards to it

    while (_CurrentIndex<Index)
      {
       _CurrentNode=_CurrentNode->Next() ;
       _CurrentIndex++ ;
      }

    // now we are in the right place  return the item
    return (_CurrentNode->Item()) ;

   }
}

#endif
