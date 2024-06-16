#include <iostream>
#include <initializer_list>
#include <fstream>

using namespace std;
struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;
    Node(int v) : value(v), left(nullptr), right(nullptr), parent(nullptr) {}
};


class BSTree {
private:
    Node* root;
public:
    BSTree() : root(nullptr) {}
	
	
	//конструктор из initializer_list
	BSTree(initializer_list<int> list) {
    for (int value : list) {
        add_element(value);
    }
	}

//деструктор
	~BSTree() {
    clear(root);
	}
	
//добавление элемента
	bool add_element(int value) {
    if (root == nullptr) {
        root = new Node(value);
        return true;
    }
    Node* current = root;
    while (true) {
        if (value < current->value) {
            if (current->left == nullptr) {
                current->left = new Node(value);
                current->left->parent = current;
                return true;
            }
            current = current->left;
        }
        else if (value > current->value) {
            if (current->right == nullptr) {
                current->right = new Node(value);
                current->right->parent = current;
                return true;
            }
            current = current->right;
        }
        else {
            return false;
        }
    }
}
	bool delete_element(int value) {
    root = remove(value, root);
    return root != nullptr;
}
bool find_element(int value) {
    return find(value, root) != nullptr;
}
void print() {
    print(root);
    cout << endl;
}

void print(Node* node) const {
		if (node != nullptr) {
			print(node->left);
			cout << node->value << " ";
			print(node->right);
		}
	}

	Node* find(int value, Node* node) {
    if (node == nullptr || node->value == value) {
        return node;
    }
    if (value < node->value) {
        return find(value, node->left);
    }
    else {
        return find(value, node->right);
    }
}
	Node* findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
	Node*remove(int value, Node* node) {
    if (node == nullptr) return nullptr;
    if (value < node->value) {
        node->left = remove(value, node->left);
    }
    else if (value > node->value) {
        node->right = remove(value, node->right);
    }
    else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        Node* temp = findMin(node->right);
        node->value = temp->value;
        node->right = remove(temp->value, node->right);
    }
    return node;
}
	void clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}


	bool save_to_file(Node* node, ofstream& file) const {
		if (node != nullptr) {
			save_to_file(node->left, file);
			file << node->value << " ";
			save_to_file(node->right, file);
			return true;
		}
		return false;
	}
	bool load_from_file(Node* node, ifstream& file) {
		int value;
		if (file >> value) {
			node = new Node(value);
			load_from_file(node->left, file);
			load_from_file(node->right, file);
			return true;
		}
		return false;
	}

};


int main() {
	BSTree tree0;
	tree0.add_element(2);
	int i = 0;
	while(i < 26){
		tree0.add_element(rand()%100);
	}
	tree0.print();
	BSTree tree1 = {34, 2905, 17, 3, 59};
	tree1.delete_element(17);
	tree1.print();
	cout << tree1.find_element(34) << endl;
    return 0;
	}
