#include <iostream>
#include <string>
using namespace std;

struct data_node {
    float frequency;
    float wavelength;
    data_node* right;
    data_node* left;

    data_node(float frequency, float wavelength) {
        this->frequency = frequency;
        this->wavelength = wavelength;
        right = left = nullptr;
    }
};

struct year_node {
    int year;
    year_node* right;
    year_node* left;
    data_node* data_root;

    year_node(int year, float frequency, float wavelength) {
        this->year = year;
        right = left = nullptr;
        data_root = new data_node(frequency, wavelength);
    }
};


class bst_tree {
public:
    year_node* root;

    bst_tree() {
        root = nullptr;
    }

    data_node* insert_data(data_node* node, float frequency, float wavelength) {
        if (node == nullptr) {
            return new data_node(frequency, wavelength);
        }

        if (frequency < node->frequency) {
            node->left = insert_data(node->left, frequency, wavelength);
        }
        else if (frequency > node->frequency) {
            node->right = insert_data(node->right, frequency, wavelength);
        } else if (wavelength < node->wavelength) {
            node->left = insert_data(node->left, frequency, wavelength);
        } else {
            node->right = insert_data(node->right, frequency, wavelength);
        }

        return node;
    }

    year_node* insert(year_node* node, int year, float frequency, float wavelength) {
        if (node == nullptr) {
            return new year_node(year, frequency, wavelength);
        }

        if (year < node->year) {
            node->left = insert(node->left, year, frequency, wavelength);
        } else if (year > node->year) {
            node->right = insert(node->right, year, frequency, wavelength);
        } else {
            node->data_root = insert_data(node->data_root, frequency, wavelength);
        }
        return node;
    }

    void in_order_data(data_node* node) {
        if (node == nullptr) {
            return;
        }
        in_order_data(node->left);
        cout << "(" << node->frequency << "," << node->wavelength << ") ";
        in_order_data(node->right);
    }

    void in_order(year_node* node) {
        if (node == nullptr) {
            return;
        }
        in_order(node->left);
        cout << node->year << ": ";
        in_order_data(node->data_root);
        cout << endl;
        in_order(node->right);
    }

    void display_tree() {
        in_order(root);
    }
};

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int time_travels;
    cin >> time_travels;

    bool is_engine_working = true;

    bst_tree tree;

    while (time_travels--) {
        int year;
        float frequency, wavelength;
        cin >> year >> frequency >> wavelength;

        float sound_speed = frequency * wavelength / 100;

        if(frequency < 20 || frequency > 20000){
            continue;
        }

        if(sound_speed < 313 || sound_speed > 350){
            continue;
        }

        if(frequency < 275 || frequency > 325) {
            is_engine_working = false;
        }

        tree.root = tree.insert(tree.root, year, frequency, wavelength);
    }

    tree.display_tree();

    if(is_engine_working){
        cout << "TAK" << endl;
    } else {
        cout << "NIE" << endl;
    }

    return 0;
}
