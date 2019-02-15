/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* curr;
  ListNode* temp;
  curr = head_;
  while(curr != NULL){
    temp = curr;
    curr = curr->next;
    delete temp;
  }
  head_ = NULL;
  tail_ = NULL;
  temp = NULL;
  length_= 0;

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* temp = new ListNode(ndata);
  if(length_ == 0){
    head_ = temp;
    tail_ = temp;
    length_++;
  }
  else{
    temp->next = head_;
    head_->prev = temp;
    head_ = head_->prev;
    length_++;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* temp = new ListNode(ndata);
  if(length_ == 0){
    head_ = temp;
    tail_ = temp;
    length_++;
  }
  else{
    tail_->next = temp;
    temp->prev = tail_;
    tail_ = tail_->next;
    length_++;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  if(startPoint == endPoint){
    return;
  }

  ListNode* curr, *temp, *leftend, *rightend, *start, *end;
  leftend = startPoint->prev;
  rightend = endPoint->next;
  start = startPoint;
  end = endPoint;

  curr = startPoint;
  temp = NULL;

  while(curr != endPoint){
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  }
  //now curr == end;
  curr->next = curr->prev;
  curr->prev = leftend;
  startPoint->next = rightend;
  //endPoint->prev = leftend;
  if(leftend != NULL){
    leftend->next = endPoint;
  }
  else{
    head_ = endPoint;
  }

  if(rightend != NULL){
    rightend->prev = startPoint;
  }
  else{
    tail_ = startPoint;
  }


  startPoint = end;
  endPoint = start;

  return;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1

  if(n <= 1 || head_ == NULL){return;}

  ListNode *blockstart, *blockend;
  blockstart = head_;
  blockend = head_;

  while(blockstart != NULL){

    blockend = blockstart;
    for(int i = 0; i < n - 1; i++){
      if(blockend->next != NULL){
        blockend = blockend->next;
      }
    }

    reverse(blockstart, blockend);

    blockstart = blockend->next;
  }


}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if(head_ == NULL){return;}
  ListNode* curr, *temp;
  int count = 1;
  curr = head_;
  while(curr != tail_ && curr != NULL){
    if(count % 2 == 0){
      curr->prev->next = curr->next;
      temp = curr;
      curr = curr->next;
      temp->next = NULL;
      //length_--;
      //insertBack(temp);
      tail_->next = temp;
      temp->prev = tail_;
      tail_ = tail_->next;
    }
    else{ //do nothing
      curr = curr->next;
    }
    count++;
  }
  return;
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if(splitPoint == 0){
    return start;
  }
  ListNode* temp;
  ListNode* second = start;
  for(int i = 1; i <= splitPoint; i++){ //splitPoint is the number of steps to walk before splitting
    temp = second;
    second = second->next;
  }
  temp->next = NULL;
  return second;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first == NULL){return second;}
  if(second == NULL){return first;}
  if(first == NULL && second == NULL){return NULL;}
  ListNode* temp, *curr_first, *curr_second, *first_next, *second_next;

  //choose head to be first
  if(second->data < first->data){
    temp = second;
    second = first;
    first = temp;
    if(first != NULL){
      first->prev = NULL;
    }
  }

  curr_first = first;
  curr_second = second;

  while (curr_second != NULL){  //insert every second into first
    second_next = curr_second->next;

    while (curr_first != NULL){
      first_next = curr_first->next;
      if (curr_second->data < curr_first->data){
        //insert before curr_first
        curr_second->next = curr_first;
        curr_first->prev->next = curr_second;
        curr_second->prev = curr_first->prev;
        curr_first->prev = curr_second;

        break;
      }
      else if (first_next == NULL && curr_second != NULL){ //first reaches the end but second still has nodes
          curr_first->next = curr_second;
          curr_second->prev = curr_first;
          break;
      }
      else{
        curr_first = first_next;
      }
    }

    if (curr_first->next == curr_second && curr_second->prev == curr_first) {break;}
    curr_second = second_next;
  }
  return first;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 1){
    start->prev = NULL;
    start->next = NULL;
    return start;
  }
  else{
    int breakpoint;
    breakpoint = int(chainLength / 2);
    ListNode* temp = start;
    for(int i = 1; i <= breakpoint; i++){
      temp = temp->next;
    }
    if (temp != NULL){  //separate the lists
      temp->prev->next = NULL;
      temp->prev = NULL;
    }
    start = mergesort(start, breakpoint);
    temp = mergesort(temp, chainLength - breakpoint);
    start = merge(start, temp);
    return start;
  }

}


//another merge algorithm but has too long runtime

/*  ListNode* first_curr, *second_curr, *head_node, *temp_second, *temp_first, *second_save;
  head_node = first;
  //check if elements in second need to be inserted before first
  if(second->data < first->data){
    second_curr = second;
    while(second_curr != NULL){
      if(first->data < second_curr->data){break;}
      temp_second = second_curr; //temp_second is one node before second_curr
      second_curr = second_curr->next;
    }
    //insert to front
    temp_second->next = first;
    first->prev = temp_second;
    head_node = second;
    second = second_curr;
  }

  //insert second to first
  first_curr = first;
  second_curr = second;
  while(second_curr != NULL){
    second_save = second_curr->next;  //next might be changed in the for loop
    for(temp_first = first; temp_first->next != NULL; temp_first = temp_first->next){
      if(temp_first->data < second_curr->data && second_curr->data < temp_first->next->data){
        second = second_curr->next; //marks how many nodes in second left
        second_curr->prev = temp_first;
        second_curr->next = temp_first->next;
        temp_first->next->prev = second_curr;
        temp_first->next = second_curr;
      }
    }
    second_curr = second_save;
  }

  //insert at end
  if(second != NULL){
    ListNode* tail_node = head_node;
    while(tail_node->next != NULL){tail_node = tail_node->next;}
    tail_node->next = second;
    second->prev = tail_node;
  }
  return head_node;
  */
