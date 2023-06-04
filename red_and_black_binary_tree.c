/*
Rules That Every Red-Black Tree Follows: 
1. Every node has a color either red or black.
2. The root of the tree is always black.
3. There are no two adjacent red nodes (A red node cannot have a red parent or red child).
4. Every path from a node (including root) to any of its descendants NULL nodes has the same number of black nodes.
5. Every leaf (e.i. NULL node) must be colored BLACK.
*/

#include <stdio.h>
#include <stdlib.h>

// Color handling
// black = 0
// red = 1
enum node_color{
    black,
    red
};

// Structure for nodes in rbt
typedef struct Node
{
    int data;
    enum node_color color;
    struct Node* parent;
    struct Node* left_child;
    struct Node* right_child;
} Node;

Node* root = NULL;

Node* new_node(int data)
{
    Node* node = malloc(sizeof(Node));
    if (node == NULL)
        exit(1);
    
    node -> data = data;
    node -> parent = NULL;
    node -> left_child = NULL;
    node -> right_child = NULL;
    node -> color = red;
    return node;
}

// Insert function for rbt.
Node* insert(Node* traverse_node, Node* node)
{
    // If tree is empty,
    // new_node is new root of the tree.
    if (traverse_node == NULL)
        return node;

    // New data is smaller, move to the left child.
    if (node -> data < traverse_node -> data)
    {
        traverse_node -> left_child = insert(traverse_node -> left_child, node);
        traverse_node -> left_child -> parent = traverse_node;
    }

    // New data is larger, move to the right child.
    else if (node -> data > traverse_node -> data)
    {
        traverse_node -> right_child = insert(traverse_node -> right_child, node);
        traverse_node -> right_child -> parent = traverse_node;
    }

    return traverse_node;
}

// Function for right rotation.
void right_rotation(Node* node)
{
    Node* left = node -> left_child;
    node -> left_child = left -> right_child;
    if (node -> left_child)
        node -> left_child -> parent = node;
    left -> parent = node -> parent;
    if (!node -> parent)
        root = left;
    else if (node == node -> parent -> left_child)
        node -> parent -> left_child = left;
    else
        node -> parent -> right_child = left;
    left -> right_child = node;
    node -> parent = left;
}

// Function for left rotation.
void left_rotation(Node* node)
{
    Node* right = node -> right_child;
    node -> right_child = right -> left_child;
    if (node -> right_child)
        node -> right_child -> parent = node;
    right -> parent = node -> parent;
    if (!node -> parent)
        root = right;
    else if (node == node -> parent -> left_child)
        node -> parent -> left_child = right;
    else
        node -> parent -> right_child = right;
    right -> left_child = node;
    node -> parent = right;
}

// Function to fix violations that arouse because of the insertion.
void fix_tree_after_insertion(Node* root, Node* node)
{
    Node* parent_of_node = NULL;
    Node* grand_parent_of_node = NULL;
    Node* uncle_of_node = NULL;
    enum node_color temp = red;

    while ((node != root) && (node -> color != black)
           && (node -> parent -> color == red))
    {
        parent_of_node = node -> parent;
        grand_parent_of_node = node -> parent -> parent;
        
        /*
        Case A:
            Parent of a node is a left child 
            of grand-parent of the node.
        */
       if (parent_of_node == grand_parent_of_node -> left_child)
       {
            uncle_of_node = grand_parent_of_node -> right_child;
           
            /*
            First Case:
                The uncle of the node is also, red
                only need to recolor nodes.
            */
           if (uncle_of_node != NULL && uncle_of_node -> color == red)
           {
                grand_parent_of_node -> color = red;
                parent_of_node -> color = black;
                uncle_of_node -> color = black;
                node = grand_parent_of_node;
           }

           else{
            
                /*
                Second Case:
                    Node is a right child of its parent node,
                    left rotation is needed.
                */
                if (node == parent_of_node -> right_child)
                {
                    left_rotation(parent_of_node);
                    node = parent_of_node;
                    parent_of_node = node -> parent;
                }

                /*
                Third Case:
                    Node is a left child of its parent node,
                    right rotation is needed.
                */
                right_rotation(grand_parent_of_node);
                temp = parent_of_node -> color;
                parent_of_node -> color = grand_parent_of_node -> color;
                grand_parent_of_node -> color = temp;
                node = parent_of_node;
           }
       }

       /*
       Case B:
            Parent of a node is right child 
            of the grand-parent of node.
       */
        else
        {
            uncle_of_node = grand_parent_of_node -> left_child;

            /*
            First Case:
                The uncle of the node is also, red
                recoloring is needed.
            */
            if ((uncle_of_node != NULL) && (uncle_of_node -> color == red))
            {
                grand_parent_of_node -> color = red;
                parent_of_node -> color = black;
                uncle_of_node -> color = black;
                node = grand_parent_of_node;
            }

            else{
                
                /*
                Second Case:
                    Node is a left child of its parent node,
                    right rotation is needed.
                */
                if (node == parent_of_node -> left_child)
                {
                    right_rotation(parent_of_node);
                    node = parent_of_node;
                    parent_of_node = node -> parent;
                }

                /*
                Third Case:
                    Node is a right child of its parent,
                    left rotation is needed.
                */
                left_rotation(grand_parent_of_node);
                temp = parent_of_node -> color;
                parent_of_node -> color = grand_parent_of_node -> color;
                grand_parent_of_node -> color = temp;
                node = parent_of_node;
            }
        }
    }
}

// Search function.
Node* search(Node* root, int data)
{
    // Root is NULL or key is present at root.
    if (root == NULL || root -> data == data)
        return root;
    if (root -> data > data)
        return search(root -> left_child, data);
    if (root -> data < data)
        return search(root -> right_child, data);
}

void show_tree(Node* root)
{
    if (root != NULL)
    {
        show_tree(root -> left_child);
        printf("%d ", root -> data);
        show_tree(root -> right_child);
    }
}

int main(int argc, char* argv[])
{
    Node* node = NULL;
    int nums[10] = {1, 2, 10, 11, 7, 3, 4, 5, 9, 12};
    for (int i = 0; i < 10; i++)
    {
        node = new_node(nums[i]);
        root = insert(root, node);
        fix_tree_after_insertion(root, node);
        root -> color = black;
    }

    show_tree(root);
    return 0;
}
