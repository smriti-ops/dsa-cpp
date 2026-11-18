# Week 3 Theory — Stack & Binary Search

Read this before solving anything on Nov 17. As in Weeks 1–2, type out every code block and run it.
Sections 1–6 (Stack) are enough for Mon–Wed. Sections 7–12 (Binary Search) are for Thu–Sat.

---

## 1. What is a stack?

A stack is a pile of plates: you can only touch the **top**. The last thing you put in is the
first thing you take out: **LIFO** (Last In, First Out).

```
push 1      push 2      push 3      pop → 3     top → 2
  [1]       [1,2]       [1,2,3]     [1,2]       [1,2]
                 ^            ^          ^           ^   ← top
```

Every operation is **O(1)**: push, pop, top, empty, size.

### When does a problem want a stack?

Ask: *"Do I need to remember things, and come back to the **most recent** one first?"*

| Clue in the problem | Why a stack fits |
|---|---|
| matching brackets / tags, "valid", "balanced" | the most recent opener must close first |
| "undo", "backspace", "remove adjacent pairs" | the last thing added is the first one removed |
| evaluate an expression (postfix / RPN) | operands wait until their operator arrives |
| "next greater / next smaller element", "how many days until warmer" | **monotonic stack** (Section 5) |
| simulate recursion without recursion | the call stack *is* a stack (Week 5 trees) |

---

## 2. C++ you'll need this week

```cpp
#include <stack>              // already inside bits/stdc++.h

stack<int> st;
st.push(5);                   // add to top
st.top();                     // look at top (does NOT remove)
st.pop();                     // remove top (returns NOTHING — void!)
st.empty();  st.size();

// Pitfall: pop() returns void
int x = st.pop();             // ❌ compile error
int x = st.top(); st.pop();   // ✅ read first, then remove

// Pitfall: top()/pop() on an EMPTY stack is undefined behaviour (often a crash)
if (!st.empty() && st.top() == '(') st.pop();   // always check empty() first
```

### A `vector` or `string` works as a stack too

```cpp
vector<int> st;
st.push_back(5);   st.back();   st.pop_back();   st.empty();
string s;          // s.push_back(c); s.back(); s.pop_back();
```
Use this when you need to **look inside** the stack or **return it** at the end
(e.g. 1047 returns the remaining string). `std::stack` doesn't let you iterate.

### Other helpers this week

```cpp
stoi("-12");              // string → int  (handles the minus sign)
to_string(42);            // int → string
pair<int,int> p = {val, idx};   p.first;  p.second;
stack<pair<int,int>> st;  st.push({val, idx});
auto [v, i] = st.top();   // structured binding (C++17)
```

---

## 3. Pattern A: matching (Valid Parentheses)

**Idea:** every opener is pushed. Every closer must match the **most recent unmatched** opener,
which is exactly the top of the stack.

```cpp
bool isValid(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty()) return false;                 // closer with nothing open
            char o = st.top(); st.pop();
            if ((c == ')' && o != '(') ||
                (c == ']' && o != '[') ||
                (c == '}' && o != '{')) return false;     // wrong type
        }
    }
    return st.empty();                                    // leftover openers = invalid
}
```

**Trace** `s = "([)]"`:

| c | action | stack after |
|---|---|---|
| `(` | push | `(` |
| `[` | push | `( [` |
| `)` | top is `[`, needs `(` → **false** | — |

Three ways to fail — test all three:
1. a closer when the stack is **empty**: `")("`
2. a closer of the **wrong type**: `"(]"`
3. openers **left over** at the end: `"(("`

Time O(n), space O(n).

---

## 4. Pattern B: stack as "undo" / simulation

The stack holds the "history so far". New input either **adds** to it or **cancels** the top.

### Example: remove adjacent equal pairs (this is 1047)

`"abbaca"` → remove `bb` → `"aaca"` → remove `aa` → `"ca"`.

```cpp
string removeDuplicates(const string& s) {
    string st;                       // string used as a stack
    for (char c : s) {
        if (!st.empty() && st.back() == c) st.pop_back();   // cancels the top
        else st.push_back(c);
    }
    return st;
}
```

| c | top | action | stack |
|---|---|---|---|
| a | — | push | a |
| b | a | push | ab |
| b | b | **pop** | a |
| a | a | **pop** | (empty) |
| c | — | push | c |
| a | c | push | ca |

One pass, no restarting. Each char is pushed once and popped at most once → **O(n)**.

- **Baseball Game (682):** numbers are pushed, `"C"` pops, `"D"` pushes `2 × top`,
  `"+"` pushes the sum of the **top two** (pop one, read the next, push it back).
- **Evaluate Reverse Polish Notation (150):** numbers are pushed. An operator pops **two**
  numbers, computes, pushes the result.

### RPN trace: `["2","1","+","3","*"]` = `(2 + 1) * 3`

| token | action | stack |
|---|---|---|
| 2 | push | 2 |
| 1 | push | 2 1 |
| + | pop b=1, pop a=2, push a+b | 3 |
| 3 | push | 3 3 |
| * | pop b=3, pop a=3, push a*b | 9 |

> ⚠️ **Order matters for `-` and `/`.** The first pop is the **right** operand.
> `["4","2","-"]` is `4 - 2 = 2`, not `2 - 4`. Pop `b` first, then `a`, compute `a - b`.

---

## 5. Pattern C: Min Stack (a stack that remembers extra info)

**Problem:** push, pop, top, and `getMin()` — **all O(1)**.

Scanning for the min is O(n). The trick: **every element remembers what the minimum was when it
was pushed.** When you pop it, the minimum underneath is still saved.

```cpp
class MinStack {
    stack<pair<int,int>> st;          // {value, min of everything up to here}
public:
    void push(int val) {
        int m = st.empty() ? val : min(val, st.top().second);
        st.push({val, m});
    }
    void pop()    { st.pop(); }
    int top()     { return st.top().first; }
    int getMin()  { return st.top().second; }
};
```

| op | stack (bottom → top) as {val, min} | getMin |
|---|---|---|
| push 5 | {5,5} | 5 |
| push 3 | {5,5} {3,3} | 3 |
| push 7 | {5,5} {3,3} {7,3} | 3 |
| pop | {5,5} {3,3} | 3 |
| pop | {5,5} | **5** ← the old min comes back for free |

Space O(n). (An alternative is two stacks: one for values, one for minimums.)

---

## 6. Pattern D: monotonic stack (next greater element)

This is the most important stack pattern, and the hardest to see the first time.

**Problem shape:** *for each element, find the **next** element to its right that is **greater**
(or smaller).* "Daily Temperatures", "Next Greater Element", "stock span", "largest rectangle".

Brute force: for each `i`, scan right → O(n²).

### The idea

Walk left to right. Keep a stack of indices that are **still waiting** for their answer.
Those waiting values are always in **decreasing** order from bottom to top (that's why it's
called *monotonic*). Why? If a bigger value had arrived after a smaller one, it would have
answered the smaller one and popped it already.

When a new value `a[i]` arrives, it is the answer for **every waiting element smaller than it**.
Pop them and record.

```cpp
// ans[i] = how many steps until a strictly greater value (0 if none)  ← this is 739
vector<int> dailyTemperatures(const vector<int>& t) {
    int n = t.size();
    vector<int> ans(n, 0);
    stack<int> st;                              // indices, values decreasing
    for (int i = 0; i < n; i++) {
        while (!st.empty() && t[i] > t[st.top()]) {
            int j = st.top(); st.pop();
            ans[j] = i - j;                     // i is j's "next warmer day"
        }
        st.push(i);                             // i now waits for its own answer
    }
    return ans;                                 // anything left in st keeps 0
}
```

**Trace** `t = [73, 74, 75, 71, 69, 72, 76]`  (stack shows `index:value`)

| i | t[i] | pops (and answers) | stack after |
|---|---|---|---|
| 0 | 73 | — | 0:73 |
| 1 | 74 | 0 → ans[0]=1 | 1:74 |
| 2 | 75 | 1 → ans[1]=1 | 2:75 |
| 3 | 71 | — | 2:75 3:71 |
| 4 | 69 | — | 2:75 3:71 4:69 |
| 5 | 72 | 4 → ans[4]=1, 3 → ans[3]=2 | 2:75 5:72 |
| 6 | 76 | 5 → ans[5]=1, 2 → ans[2]=4 | 6:76 |

`ans = [1, 1, 4, 2, 1, 1, 0]`

**Why O(n)?** Same argument as Week 2's sliding window: each index is pushed **once** and popped
**at most once**. Total work ≤ 2n, even with a `while` inside the `for`.

### Store indices, not values

Store the **index** in the stack. From an index you can get the value (`t[j]`) *and* the distance
(`i - j`). From a value you can only get the value.

### Variations

| Want | Stack keeps values… | Pop while… |
|---|---|---|
| next **greater** | decreasing | `a[i] > a[top]` |
| next **smaller** | increasing | `a[i] < a[top]` |
| next greater **or equal** | strictly decreasing | `a[i] >= a[top]` |

- **Next Greater Element I (496):** run the template over `nums2`, save the answers in an
  `unordered_map<int,int>` (value → next greater), then look up each `nums1` value. Week 1 hash map
  meets Week 3 stack.

---

## 7. Binary search: the idea

Week 2's two pointers threw away **one** element per step. Binary search throws away **half**.

Requirement: the search space must be **sorted**, or more generally, **monotonic**:

```
index:     0   1   2   3   4   5   6   7
a[i] >= 7: F   F   F   T   T   T   T   T
                       ^ first true
```

If you can ask a yes/no question where the answers look like `F F F … T T T` (all the falses
first, then all the trues), you can binary search for the boundary. That one sentence is the whole
pattern, and it's what unlocks the hard-looking Medium problems (Section 10).

**Why O(log n):** each step halves the range. `n = 10⁹` → about 30 steps. `n = 10⁵` → about 17.

| n | log₂ n |
|---|---|
| 1,000 | ~10 |
| 1,000,000 | ~20 |
| 1,000,000,000 | ~30 |

---

## 8. Template 1: find an exact value (704)

```cpp
int search(const vector<int>& a, int target) {
    int lo = 0, hi = (int)a.size() - 1;        // search space: [lo, hi], both included
    while (lo <= hi) {                          // <= because [lo, lo] still has one element
        int mid = lo + (hi - lo) / 2;           // avoids overflow of (lo + hi)
        if (a[mid] == target) return mid;
        if (a[mid] < target) lo = mid + 1;      // mid is too small, and so is everything left of it
        else                 hi = mid - 1;      // mid is too big, and so is everything right of it
    }
    return -1;
}
```

**Trace** `a = [-1, 0, 3, 5, 9, 12]`, `target = 9`

| lo | hi | mid | a[mid] | action |
|---|---|---|---|---|
| 0 | 5 | 2 | 3 | 3 < 9 → lo = 3 |
| 3 | 5 | 4 | 9 | **found 4** |

`target = 2` (missing):

| lo | hi | mid | a[mid] | action |
|---|---|---|---|---|
| 0 | 5 | 2 | 3 | 3 > 2 → hi = 1 |
| 0 | 1 | 0 | -1 | -1 < 2 → lo = 1 |
| 1 | 1 | 1 | 0 | 0 < 2 → lo = 2 |
| 2 | 1 | — | — | lo > hi, stop → **-1** |

Notice where `lo` ended: **index 2**, exactly where 2 *would be inserted*. That's 35 (Search
Insert Position) for free: return `lo` instead of `-1`.

### Why `lo + (hi - lo) / 2`?

`lo + hi` can overflow `int` when both are near 2·10⁹ (it happens in Section 10 problems where
`hi` is a big number, not an index). `lo + (hi - lo) / 2` is the same value and never overflows.

---

## 9. Template 2: find the first `true` (lower bound)

This is the one to memorize. It solves **every** binary search problem this week.

```cpp
// smallest x in [lo, hi] where ok(x) is true.
// Assumes ok is F F F ... T T T, and ok(hi) is true.
int lo = LOW, hi = HIGH;
while (lo < hi) {                // stops when lo == hi: one candidate left
    int mid = lo + (hi - lo) / 2;
    if (ok(mid)) hi = mid;       // mid could be the answer, keep it
    else         lo = mid + 1;   // mid is false, the answer is strictly right of it
}
return lo;                       // lo == hi == first true
```

Compare with Template 1:

| | Template 1 (exact) | Template 2 (first true) |
|---|---|---|
| loop | `lo <= hi` | `lo < hi` |
| on "good" mid | return | `hi = mid` (keep it) |
| on "bad" mid | `lo = mid + 1` / `hi = mid - 1` | `lo = mid + 1` |
| ends with | `-1` or found | `lo` = the boundary |

> ⚠️ **Infinite-loop rule:** with `hi = mid`, `mid` must round **down** (`lo + (hi - lo) / 2`).
> If you ever write `lo = mid` (no `+1`), you must round **up** (`lo + (hi - lo + 1) / 2`),
> otherwise `lo = 3, hi = 4` gives `mid = 3` forever. Easiest fix: always use the form above.

**Trace** first index with `a[i] >= 6` in `a = [1, 3, 5, 7, 9]` (`ok(i) = a[i] >= 6`):

| lo | hi | mid | a[mid] | ok? | action |
|---|---|---|---|---|---|
| 0 | 4 | 2 | 5 | F | lo = 3 |
| 3 | 4 | 3 | 7 | T | hi = 3 |
| 3 | 3 | — | — | — | stop → **3** |

### The STL already does this

```cpp
// a must be sorted
auto it = lower_bound(a.begin(), a.end(), x);   // first element >= x
auto jt = upper_bound(a.begin(), a.end(), x);   // first element >  x
int idx = it - a.begin();                       // iterator → index (== a.size() if none)
binary_search(a.begin(), a.end(), x);           // bool: is x present?
int count_x = jt - it;                          // how many times x appears, O(log n)
```

Write it by hand in every problem this week (interviewers ask for that). Use the STL afterwards
to double-check your answer.

---

## 10. Binary search on the answer (Koko)

**Trigger words:** *minimum speed / capacity / time such that…*, *maximize the minimum*,
*minimize the maximum*, and a feasibility check that's easy to write.

Here you're not searching inside an array. You're searching the **range of possible answers**.

### Koko Eating Bananas (875)

Piles `[3, 6, 7, 11]`, `h = 8` hours. Koko eats `k` bananas/hour, one pile at a time (a pile of 3
at speed 5 still takes a whole hour). Find the **minimum** `k` that finishes in `h` hours.

1. **The answer range:** `k` is at least 1, at most `max(piles)` (at that speed every pile takes
   exactly 1 hour, so faster is pointless). So `lo = 1`, `hi = 11`.
2. **The yes/no question:** `ok(k)` = "can she finish within `h` hours at speed `k`?"
   Hours at speed `k` = sum of `ceil(pile / k)`.
3. **Monotonic?** Faster never makes it slower. So `ok` looks like `F F F T T T`. ✅
   Find the first `T` with Template 2.

```cpp
bool ok(const vector<int>& piles, int h, int k) {
    long long hours = 0;                       // can exceed int: 10⁴ piles × 10⁹
    for (int p : piles) hours += (p + k - 1) / k;   // integer ceil(p / k)
    return hours <= h;
}
```

| k | hours = ceil(3/k)+ceil(6/k)+ceil(7/k)+ceil(11/k) | ok (≤ 8)? |
|---|---|---|
| 1 | 3+6+7+11 = 27 | F |
| 2 | 2+3+4+6 = 15 | F |
| 3 | 1+2+3+4 = 10 | F |
| **4** | 1+2+2+3 = **8** | **T** ← first true |
| 5 | 1+2+2+3 = 8 | T |

Answer **4**. Time: O(n · log(max pile)). Checking every `k` from 1 up would be O(n · max pile),
which is 10⁴ × 10⁹: far too slow.

### Integer ceiling without floating point

```cpp
(p + k - 1) / k      // == ceil(p / k) for positive ints
ceil((double)p / k)  // works, but floating point can bite on huge numbers. Avoid.
```

### The general recipe

1. What's the smallest and largest the answer could be? → `lo`, `hi`.
2. Write `ok(x)`: "is `x` good enough?" Usually a simple O(n) greedy check.
3. Convince yourself `ok` is monotonic (if `x` works, does `x + 1` also work?).
4. Template 2.

---

## 11. Binary search on a modified sorted array

### Search a 2D Matrix (74)

Each row is sorted, and each row's first value is bigger than the previous row's last.
So reading row by row gives **one long sorted array** of length `m * n`.
Binary search over `[0, m*n - 1]` and convert each index:

```cpp
int row = mid / n;     // n = number of columns
int col = mid % n;
```

O(log(m·n)). No need to flatten into a new vector.

### Rotated sorted array (153, 33)

`[0,1,2,4,5,6,7]` rotated → `[4,5,6,7,0,1,2]`. It's two sorted pieces. The minimum is where
the second piece starts.

**Find the minimum (153):** compare `a[mid]` with `a[hi]` (the last element of the current range).

- `a[mid] > a[hi]`: there is a drop somewhere between `mid` and `hi`, so the minimum is
  **strictly right** of `mid` → `lo = mid + 1`.
- `a[mid] < a[hi]`: `mid..hi` is sorted, so the minimum is `mid` or to its left → `hi = mid`.

That's Template 2 with `ok(i) = a[i] <= a[last]`... try writing out the T/F row for
`[4,5,6,7,0,1,2]` and check it's `F F F F T T T`.

| lo | hi | mid | a[mid] vs a[hi] | action |
|---|---|---|---|---|
| 0 | 6 | 3 | 7 > 2 | lo = 4 |
| 4 | 6 | 5 | 1 < 2 | hi = 5 |
| 4 | 5 | 4 | 0 < 1 | hi = 4 |
| 4 | 4 | — | — | stop → a[4] = **0** |

> Why compare with `a[hi]` and not `a[lo]`? If the range isn't rotated at all
> (`[1,2,3]`), `a[mid] > a[lo]` would wrongly push you right. Dry-run both to see it.

**Search in rotated array (33) — optional:** at every `mid`, **one of the two halves is sorted**
(check `a[lo] <= a[mid]`). If the target is inside the sorted half's range, go there; otherwise go to
the other half. Do 153 first.

---

## 12. Pattern cheat sheet

| If the problem says… | Think… |
|---|---|
| brackets, valid / balanced, matching pairs | stack of openers |
| remove adjacent duplicates, backspace, undo | stack (or `string` as stack), cancel the top |
| evaluate postfix / RPN | stack of numbers; operator pops two (right operand first) |
| O(1) getMin / getMax on a stack | store `{val, minSoFar}` per element |
| next greater / smaller, "days until warmer", span | **monotonic stack** of indices |
| sorted array, find a value | Template 1 (`lo <= hi`) |
| first index where …, insert position, `>= x` | Template 2 (`lo < hi`, `hi = mid`) / `lower_bound` |
| **minimum** speed / capacity / days such that it works | binary search on the answer + `ok(x)` |
| sorted 2D matrix | treat as 1-D, `row = mid / n`, `col = mid % n` |
| rotated sorted array | compare `a[mid]` with `a[hi]` |
| O(log n) required in the statement | it's binary search, find the monotonic thing |

---

## 13. Common mistakes to avoid

1. `int x = st.pop();` — `pop()` returns `void`. Use `top()` then `pop()`.
2. Calling `top()` / `pop()` on an empty stack. Always check `!st.empty()` first.
3. Valid Parentheses: forgetting to check the stack is **empty at the end**.
4. RPN: computing `b - a` instead of `a - b` (first pop is the right operand).
5. Monotonic stack: pushing **values** when you need the **distance** (push indices).
6. Binary search: `(lo + hi) / 2` overflowing when `hi` is ~10⁹. Use `lo + (hi - lo) / 2`.
7. Mixing templates: `lo <= hi` with `hi = mid` → infinite loop. Pick one template and stick to it.
8. Search Insert Position: returning `-1` instead of `lo` when the target isn't found.
9. Koko: summing hours in an `int` (overflow), or using `p / k` instead of the ceiling.
10. Koko: `lo = 0` → division by zero in `ok(0)`. Speed starts at 1.

---

## 14. Check yourself before Monday's problems

Answer these out loud, without notes:

1. What does LIFO mean, and which three problem clues tell you to use a stack?
2. Valid Parentheses can fail in three different ways. Name them.
3. In a monotonic stack, why are the waiting values always in decreasing order?
4. There's a `while` inside a `for` in Daily Temperatures. Why is it still O(n)?
5. How does Min Stack get the old minimum back after a pop, in O(1)?
6. What property must a problem have for binary search to work? (Hint: `F F F T T T`.)
7. Write `mid` without overflow. Why does it matter?
8. In Template 2, why `hi = mid` and not `hi = mid - 1`?
9. For Koko: what are `lo` and `hi`, what is `ok(k)`, and why is `ok` monotonic?
10. In a rotated sorted array, why compare `a[mid]` with `a[hi]` rather than `a[lo]`?

If any of these feel shaky, re-read that section. Don't move on.
