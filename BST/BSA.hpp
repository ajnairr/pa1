/**
 * Implementation of a binary search array.
 * 
 * Name: Ajay Nair
 * Email: ajnair@ucsd.edu
 * Sources of Help: Piazza
 */
#ifndef BSA_HPP
#define BSA_HPP

#include <vector>
using namespace std;

template<typename Data>

/** This class implements a binary search array */
class BSA {
    
    private:
        vector<Data> v;

        /** Helper method used to either find an element if it exists
         * or else find where it should be inserted.
         */
        virtual size_t binarySearch(const Data& item) const {
            long long leftEnd = 0;
            long long rightEnd = this->v.size() - 1;
            long long mid;
            while(leftEnd <= rightEnd) {
               mid = (leftEnd + rightEnd) / 2;
               if(this->v[mid] < item) {
                  leftEnd = mid + 1;
               }
               else if(item < this->v[mid]) {
                  rightEnd = mid - 1;
               }
               else {
                  return (size_t)mid;
               }
            }
            return (size_t)leftEnd;
        }

    public:
        /** Return the position of item, otherwise v.cend() */
        virtual typename vector<Data>::const_iterator
                         find(const Data& item) const {
            if(this->v.empty()) {
               return this->v.cend();
            }
            typename vector<Data>::const_iterator it = this->v.cbegin() +
                                                       this->binarySearch(item);
            if(*it < item || item < *it) {
               return this->v.cend();
            }
            return it;
        }

        /** Insert item into sorted position */
        virtual bool insert(const Data& item) {
            if(this->v.empty()) {
               this->v.push_back(item);
               return true;
            }
            typename vector<Data>::iterator it = this->v.begin() +
                                                 this->binarySearch(item);

            if(*it < item || item < *it) {
               this->v.insert(it, item);
               return true;
            }
            return false;
        }

        typename vector<Data>::iterator begin() {
            return this->v.begin();
        }

        typename vector<Data>::iterator end() {
            return this->v.end();
        }
};

#endif
