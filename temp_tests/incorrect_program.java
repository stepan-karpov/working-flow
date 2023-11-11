import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class incorrect_program {

  public static Long getAnswer(ArrayList<Integer> a, Integer ind) {
    Long answer = Long.valueOf(0);
    Integer base = a.get(ind);

    for (int i = ind; i < a.size(); ++i) {
      answer += (a.get(i) / base) * base;
    }

    return answer;
  }

  public static Integer TernarySearch(ArrayList<Integer> a) {

    Integer l = -1;
    Integer r = a.size();

    while (r - l > 2) {
      Integer m1 = l + (r - l) / 3;
      Integer m2 = r - (r - l) / 3;

      Long ans1 = getAnswer(a, m1);
      Long ans2 = getAnswer(a, m2);

      if (ans1 > ans2) {
        r = m2;
      } else {
        l = m1;
      }
    }

    Integer best_ind = 0;
    Long best_ans = Long.valueOf(-1);

    Integer lb = Math.max(0, l - 10);
    Integer rb = Math.min(a.size() - 1, r + 10);

    for (int i = lb; i <= rb; ++i) {
      Long cur_answer = getAnswer(a, i);
      if (cur_answer > best_ans) {
        best_ans = cur_answer;
        best_ind = i;
      }
    }

    return best_ind;
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();

    ArrayList<Integer> a = new ArrayList<Integer>();

    for (int i = 0; i < n; ++i) {
      Integer x = sc.nextInt();
      a.add(x);
    }

    Collections.sort(a);

    Long answer = getAnswer(a, TernarySearch(a));

    System.out.println(answer);

  }
}