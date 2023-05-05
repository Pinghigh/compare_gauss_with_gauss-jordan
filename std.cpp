// coder: Feliks Hacker of IOI == YB an AKer of IMO
// LU分解
// https://blog.csdn.net/yang10560/article/details/77948021
#include <bits/stdc++.h>
#define db double
#define ll long long
using namespace std;
const int N = 1016;
int n;
db a[N][N], b[N];
db l[N][N], u[N][N];
// 递推前两步
inline void init() {
    for (int i = 1; i <= n; i++) {
        l[i][i] = 1;
        u[1][i] = (db)a[1][i];
        // 特判
        if (u[1][1] == 0) {
            puts("No Solution");
            exit(0);
        }
        l[i][1] = (db)a[i][1] / u[1][1];
    }
}  // 行列交错递推
inline void lu_div() {
    init();
    // 递推式
    // U[i][j] = A[i][j] - (for (k = 1 to i-1) L[i][k] * U[k][j])
    // L[j][i] = (A[j][i] - (for (k = 1 to i-1) L[j][k] * U[k][i])) / U[i][i]
    for (int i = 2; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            // 递推U第i行
            u[i][j] = a[i][j];
            for (int k = 1; k <= i - 1; k++)
                u[i][j] -= l[i][k] * u[k][j];
            // 递推L第i列
            l[j][i] = a[j][i];
            for (int k = 1; k <= i - 1; k++)
                l[j][i] -= l[j][k] * u[k][i];
            // 特判
            if (u[i][i] == (db)0) {
                puts("No Solution");
                exit(0);
            }
            l[j][i] /= u[i][i];
        }
    }
}  // 求行列式的值
inline db det() {
    // det(A) = det(L * U) = det(L) * det(U) = det(U)
    db res = 1;
    for (int i = 1; i <= n; i++)
        res *= u[i][i];
    return res;
}  // 解 Z相关的那两个方程
// 直接用代入消元一个个求即可
db z[N];
// L * Z = B
inline void solve_z() {
    for (int i = 1; i <= n; i++) {
        z[i] = b[i];
        for (int j = 1; j < i; j++)
            z[i] -= l[i][j] * z[j];
    }
}
// U * X = Z
db x[N];
inline void solve_x() {
    for (int i = n; i >= 1; i--) {
        x[i] = z[i];
        for (int j = n; j > i; j--)
            x[i] -= u[i][j] * x[j];
        x[i] /= u[i][i];
    }
}
int main() {
    freopen("example.in", "r", stdin);
    freopen("std.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%lf", &a[i][j]);
        }
        scanf("%lf", &b[i]);
    }
    lu_div();
    // 行列式 = 0，方程无唯一解
    if (det() == 0) {
        puts("No Solution");
        return 0;
    }
    solve_z();
    solve_x();
    for (int i = 1; i <= n; i++)
        printf("%.6lf\n", x[i]);
    fclose(stdin);
    fclose(stdout);
    return 0;
}