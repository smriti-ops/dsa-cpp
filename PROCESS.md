# DSA Process: 8 weeks, 1.5 h/day, C++

**Goal by Dec 28, 2026:** about 90 problems (Easy/Medium) in C++, organized by pattern. You should be able to
solve an unseen Medium in 30–40 min and explain its time and space complexity out loud.

---

## 1. The roadmap

| Week | Dates | Pattern | Theory notes |
|---|---|---|---|
| 1 | Nov 3–9 | Big-O + STL + **Arrays & Hashing** | `notes/01_bigO_stl_arrays_hashing.md` |
| 2 | Nov 10–16 | **Two Pointers + Sliding Window** | `notes/02_two_pointers_sliding_window.md` |
| 3 | Nov 17–23 | **Stack + Binary Search** | `notes/03_stack_binary_search.md` |
| 4 | Nov 24–30 | **Linked List** + recursion basics | `notes/04_...` |
| 5 | Dec 1–7 | **Trees** (DFS, BFS, BST) | `notes/05_...` |
| 6 | Dec 8–14 | **Heap + Backtracking** | `notes/06_...` |
| 7 | Dec 15–21 | **Graphs** (grid BFS/DFS, topological sort) | `notes/07_...` |
| 8 | Dec 22–28 | **1-D DP** + mock interviews | `notes/08_...` |

Each week starts with its theory note. Read it **on the weekend before** (or in Monday's first 30 min).

---

## 2. The daily 90 minutes (Mon–Sat)

| Time | Step | What exactly |
|---|---|---|
| 0–10 min | **Warm-up re-solve** | Re-code yesterday's hardest problem from a **blank file**, no peeking |
| 10–70 min | **2 new problems** | Use the 7-step method below for each (about 30 min each) |
| 70–90 min | **Log + commit** | Fill in your pattern log, add the solution file, `git commit` |

On Monday, swap the warm-up for 30 min of theory. Monday's two problems are Easy, so that fits.

## 3. Sunday: review day (no new problems)

1. Pick **5 problems** from the week, including at least 2 you struggled with.
2. Solve each with a **20-min timer**, on a blank file.
3. Explain each one out loud as if to an interviewer: approach → complexity → edge cases.
4. If a problem took more than 20 min, it goes on next Sunday's list too.
5. Read the next week's theory note.

---

## 4. The 7-step method for every problem

Do these in order, every time, including the easy problems. The habit is what you're training.

1. **Read & restate.** Say the problem in one sentence of your own.
2. **Constraints → target complexity.** Look at `n`. If `n ≤ 10⁵`, you need O(n) or O(n log n).
3. **Examples by hand.** Work 1 normal example + 1 edge case (empty, one element, all the same, negatives).
4. **Brute force first.** Say it and its complexity, even if you won't code it.
5. **Find the pattern.** Ask "Which pattern from my cheat sheet fits?" and then optimize.
6. **Code it**, then **dry-run** your code on the small example *before* you hit Submit.
7. **State the final time and space complexity.**

### The 25-minute stuck rule

- **0–25 min:** work on your own. Being stuck is where the learning happens, so stay with it.
- **At 25 min:** ask me for a **hint** (see section 6). Don't look at the solution.
- **After 2 hints and still stuck:** read the **idea** of the solution (NeetCode explanation),
  close it, and **write the code yourself.**
- Any problem where you needed the solution gets **★ marked** and re-solved within 3 days.

> ❌ Never watch a solution video while copying the code. Watch, close it, then type it from memory.

---

## 5. Folder structure & file template

```
dsa/
├── PROCESS.md                     ← this file
├── pattern_log.md                 ← one line per problem (create it on Nov 3)
├── notes/
│   └── 01_bigO_stl_arrays_hashing.md
└── solutions/
    ├── 01_arrays_hashing/
    │   ├── 0217_contains_duplicate.cpp
    │   └── 0001_two_sum.cpp
    ├── 02_two_pointers_sliding_window/
    └── ...
```

File name: `<4-digit LeetCode number>_<snake_case_name>.cpp`

Put this at the top of every solution file:

```cpp
// LeetCode 1. Two Sum (Easy)
// Pattern: hash map, value -> index ("find the partner")
// Idea: for each x, check whether target - x was already seen.
// Time: O(n)   Space: O(n)
// Status: solved alone in 18 min | needed hint | ★ needed solution
```

### Pattern log format (`pattern_log.md`)

```
| Date | # | Problem | Pattern | Key trick | Time/Space | Status |
|------|---|---------|---------|-----------|------------|--------|
| Nov 3 | 217 | Contains Duplicate | hash set | insert after check | O(n)/O(n) | ✅ 10 min |
```

### Commit after every session

```bash
git add dsa && git commit -m "DSA: Two Sum, Valid Anagram"
```

At the end of Week 8 the `dsa/` folder moves into its own public **`dsa-cpp`** repo on
GitHub (smriti-ops) with a README that links the pattern notes.

---

## 6. How to work with Claude

| You send | I'll do |
|---|---|
| "Hint 1 for <problem>" | A nudge toward the pattern only, no code |
| "Hint 2 for <problem>" | The key idea and data structure, no code |
| Your C++ code + "review" | Find bugs, check complexity, suggest cleaner STL, and point out missed edge cases |
| "Explain <concept>" | Step-by-step trace on a tiny example |
| "Mock interview" (Week 8) | I play the interviewer: give a problem, ask follow-ups, then give feedback |

I won't hand you full solutions unless you explicitly ask *after* 2 hints.

---

## 7. Weekly checkpoints

Every Sunday, answer these honestly:

- [ ] Did I finish this week's problem list? (Target: 12)
- [ ] Can I re-solve the 5 review problems in ≤ 20 min each?
- [ ] Can I name the pattern for each problem from its title alone?
- [ ] Is everything committed?

**If you fall behind:** don't skip the review Sunday, and don't push the plan back.
Drop the **last 2–3 problems** of that week (they're marked *optional* in each list) and move on.
Finishing the patterns matters more than the problem count.

---

## 8. Week 1 problem list: Nov 3–9 (Arrays & Hashing)

Read `notes/01_bigO_stl_arrays_hashing.md` first.

| Day | Date | Problems | Difficulty | Pattern |
|---|---|---|---|---|
| Mon | Nov 3 | 30 min theory (sections 1–4) + **1929** Concatenation of Array, **217** Contains Duplicate | Easy, Easy | vector basics, hash set |
| Tue | Nov 4 | **242** Valid Anagram, **1** Two Sum | Easy, Easy | frequency count, hash map partner |
| Wed | Nov 5 | **1480** Running Sum of 1d Array, **303** Range Sum Query – Immutable, **169** Majority Element | Easy ×3 | prefix sums, counting |
| Thu | Nov 6 | **49** Group Anagrams, **347** Top K Frequent Elements | Medium, Medium | canonical key, bucket sort |
| Fri | Nov 7 | **238** Product of Array Except Self, **271** Encode and Decode Strings *(optional)* | Medium, Medium | prefix × suffix, string design |
| Sat | Nov 8 | **36** Valid Sudoku, **128** Longest Consecutive Sequence *(optional)* | Medium, Medium | hash sets per row/col/box, set + sequence start |
| Sun | Nov 9 | **Review:** re-solve 1, 242, 49, 347, 238 on a 20-min timer + read Week 2 theory | — | — |

**Total: 12 problems** (5 Easy warm-ups + 7 NeetCode 150 core).

Notes:
- **271 is LeetCode Premium.** Solve it free on the NeetCode website (neetcode.io → Arrays & Hashing)
  or as LintCode 659.
- For **169**, first do the hash map count. Then look up Boyer–Moore voting as a bonus (O(1) space).
- For **347**, do it with sorting first, then rewrite with bucket sort. Compare the complexities.
- For **128**, the problem *demands* O(n), so sorting isn't allowed. Use Pattern G from the notes.

---

## 9. Week 2 problem list: Nov 10–16 (Two Pointers + Sliding Window)

Read `notes/02_two_pointers_sliding_window.md` first. Sections 1–5 before Monday, 6–10 before Thursday.
Solutions go in `02_two_pointers_sliding_window/` (same layout as `01_bigO_stl_arrays_hashing/`).

| Day | Date | Problems | Difficulty | Pattern | Notes section |
|---|---|---|---|---|---|
| Mon | Nov 10 | 30 min theory (sections 1–4) + **344** Reverse String, **125** Valid Palindrome | Easy, Easy | opposite ends | 3 |
| Tue | Nov 11 | **283** Move Zeroes, **26** Remove Duplicates from Sorted Array | Easy, Easy | read/write pointers | 4 |
| Wed | Nov 12 | **167** Two Sum II – Input Array Is Sorted, **15** 3Sum | Medium, Medium | sorted pair sum, fix one + two pointers | 3, 5 |
| Thu | Nov 13 | **11** Container With Most Water, **121** Best Time to Buy and Sell Stock | Medium, Easy | greedy two pointers, min-so-far window | 6, 9 |
| Fri | Nov 14 | **643** Maximum Average Subarray I, **3** Longest Substring Without Repeating Characters | Easy, Medium | fixed window, variable window | 8, 9 |
| Sat | Nov 15 | **424** Longest Repeating Character Replacement, **567** Permutation in String *(optional)* | Medium, Medium | window + `len − maxFreq ≤ k`, fixed window + `cnt[26]` | 9, 8 |
| Sun | Nov 16 | **Review:** re-solve 167, 15, 11, 3, 424 on a 20-min timer + read Week 3 theory | — | — | — |

**Total: 12 problems** (6 Easy + 6 Medium; 7 of them are NeetCode 150).

Notes:
- **Mon:** for 125, solve it once with an extra cleaned-up string (O(n) space), then redo it with
  two pointers that skip in place (O(1) space).
- **Wed:** do 167 *before* 15. 3Sum is just 167 inside a loop plus duplicate skipping.
  Write the triplets for `[-1, 0, 1, 2, -1, -4]` by hand before coding.
- **Thu:** for 11, write down *why* moving the shorter line is safe in your file's header comment.
- **Fri:** for 3, draw the window on paper for `"abcabcbb"` and `"pwwkew"` first.
- **Sat:** for 424, first recompute the max over all 26 counts each step. Only then try keeping a
  stale `maxFreq`.
- **Bonus (only if the week went well, not counted):** 209 Minimum Size Subarray Sum (Medium,
  shortest-window template), 42 Trapping Rain Water (Hard, two pointers).

---

## 10. Week 3 problem list: Nov 17–23 (Stack + Binary Search)

Read `notes/03_stack_binary_search.md` first. Sections 1–6 (Stack) before Monday, 7–11 (Binary Search) before Thursday.
Solutions go in `03_stack_binary_search/` (same layout as the first two weeks).

| Day | Date | Problems | Difficulty | Pattern | Notes section |
|---|---|---|---|---|---|
| Mon | Nov 17 | 30 min theory (sections 1–4) + **20** Valid Parentheses, **682** Baseball Game | Easy, Easy | matching stack, simulation stack | 3, 4 |
| Tue | Nov 18 | **1047** Remove All Adjacent Duplicates In String, **155** Min Stack | Easy, Medium | cancel the top, `{val, minSoFar}` | 4, 5 |
| Wed | Nov 19 | **150** Evaluate Reverse Polish Notation, **739** Daily Temperatures | Medium, Medium | operand stack, monotonic stack | 4, 6 |
| Thu | Nov 20 | **704** Binary Search, **35** Search Insert Position | Easy, Easy | Template 1, return `lo` | 8, 9 |
| Fri | Nov 21 | **74** Search a 2D Matrix, **875** Koko Eating Bananas | Medium, Medium | 1-D index → (row, col), binary search on the answer | 11, 10 |
| Sat | Nov 22 | **153** Find Minimum in Rotated Sorted Array, **496** Next Greater Element I *(optional)* | Medium, Easy | compare `a[mid]` with `a[hi]`, monotonic stack + hash map | 11, 6 |
| Sun | Nov 23 | **Review:** re-solve 155, 150, 739, 875, 153 on a 20-min timer + read Week 4 theory | — | — | — |

**Total: 12 problems** (6 Easy + 6 Medium; 8 of them are NeetCode 150).

Notes:
- **Mon:** for 20, write the three failing test cases (`")("`, `"(]"`, `"(("`) *before* coding and check each one.
- **Tue:** for 1047, use a `string` as the stack so you can return it directly. For 155, first write the
  O(n) `getMin` that scans, then fix it with the pair trick.
- **Wed:** for 150, test `["4","13","5","/","+"]` (answer 6) to catch operand-order bugs. For 739,
  fill in the trace table from Section 6 on paper before coding.
- **Thu:** solve 704 and 35 with the **same** loop; the only change is the final `return`.
  Then check your 35 answer against `lower_bound`.
- **Fri:** for 875, write `ok(k)` as its own function and test it on `k = 3` and `k = 4` first.
- **Sat:** for 153, write out the `F/T` row for `[4,5,6,7,0,1,2]` in your header comment.
- **Week 2 leftover:** 424 is still an empty stub. Finish it in a warm-up slot this week if it wasn't solved elsewhere.
- **Bonus (only if the week went well, not counted):** 33 Search in Rotated Sorted Array (Medium),
  853 Car Fleet (Medium, stack), 84 Largest Rectangle in Histogram (Hard, monotonic stack).
