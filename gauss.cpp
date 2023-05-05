#include <iomanip>
#include <cstdio>
#include <iostream>

using std::cin;
using std::cout;
using std::swap;

#define N 1015

using f64 = double;
using i32 = int;

const char endl = '\n';
constexpr f64 eps = 1e-8;
f64 f[N][N], tmp, ans[N];

#include <cstdlib>

void failed(f64 num) {
    puts("No Solution");
    // cout << std::fixed << eps << ' ' << num;
    exit(0);
}

i32 n;

int main() {
	freopen("example.in", "r", stdin);
	freopen("gauss.out", "w", stdout);
	scanf("%d", &n);
    for (i32 i = 1; i <= n; ++i) {
        for (i32 j = 1; j <= n + 1; ++j) {
            scanf("%lf", &f[i][j]);
            // cout << f[i][j] << ' ' << i << ' ' << j << endl;
        }
    }

    // gauss

    for (i32 i = 1; i <= n; ++i) {  // 枚举的实际上是元，正下方这个循环用于寻找 r
        i32 r = i;
        for (i32 j = i + 1; j <= n; ++j)
            if (abs(f[j][i]) > abs(f[r][i])) r = j;  // 找到第 i 个元的系数最大的一行。
        if (abs(f[r][i]) < eps) failed(f[r][i]);
        if (r != i) swap(f[r], f[i]);
        tmp = f[i][i];
        for (i32 j = i; j <= n + 1; ++j) {
            f[i][j] /= tmp;  // 先通过等式性质把 f[i][i] 化为 1
        }
        for (i32 j = i + 1; j <= n; ++j) {
            tmp = f[j][i];  // f[i][i] 已经是 1 了，不必再除
            for (i32 k = 1; k <= n + 1; ++k) {
                f[j][k] -= f[i][k] * tmp;  // 加减消元
            }
        }
    }

    // 代入消元

    for (i32 i = n; i; --i) {
        ans[i] = f[i][n + 1];
        for (i32 j = i; j; --j) {
            f[j][n + 1] -= ans[i] * f[j][i]; // 直接减就完事了，从下往上减，系数不用了所以不用操作。
        }
    }

    for (int i = 1; i <= n; ++i) {
        printf("%.6lf ", ans[i]);
    }
    
    fclose(stdin);
    fclose(stdout);

    return 0;
}
