#include <iostream>
#include <string>
#include <vector>
#include <cmath>


// why this function?
// to do a binary search to find the leftmost idx of where points[i]>=query_point
// eg. points =[1, 3, 5,7], target =4, left_idx = 0 , right most idx = 1
int binarySearchLeft(const std::vector<double> points, double target){
    int left = 0;
    int right = points.size() - 1;
    int result = -1;
    while(left<=right){
        int mid = left + (right - left) / 2;
        if(points[mid]>=target){
            result = mid;
            right = mid - 1;
        }else{
            left = mid + 1;

        }
    }
    return result;
}

int binarySearchRight(const std::vector<double> points, double target){
    int left = 0;
    int right = points.size() - 1;
    int result = -1;
    while(left<=right){
        int mid = left + (right - left) /2;
        if(points[mid]<=target){
            result = mid;
            left = mid + 1;
    }else{
            right = mid - 1;
        }
    }
    return result;
}

int query(const std::vector<double> &points, double query_point, double d){
    if (points.empty()){
        return 0;
    }

    double left_bound = query_point - d;
    double right_bound = query_point + d;

    // find boundaries
    int left_idx = binarySearchLeft(points, left_bound);
    int right_idx = binarySearchRight(points, right_bound);
    
    // this is if points exist in the range
    // for eg. points = [1,3,5,7], query_point = 4, d=0.5

    if(left_idx == -1 || right_idx == -1 || left_idx > right_idx){
        return 0;
    }

    return right_idx - left_idx + 1;
}

int query_and(const std::vector<double> points, double querypoint1, double querypoint2, double d){
    if (points.empty()){
        return 0;
    }

    double left_bound = std::max(querypoint1 -d, querypoint2 -d);
    double right_bound = std::min(querypoint1+1, querypoint2 +d);

    int left_idx = binarySearchLeft(points, left_bound);
    int right_idx = binarySearchRight(points, right_bound);
    if(left_idx == -1 || right_idx == -1 || left_idx > right_idx){
        return 0;
    }
    return right_idx - left_idx + 1;

}
//Uses the set theory formula: |A ∪ B| = |A| + |B| - |A ∩ B|
int query_or(const std::vector<double> points, double querypoint1, double querypoint2, double d){
    if (points.empty()){
        return 0;
    }

    int count1 = query(points, querypoint1, d);
    int count2 = query(points, querypoint2, d);
    int count_and = query_and(points, querypoint1, querypoint2, d);

    return count1 + count2 - count_and;
}