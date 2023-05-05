#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

using namespace std;

#define MAXNUM 100000
#define MAXN 1005

ifstream gauss_ans, jordan_ans, std_ans;
ofstream fout;

random_device seed;
mt19937 eng(seed());
uniform_real_distribution<double> rd(-MAXN, MAXN);

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

i64 t, n;
string gauss, jordan, stda, compiler, args;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cout << "Please input your C++ compiler (default: g++)" << endl;
    cin >> compiler;
    if (compiler.size() < 2) compiler = "g++";
    cout << "Please input your compile arguments (default: -O2 -march=native -mtune=native)" << endl;
    cin >> args;
    if (args.size() < 2) args = "-O2 -march=native -mtune=native";

    auto beforeTime = chrono::steady_clock::now();
    auto afterTime = chrono::steady_clock::now();

    system(format("{} gauss.cpp -o gauss.exe {}", compiler, args).c_str());
    system(format("{} jordan.cpp -o jordan.exe {}", compiler, args).c_str());
    system(format("{} std.cpp -o std.exe {}", compiler, args).c_str());
    for (t = 1;; ++t) {
        cout << "# TEST " << t << endl;
        n = eng() % MAXN + 1;
        fout.open("example.in", ios::out);
        fout << n << endl;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n + 1; ++j) {
                fout << rd(eng) << ' ';
            }
            fout << endl;
        }
        fout.close();

        beforeTime = chrono::steady_clock::now();
        system("gauss.exe");
        afterTime = chrono::steady_clock::now();
        cout << "高斯消元：" << chrono::duration<double>(afterTime - beforeTime).count() << "s ";

        beforeTime = chrono::steady_clock::now();
        system("jordan.exe");
        afterTime = chrono::steady_clock::now();
        cout << "约旦消元：" << chrono::duration<double>(afterTime - beforeTime).count() << "s" << endl;

        beforeTime = chrono::steady_clock::now();
        system("std.exe");
        afterTime = chrono::steady_clock::now();
        cout << "std：" << chrono::duration<double>(afterTime - beforeTime).count() << "s " << endl;

        gauss_ans.open("gauss.out", ios::in);
        jordan_ans.open("jordan.out", ios::in);
        std_ans.open("std.out", ios::in);
        gauss_ans >> gauss;
        jordan_ans >> jordan;
        std_ans >> stda;
        gauss_ans.close();
        jordan_ans.close();
        std_ans.close();
        if (gauss == jordan && gauss == stda) {
            cout << "same answer, ";
            if (gauss == "no solution")
                cout << "No Solution" << endl;
            else
                cout << "soluted" << endl;
        } else {
            if (gauss != stda) cout << "高斯消元错误 ";
            if (jordan != stda) cout << "约旦消元错误 ";
            if (gauss == jordan) cout << "高斯约旦相同 ";
            return 1;
        }
        cout << endl;
    }

    return 0;
}