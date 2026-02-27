# Tic-tac-toe_plus_AI
:::align{center}

![](https://cdn.luogu.com.cn/upload/image_hosting/06wqmv0v.png)

:::

如果你在不允许玩此小游戏的时候玩，后果自负。

## 项目概述

这是一个智能**升级版**井字棋软件，你可以和 AI 对弈或者双人对弈，甚至可以看 AI 自己和自己对弈。

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
- 核心 AI 使用 [Minimax](https://oi-wiki.org/search/alpha-beta/) 对抗搜索实现，并加上状态压缩的记忆化数组。

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

## 友情链接

[项目可执行文件](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/0j81vmxc)

[项目源代码](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/8jag0cd8)（编译 zhiyi.dev 即可得到可执行文件）

[项目文档](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/l0cj5uho)
