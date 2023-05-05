#include <iomanip>
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
    freopen("jordan.out", "w", stdout);
    // std::ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);
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
        for (i32 j = 1; j <= n + 1; ++j) {
            f[i][j] /= tmp;  // 先通过等式性质把 f[i][i] 化为 1
        }
        // 这里是高斯约旦消元和高斯消元的区别所在，j 是行数从 1 枚举就能把每一行的第 i 个元消掉
        for (i32 j = 1; j <= n; ++j) {
            if (i != j) {
                tmp = f[j][i];  // f[i][i] 已经是 1 了，不必再除
                for (i32 k = i + 1; k <= n + 1; ++k) {
                    f[j][k] -= f[i][k] * tmp;  // 加减消元
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        printf("%.6lf ", f[i][n + 1]);
    }

    fclose(stdin);
    fclose(stdout);

    return 0;
}
