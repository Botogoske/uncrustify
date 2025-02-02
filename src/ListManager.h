/**
 * @file ListManager.h
 * Template class that manages items in a double-linked list.
 * If C++ could do it, this would just be a class that worked on an interface.
 *
 * @author  Ben Gardner
 * @license GPL v2+
 */

#ifndef LIST_MANAGER_H_INCLUDED
#define LIST_MANAGER_H_INCLUDED

/*
 * TODO: why do we provide this template class? can't we use
 * a double linked list std::deque from the standard library ?
 */
/**
 * A simple list manager for a double-linked list.
 * Class T must define 'next' and 'prev', which must be pointers to type T.
 */
template<class T>
class ListManager
{
protected:
   T *first; //! pointer to the head of list
   T *last;  //! pointer to tail of list

private:
   // Hide copy constructor
   ListManager(const ListManager &ref)
   {
      first = nullptr;
      last  = nullptr;
   }

public:
   ListManager()
   {
      first = nullptr;
      last  = nullptr;
   }


   /**
    * @brief return the first element of the linked list
    *
    * @return pointer to first element or nullptr if list is empty
    */
   T *GetHead() const
   {
      return(first);
   }


   /**
    * @brief return the last element of the linked list
    *
    * @return pointer to last element or nullptr if list is empty
    */
   T *GetTail() const
   {
      return(last);
   }


   /**
    *  @brief return the next element of the linked list
    *
    * @param[in] ref  pointer to current list element
    *
    * @return pointer to next element or nullptr if no next element exists
    */
   T *GetNext(const T *ref) const
   {
      return((ref != nullptr) ? ref->next : nullptr);
   }


   /**
    * @brief return the previous element of the linked list
    *
    * @param[in] ref  pointer to current list element
    *
    * @return pointer to previous element or nullptr if no previous element exists
    */
   T *GetPrev(const T *ref) const
   {
      return((ref != nullptr) ? ref->prev : nullptr);
   }


   /**
    * @brief remove an element from a linked list
    *
    * @param[in] obj  list element to remove
    */
   void Pop(T *obj)
   {
      if (obj != nullptr)
      {
         if (first == obj)
         {
            first = obj->next;
         }

         if (last == obj)
         {
            last = obj->prev;
         }

         if (obj->next != nullptr)
         {
            obj->next->prev = obj->prev;
         }

         if (obj->prev != nullptr)
         {
            obj->prev->next = obj->next;
         }
         obj->next = nullptr;
         obj->prev = nullptr;
      }
   }


   //! swap two elements of a list
   void Swap(T *obj1, T *obj2)
   {
      if (  obj1 != nullptr
         && obj2 != nullptr)
      {
         if (obj1->prev == obj2)
         {
            Pop(obj1);
            AddBefore(obj1, obj2);
         }
         else if (obj2->prev == obj1)
         {
            Pop(obj2);
            AddBefore(obj2, obj1);
         }
         else
         {
            T *prev1 = obj1->prev;
            Pop(obj1);

            T *prev2 = obj2->prev;
            Pop(obj2);

            AddAfter(obj1, prev2);
            AddAfter(obj2, prev1);
         }
      }
   }


   /**
    * @brief add a new element after a reference position in a list
    *
    * @param obj  new element to add to list
    * @param ref  chunk after which to insert new object
    */
   void AddAfter(T *obj, T *ref)
   {
      if (  obj != nullptr
         && ref != nullptr)
      {
         Pop(obj); // TODO: is this necessary?
         obj->next = ref->next;
         obj->prev = ref;

         if (ref->next != nullptr)
         {
            ref->next->prev = obj;
         }
         else
         {
            last = obj;
         }
         ref->next = obj;
      }
   }


   /**
    * @brief add a new element before a reference position in a list
    *
    * @param obj  new element to add to list
    * @param ref  chunk before to insert new object
    */
   void AddBefore(T *obj, T *ref)
   {
      if (  obj != nullptr
         && ref != nullptr)
      {
         Pop(obj);
         obj->next = ref;
         obj->prev = ref->prev;

         if (ref->prev != nullptr)
         {
            ref->prev->next = obj;
         }
         else
         {
            first = obj;
         }
         ref->prev = obj;
      }
   }


   /**
    * @brief add a new element to the tail of a lis
    *
    * @param obj  new element to add to the list
    */
   void AddTail(T *obj)
   {
      obj->next = nullptr;
      obj->prev = last;

      if (last == nullptr)
      {
         last  = obj;
         first = obj;
      }
      else
      {
         last->next = obj;
      }
      last = obj;
   }


   /**
    * @brief add a new element to the head of a list
    *
    * @param obj  new element to add to the list
    */
   void AddHead(T *obj)
   {
      obj->next = first;
      obj->prev = nullptr;

      if (first == nullptr)
      {
         last  = obj;
         first = obj;
      }
      else
      {
         first->prev = obj;
      }
      first = obj;
   }
};


#endif /* LIST_MANAGER_H_INCLUDED */
