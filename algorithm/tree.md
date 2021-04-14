* B-Tree (B树)

  * m阶B树定义

    * 每个结点至多有m个孩子
    * 如果根结点不是叶子结点，至少有两个孩子，每个非叶结点至少有$\lceil m/2\rceil$个孩子
    * 有k个孩子的非叶结点，有k-1个元素，且顺序排列
    * 所有叶结点在一层

    ![](https://upload.wikimedia.org/wikipedia/commons/3/33/B_tree_insertion_example.png)

* B+Tree (B+树)

  * m阶B+树不同

    * B+树非叶子结点只存索引数据
    * B+树叶子结点包含索引值，并指向数据
    * B+树所有叶子结点相连

    ![](https://upload.wikimedia.org/wikipedia/commons/thumb/3/37/Bplustree.png/600px-Bplustree.png)

* MySql使用B+树

  * B树每个结点都要存储数据，适合单一查询，单一查询效率好于B+树，查询效率不稳定。
  * B+树的数据只出现在叶子结点，单一查询效率稳定。同时叶子结点相连，也适合范围查询