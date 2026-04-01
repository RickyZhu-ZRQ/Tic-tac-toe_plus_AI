![](https://cdn.luogu.com.cn/upload/image_hosting/06wqmv0v.png)

[前情提要](https://www.luogu.com.cn/article/k3wx8ohb)

[洛谷对应专栏](https://www.luogu.com.cn/article/miq58bj8)

**如果你在不允许玩此小游戏的时候玩，后果自负。**

## 项目概述

这是一个智能**升级版**井字棋软件，你可以和 AI 对弈或者双人对弈，甚至可以看 AI 自己和自己对弈。对于更多项目的细节，你可以在文初的“前情提要”了解。

**提示：该项目只能在 Windows 下运行。**

## 更新内容

在原版本的基础上，我们对项目做了以下修改：

- 增加游戏的“难度选择”功能，将和“参数配置”在一起，机制类似，共有“简单”“中等”“困难”“王者”四个难度（AI 强度）
- 加快 AI 在后期的运行速度
- 优化界面，增加一些清屏
- 对 GitHub 仓库进行完善

## 活动：你们的 AI 有问题

如果你在“**人机对弈（AI 先手）**”模式下、难度选择为“**王者**”的情况下使 AI 没有在第 13 步及以内获胜（这里一步指的是玩家**或** AI 下子一次，即 2 步为一回合），你将获得两个关注，仅限前 3 名。

如果你在“**人机对弈（AI 先手）**”或“**人机对弈（你先手）**”模式下、难度选择为“**王者**”的情况下在第 12 步及以内获胜（这里一步指的是玩家**或** AI 下子一次，即 2 步为一回合），你将获得两个关注，仅限前 3 名。

对于奖励的领取，请[**洛谷**](https://www.luogu.com.cn)**私信**@[wolf224322](https://www.luogu.com.cn/user/1826908) 或 @[RickyZhu](https://www.luogu.com.cn/user/2003521) 并在私信开头加上“【井字棋奖励领取】”。为了避免虚假情况，我们可能会询问你的下棋步骤。

**提示：不一定存在拿到奖励的操作步骤。**

## 相关链接

[项目文档](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/3vlg44rr)

[可执行文件](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/jmvqf0ei)

[项目源代码](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/y6d0kqz3)

[更新公告板](https://www.luogu.com.cn/problem/U665191)（这里可以第一时间获得程序的新版本与活动）

## 常见问题

- 可执行文件显示不安全怎么办？
  
请忽略系统的提示，我们保证项目是安全的。

- 源代码显示乱码怎么办？

请将源代码**文件**拖入游览器中，复制文本粘贴回编辑器。（实测笔者 Windows 11 电脑的 Edge 游览器可以）

- 如何运行三个文件？

解压并处理（可能的）编码问题后在 **run.cpp 所在的文件夹**中新建一个 build.cpp，内容如下。

```cpp
#include<cstdlib>
int main(){
	system("\"g++.exe\" ./run.cpp ./dfs.cpp -o ./zhiyi.exe -std=c++14 -O2 -static -Wl,--stack=67108864");
	return 0;
}
```
再将代码中的 `g++.exe` 替换成你自己电脑上 g++ 的位置（**不含表示位置的引号，因为已经在程序中出现了，但特殊字符需转义**，相对位置和绝对位置皆可），编译运行，即可得到可以玩的 zhiyi.exe。

- 为什么要使用题目作为公告板？

我们发现如果使用剪贴板或公开文章作为公告板，需要至[洛谷保存站](https://luogu.me)访问，对于限制网络的同学不太方便。于是我们模仿部分比赛的公告栏，使用题目作为公告板。

- 如何提出建议？

请[**洛谷**](https://www.luogu.com.cn)**私信**@[wolf224322](https://www.luogu.com.cn/user/1826908) 或 @[RickyZhu](https://www.luogu.com.cn/user/2003521) 并在私信开头加上“【井字棋建议反馈】”。同时，你也可以通过在此项目下加 Issue 来提出建议。

## 致谢

感谢 @[RickyZhu](https://www.luogu.com.cn/user/2003521) 编写大部分项目代码。

感谢 @[lijingshu_304775](https://www.luogu.com.cn/user/1019968)、@[jsntzth666](https://www.luogu.com.cn/user/1294443)、@[chenyongxi3](https://www.luogu.com.cn/user/1047464)、@[ChasonWang](https://www.luogu.com.cn/user/1251100) 为我们原版项目提出建议，使我们的项目越来越好。

感谢 DeepSeek、百度 AI、千问等 AI 模型为我们的项目做出一些帮助。

## 参考文章

在项目制作过程中，我们参考了以下文章，感谢它们的作者：

- [Alpha-Beta 剪枝 - OI Wiki](https://oi-wiki.org/search/alpha-beta/)
- [完全信息对抗性博弈算法从入门到初识 - 洛谷专栏](https://www.luogu.com.cn/article/6xz49rys)
