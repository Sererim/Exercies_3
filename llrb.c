// Characteristics of LLRB 
// 1. Root node is Always BLACK in color. 
// 2. Every new Node inserted is always RED in color. 
// 3. Every NULL child of a node is considered as BLACK in color. 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define RED true
#define BLACK false

// Basic red-black tree node struct, but without parent data in it.
typedef struct Node
{
    int data;
    struct Node* left_child;
    struct Node* right_child;
    // RED == true
    // BLACK == false
    bool color;
} Node;

// Function for node creation.
Node* create_new_node(int data)
{
    Node* new_node = malloc(sizeof(Node));
    new_node -> left_child = new_node -> right_child = NULL;
    new_node -> data = data;
 
    // New Node which is always RED.
    new_node -> color = RED;
    return new_node;
}
 
// Function for left/anti-clockwise rotation of the nodes in tree.
Node* rotate_to_the_left(Node* node)
{
    Node* r_child = node -> right_child;
    Node* l_child = r_child -> left_child;
 
    r_child -> left_child = node;
    node -> right_child = l_child;
 
    return r_child;
}
 
// Function for right/clockwise rotation of the nodes in the tree.
Node* rotate_to_the_right(Node* node)
{
    Node* l_child = node -> left_child;
    Node* r_child =  l_child -> right_child;
 
    l_child -> right_child = node;
    node -> left_child = r_child;
     
    return l_child;
}

 
// Function for changing color of two nodes.
void change_colors(Node* node1, Node* node2)
{
    bool temp = node1 -> color;
    node1 -> color = node2 -> color;
    node2 -> color = temp;
}
 
bool check_if_exist(Node* node)
{
    if (node == NULL)
        return BLACK;
    else
        return node -> color;
}

// Function for insertion of a new node in red-black tree.
Node* insert(Node* node, int data)
{
    // Normal insertion code for any Binary
    // Search tree.
    if (node == NULL)
        return create_new_node(data);   
 
    if (data < node -> data)
        node -> left_child = insert(node -> left_child, data);
    else if (data > node -> data)
        node -> right_child = insert(node -> right_child, data);
    else   
        return node;
 
     
    // First Case:
    // Right child is RED but, left child is
    // BLACK or NULL.
    if ((check_if_exist(node -> right_child)) && (check_if_exist(node -> left_child)))
    {
        // Rotate node to the left to turn into a correct form.
        node = rotate_to_the_left(node);
 
        // Change colors of the left child and parent node to enforce rules of llbrt.
        change_colors(node, node -> left_child);
    }
     
    // Second Case:
    // Left child and left grandchild are both RED.
    if ((check_if_exist(node -> left_child)) && (check_if_exist(node -> left_child -> left_child)))
    {  
        // Rotate node to the right to turn it into a correct form.
        node = rotate_to_the_right(node);
        change_colors(node, node -> right_child);
    }
     
     
    // Third CASE:
    // Both children are RED.
    if ((check_if_exist(node -> left_child)) && (check_if_exist(node -> right_child)))
    {
        // Change the color of the node.
        node -> color = !(node -> color);
 
        // Change the color to BLACK.
        node -> left_child -> color = BLACK;
        node -> right_child -> color = BLACK;
    }
 
    return node;
}
 
// Inorder traversal function for printing out the tree.
void inorder(Node* node)
{
    if (node)
    {
        inorder(node -> left_child);
        printf("%d ", node -> data);
        inorder(node -> right_child);
    }
}
 

int main()
{
    Node* root = NULL;
    const short n = 10;
    const int nums[10] = {1, 10, 22, 31, 29, 18, 71, 44, 45, 60};
    for (short i = 0; i < n; i++)
    {
        root = insert(root, nums[i]);
        root -> color = BLACK;
        printf("%d ", nums[i]);
    }
    printf("\n");
    // Show inorder transversal of the tree.
    inorder(root);
    return 0;
}
