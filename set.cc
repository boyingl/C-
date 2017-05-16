#include "intSet.h"
#include <iostream>
  
intSet::intSet(): size{0}, capacity{0}{}


intSet::intSet(const intSet& is):size{is.size}, capacity{is.capacity}{
  data = (is.data)? new int[capacity] : nullptr;
  if(data){
    for(int i = 0; i < size; i++)  *(data + i) = *(is.data + i);
  }
}


intSet::intSet(intSet &&is):data{is.data}, size{is.size}, capacity{is.capacity}{
  is.data = nullptr;
}


intSet::~intSet(){ //data has to heap allocated
  if(capacity != 0) delete [] data;
}


intSet & intSet::operator=(const intSet& is){
  intSet temp = intSet(is);
  swap(temp);
  return *this;
}


intSet & intSet::operator=(intSet &&is){
  swap(is);
  return *this;
}


void intSet::swap(intSet &is){
  int* tmpData = is.data;
  int tmpSize = is.size;
  int tmpCapacity = is.capacity;
  is.data = this->data;
  is.size = this->size;
  is.capacity = this->capacity;
  this->data = tmpData;
  this->size = tmpSize;
  this->capacity = tmpCapacity;
  return;
}


intSet intSet::operator|(const intSet &other){

  int shortSize = (size < other.size)? size : other.size;
  const intSet* pShortSet = (size < other.size)? this: &other;
  const intSet* pLongSet = (size < other.size)? &other: this;

  intSet setUnion = *pLongSet;

  //each element in the short set that is not in long, is in union
  for(int i = 0; i < shortSize; i++){
    int element = *(pShortSet->data +i);
    if(! (pLongSet->contains(element)))  setUnion.add(element);
  }
  return setUnion;  
}


intSet intSet::operator&(const intSet &other){
  intSet intersect {};
  
  int shortSize = (size < other.size)? size : other.size;
  const intSet* pShortSet = (size < other.size)? this: &other;
  const intSet* pLongSet = (size < other.size)? &other: this;
  //for each element in the short set that is also in long set is in intersect
  for(int i = 0; i < shortSize; i++){
    int element = *(pShortSet->data +i);
    if(pLongSet->contains(element))  intersect.add(element);
  }
  return intersect;
}


bool intSet::operator==(const intSet &other){
  if(size != other.size) return false;

  //sets are already in sorted order
  for(int i = 0; i < size; i++){
    if(*(data +i) != *(other.data +i) ) return false;
  }

  return true;
}


bool intSet::isSubset(const intSet &s){
  return (((*this) & s) == s);
}


bool intSet::contains(int e) const {
  for(int i = 0; i < size; i ++){
    if(*(data +i) == e) return true;
  }
  return false;
}


//insert e if e does not exist and maintain ascending order of the set
void intSet::add(int e){

  if(size == 0){
    capacity = 5;
    data = new int[capacity];
    *data = e;
    size ++;
    return;
  }

  int index = size;

  //get the index e should be inserted at, or return size+1 if e exists
  for(int i = 0; i < size; i++){
    if(*(data + i) == e){
      index = size + 1;
      break;
    }

    else if(*(data + i) > e){
      index = i;
      break;
    }  
  }

  //e exist
  if(index == size +1) return; 
 
  if(0 == size)  capacity = 5; 
  else if(capacity == size)  capacity *= 2;
  
  int* temp = new int[capacity];

  //insert e at index
  *(temp +index) = e;
  //copy original set to temp
  for(int i = 0; i < size; i++) {
    if(i < index) *(temp + i) = *(data +i);
    else *(temp +i + 1) = *(data + i);
  }

  delete [] data;
  data = temp;

  size ++;
  return;
}


//remove e if e exist and maintain ascending order of the set
void intSet::remove(int e){

  bool deleted = false;
  for(int i = 0; i < size; i ++){
    if(*(data +i) == e){
      deleted = true;
      //move every element after index forward 
      for(int j = i; j < size-1; j++){
        *(data +j) = *(data +j +1);
      }
      break;
    }
  }
  
  if(deleted) size --;
  return;
}


std::ostream& operator<<(std::ostream& out, const intSet& is){
  out << "(";

  if(is.size != 0)  out << *(is.data);

  for(int i = 1; i < is.size; i++){
    out <<"," << *(is.data +i);
  }

  out << ")"; 
  return out;
}
