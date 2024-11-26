static auto _ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);
struct Solution {
    static vector<int> z_function(const vector<char>& buf)
        __attribute__((target("arch=native"))) __attribute__((hot))
        __attribute__((optimize("Ofast"))) __attribute__((nothrow))
        __attribute__((pure)) __attribute__((no_stack_protector))
        __attribute__((no_split_stack)) __attribute__((flatten))
        __attribute__((const))
        __attribute__((no_sanitize("address", "undefined", "thread")))
        __attribute__((no_instrument_function))
        __attribute__((no_profile_instrument_function)) {
        int n = buf.size();
        vector<int> z(n);
        int l = 0, r = 0;
        for (int i = 1; i < n; ++i) {
            int& zi = z[i];
            if (i < r) {
                zi = min(r - i, z[i - l]);
            }
            while (i + zi < n && buf[zi] == buf[i + zi]) {
                ++zi;
            }
            int ipzi = i + zi;
            if (ipzi > r) {
                l = i;
                r = ipzi;
            }
        }
        return z;
    }
    static int minStartingIndex(const string& s, const string& pattern)
        __attribute__((target("arch=native"))) __attribute__((hot))
        __attribute__((optimize("Ofast"))) __attribute__((nothrow))
        __attribute__((pure)) __attribute__((no_stack_protector))
        __attribute__((no_split_stack)) __attribute__((flatten))
        __attribute__((const))
        __attribute__((no_sanitize("address", "undefined", "thread")))
        __attribute__((no_instrument_function))
        __attribute__((no_profile_instrument_function)) {
        int n = s.length(), m = pattern.length();
        vector<char> z_buffer(n + m);
        memcpy(&z_buffer[0], pattern.data(), m);
        memcpy(&z_buffer[m], s.data(), n);
        auto forward_z = z_function(z_buffer);
        memcpy(&z_buffer[0], s.data(), n);
        memcpy(&z_buffer[n], pattern.data(), m);
        reverse(z_buffer.begin(), z_buffer.end());
        auto backward_z = z_function(z_buffer);
        for (int i = m; i <= n; ++i) {
            if (forward_z[i] + backward_z[n + m - i] >= m - 1)
                return i - m;
        }
        return -1;
    }
};