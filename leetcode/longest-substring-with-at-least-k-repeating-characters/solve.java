public int longestSubstring(String s, int k) {
    if (k < 2) return s.length();
    return process(s.toCharArray(), k, 0, s.length() - 1);
}

private int process(char[] s, int k, int lo, int hi) {
    if (hi - lo + 1 < k) return 0;

    int[] cnts = new int[26];
    for (int i = lo; i <= hi; ++i) cnts[s[i]-'a']++;

    while (hi - lo + 1 >= k && cnts[s[lo]-'a'] < k) lo++;
    while (hi - lo + 1 >= k && cnts[s[hi]-'a'] < k) hi--;
    if (hi - lo + 1 < k) return 0;

    for (int i = lo; i <= hi; ++i)
        if (cnts[s[i]-'a'] < k) return Math.max(process(s, k, lo, i - 1), process(s, k, i + 1, hi));

    return hi - lo + 1;
}
