#include <cassert>
#include <cassert>
#include <iostream>

struct JumpList { JumpList *next, *jump; unsigned id; };


JumpList* deserialize(unsigned* begin, unsigned* end) {
  int size = (end - begin) / 2;
  JumpList** vertexes = new JumpList*[size];

  for (int i = 0; i < size; ++i) {
    vertexes[i] = new JumpList();
  }

  for (unsigned* i = begin; i < end; i += 2) {
    int id = *i;
    int next = *(i + 1) + id - 1;
    vertexes[id - 1]->id = id;
    if (next == id - 1) {
      vertexes[id - 1]->jump = nullptr;
    } else {
      vertexes[id - 1]->jump = vertexes[next];
    }
    if (id == size) {
      vertexes[id - 1]->next = nullptr;
    } else {
      vertexes[id - 1]->next = vertexes[id];
    }
  }
  return vertexes[0];
}

void erase_jump_list(JumpList *head) {
    if (nullptr == head) return;
    erase_jump_list(head->next);
    delete head;
}

JumpList* deserialize(unsigned *begin, unsigned *end);

int main() {
    unsigned dscr[12] = {1, 3, 2, 3, 3, 3, 4, 0, 5, 0, 6, 0};
    auto head = deserialize(dscr, dscr + 12);
    {
        auto tmp = head; unsigned cnt = 0;
        while (nullptr != tmp) {
            assert(tmp->id == dscr[cnt]);
            assert(tmp->jump == nullptr or tmp->jump->id == dscr[cnt + 2 * dscr[cnt + 1]]);
            tmp = tmp->next;
            cnt += 2;
        }
    }
    erase_jump_list(head);
    return 0;
}