# Week 1 Theory — Big-O, C++ STL, Arrays & Hashing

Read this before solving anything on Nov 3. Type out every code block yourself and run it,
because reading code without running it doesn't stick.

---

## 1. Big-O: how fast is my solution?

Big-O tells you **how the running time grows as the input size `n` grows**.
It ignores constants: `3n + 5` is just **O(n)**.

### Counting rules

| Code shape | Complexity |
|---|---|
| Fixed number of steps (no loop over input) | O(1) |
| One loop over `n` items | O(n) |
| Loop inside a loop, both over `n` | O(n²) |
| Two loops one *after* another | O(n) + O(n) = O(n) |
| Halving the range each step (binary search) | O(log n) |
| Sorting | O(n log n) |

```cpp
// O(n): one pass
for (int i = 0; i < n; i++) sum += a[i];

// O(n^2): every pair
for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
        if (a[i] == a[j]) return true;
```

### Will my solution pass? Use the constraints.

A computer does roughly **10⁸ simple operations per second**. Read `n` from the
problem's constraints and pick a complexity that fits:

| Max `n` | Complexity you need |
|---|---|
| ≤ 20 | O(2ⁿ) is okay (backtracking) |
| ≤ 1,000 | O(n²) is okay |
| ≤ 100,000 (10⁵) | O(n log n) or O(n) |
| ≤ 10⁸ | O(n) or O(log n) |

Most LeetCode array problems say `n ≤ 10⁵`, so **O(n²) will usually time out.**
You'll need O(n) or O(n log n).

### Space complexity

This is the extra memory you create. An `unordered_set` holding up to `n` items is **O(n) space**.
A few `int` variables are **O(1) space**. The output array usually doesn't count.

### The trade-off you'll use all week

> **Spend memory to save time.** A hash map uses O(n) extra space and turns an
> O(n²) "search for it again" into an O(1) lookup.

---

## 2. C++ for LeetCode

LeetCode gives you a class. You write only the function:

```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        // your code
    }
};
```

To test locally, add a `main` and compile:

```cpp
#include <bits/stdc++.h>   // includes all of the STL (fine for practice, not for real projects)
using namespace std;

// paste class Solution here

int main() {
    vector<int> nums = {1, 2, 3, 1};
    Solution s;
    cout << boolalpha << s.containsDuplicate(nums) << "\n";  // true
}
```

```bash
g++ -std=c++17 -Wall -o sol sol.cpp && ./sol
```

**Always take containers by reference (`vector<int>& nums`).** Without the `&`,
C++ copies the whole vector, which costs an extra O(n) on every call.

---

## 3. `vector`: the dynamic array

```cpp
vector<int> v;               // empty
vector<int> v(5, 0);         // [0,0,0,0,0]
vector<int> v = {3, 1, 2};

v.push_back(4);              // add to end        O(1) amortized
v.pop_back();                // remove last       O(1)
v[i];                        // access            O(1)
v.size();                    // length            O(1)
v.back();                    // last element      O(1)
v.insert(v.begin() + i, x);  // insert in middle  O(n), so avoid it in loops
sort(v.begin(), v.end());    // ascending         O(n log n)
sort(v.rbegin(), v.rend());  // descending
reverse(v.begin(), v.end()); // O(n)

for (int x : v) cout << x;          // read-only loop (copies each int, fine for ints)
for (int& x : v) x *= 2;            // modify in place
for (auto& row : grid) { ... }      // use auto& for big elements (strings, vectors)

vector<vector<int>> grid(rows, vector<int>(cols, 0));   // 2-D, rows x cols of zeros
```

**Amortized O(1):** `push_back` sometimes has to copy everything into a bigger block, but
that happens so rarely that the average cost per push is still O(1).

### Pitfalls

- `v.size()` is **unsigned**. `v.size() - 1` on an empty vector wraps to a huge number.
  Write `(int)v.size() - 1`, or check `v.empty()` first.
- `v[i]` with a bad `i` doesn't throw an error. It reads garbage memory or crashes.

---

## 4. `string`

```cpp
string s = "hello";
s.size();               // 5
s[0];                   // 'h'
s += "!";               // append
s.substr(1, 3);         // "ell"  (start, LENGTH), and it costs O(length)
sort(s.begin(), s.end());   // "ehllo", sorts the characters
to_string(42);          // "42"
stoi("42");             // 42
```

### Character arithmetic (you'll use this constantly)

Characters are small integers. `'a'` is 97, `'b'` is 98, and so on.

```cpp
char c = 'd';
int idx = c - 'a';      // 3, which maps 'a'..'z' to 0..25
char back = 'a' + 3;    // 'd'

int count[26] = {0};    // frequency of each lowercase letter
for (char c : s) count[c - 'a']++;
```

A fixed `int[26]` is faster and simpler than a hash map when the input is "lowercase English letters".

---

## 5. Hashing: `unordered_set` and `unordered_map`

A **hash table** stores items so you can check "is X here?" in **O(1) on average**.
It works by computing `hash(X)`, which points almost directly at the item's bucket.

### `unordered_set`: "have I seen this before?"

```cpp
unordered_set<int> seen;
seen.insert(5);          // O(1) avg
seen.count(5);           // 1 if present, 0 if not   O(1) avg
seen.erase(5);           // O(1) avg
seen.size();
```

### `unordered_map`: key → value

```cpp
unordered_map<int, int> freq;        // value -> how many times
freq[7]++;                           // if 7 is missing, it's created as 0 first, then becomes 1

unordered_map<string, int> idx;
idx["apple"] = 3;

if (idx.count("apple")) { ... }      // check existence WITHOUT creating it
auto it = idx.find("pear");
if (it != idx.end()) cout << it->second;

for (auto& [key, val] : freq)        // C++17 structured binding
    cout << key << " -> " << val << "\n";
```

> ⚠️ **The #1 hashing bug:** `if (m[x] > 0)` *inserts* `x` with value 0 if it wasn't there.
> To only check, use `m.count(x)` or `m.find(x)`.

### Ordered vs unordered

| | `unordered_map` / `unordered_set` | `map` / `set` |
|---|---|---|
| Built on | Hash table | Balanced tree (red-black) |
| Insert / find | **O(1)** average | O(log n) |
| Keys kept sorted? | No | **Yes** |
| Use when | You only need fast lookup (most of the time) | You need sorted order or smallest/largest key |

The worst case for a hash table is O(n) per operation, when many keys collide. Interviewers
accept "O(1) average", so that's what you say.

### What can be a key?

`int`, `char`, `string`, and `long long` work out of the box.
`vector<int>` or `pair<int,int>` **don't** work as `unordered_map` keys without a custom hash.
The easy workaround is to turn them into a `string` key, or use `map`, which does accept them.

---

## 6. Sorting with a custom order

```cpp
vector<pair<int,int>> v = {{3, 'a'}, {1, 'b'}};
sort(v.begin(), v.end());                      // sorts by .first, then .second

// sort by frequency, highest first
sort(v.begin(), v.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
    return a.second > b.second;                // "should a come before b?"
});
```

The lambda has to return `true` only when `a` must come *strictly before* `b`.
Never use `>=` in it, because that can crash `sort`.

---

## 7. Two more containers you'll need on Thursday

```cpp
pair<int, string> p = {3, "abc"};
p.first; p.second;

// min-heap of pairs (smallest .first on top)
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;
minHeap.push({freq, num});   // O(log k)
minHeap.top();               // O(1)
minHeap.pop();               // O(log k)
```

The heap gets its own week (Week 6). Here it's just one of the ways to solve "Top K".

---

## 8. The Week 1 patterns

Every problem this week is one of these. **Learn to recognize the trigger.**

### Pattern A: "Seen before?" → hash set

**Trigger:** *duplicate*, *appears twice*, *have I visited this?*

```cpp
unordered_set<int> seen;
for (int x : nums) {
    if (seen.count(x)) return true;   // found a repeat
    seen.insert(x);
}
return false;
```
O(n) time, O(n) space. The brute force (compare every pair) is O(n²).
You could also sort first and compare neighbours, which is O(n log n) time and O(1) extra space.

### Pattern B: "Find the partner" → hash map of value → index

**Trigger:** *two numbers that add up to target*, *pair with difference k*

The idea: for each `x`, the partner I need is `target - x`. Have I already seen it?

```cpp
unordered_map<int, int> pos;          // value -> index
for (int i = 0; i < (int)nums.size(); i++) {
    int need = target - nums[i];
    if (pos.count(need)) return {pos[need], i};
    pos[nums[i]] = i;                 // insert AFTER checking, so you don't pair an element with itself
}
```

**Trace** for `nums = [2, 7, 11, 15]`, `target = 9`:

| i | nums[i] | need | pos before | found? |
|---|---|---|---|---|
| 0 | 2 | 7 | {} | no, so store 2→0 |
| 1 | 7 | 2 | {2:0} | **yes, return [0, 1]** |

### Pattern C: Frequency counting

**Trigger:** *anagram*, *same characters*, *most frequent*, *majority*

```cpp
// Valid Anagram: same letters, same counts
if (s.size() != t.size()) return false;
int cnt[26] = {0};
for (char c : s) cnt[c - 'a']++;
for (char c : t) cnt[c - 'a']--;
for (int k = 0; k < 26; k++) if (cnt[k] != 0) return false;
return true;
```

### Pattern D: Group by a canonical key

**Trigger:** *group items that are "the same" in some way*

Turn each item into a **key** that's identical for all members of a group, then use
`unordered_map<key, vector<item>>`.

```cpp
// Group Anagrams: "eat", "tea", "ate" all sort to "aet"
unordered_map<string, vector<string>> groups;
for (string& w : strs) {
    string key = w;
    sort(key.begin(), key.end());     // canonical form
    groups[key].push_back(w);
}
```
Sorting each word costs O(k log k) for a word of length k. A faster key is the
26-letter count turned into a string, like `"1#0#0#...#1"`, which costs O(k).

### Pattern E: Prefix sums

**Trigger:** *sum of a range `[l, r]`*, asked many times

```
nums   =    [ 3,  1,  4,  1,  5 ]
prefix = [0,  3,  4,  8,  9, 14 ]     prefix[i] = sum of the first i elements
```

```cpp
vector<int> prefix(n + 1, 0);
for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + nums[i];

// sum of nums[l..r] inclusive, O(1) per query:
int rangeSum = prefix[r + 1] - prefix[l];
```
Check: the sum of `nums[1..3]` = 1+4+1 = 6, and `prefix[4] - prefix[1]` = 9 − 3 = **6** ✓

**Prefix/suffix *products*** use the same idea (Product of Array Except Self).
`answer[i]` = (product of everything left of i) × (product of everything right of i).
Fill the left products in one pass, then multiply by the right products in a backward pass.
No division needed.

### Pattern F: Bucket sort by count

**Trigger:** *top k most frequent*, where the counts are bounded by `n`

A count can only be between 1 and n, so make `n + 1` buckets where `bucket[c]` holds
all numbers that appear exactly `c` times. Then walk the buckets from `n` down to 1.
That's O(n), which beats sorting (O(n log n)) and a heap (O(n log k)).

### Pattern G: "Start of a sequence" with a set

**Trigger:** *longest consecutive run*, and the problem demands O(n), so you can't sort

Put everything in a set. A number `x` **starts** a run only if `x - 1` is *not* in the set.
Only from starts do you count upward with `x+1, x+2, ...`. Each number is visited a
constant number of times overall, so the whole thing is O(n).

---

## 9. Pattern cheat sheet

| If the problem says… | Think… |
|---|---|
| duplicate / seen before | `unordered_set` |
| pair summing to target | `unordered_map` value → index |
| anagram / same letters | `int cnt[26]` |
| group things that are "equivalent" | map from canonical key → list |
| sum of a subarray / range | prefix sums |
| product except self | prefix × suffix |
| top k frequent | count map + bucket sort (or heap) |
| longest consecutive, O(n) | set + "is x−1 missing?" |
| sorted output order needed | `map` / `set` / `sort` |

---

## 10. Common mistakes to avoid

1. Using `m[x]` to *check* a key. It inserts the key. Use `count` or `find`.
2. Forgetting `&`, which copies big vectors and strings.
3. `int` overflow. Sums of up to 10⁵ numbers that each go up to 10⁹ need `long long`.
4. `v.size() - 1` when `v` is empty (it's unsigned, so it wraps around).
5. In Two Sum, inserting before checking, which pairs an element with itself.
6. Jumping to code before you've done one small example by hand.

---

## 11. Check yourself before Monday's problems

Answer these out loud, without notes:

1. Why is `n ≤ 10⁵` a hint that O(n²) won't pass?
2. What is the difference between `m.count(x)` and `m[x]`?
3. When would you pick `map` over `unordered_map`?
4. In Two Sum, why do we store `nums[i]` *after* checking for its partner?
5. Write the prefix-sum array for `[2, 4, 6]` and use it to find the sum of index 1..2.
6. What's the canonical key for grouping anagrams, and what does it cost?

If any of these feel shaky, re-read that section. Don't move on.
