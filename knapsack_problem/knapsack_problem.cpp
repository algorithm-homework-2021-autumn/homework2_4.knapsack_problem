// knapsack_problem.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>

const int data_num = 2;
const int maxn = 1000;
struct goods {
    int value;
    int weight;
};
struct dp {
    int value;
    bool exist;
};
void get_Goods(goods** a, int* num, int* limit) {
    std::ifstream Data;
    Data.open("knapsack_data.txt");
    for (int i = 0; i < data_num; ++i) {
        Data >> limit[i];
        for (int j = 1; ; ++j) {
            Data >> a[i][j].weight;
            if (a[i][j].weight < 0) {
                num[i] = j - 1; break;
            }
        }
        for (int j = 1; j <= num[i]; ++j)Data >> a[i][j].value;
    }
    Data.close();
    return;
}
void knapsack(goods* a, int num, int limit) {
    dp** f = new dp*[num+2];
    for (int i = 0; i < num+2; ++i) f[i] = new dp[limit + 2];
    int mx = 0, id = 0;
    for (int j = 0; j <= limit; ++j)f[0][j].value = 0;
    for (int i = 1; i <= num; ++i) {
        int w = a[i].weight, v = a[i].value;
        for (int j = 0; j <= limit; ++j) {
            if (j<w || f[i - 1][j].value>f[i - 1][j - w].value + v) {
                f[i][j].value = f[i - 1][j].value;
                f[i][j].exist = 0;
            }
            else {
                f[i][j].value = f[i - 1][j - w].value + v;
                f[i][j].exist = 1;
            }
        }
    }
    std::cout << "背包内可装的最大价值为" << f[num][limit].value << std::endl;
    std::cout << "放入背包的物品序号及数据如下" << std::endl;
    int now_lim = limit;
    for (int i = num; i > 0; --i) {
        if (!f[i][now_lim].exist)continue;
        now_lim -= a[i].weight;
        std::cout << "序号为" << i << ' ';
        std::cout << "重量为" << a[i].weight << ' ';
        std::cout << "价值" << a[i].value << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < num; ++i) delete[]f[i];
    delete[]f;
}
int main(){
    std::cout << "Hello World!\n";
    goods** a = new goods*[data_num];
    for (int i = 0; i < data_num; ++i)a[i] = new goods[maxn];
    int* num = new int[data_num];
    int* limit = new int[data_num];
    
    get_Goods(a, num, limit);

    for (int i = 0; i < data_num; ++i) {
        std::cout << "对第" << i+1 << "组数据进行背包问题求解" << std::endl;
        knapsack(a[i], num[i], limit[i]);
    }

    for (int i = 0; i < data_num; ++i)delete[]a[i];
    delete[]a;
    delete[]num;
    delete[]limit;
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
