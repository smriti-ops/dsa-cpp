# Week 2 Theory — Two Pointers & Sliding Window

Read this before solving anything on Nov 10. As in Week 1, type out every code block and run it.
Sections 1–5 are enough for Mon–Wed. Sections 6–10 are for Thu–Sat.

---

## 1. Why two pointers?

Lots of brute-force solutions look like this:

```cpp
for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
        // check the pair (i, j)
```

That's O(n²). With `n ≤ 10⁵`, it times out.

Two pointers works because of a simple fact: **if the array has some order (sorted, or
a symmetric shape like a palindrome), one comparison can rule out many pairs at once.**
Then each pointer only ever moves forward, so together they make at most `n` moves: **O(n)**.

There are three shapes you'll use this week:

| Shape | Pointers start at | They move | Typical problem |
|---|---|---|---|
| **Opposite ends** | `l = 0`, `r = n-1` | toward each other | palindrome, pair sum in sorted array |
| **Read / write** | both at 0 | same direction, different speeds | remove/move elements in place |
| **Sliding window** | both at 0 | same direction, the gap between them is the "window" | longest/shortest substring or subarray |

Week 1 used **extra memory** to save time (hash maps). Two pointers usually saves time with
**O(1) extra memory**, and that's often the follow-up question: *"Can you do it without the hash map?"*

---

## 2. C++ you'll need this week

```cpp
#include <cctype>         // already inside bits/stdc++.h

isalnum(c);               // letter or digit?
isalpha(c);  isdigit(c);
tolower(c);               // 'A' -> 'a', leaves other chars alone
swap(a[i], a[j]);         // O(1)
reverse(s.begin(), s.end());

int cnt[128] = {0};       // count for ANY ASCII char (letters, digits, spaces, symbols)
cnt[c]++;                 // a char is a small int, so it works directly as the index

max(a, b);  min(a, b);    // both arguments must be the same type!
max(best, r - l + 1);     // fine: both int
max(best, (int)s.size()); // size() is unsigned, so cast it
```

### Pitfall: `size_t` and pointer loops

```cpp
// BUG: if s is empty, s.size() - 1 is a huge number, and r is unsigned so r >= 0 is always true
for (size_t l = 0, r = s.size() - 1; l < r; l++, r--) ...

// SAFE: use int everywhere
int l = 0, r = (int)s.size() - 1;
while (l < r) { ... }
```

**Rule for this week:** declare every pointer as `int`, and cast `size()` once at the top:
`int n = nums.size();`

---

## 3. Shape A: opposite ends (converging pointers)

### Template

```cpp
int l = 0, r = n - 1;
while (l < r) {
    if (/* the pair (l, r) is the answer */) return ...;
    if (/* need something bigger */) l++;
    else r--;
}
```

### Example 1: Is a plain string a palindrome?

```cpp
bool isPal(const string& s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}
```
O(n) time, O(1) space. **Valid Palindrome (125)** is this plus two twists:
skip characters that aren't letters/digits, and compare case-insensitively.
Skip with a `while` inside the loop, and keep checking `l < r` in that inner `while` too.

### Example 2: Pair with a given sum in a **sorted** array

The array is sorted. Look at `a[l] + a[r]`:

- **Too small?** `a[l]` paired with the *biggest* remaining value is still too small, so `a[l]`
  can't be in any answer. Throw it away: `l++`.
- **Too big?** `a[r]` paired with the *smallest* remaining value is still too big, so `a[r]` is
  useless. `r--`.
- **Equal?** Found it.

Each step throws away one element for good. That's why it's correct, and why it's O(n).

**Trace** for `a = [1, 3, 4, 6, 9]`, `target = 10`:

| l | r | a[l] + a[r] | action |
|---|---|---|---|
| 0 | 4 | 1 + 9 = 10 | **found** |

Try `target = 7`:

| l | r | a[l] + a[r] | action |
|---|---|---|---|
| 0 | 4 | 1 + 9 = 10 | too big, `r--` |
| 0 | 3 | 1 + 6 = 7 | **found (0, 3)** |

Compare with Week 1 Two Sum: hash map, O(n) time but **O(n) space**. Sorted input lets you
drop to **O(1) space**. (Two Sum II, 167, is exactly this, but its answer is **1-indexed**.)

> Two pointers on pairs **needs sorted input**. If the input isn't sorted and you need indices,
> sorting destroys them, so use the Week 1 hash map instead.

---

## 4. Shape B: read / write pointers (in-place editing)

**Trigger:** *in place*, *O(1) extra memory*, *remove*, *move to the end*, *keep the relative order*.

`r` (read) scans every element. `w` (write) marks where the next **kept** element goes.
Everything before `w` is the finished answer.

```cpp
// Keep only elements that pass some test, in order, in place.
int w = 0;
for (int r = 0; r < n; r++) {
    if (keep(a[r])) {
        a[w] = a[r];     // or swap(a[w], a[r]) if the rest must be preserved
        w++;
    }
}
// a[0..w-1] is the result; w is its length
```

**Trace**: keep only the odd numbers of `[2, 3, 4, 5, 7]`

| r | a[r] | keep? | array after | w |
|---|---|---|---|---|
| 0 | 2 | no | [2,3,4,5,7] | 0 |
| 1 | 3 | yes | [**3**,3,4,5,7] | 1 |
| 2 | 4 | no | [3,3,4,5,7] | 1 |
| 3 | 5 | yes | [3,**5**,4,5,7] | 2 |
| 4 | 7 | yes | [3,5,**7**,5,7] | 3 |

Result: the first 3 elements, `[3, 5, 7]`.

- **Move Zeroes (283):** "keep" = non-zero. Think about whether you need `=` or `swap` so the
  zeros end up at the back.
- **Remove Duplicates from Sorted Array (26):** "keep" = different from the last thing you
  *wrote*. Because the array is sorted, duplicates sit next to each other.

---

## 5. Shape C: fix one, two-pointer the rest (3Sum)

**Trigger:** *triplets* (or quadruplets) that sum to a target, *no duplicate triplets*.

Brute force is O(n³). The plan:

1. **Sort** the array: O(n log n).
2. For each index `i`, fix `a[i]`. Now you need a pair in `a[i+1..n-1]` with sum `-a[i]`.
   That's Section 3, Example 2: O(n).
3. Total: n × O(n) = **O(n²)**. That's the best known for 3Sum, and it passes for `n ≤ 3000`.

### Skipping duplicates (the hard part)

The answer must not contain the same triplet twice. Since the array is sorted, equal values
sit next to each other, so you skip them:

```cpp
for (int i = 0; i < n; i++) {
    if (i > 0 && a[i] == a[i - 1]) continue;   // same first value as last time: skip
    int l = i + 1, r = n - 1;
    while (l < r) {
        int sum = a[i] + a[l] + a[r];
        if (sum < 0) l++;
        else if (sum > 0) r--;
        else {
            // record the triplet, then move BOTH pointers
            // and also skip over repeats of a[l] (one while loop is enough)
        }
    }
}
```

Ask yourself: why `a[i] == a[i - 1]` and **not** `a[i] == a[i + 1]`? Dry-run `[-1, -1, 2]` with both
versions and you'll see the difference.

Small speed-up: if `a[i] > 0`, every number after it is also positive, so you can `break`.

---

## 6. Container With Most Water: a greedy two-pointer

Area between lines `l` and `r` = `min(h[l], h[r]) * (r - l)`.

Start with the widest container (`l = 0`, `r = n-1`). Every move makes the width smaller, so the
only hope of a bigger area is a **taller short side**.

**Which pointer moves?** The shorter one. Here's why: say `h[l] < h[r]`. Any container that uses
`l` with some `r' < r` is **narrower**, and its height is still capped at `h[l]`. So it can't beat the
area you just computed. Line `l` has no better partner left, so throw it away: `l++`.

This "throw away the side that can't possibly do better" argument is the same idea as
Section 3. If you can explain it out loud, you understand two pointers.

---

## 7. Sliding window: the idea

**Trigger words:** *contiguous*, *subarray*, *substring*, *longest / shortest / maximum*,
*at most k*, *window of size k*.

A window is the stretch `[l, r]`. Instead of recomputing everything for each new window, you
**update** a running state: add `a[r]` when the right edge moves, remove `a[l]` when the left
edge moves.

```
a = [ 2, 1, 5, 1, 3, 2 ]
       [-----]              window [0..2], sum 8
          [-----]           drop a[0]=2, add a[3]=1, sum 7   (O(1) update, not O(k))
```

**Why it's O(n):** `r` moves right `n` times total. `l` moves right *at most* `n` times total.
Even though there's a `while` inside the `for`, the total work is ≤ 2n.

> ⚠️ "Nested loop" doesn't automatically mean O(n²). Count how many times each pointer moves
> **over the whole run**, not per iteration.

---

## 8. Fixed-size window

**Trigger:** *every window of size k*, *subarray of length k*.

```cpp
// maximum sum of any k consecutive elements
long long sum = 0, best = LLONG_MIN;
for (int r = 0; r < n; r++) {
    sum += a[r];                    // 1. add the new element
    if (r >= k) sum -= a[r - k];    // 2. drop the one that fell off the left
    if (r >= k - 1)                 // 3. once the window is full, record
        best = max(best, sum);
}
```

`r - k` is the index that just left. The window is `[r-k+1, r]`.

- **Maximum Average Subarray I (643):** exactly this, then divide by `k` at the end.
  Watch for `int / int` doing integer division.
- **Permutation in String (567):** fixed window of size `s1.size()` over `s2`. The "state" is
  a `cnt[26]` of the window instead of a sum. A window is a permutation of `s1` when its counts
  equal `s1`'s counts. Comparing two arrays of 26 is O(26) = O(1), so the total is still O(n).

---

## 9. Variable-size window

**Trigger:** *longest* / *shortest* substring/subarray **such that some condition holds**.

### Template A: longest valid window

```cpp
int l = 0, best = 0;
for (int r = 0; r < n; r++) {
    add(a[r]);                     // grow: include a[r]
    while (/* window [l, r] is INVALID */) {
        remove(a[l]);              // shrink from the left until valid again
        l++;
    }
    best = max(best, r - l + 1);   // window is valid here: record it
}
```

### Template B: shortest valid window

```cpp
int l = 0, best = INT_MAX;
for (int r = 0; r < n; r++) {
    add(a[r]);
    while (/* window [l, r] is VALID */) {
        best = min(best, r - l + 1);   // record BEFORE shrinking
        remove(a[l]);
        l++;
    }
}
return best == INT_MAX ? 0 : best;
```

Notice the only difference: **longest** shrinks while *invalid* and records after;
**shortest** shrinks while *valid* and records inside.

### Worked example: longest window with sum ≤ S (all numbers ≥ 0)

`a = [3, 1, 2, 1, 4]`, `S = 5`, using Template A (state = running `sum`):

| r | add | sum | invalid (sum > 5)? → shrink | l | window | best |
|---|---|---|---|---|---|---|
| 0 | 3 | 3 | no | 0 | [3] | 1 |
| 1 | 1 | 4 | no | 0 | [3,1] | 2 |
| 2 | 2 | 6 | yes: drop 3 → sum 3 | 1 | [1,2] | 2 |
| 3 | 1 | 4 | no | 1 | [1,2,1] | **3** |
| 4 | 4 | 8 | yes: drop 1 → 7, drop 2 → 5 | 3 | [1,4] | 3 |

Answer: **3**.

### What can the "state" be?

| Condition on the window | State to keep |
|---|---|
| sum ≤ S / sum ≥ S | `long long sum` |
| no repeated characters | `cnt[128]` (or `unordered_map<char,int>`) + check the char you just added |
| at most k distinct | `unordered_map<char,int>` and its `.size()` (erase keys whose count hits 0) |
| same letters as a pattern | `cnt[26]` compared to the pattern's `cnt[26]` |

### Longest Substring Without Repeating Characters (3)

State = `cnt[128]`. After adding `s[r]`, the window is invalid exactly when `cnt[s[r]] > 1`
(only the character you just added can be the repeat). Shrink until it's 1 again.

### Longest Repeating Character Replacement (424): the clever condition

You may change up to `k` characters. In a window, the cheapest plan is to keep the most common
letter and change everything else. So:

```
chars to change = window length − (count of the most frequent letter in the window)
window is valid  ⇔  (r − l + 1) − maxFreq ≤ k
```

Keep `cnt[26]` and `maxFreq`. **Surprising trick:** when you shrink, you don't need to lower
`maxFreq`. A stale (too-big) `maxFreq` never produces a wrong *longer* answer, because the answer
only grows when a real, bigger `maxFreq` appears. Try to convince yourself of this after you
solve it the straightforward way (recompute max over 26 counts, which is still O(26·n)).

### Best Time to Buy and Sell Stock (121): a window in disguise

`l` = the day you buy (the cheapest day so far), `r` = the day you sell. If `prices[r] < prices[l]`,
you've found a cheaper buy day, so jump `l = r`. Otherwise record `prices[r] - prices[l]`.
It's the same as tracking "minimum price seen so far". One pass, O(1) space.

---

## 10. When sliding window does NOT work

Sliding window relies on this: **growing the window only pushes it one way** (e.g. the sum only
goes up). With **negative numbers**, adding an element can make the sum *smaller*, so "shrink
while sum > S" is no longer correct.

| Situation | Use instead |
|---|---|
| subarray sum = k, **negatives allowed** | Week 1 prefix sums + hash map of prefix counts (LeetCode 560) |
| not contiguous (subsequence, any subset) | not a window problem at all (often DP, Week 8) |
| array unsorted, need pair sum + indices | Week 1 hash map |

---

## 11. Pattern cheat sheet

| If the problem says… | Think… |
|---|---|
| palindrome, reverse, compare from both ends | opposite-ends pointers |
| **sorted** array, pair with sum/difference | opposite ends: too small → `l++`, too big → `r--` |
| triplets / 3Sum | sort + fix `i` + two pointers, skip duplicates |
| in place, O(1) memory, remove/move elements | read/write pointers |
| maximize area/width between two choices | opposite ends, move the **worse** side |
| every window of size k | fixed window: add `a[r]`, drop `a[r-k]` |
| longest substring/subarray with a condition | variable window, shrink while **invalid** |
| shortest subarray reaching a target | variable window, shrink while **valid** |
| "is some permutation of p inside s?" | fixed window + `cnt[26]` compare |
| subarray sum with **negatives** | prefix sum + hash map (Week 1), not a window |

---

## 12. Common mistakes to avoid

1. Using `size_t` pointers, so `r--` below 0 wraps around. Use `int`.
2. Inner `while` loops that skip characters but forget the `l < r` check, so they run off the end.
3. 3Sum: skipping duplicates with `a[i] == a[i+1]` instead of `a[i] == a[i-1]` (loses valid triplets).
4. 3Sum: after finding a triplet, moving only one pointer (infinite loop).
5. Window length off by one: it's `r - l + 1`, not `r - l`.
6. Shortest-window problems: recording the answer *after* shrinking instead of *before*.
7. Forgetting to remove `a[l]` from the state before `l++`.
8. `int` division in averages (`sum / k` with both `int`), and `int` overflow in sums.
9. Using a sliding window when the array has negative numbers.

---

## 13. Check yourself before Monday's problems

Answer these out loud, without notes:

1. Why does opposite-ends two pointers need a **sorted** array for pair-sum problems?
2. In "sorted pair sum", the sum is too small. Why is it safe to throw away `a[l]` forever?
3. A loop has a `while` inside a `for`. Why can sliding window still be O(n)?
4. Write the length of the window `[l, r]`.
5. What's the difference between the "longest" and "shortest" window templates?
6. In Container With Most Water, why move the **shorter** line?
7. Why doesn't sliding window work for "subarray sum = k" when there are negative numbers?
8. In 3Sum, what's the total time complexity, and where does each factor come from?

If any of these feel shaky, re-read that section. Don't move on.
