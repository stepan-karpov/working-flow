import java.util.ArrayList;
import java.util.Scanner;
import java.util.Collections;

public class incorrect_program {
  static public class SplayTree {
    static public class Node {
      String value;
      String key;
      Integer left_son = -1;
      Integer right_son = -1;
      Integer parent = -1;
      public Node(String value, String key) {
        this.value = value;
        this.key = key;
      }
      public Node() {}
    }

    public Boolean Less(Node a, Node b) {
      Integer res = a.value.compareTo(b.value);
      if (res < 0) {
        return true;
      } else if (res == 0) {
        if (a.key.compareTo(b.key) < 0) {
          return true;
        }
        return false;
      }
      return false;
    }

    public Boolean Equals(Node a, Node b) {
      if (a.value.compareTo(b.value) != 0) {
        return false;
      }
      return a.key.compareTo(b.key) == 0;
    }

    ArrayList<Node> tree = new ArrayList<Node>();

    private void AssignParent(Integer subtree, Integer parent) {
      if (subtree != -1) {
        tree.get(subtree).parent = parent;
      }
    }

    private void LeftZig(Integer p) {
      Node cur_p = tree.get(p);
      Integer x = cur_p.left_son;
      Node cur_x = tree.get(x);
      Integer A = cur_x.left_son;
      Integer B = cur_x.right_son;
      Integer C = cur_p.right_son;
      Collections.swap(tree, p, x);
      Integer temp = x; x = p; p = temp;
      cur_x = tree.get(x); cur_p = tree.get(p);
      cur_x.left_son = A;
      cur_x.right_son = p;
      cur_p.left_son = B;
      cur_p.right_son = C;
      Integer temp_p = cur_p.parent;
      cur_p.parent = cur_x.parent;
      cur_x.parent = temp_p;
      AssignParent(A, x);
      AssignParent(B, p);
      AssignParent(C, p);
    }

    private void RightZig(Integer p) {
      Node cur_p = tree.get(p);
      Integer x = cur_p.right_son;
      Node cur_x = tree.get(x);
      Integer A = cur_p.left_son;
      Integer B = cur_x.left_son;
      Integer C = cur_x.right_son;
      Collections.swap(tree, p, x);
      Integer temp = x; x = p; p = temp;
      cur_x = tree.get(x); cur_p = tree.get(p);
      cur_x.left_son = p;
      cur_x.right_son = C;
      cur_p.left_son = A;
      cur_p.right_son = B;
      Integer temp_p = cur_p.parent;
      cur_p.parent = cur_x.parent;
      cur_x.parent = temp_p;
      AssignParent(A, p);
      AssignParent(B, p);
      AssignParent(C, x);
    }

    private void LeftZigZig(Integer g) {
      Integer p = tree.get(g).left_son;
      LeftZig(p);
      LeftZig(g);
    }

    private void RightZigZig(Integer g) {
      Integer p = tree.get(g).right_son;
      RightZig(p);
      RightZig(g);
    }

    private void LeftZigZag(Integer g) {
      Integer p = tree.get(g).left_son;
      RightZig(p);
      LeftZig(g);
    }

    private void RightZigZag(Integer g) {
      Integer p = tree.get(g).right_son;
      LeftZig(p);
      RightZig(g);
    }

    private void Splay(Integer x) {
      Integer p = tree.get(x).parent;
      if (p == -1) {
        return;
      }
      Integer g = tree.get(p).parent;
      if (g == -1) {
        Node cur_p = tree.get(p);
        if (cur_p.left_son == x) {
          LeftZig(p);
        } else {
          RightZig(p);
        }
      } else {
        Node cur_g = tree.get(g);
        Node cur_p = tree.get(p);
        if (cur_g.left_son == p) {
          if (cur_p.left_son == x) {
            LeftZigZig(g);
          } else {
            LeftZigZag(g);
          }
        } else {
          if (cur_p.left_son == x) {
            RightZigZag(g);
          } else {
            RightZigZig(g);
          }
        }
      }
    }
    
    private void Add(Node value, Integer x) {
      Node cur_x = tree.get(x);
      if (Equals(cur_x, value)) {
        return;
      }
      if (Less(value, cur_x)) {
        if (cur_x.left_son == -1) {
          tree.add(value);
          cur_x.left_son = tree.size() - 1;
          tree.get(tree.size() - 1).parent = x;
          return;
        }
        Add(value, cur_x.left_son);
      } else {
        if (cur_x.right_son == -1) {
          tree.add(value);
          cur_x.right_son = tree.size() - 1;
          tree.get(tree.size() - 1).parent = x;
          return;
        }
        Add(value, cur_x.right_son);
      }
    }

    public void Add(Node value) {
      if (tree.isEmpty()) {
        tree.add(value);
        return;
      }
      Add(value, 0);
    }

    private String Find(String value, Integer x) {
      Node cur_x = tree.get(x);
      if (cur_x.value.compareTo(value) == 0) {
        Splay(x);
        return cur_x.key;
      }
      if (cur_x.value.compareTo(value) > 0) {
        if (cur_x.left_son == -1) {
          return "None";
        }
        String ans = Find(value, cur_x.left_son);
        if (ans != "None") {
          Splay(x);
        }
        return ans;
      } else {
        if (cur_x.right_son == -1) {
          return "None";
        }
        String ans = Find(value, cur_x.right_son);
        if (ans != "None") {
          Splay(x);
        }
        return ans;
      }
    }

    public String Find(String value) {
      if (tree.isEmpty()) {
        return "None";
      }
      return Find(value, 0);
    }
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    Integer n;
    SplayTree a1 = new SplayTree();
    SplayTree a2 = new SplayTree();

    n = sc.nextInt();

    for (int i = 0; i < n; ++i) {
      SplayTree.Node temp1 = new SplayTree.Node();
      SplayTree.Node temp2 = new SplayTree.Node();
      temp1.value = sc.next();
      temp1.key = sc.next();
      temp2.key = temp1.value;
      temp2.value = temp1.key;
      a1.Add(temp1);
      a2.Add(temp2);
    }

    Integer q;
    
    q = sc.nextInt();

    for (int i = 0; i < q; ++i) {
      String query = sc.next();
      String ans1 = a1.Find(query);
      String ans2 = a2.Find(query);
      if (ans1 != "None") {
        System.out.println(ans1);
      } else {
        System.out.println(ans2);
      }
    }
  }
}