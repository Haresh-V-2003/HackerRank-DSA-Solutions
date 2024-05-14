import java.io.*;
import java.util.*;

public class Solution {

  static class Node {
    int name;
    Node parent;
    List<Node> children;
    boolean odd=true;
  }
  
  Node[] buildTree(int numEdges, int[][] edgeData) {
    Node[] nodes = new Node[numEdges+1+1];
    for (int i=0; i<edgeData.length; i++) {
      int child = edgeData[i][0];
      int parent = edgeData[i][1];
      if (nodes[child] == null) {
        nodes[child] = new Node();
        nodes[child].name=child;
      }
      if (nodes[parent] == null) {
        nodes[parent] = new Node();
        nodes[parent].name=parent;
      }
      nodes[child].parent = nodes[parent];
      if (nodes[parent].children == null) {
        nodes[parent].children = new ArrayList<Node>();
      }
      nodes[parent].children.add(nodes[child]);
    }
    return nodes;
  }
  
  int dowork(int numEdges, int[][] edgeData) {
    Node[] nodes = buildTree(numEdges, edgeData);
    return makeEvenTrees(nodes[1]); // nodes[0] is not used, so that it's easy to keep track of node names..
  }

  int makeEvenTrees(Node node) {
    if (node == null) {
      return 0;
    }  
    int numCuts=0;
    if (node.children == null) {
      return 0; //no cut
    } else {    
      for (Node child : node.children) {
        numCuts += makeEvenTrees(child);
        if (child.odd) {
          node.odd ^= child.odd;
        } else {
          numCuts += 1;
        }
      }
    }
    return numCuts;
  }
  
  public static void main(String[] args) {
    Solution soln = new Solution();

    try (Scanner scan = new Scanner(System.in)) {
      int numNodes = scan.nextInt();
      int numEdges = scan.nextInt();
      int[][] edgeData = new int[numEdges][2];
      for (int i = 0; i < numEdges; i++) {
        edgeData[i][0] = scan.nextInt();
        edgeData[i][1] = scan.nextInt();
      }
      int result = soln.dowork(numEdges, edgeData);
      System.out.println(result);
    }
  }
}
