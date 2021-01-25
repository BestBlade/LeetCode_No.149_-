/* ------------------------------------------------------------------|
给定一个二维平面，平面上有 n 个点，求最多有多少个点在同一条直线上。

示例 1:

输入: [[1,1],[2,2],[3,3]]
输出: 3
解释:
^
|
|        o
|     o
|  o  
+------------->
0  1  2  3  4
示例 2:

输入: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
输出: 4
解释:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/max-points-on-a-line
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*	双指针法
*
*	执行用时：8 ms, 在所有 C++ 提交中击败了100.00%的用户
*	内存消耗：11.2 MB, 在所有 C++ 提交中击败了57.51%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

int maxPoints(vector<vector<int>>& points) {
    if (points.size() < 3) {
        return points.size();
    }

    int res = 0;
    for (int i = 0; i < points.size(); i++) {
        unordered_map<long double, int> map;
        int dup = 0;
        int one_round_res = 0;
        for (int j = i + 1; j < points.size(); j++) {
            //加引用会更节省内存空间
            const vector<int> &p = points[i];
            const vector<int> &q = points[j];
            //如果pq是同一个点
            if (p[1] == q[1] && p[0] == q[0]) {
                //计数+1
                dup++;
            }
            //如果此处斜率为正无穷
            else if (p[0] == q[0]) {
                //没有记录过的话
                if (map.find(FLT_MAX) == map.end()) {
                    //创建记录，2个点起步
                    map[FLT_MAX] += 2;
                }
                //记录过就在原先的记录上+1
                else {
                    map[FLT_MAX]++;
                }
                one_round_res = max(one_round_res, map[FLT_MAX]);
            }
            else {
                //计算斜率
                int dy = p[1] - q[1];
                int dx = p[0] - q[0];
                //此处不能把dx扩住，不然会按照int截断
                //static_cast强制限定结果范围
                long double k = static_cast<long double> (dy) / dx;

                if (map.find(k) == map.end()) {
                    map[k] += 2;
                }
                else {
                    map[k]++;
                }
                one_round_res = max(one_round_res, map[k]);
            }
        }
        //如果此轮没有产生结果，说明全是重复的点
        if (!one_round_res) {
            res = max(res, dup + 1);
        }
        //否则就把结果和重复得点相加得到结果
        else {
            res = max(res, one_round_res + dup);
        }
    }
    return res;
}

int main() {
    vector<vector<int>> points = { {1,1},{1,1},{0,0},{3,4},{4,5},{5,6},{7,8},{8,9} };
    maxPoints(points);
}