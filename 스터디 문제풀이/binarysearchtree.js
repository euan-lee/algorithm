ar BSTIterator = function (root) {
  this.list = []; //  Use an array to store the value of each node 
  this.index = 0; //  With a pointer , Always point to the next element 

  //  Use middle order to traverse the binary search tree , Save values in order to list
  const traversal = (node) => {
    //  If the node is empty , The exit 
    if (!node) {
      return;
    }

    //  Search the left child node 
    traversal(node.left);
    //  The node value traversed in the middle order , Deposit in list
    this.list.push(node.val);
    //  Search right child node 
    traversal(node.right);
  };
  //  Middle order traversal binary search tree 
  traversal(root);
};

/** * @return {number} */
BSTIterator.prototype.next = function () {
  //  Returns the current value to , And move the pointer back 
  return this.list[this.index++];
};

/** * @return {boolean} */
BSTIterator.prototype.hasNext = function () {
  //  If the value type corresponding to the pointer is number, Indicates that the next item exists , Otherwise undefined
  return typeof this.list[this.index] === 'number';
};
