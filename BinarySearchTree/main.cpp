#include <iostream>
#include <queue>
#include <unordered_set>
#include <stack>

class AVL_Node
{
public:
  int val{};
  int height{};
  int count{};
  AVL_Node *parent{};
  AVL_Node *left{};
  AVL_Node *right{};

  AVL_Node(int val)
      : val(val), height(1), count(1), parent(nullptr), left(nullptr), right(nullptr)
  {
  }

  ~AVL_Node()
  {
    delete left;
    delete right;
  }
};

class AVL_Tree
{
public:
  AVL_Node *root{};

  AVL_Tree() {}

  ~AVL_Tree()
  {
    delete root;
  }

  AVL_Node *subtreeFirst(AVL_Node *node)
  {
    AVL_Node *travel = node;

    while (travel->left)
      travel = travel->left;

    return travel;
  }

  AVL_Node *subtreeLast(AVL_Node *node)
  {
    AVL_Node *travel = node;

    while (travel->right)
      travel = travel->right;

    return travel;
  }

  AVL_Node *next(AVL_Node *node)
  {
    if (node->right)
    {
      return subtreeFirst(node->right);
    }

    // in case we are the rightmost subtree node
    while (node->parent && node->parent->right == node)
      node = node->parent;

    return node->parent;
  }

  AVL_Node *prev(AVL_Node *node)
  {
    if (node->left)
    {
      return subtreeLast(node->left);
    }

    // in case we are leftmost child
    while (node->parent && node->parent->left == node)
      node = node->parent;

    return node->parent;
  }

  AVL_Node *insert(int val)
  {
    AVL_Node *newNode = new AVL_Node(val);

    if (!root)
    {
      root = newNode;
      return newNode;
    }

    AVL_Node *travel = root;

    while (true)
    {
      if (val == travel->val)
      {
        ++travel->count;
        break;
      }
      else if (val < travel->val)
      {
        if (travel->left)
        {
          travel = travel->left;
        }
        else
        {
          travel->left = newNode;
          newNode->parent = travel;
          break;
        }
      }
      else if (val > travel->val)
      {
        if (travel->right)
        {
          travel = travel->right;
        }
        else
        {
          travel->right = newNode;
          newNode->parent = travel;
          break;
        }
      }
    }

    maintain(travel);

    return travel;
  }

  AVL_Node *search(int val)
  {
    AVL_Node* travel = root;

    while (travel)
    {
      if (travel->val == val)
      {
        return travel;
      }
      else if (travel->val > val)
      {
        travel = travel->left;
      }
      else
      {
        travel = travel->right;
      }
      
    }

    return nullptr;
  }

  void remove(int val)
  {
    AVL_Node *travel = root;

    while (travel)
    {
      if (val == travel->val)
      {
        if (travel->count > 1)  
          --travel->count;
        else  
          removeNode(travel);
        break;
      }
      else if (val < travel->val)
        travel = travel->left;
      else
        travel = travel->right;
    }
  }

  void printSubtree(AVL_Node *node)
  {
    if (!node)
      return;

    if (node->left)
      printSubtree(node->left);
    std::cout << "Value: " << node->val << ' ';
    std::cout << "Height: " << node->height << '\n';
    if (node->right)
      printSubtree(node->right);
  }

private:
  void maintain(AVL_Node *n)
  {
    if (!n)
      return;

    rebalance(n);
    update_height(n);
    if (n->parent)
      maintain(n->parent);
  }

  int skew(AVL_Node *node)
  {
    // negative: left bigger
    // positive: right bigger
    if (!node->right && !node->left)
      return 0;
    if (!node->right)
      return -node->left->height;
    if (!node->left)
      return node->right->height;
    return node->right->height - node->left->height;
  }

  void update_height(AVL_Node *node)
  {
    AVL_Node *left = node->left;
    AVL_Node *right = node->right;

    if (!left && !right)
      node->height = 1;
    else if (!left)
      node->height = 1 + right->height;
    else if (!right)
      node->height = 1 + left->height;
    else
      node->height = 1 + std::max(left->height, right->height);
  }

  void rebalance(AVL_Node *node)
  {
    if (skew(node) == 2)
    {
      if (node->right && skew(node->right) < 0)
        right_rotate(node->right);
      left_rotate(node);
    }
    else if (skew(node) == -2)
    {
      if (node->left && skew(node->left) > 0)
        left_rotate(node->left);
      right_rotate(node);
    }
  }

  void left_rotate(AVL_Node *node)
  {
    if (!node->right)
      return;

    AVL_Node *parent = node->parent;
    AVL_Node *newParent = node->right;
    // node->left, newParent->right remain same

    // node parent links
    if (parent)
    {
      if (node == parent->left)
        parent->left = newParent;
      else
        parent->right = newParent;
    }
    newParent->parent = parent;

    // node right link
    node->right = newParent->left;
    if (node->right)
    {
      node->right->parent = node;
    }

    // node and newparent link
    node->parent = newParent;
    newParent->left = node;

    update_height(node);
    update_height(newParent);
  }

  void right_rotate(AVL_Node *node)
  {
    if (!node->left)
      return;

    AVL_Node *nodeParent = node->parent;
    AVL_Node *nodeReplacement = node->left;
    // node right and newNode left remain the same

    // node parent link
    if (nodeParent)
    {
      if (node == nodeParent->left)
        nodeParent->left = nodeReplacement;
      else
        nodeParent->right = nodeReplacement;
    }
    nodeReplacement->parent = nodeParent;

    // node left link
    node->left = nodeReplacement->right;
    if (node->left)
    {
      node->left->parent = node;
    }

    node->parent = nodeReplacement;
    nodeReplacement->right = node;

    update_height(node);
    update_height(nodeReplacement);
  }

  void removeNode(AVL_Node *node)
  {
    if (node->right)
    {
      // for sure a leaf
      AVL_Node *nextNode = next(node);
      node->val = nextNode->val;
      node->count = nextNode->count;

      AVL_Node* nextNodeParent = nextNode->parent;
      if (nextNodeParent->left == nextNode)
        nextNodeParent->left = nullptr;
      else
        nextNodeParent->right = nullptr;
      delete nextNode;
      maintain(nextNodeParent);
      return;
    }
    else if (node->left)
    {
      node->left->parent = node->parent;
    }
    
    AVL_Node* parent = node->parent;
    if (parent->left == node)
      parent->left = nullptr;
    else
      parent->right = nullptr;
    delete node;
    maintain(parent);
    
  }
};

void bfs(AVL_Node* node)
{
  std::queue<AVL_Node*> queue {};

  queue.push(node);

  while (!queue.empty())
  {
    AVL_Node* n = queue.front();
    queue.pop();

    std::cout << n->val << ' ';

    if (n->left)
      queue.push(n->left);

    if (n->right)
      queue.push(n->right);
  }

  std::cout << '\n';
}

void dfs_r(AVL_Node* node)
{
  if (!node) return;

  std::cout << node->val << ' ';
  dfs_r(node->left);
  dfs_r(node->right);
}

void dfs(AVL_Node* node)
{
  if (!node) return;

  std::stack<AVL_Node*> st {};

  st.push(node);

  while (!st.empty())
  {
    AVL_Node* n = st.top();
    st.pop();

    std::cout << n->val << ' ';

    if (n->right)
      st.push(n->right);

    if (n->left)
      st.push(n->left);
  }
  std::cout << '\n';
}




int main()
{
  AVL_Tree myTree{};

  myTree.insert(15);
  myTree.insert(16);
  myTree.insert(4);
  myTree.insert(17);
  myTree.insert(22);
  myTree.insert(2);
  myTree.insert(1);

  myTree.insert(0);
  myTree.insert(-1);

  std::cout << "\nEND: \n";
  myTree.printSubtree(myTree.root);

  myTree.remove(-1);
  myTree.remove(0);
  myTree.remove(15);
  myTree.remove(22);

  std::cout << "AFTER DELETING\n";
  myTree.printSubtree(myTree.root);

  bfs(myTree.root);
  dfs(myTree.root);
  dfs_r(myTree.root);

  return 0;
}