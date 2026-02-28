# Tic-tac-toe_plus_AI


![](https://cdn.luogu.com.cn/upload/image_hosting/06wqmv0v.png)


**如果你在不允许玩此小游戏的时候玩，后果自负。**

## 项目概述

这是一个智能**升级版**井字棋软件，你可以和 AI 对弈或者双人对弈，甚至可以看 AI 自己和自己对弈。

**提示：该项目只能在 Windows 下运行。**

## 适用对象

- 在**空闲时分**希望稍稍娱乐，又没有同伴一起玩。
- 想和同伴一起玩这个游戏，却因其规则不易用纸笔模拟而不便。
- 想开发一个棋类简易 AI，又找不到示例。

## 游戏规则

### 基本规则（普通井字棋）：
1. 两个玩家轮流在 $3\times 3$ 棋盘上下子
2. 先连成一条长度为 $3$ 直线（横、竖、斜）的玩家获胜
### 特殊规则（井字棋Plus新增）：

1. 第 $6$ 子落下后 → 消第 $1$ 子
2. 第 $7$ 子落下后 → 消第 $2$ 子
3. 第 $8$ 子落下后 → 消第 $3$ 子
4. 以此类推，循环消失

## 代码揭秘

- 游戏界面使用 Windows 控制台函数编写，轻量而无需外来库。
- 核心 AI 使用 Minimax 对抗搜索实现，并加上状态压缩的记忆化数组。

## 界面展示

这里展示了几个运行时的界面，完整运行方法详见文末的项目文档。

![](https://cdn.luogu.com.cn/upload/image_hosting/1tqnawim.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/ewda5k4u.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/6v6f3jzw.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/n0s5xraj.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/3ocwfi0u.png)

## 分工

@[RickyZhu](https://www.luogu.com.cn/user/2003521) 编写了主界面程序。

@[wolf224322](https://www.luogu.com.cn/user/1826908) 编写了底层 AI 算法。

DeepSeek、豆包、千问等多个 AI 大模型在项目制作过程中为我们提供了算法、调试、Logo 等多方面的帮助。

## 源代码编译方法

先下载**代码包**文件夹。

解压后在 **run.cpp 所在的文件夹**中新建一个 build.cpp，内容如下。

```cpp
#include<cstdlib>
int main(){
    system("\"g++.exe\" ./run.cpp ./dfs.cpp -o ./zhiyi.exe -std=c++14 -O2 -static -Wl,--stack=67108864");
    return 0;
}
```
再将代码中的 `g++.exe` 替换成你自己电脑上 g++ 的位置（**不含表示位置的引号，因为已经在程序中出现了，但特殊字符需转义**，相对位置和绝对位置皆可），编译运行，即可得到可以玩的 zhiyi.exe。

项目文档中介绍了此游戏的具体操作方法。

如果你想直接运行，请下载**智弈升级版井字棋**文件夹，解压后就是可以玩的 zhiyi.exe。

## 参考文章

在项目制作过程中，我们参考了以下文章，感谢它们的作者：

- [Alpha-Beta 剪枝 - OI Wiki](https://oi-wiki.org/search/alpha-beta/)
- [完全信息对抗性博弈算法从入门到初识 - 洛谷专栏](https://www.luogu.com.cn/article/6xz49rys)
