#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <math.h>



using namespace std;

int get_left_childIdx(int i);
int get_right_childIdx(int i);
int get_parentIdx(int i);
void swap(vector<pair<int, double>>& heap_vector, int index1, int index2);
int get_minIdx_two_child(vector<pair<int, double>>& heap_vector, int parentIdx, int leftIdx, int rightIdx);
int get_minIdx_one_child(vector<pair<int, double>>& heap_vector, int parentIdx, int leftIdx);
void min_heapify(vector<pair<int, double>>& heap_vector, int i);
//internal function(only to be called after heap is built)
void bubble_down(vector<pair<int, double>>& heap_vector, int i);
//internal function(only to be called after heap is built)
void bubble_up(vector<pair<int, double>>& heap_vector, int child_i);
void remove_element(vector<pair<int, double>>& heap_vector, int i); //pass in the index
void insert_element(vector<pair<int, double>>& heap_vector, pair<int, double> new_element);
void build_heap(vector<pair<int, double>>& heap_vector);
void print_heap(vector<pair<int, double>>& heap_vector);

double minimum_distance(vector<int> x, vector<int> y);

unordered_map<int, int> vertex_positions;
vector<bool> set_x;
vector<pair<int, double>> heap_vector;



double minimum_distance(vector<int> x, vector<int> y) {
    double result = 0.;
    // your code here
    size_t num_points = x.size();
    set_x.reserve(num_points);
    vertex_positions.reserve(num_points);
    for (size_t i = 0; i < num_points; i++) {
        set_x.push_back(false);
    }
    heap_vector.reserve(num_points);
    //since the heap vector does not contain any values in the beginning, we can start by inserting elements(instead of using the build_heap method)
    heap_vector.push_back(make_pair(0, 0));
    pair<int, double> temp_extracted_node;
    double temp_dist;
    double temp_x1;
    double temp_x2;
    double temp_y1;
    double temp_y2;
    unordered_map<int, int>::iterator itr;
    int temp_neighbour_position;
    pair<int, double> temp_neighbor_node;

    while (!heap_vector.empty()) {
        temp_extracted_node = heap_vector[0];
        result += temp_extracted_node.second;
        remove_element(heap_vector, 0);
        set_x[temp_extracted_node.first] = true;
        //add in all the extracted nodes neighbours to the heap. if the neighbour is already preset, update it's key if needed
        for (size_t i = 0; i < num_points; i++) {
            if (set_x[i] == false) {
                temp_x1 = x[temp_extracted_node.first];
                temp_y1 = y[temp_extracted_node.first];
                temp_x2 = x[i]; //neighbor x co-ordinate
                temp_y2 = y[i]; //neighbor y co-ordinate
                temp_dist = sqrt((pow(temp_x1- temp_x2, 2)) + (pow(temp_y1 - temp_y2, 2)));
                itr = vertex_positions.find(i);
                if (itr != vertex_positions.end()) { //neighbour already exists in the heap
                    temp_neighbour_position = vertex_positions[i];
                    temp_neighbor_node = heap_vector[temp_neighbour_position];
                    if (temp_dist < temp_neighbor_node.second) {
                        remove_element(heap_vector, temp_neighbour_position);
                        insert_element(heap_vector, make_pair(i, temp_dist));
                    }
                }
                else { //neighbour doesn't exist in the heap :: insert a new element
                    insert_element(heap_vector, make_pair(i, temp_dist));
                }
            }
        }

    }

    set_x.clear();
    vertex_positions.clear();

    return result;
}


int main() {
    size_t n;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;

    return 0;
}




int get_left_childIdx(int i) {
    return i * 2 + 1;
}

int get_right_childIdx(int i) {
    return i * 2 + 2;
}

int get_parentIdx(int i) {
    return (i - 1) / 2;
    //return floor((i + 1) / 2) - 1;
}


void swap(vector<pair<int, double>>& heap_vector, int index1, int index2) {
    pair<int, double> temp = heap_vector[index1];
    heap_vector[index1] = heap_vector[index2];
    heap_vector[index2] = temp;
    //update the positions
    vertex_positions[heap_vector[index1].first] = index1;
    vertex_positions[heap_vector[index2].first] = index2;
}

int get_minIdx_two_child(vector<pair<int, double>>& heap_vector, int parentIdx, int leftIdx, int rightIdx) {

    int min_idx;
    if (heap_vector[leftIdx].second < heap_vector[parentIdx].second) {

        min_idx = leftIdx;

        if (heap_vector[leftIdx].second < heap_vector[rightIdx].second) {
            min_idx = leftIdx;
        }
        else if (heap_vector[leftIdx].second > heap_vector[rightIdx].second) {
            min_idx = rightIdx;
        }
        else {
            min_idx = leftIdx;
        }

    }
    else if (heap_vector[leftIdx].second > heap_vector[parentIdx].second) {

        min_idx = parentIdx;

        if (heap_vector[parentIdx].second < heap_vector[rightIdx].second) {
            min_idx = parentIdx;
        }
        else if (heap_vector[parentIdx].second > heap_vector[rightIdx].second) {
            min_idx = rightIdx;
        }
        else {
            min_idx = parentIdx;
        }

    }
    else { // element at left and parent positions are equal

        min_idx = parentIdx;

        if (heap_vector[parentIdx].second < heap_vector[rightIdx].second) {
            min_idx = parentIdx;
        }
        else if (heap_vector[parentIdx].second > heap_vector[rightIdx].second) {
            min_idx = rightIdx;
        }
        else {
            min_idx = parentIdx;
        }

    }

    return min_idx;
}

int get_minIdx_one_child(vector<pair<int, double>>& heap_vector, int parentIdx, int leftIdx) {

    int minIdx;
    if (heap_vector[leftIdx].second < heap_vector[parentIdx].second) {
        minIdx = leftIdx;
    }
    else if (heap_vector[leftIdx].second > heap_vector[parentIdx].second) {
        minIdx = parentIdx;
    }
    else {
        minIdx = parentIdx;
    }

    return minIdx;
}

void min_heapify(vector<pair<int, double>>& heap_vector, int i) {
    int last_i = heap_vector.size() - 1;

    int left_i = get_left_childIdx(i);
    int right_i = get_right_childIdx(i);

    int  min_i;

    if (left_i <= last_i && right_i <= last_i) {    // it's got both it's children
        vertex_positions[heap_vector[i].first] = i;
        vertex_positions[heap_vector[left_i].first] = left_i;
        vertex_positions[heap_vector[right_i].first] = right_i;
        min_i = get_minIdx_two_child(heap_vector, i, left_i, right_i);
        if (min_i != i) {
            swap(heap_vector, i, min_i);
            bubble_down(heap_vector, min_i);
        }

    }
    else if (left_i <= last_i && right_i > last_i) { //it's only got a left child
        vertex_positions[heap_vector[i].first] = i;
        vertex_positions[heap_vector[left_i].first] = left_i;
        min_i = get_minIdx_one_child(heap_vector, i, left_i);
        if (min_i != i) {
            swap(heap_vector, i, min_i);
            bubble_down(heap_vector, min_i);
        }

    }
    else { //it's a leaf node
        vertex_positions[heap_vector[i].first] = i;
    }

}

void bubble_down(vector<pair<int, double>>& heap_vector, int i) {
    int last_i = heap_vector.size() - 1;

    int left_i = get_left_childIdx(i);
    int right_i = get_right_childIdx(i);

    int min_i;

    if (left_i <= last_i && right_i <= last_i) { //it has got both its children
        min_i = get_minIdx_two_child(heap_vector, i, left_i, right_i);
        if (min_i != i) {
            swap(heap_vector, i, min_i);
            bubble_down(heap_vector, min_i);
        }
    }
    else if (left_i <= last_i && right_i > last_i) { //it has got the left child only
        min_i = get_minIdx_one_child(heap_vector, i, left_i);
        if (min_i != i) {
            swap(heap_vector, i, min_i);
            bubble_down(heap_vector, min_i);
        }
    }
    else { //it is a leaf node
        //do nothing
    }

}


void bubble_up(vector<pair<int, double>>& heap_vector, int child_i) {
    int last_i = heap_vector.size() - 1;

    int parent_i;
    int left_i;
    int right_i;

    int min_i;

    if (child_i > 0) {
        parent_i = get_parentIdx(child_i);
        left_i = get_left_childIdx(parent_i);
        right_i = get_right_childIdx(parent_i);

        if (left_i <= last_i && right_i <= last_i) { //two child case
            min_i = get_minIdx_two_child(heap_vector, parent_i, left_i, right_i);
            if (min_i != parent_i) {
                swap(heap_vector, parent_i, min_i);
                bubble_up(heap_vector, parent_i);
            }

        }
        else if (left_i <= last_i && right_i > last_i) { //one child case
            min_i = get_minIdx_one_child(heap_vector, parent_i, left_i);
            if (min_i != parent_i) {
                swap(heap_vector, parent_i, min_i);
                bubble_up(heap_vector, parent_i);
            }
        }
        else {
            // this condition won't exist: since child_i > 0, there will be at least one child
        }

    }
}


void remove_element(vector<pair<int, double>>& heap_vector, int i) {
    int last_i = heap_vector.size() - 1;

    int parent_i;

    if (i == 0) {
        swap(heap_vector, 0, last_i);
        //remove the last element position
        vertex_positions.erase(heap_vector[last_i].first);
        heap_vector.pop_back();
        last_i--;
        bubble_down(heap_vector, 0);
    }
    else if (i == last_i) {
        //remove the last element position
        vertex_positions.erase(heap_vector[last_i].first);
        heap_vector.pop_back();
        last_i--;
    }
    else {
        swap(heap_vector, i, last_i);
        //remove the last element position
        vertex_positions.erase(heap_vector[last_i].first);
        heap_vector.pop_back();
        last_i--;
        parent_i = get_parentIdx(i);

        if (heap_vector[i] > heap_vector[parent_i]) {
            bubble_down(heap_vector, i);
        }
        else {
            bubble_up(heap_vector, i);
        }

    }
}


void insert_element(vector<pair<int, double>>& heap_vector, pair<int, double> new_element) {
    heap_vector.push_back(new_element);
    vertex_positions[new_element.first] = heap_vector.size() - 1;
    int last_i = heap_vector.size() - 1;
    bubble_up(heap_vector, last_i);
}


void build_heap(vector<pair<int, double>>& heap_vector) {
    int lim = (heap_vector.size() / 2) - 1;
    for (int i = lim; i >= 0; i--) {
        min_heapify(heap_vector, i);
    }
}

void print_heap(vector<pair<int, double>>& heap_vector) {
    int heap_vector_size = heap_vector.size();
    for (int i = 0; i < heap_vector_size; i++) {
        cout << heap_vector[i].first << " : " << heap_vector[i].second << endl;
    }
}
